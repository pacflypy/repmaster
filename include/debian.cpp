#include "debian.hpp"
#include "exception.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <gpgme.h>

void RepoManager::Control::read(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw PathNotFoundError("Failed to open file");
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            if (!value.empty() && value[0] == ' ') {
                value.erase(0, 1);
            }
            data[key] = value;
        } 
    }
    file.close();
}

bool RepoManager::Control::validate() const {
    const std::vector<std::string> requiredKeys = {"Package", "Version", "Section", "Priority", "Architecture", "Maintainer", "Description"};
    const std::vector<std::string> optionalKeys = {"Depends", "Recommends", "Suggests", "Conflicts", "Breaks", "Provides", "Replaces", "Installed-Size", "MD5sum", "SHA256", "Files"};

    for (const auto& key : requiredKeys) {
        if (data.find(key) == data.end()) {
            throw ControlFileError("Required Key Not Found: " + key);
        }
    }
    return true;
}

std::string RepoManager::Control::get(const std::string& key) const {
    auto it = data.find(key);
    if (it == data.end()) {
        throw ControlFileError("Key Not Found: " + key);
    }
    return it->second;
}

RepoManager::Release::Release(const std::string& path) : filepath(path) {}

void RepoManager::Release::NewRelease()
{
    std::ofstream file(filepath, std::ios::trunc);
    if (!file.is_open()) {
        throw PathNotFoundError("Failed to Open File: " + filepath);
    }
    file.close();
    data.clear();
}

void RepoManager::Release::append(const std::string& key, const std::string& value)
{
    data[key] = value;
}

void RepoManager::Release::remove(const std::string& key)
{
    auto it = data.find(key);
    if (it != data.end()) {
        data.erase(it);
    } else {
        throw ReleaseFileError("Key Not Found: " + key);
    }
}

void RepoManager::Release::save()
{
    std::ofstream file(filepath);
    if (!file.is_open()) {
        throw PathNotFoundError("Failed to Open File: " + filepath);
    }
    for (const auto& pair : data) {
        file << pair.first << ": " << pair.second << "\n";
    }
    file.close();
}

void RepoManager::Release::sign(const std::string& privateKeyPath) {
    gpgme_ctx_t ctx = NULL;
    gpgme_error_t err;
    gpgme_key_t key = NULL;
    gpgme_data_t in = NULL, out = NULL;

    gpgme_check_version(NULL);
    gpgme_set_locale(NULL, LC_CTYPE, setlocale(LC_CTYPE, NULL));

    err = gpgme_new(&ctx);
    if (gpgme_err_code(err) != GPG_ERR_NO_ERROR) {
        throw std::runtime_error("Failed to create gpgme context: " + std::string(gpgme_strerror(err)));
    }

    gpgme_set_protocol(ctx, GPGME_PROTOCOL_OpenPGP);

    err = gpgme_get_key(ctx, privateKeyPath.c_str(), &key, 1);
    if (gpgme_err_code(err) != GPG_ERR_NO_ERROR) {
        gpgme_release(ctx);
        throw std::runtime_error("Failed to load private key: " + std::string(gpgme_strerror(err)));
    }

    // Öffne die Release-Datei zum Lesen
    std::ifstream file(filepath);
    if (!file.is_open()) {
        gpgme_release(ctx);
        throw PathNotFoundError("Failed to open file: " + filepath);
    }

    // Lese den Inhalt der Datei in einen std::string
    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Erstelle ein gpgme_data_t Objekt aus dem Dateiinhalt
    err = gpgme_data_new_from_mem(&in, fileContents.c_str(), fileContents.length(), 0);
    if (gpgme_err_code(err) != GPG_ERR_NO_ERROR) {
        gpgme_key_release(key);
        gpgme_release(ctx);
        throw std::runtime_error("Failed to create data buffer from file contents: " + std::string(gpgme_strerror(err)));
    }

    err = gpgme_data_new(&out);
    if (gpgme_err_code(err) != GPG_ERR_NO_ERROR) {
        gpgme_data_release(in);
        gpgme_key_release(key);
        gpgme_release(ctx);
        throw std::runtime_error("Failed to create data buffer for output: " + std::string(gpgme_strerror(err)));
    }

    err = gpgme_op_sign(ctx, in, out, GPGME_SIG_MODE_DETACH);
    if (gpgme_err_code(err) != GPG_ERR_NO_ERROR) {
        gpgme_data_release(in);
        gpgme_data_release(out);
        gpgme_key_release(key);
        gpgme_release(ctx);
        throw std::runtime_error("Failed to sign data: " + std::string(gpgme_strerror(err)));
    }

    // Schreibe die Signatur in eine Datei
    std::ofstream sigFile(filepath + ".sig", std::ios::binary);
    if (!sigFile.is_open()) {
        gpgme_data_release(in);
        gpgme_data_release(out);
        gpgme_key_release(key);
        gpgme_release(ctx);
        throw PathNotFoundError("Failed to open signature file: " + filepath + ".sig");
    }

    char buffer[1024];
    ssize_t read_bytes;
    while ((read_bytes = gpgme_data_read(out, buffer, sizeof(buffer))) > 0) {
        sigFile.write(buffer, read_bytes);
    }

    sigFile.close();
    gpgme_data_release(in);
    gpgme_data_release(out);
    gpgme_key_release(key);
    gpgme_release(ctx);
}