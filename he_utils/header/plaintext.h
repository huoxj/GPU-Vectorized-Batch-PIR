#pragma once

#include <seal/seal.h>
#include <troy/troy.h>
#include "utils.h"

class Plaintext {
public:
    static std::unique_ptr<Plaintext> create();
    virtual std::unique_ptr<Plaintext> clone() const = 0;
};

class PlaintextSeal : public Plaintext {
public:
    PlaintextSeal();
    std::unique_ptr<Plaintext> clone() const override;
    seal::Plaintext & get_raw();
private:
    std::unique_ptr<seal::Plaintext> plain;
};

class PlaintextTroy : public Plaintext {
public:
    PlaintextTroy();
    std::unique_ptr<Plaintext> clone() const override;
    troy::Plaintext & get_raw();
private:
    std::unique_ptr<troy::Plaintext> plain;
};
