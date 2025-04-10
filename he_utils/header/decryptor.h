#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "hecontext.h"
#include "ciphertext.h"
#include "plaintext.h"
#include "keys.h"

class Decryptor {
public:
    static std::unique_ptr<Decryptor> create(HeContext &context, SecretKeys &secret_key);
    virtual void decrypt(Ciphertext &, Plaintext &) = 0;
};

class DecryptorSeal : public Decryptor {
public:
    DecryptorSeal(HeContextSeal &context, SecretKeysSeal &secret_key);
    void decrypt(Ciphertext &cipher, Plaintext &plain) override;
private:
    std::unique_ptr<seal::Decryptor> decryptor;
};

class DecryptorTroy : public Decryptor {
public:
    DecryptorTroy(HeContextTroy &context, SecretKeysTroy &secret_key);
    void decrypt(Ciphertext &cipher, Plaintext &plain) override;
private:
    std::unique_ptr<troy::Decryptor> decryptor;
};
