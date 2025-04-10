#pragma once

#include <seal/seal.h>
#include <troy/troy.h>
#include "utils.h"

class CiphertextSeal;
class CiphertextTroy;

class Ciphertext {
public:
    static std::unique_ptr<Ciphertext> create();
    virtual ~Ciphertext() = default;
};

class CiphertextSeal: public Ciphertext {
public:
    seal::Ciphertext & get_raw();
private:
    std::unique_ptr<seal::Ciphertext> cipher;
};

class CiphertextTroy: public Ciphertext {
public:
    troy::Ciphertext & get_raw();
private:
    std::unique_ptr<troy::Ciphertext> cipher;
};
