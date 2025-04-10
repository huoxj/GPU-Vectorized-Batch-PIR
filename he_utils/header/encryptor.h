#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "hecontext.h"
#include "plaintext.h"
#include "ciphertext.h"
#include "keys.h"

class Encryptor {
public:
    static std::unique_ptr<Encryptor> create(HeContext &, SecretKeys &);
    virtual void encrypt_symmetric(Plaintext &, Ciphertext &) = 0;
};

class EncryptorSeal : public Encryptor {
public:
    EncryptorSeal(HeContextSeal &, SecretKeysSeal &);
    void encrypt_symmetric(Plaintext &, Ciphertext &) override;
private:
    std::unique_ptr<seal::Encryptor> encryptor;
};

class EncryptorTroy : public Encryptor {
public:
    EncryptorTroy(HeContextTroy &, SecretKeysTroy &);
    void encrypt_symmetric(Plaintext &, Ciphertext &) override;
private:
    std::unique_ptr<troy::Encryptor> encryptor;
};
