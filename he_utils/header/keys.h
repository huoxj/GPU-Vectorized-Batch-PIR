#pragma once

#include <seal/seal.h>
#include <troy/troy.h>
#include "keygen.h"

class PublicKeys {
};

class PublicKeysSeal : public PublicKeys {
public:
    PublicKeysSeal(std::unique_ptr<KeyGenSeal> &);
    seal::GaloisKeys & getGaloisKeys();
    seal::RelinKeys & getRelinKeys();
private:
    seal::GaloisKeys galois_keys;
    seal::RelinKeys relin_keys;
};

class PublicKeysTroy : public PublicKeys {
public:
    PublicKeysTroy(std::unique_ptr<KeyGenTroy> &);
    troy::GaloisKeys & getGaloisKeys();
    troy::RelinKeys & getRelinKeys();
private:
    troy::GaloisKeys galois_keys;
    troy::RelinKeys relin_keys;
};

class SecretKeys {
};

class SecretKeysSeal : public SecretKeys {
public:
    SecretKeysSeal(std::unique_ptr<KeyGenSeal> &);
    seal::SecretKey & getSecretKey();
private:
    seal::SecretKey secret_key;
};

class SecretKeysTroy : public SecretKeys {
public:
    SecretKeysTroy(std::unique_ptr<KeyGenTroy> &);
    troy::SecretKey & getSecretKey();
private:
    troy::SecretKey secret_key;
};
