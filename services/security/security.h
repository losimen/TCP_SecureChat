#pragma once

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/sha.h>

#include <QtGlobal>
#include <QString>
#include <QFile>
#include <QDebug>
#include <string>
#include <random>

#define CRYPTO_RSA_KEY_LEN_2048 2048
#define CRYPTO_RSA_KEY_EXP      65535


class Security
{
public:
    Security() = delete;
    Security(const QString &filename);

    std::string encryptPublicMSG(const std::string &toEncrypt);
    std::string encryptPrivateMSG(const std::string &toEncrypt);

    std::string decryptPrivateMSG(const std::string &toDecrpyt);
    std::string decryptPublicMSG(const std::string &toDecrpyt);

    const QString getPubKey();
    const QString getPrivKey();

    bool writePubKey();
    bool writePrivKey();

    void generateKeyPair();

    static std::string SHA256generatorRandom();
    static std::string SHA256generator(const std::string &input_);

private:
    QString _filename;

    const QString _readFile(const QString &filename);
    static const std::string _getRandomString();

    RSA *_getPubKey();
    RSA *_getPrivKey();
};
