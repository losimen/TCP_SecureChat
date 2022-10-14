#include "security.h"


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


std::string Security::SHA256generatorRandom()
{
    auto* input = reinterpret_cast<unsigned char*>(const_cast<char*>(Security::_getRandomString().c_str()));
    unsigned char md[SHA256_DIGEST_LENGTH];

    std::string result ("none");
    SHA256_CTX context;

    if(!SHA256_Init(&context))
        return result;

    if(!SHA256_Update(&context, (unsigned char*)input, strlen((char*)input)))
        return result;

    if(!SHA256_Final(md, &context))
        return result;

    result.clear();
    for (unsigned char i : md) {
        char buffer [4];
        snprintf ( buffer, 4, "%02x", i );

        result += buffer;
    }

    return result;
}

std::string Security::SHA256generator(const std::string &input_)
{
    auto* input = reinterpret_cast<unsigned char*>(const_cast<char*>(input_.c_str()));
    unsigned char md[SHA256_DIGEST_LENGTH];

    std::string result ("none");
    SHA256_CTX context;

    if(!SHA256_Init(&context))
        return result;

    if(!SHA256_Update(&context, (unsigned char*)input, strlen((char*)input)))
        return result;

    if(!SHA256_Final(md, &context))
        return result;

    result.clear();
    for (unsigned char i : md) {
        char buffer [4];
        snprintf ( buffer, 4, "%02x", i );

        result += buffer;
    }

    return result;
}


const std::string Security::_getRandomString()
{
    const int length = 1000;
    std::string result;
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/][';.,=+-_)(*&^%$#@!~`";

    // get random number C++11
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, int(chars.length()) - 1);

    for (int i = 0; i < length; i++) {
        result += chars[dis(gen)];
    }

    return result;
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
