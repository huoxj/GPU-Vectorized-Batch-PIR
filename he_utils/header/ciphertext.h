#pragma once

#include <seal/seal.h>
#include <troy/troy.h>
#include "utils.h"

class Ciphertext {
public:
    static std::unique_ptr<Ciphertext> create();
    virtual std::unique_ptr<Ciphertext> clone() const = 0;
};

class CiphertextSeal: public Ciphertext {
public:
    CiphertextSeal();
    std::unique_ptr<Ciphertext> clone() const override;
    seal::Ciphertext & get_raw();
private:
    std::unique_ptr<seal::Ciphertext> cipher;
};

class CiphertextTroy: public Ciphertext {
public:
    CiphertextTroy();
    std::unique_ptr<Ciphertext> clone() const override;
    troy::Ciphertext & get_raw();
private:
    std::unique_ptr<troy::Ciphertext> cipher;
};
