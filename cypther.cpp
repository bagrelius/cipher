#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

void CreateNewEncryptedFile(std::string filename, std::string key, std::string iv);
void CreateNewDecryptedFile(std::string filename, std::string key, std::string iv, std::string extension);

std::vector<char> readFile(const std::string& filename);
bool createFile(const std::string& filename, const std::string& content);
std::string encrypt(const std::string& data, const std::string& key, const std::string& iv);
std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv);
std::string getRawFilename(std::string fullName);
std::string trim(const std::string& str);



int main(int argc, char* argv[]) {
    std::string key = "0123456789ABCDEF"; // Default key
    std::string iv = "FEDCBA9876543210"; // Default IV
    std::string filename;
    std::string extension;
    bool decrypt = false;

    int opt;
    while ((opt = getopt(argc, argv, "k:i:f:d:")) != -1) {
        switch (opt) {
            case 'k': // Key
                key = optarg;
                break;
            case 'i': // Initialization vector
                iv = optarg;
                break;
            case 'f': // Filename
                filename = optarg;
                filename = trim(filename); // Trim whitespace
                break;
            case 'd': //Decrypt extension
                decrypt = true;
                extension = optarg;
                extension = trim(extension); // Trim whitespace
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -f <filename> [-k <key>] [-i <iv>] [-d <decrypt extension>]" << std::endl;
                return 1;
        }
    }

    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH || iv.size() != CryptoPP::AES::BLOCKSIZE) {
        std::cerr << "Error: Key must be 16 bytes and IV must be 16 bytes." << std::endl;
        return 1;
    }

    if (filename.empty()) {
        std::cerr << "Error: Filename is required. Use -f <filename>." << std::endl;
        return 1;
    }

    if (!decrypt) {
        try {
            CreateNewEncryptedFile(filename, key, iv);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else {
        // Decrypting process
        try {
            CreateNewDecryptedFile(filename, key, iv, extension);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}

//Function that for encrypting process
void CreateNewEncryptedFile(std::string filename, std::string key, std::string iv) {
    std::vector<char> fileContent;

    try {
        fileContent = readFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Error reading file");
    }

    // Encrypt the file
    std::string encryptedData = encrypt(std::string(fileContent.begin(), fileContent.end()), key, iv);

    // Write the encrypted lines to a new file
    std::string encryptedFileName = getRawFilename(filename) + ".enc";
    
    createFile(encryptedFileName, encryptedData);
}

//Function that for decrypting process
void CreateNewDecryptedFile(std::string filename, std::string key, std::string iv, std::string extension = ".txt") {
    std::vector<char> fileContent;

    try {
        fileContent = readFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Error reading file");
    }

    // Decrypt the file
    std::string decryptedData = decrypt(std::string(fileContent.begin(), fileContent.end()), key, iv);

    // Write the decrypted lines to a new file
    std::string decryptedFileName = getRawFilename(filename) + extension;
    
    createFile(decryptedFileName, decryptedData);
}

std::vector<char> readFile(const std::string& filename) {

    // Open the file - seek end immediately to get the size
    std::ifstream originalFile(filename, std::ios::binary | std::ios::ate);
    if (!originalFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
        return {};
    }

    // Read the file  into memory
    std::streamsize size = originalFile.tellg();
    originalFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);

    if(originalFile.read(buffer.data(), size)) {
        return buffer;
    } else {
        std::cerr << "Error reading file: " << filename << std::endl;
        throw std::runtime_error("Error reading file");
    }  
}

bool createFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error creating encrypted file: " << filename << std::endl;
        return false;
    }
    file.write(content.c_str(), content.size());
    file.close();

    return true;
}


std::string encrypt(const std::string& data, const std::string& key, const std::string& iv) {

    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH || iv.size() != CryptoPP::AES::BLOCKSIZE) {
        throw std::invalid_argument("Key and IV sizes are incorrect.");
    }        

    std::string ciphertext;
    CryptoPP::AES::Encryption aesEncryption((const unsigned char *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (const unsigned char *)iv.c_str());
    CryptoPP::StreamTransformationFilter stf(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stf.Put(reinterpret_cast<const unsigned char *>(data.c_str()), data.length());
    stf.MessageEnd();

    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv) {

    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH || iv.size() != CryptoPP::AES::BLOCKSIZE) {
        throw std::invalid_argument("Key and IV sizes are incorrect.");
    }
    std::string decryptedtext;
    CryptoPP::AES::Decryption aesDecryption((const unsigned char*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (const unsigned char*)iv.c_str());
    CryptoPP::StreamTransformationFilter stf(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stf.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.length());
    stf.MessageEnd();
    return decryptedtext;
}

std::string getRawFilename(std::string fullName) {
    std::string rawName = fullName.substr(0, fullName.find_last_of("."));    
    return rawName;
}

std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char ch) {
        return std::isspace(ch);
    });

    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) {
        return std::isspace(ch);
    }).base();

    return (start < end ? std::string(start, end) : std::string());
}
