#pragma once

#include <seal/seal.h>
#include <troy/troy.h>
#include "utils.h"
#include "keygen.h"

class PublicKeys {
public:
    static std::unique_ptr<PublicKeys> create(KeyGen &);
    virtual ~PublicKeys() = default;
};

class PublicKeysSeal : public PublicKeys {
public:
    PublicKeysSeal(KeyGenSeal &);
    seal::GaloisKeys & getGaloisKeys();
    seal::RelinKeys & getRelinKeys();
private:
    seal::GaloisKeys galois_keys;
    seal::RelinKeys relin_keys;
};

class PublicKeysTroy : public PublicKeys {
public:
    PublicKeysTroy(KeyGenTroy &);
    troy::GaloisKeys & getGaloisKeys();
    troy::RelinKeys & getRelinKeys();
private:
    troy::GaloisKeys galois_keys;
    troy::RelinKeys relin_keys;
};

class SecretKeys {
public:
    static std::unique_ptr<SecretKeys> create(KeyGen &);
    virtual ~SecretKeys() = default;
};

class SecretKeysSeal : public SecretKeys {
public:
    SecretKeysSeal(KeyGenSeal &);
    seal::SecretKey & getSecretKey();
private:
    seal::SecretKey secret_key;
};

class SecretKeysTroy : public SecretKeys {
public:
    SecretKeysTroy(KeyGenTroy &);
    troy::SecretKey & getSecretKey();
private:
    troy::SecretKey secret_key;
};
