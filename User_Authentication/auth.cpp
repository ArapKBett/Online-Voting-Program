#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <openssl/sha.h>

std::map<std::string, std::string> users; // username -> hashed password

std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.length(), hash);
    std::string hashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashedPassword += sprintf("%02x", hash[i]);
    }
    return hashedPassword;
}

void loadUsers() {
    std::ifstream file("users.txt");
    std::string username, password;
    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
}

bool authenticateUser(const std::string& username, const std::string& password) {
    return users.find(username) != users.end() && users[username] == hashPassword(password);
}

void registerUser(const std::string& username, const std::string& password) {
    users[username] = hashPassword(password);
    std::ofstream file("users.txt", std::ios::app);
    file << username << " " << users[username] << std::endl;
    file.close();
}
