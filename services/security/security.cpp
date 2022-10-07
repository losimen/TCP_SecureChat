#include "security.h"
#include <string>

Security::Security(const QString &filename)
{
    this->_filename = filename;
}


std::string Security::encryptPublicMSG(const std::string &toEncrypt)
{
    std::string encryptResult;

    unsigned char *encryptMsg_, *plainMsg;
    RSA *publicKey = _getPubKey();
    int encryptMsgLen;

    int key_size = RSA_size(publicKey);

    encryptMsg_ = (unsigned char *)malloc(key_size);
    plainMsg = reinterpret_cast<unsigned char*>(const_cast<char*>(toEncrypt.c_str()));

    OpenSSL_add_all_algorithms();
    encryptMsgLen = RSA_public_encrypt(int(toEncrypt.size()), plainMsg, encryptMsg_, publicKey, RSA_PKCS1_PADDING);

    encryptResult = std::string((reinterpret_cast<char*>(encryptMsg_)), encryptMsgLen);

    RSA_free(publicKey);

    return encryptResult;
}


std::string Security::encryptPrivateMSG(const std::string &toEncrypt)
{
    std::string encryptResult;

    unsigned char *encryptMsg_, *plainMsg;
    RSA *privateKey = _getPrivKey();
    int encryptMsgLen;

    int key_size = RSA_size(privateKey);

    encryptMsg_ = (unsigned char *)malloc(key_size);
    plainMsg = reinterpret_cast<unsigned char*>(const_cast<char*>(toEncrypt.c_str()));

    OpenSSL_add_all_algorithms();
    encryptMsgLen = RSA_private_encrypt(int(toEncrypt.size()), plainMsg, encryptMsg_, privateKey, RSA_PKCS1_PADDING);

    encryptResult = std::string((reinterpret_cast<char*>(encryptMsg_)), encryptMsgLen);

    RSA_free(privateKey);

    return encryptResult;
}


std::string Security::decryptPrivateMSG(const std::string &toDecrpyt)
{
    std::string decryptionResult;

    unsigned char *decryptMsg, *encodeMsg;
    RSA *privateKey = _getPrivKey();
    int key_size = RSA_size(privateKey);

    decryptMsg = (unsigned char *)malloc(key_size);
    encodeMsg = reinterpret_cast<unsigned char*>(const_cast<char*>(toDecrpyt.c_str()));

    auto lenOfMsg = RSA_private_decrypt(int(toDecrpyt.size()), encodeMsg, decryptMsg, privateKey, RSA_PKCS1_PADDING);
    decryptionResult = std::string((reinterpret_cast<char*>(decryptMsg)), lenOfMsg);

    RSA_free(privateKey);

    return decryptionResult;
}


std::string Security::decryptPublicMSG(const std::string &toDecrpyt)
{
    std::string decryptionResult;

    unsigned char *decryptMsg, *encodeMsg;
    RSA *publicKey = _getPubKey();
    int key_size = RSA_size(publicKey);

    decryptMsg = (unsigned char *)malloc(key_size);
    encodeMsg = reinterpret_cast<unsigned char*>(const_cast<char*>(toDecrpyt.c_str()));

    auto lenOfMsg = RSA_public_decrypt(int(toDecrpyt.size()), encodeMsg, decryptMsg, publicKey, RSA_PKCS1_PADDING);
    decryptionResult = std::string((reinterpret_cast<char*>(decryptMsg)), lenOfMsg);

    RSA_free(publicKey);

    return decryptionResult;
}


const QString Security::getPubKey()
{
    QString res;
    QFile f(_filename + "_public.txt");

    if (!f.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error in reading public key";
        return res;
    }
    QTextStream in(&f);

    res = f.readAll();

    return res;
}


const QString Security::getPrivKey()
{
    QString res;
    QFile f(_filename + "_private.txt");

    if (!f.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error in reading public key";
        return res;
    }
    QTextStream in(&f);

    res = f.readAll();

    return res;
}


void Security::generateKeyPair()
{
    FILE *fp;
    RSA *pRSA = RSA_generate_key(CRYPTO_RSA_KEY_LEN_2048, CRYPTO_RSA_KEY_EXP, nullptr, nullptr);

    if (RSA_check_key(pRSA) != 1){
      // THROW error
      qDebug() << "error generating";
      return;
    }

    fp = fopen(QString(_filename + "_public.txt").toStdString().c_str(), "w");
    if (fp == nullptr)
    {
        qDebug() << "error in opening file";
        return;
    }

    if (PEM_write_RSAPublicKey(fp, pRSA) == 0)
    {
        // THROW error
        qDebug() << "error writing RSA public";
        return;
    }
    fclose(fp);

    fp = fopen(QString(_filename + "_private.txt").toStdString().c_str(), "w");
    if (fp == nullptr)
    {
        qDebug() << "error in opening file";
        return;
    }

    if (PEM_write_RSAPrivateKey(fp, pRSA, nullptr, nullptr, 0, nullptr, nullptr) == 0)
    {
        qDebug() << "error writing RSA private";
        return;
    }

    RSA_free(pRSA);
    fclose(fp);
}


RSA *Security::_getPubKey()
{
    RSA *pRSA;
    FILE *pubKey_file;

    pubKey_file = fopen(QString(_filename + "_public.txt").toStdString().c_str(), "rb");
    pRSA = PEM_read_RSAPublicKey(pubKey_file, nullptr, nullptr, nullptr);

    fclose(pubKey_file);

    return pRSA;
}


RSA *Security::_getPrivKey()
{
     RSA *pRSA;
     FILE *privKey_file;

     OpenSSL_add_all_algorithms();
     privKey_file = fopen(QString(_filename + "_private.txt").toStdString().c_str(), "rb");
     pRSA = PEM_read_RSAPrivateKey(privKey_file, nullptr, nullptr, nullptr);

     fclose(privKey_file);

     return pRSA;
}
