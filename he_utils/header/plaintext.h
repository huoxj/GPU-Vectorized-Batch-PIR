#pragma once

#include <seal/seal.h>
#include <troy/troy.h>
#include "utils.h"

class Plaintext {
public:
    static std::unique_ptr<Plaintext> create();
    virtual ~Plaintext() = default;
};

class PlaintextSeal : public Plaintext {
public:
    PlaintextSeal();
    seal::Plaintext & get_raw();
private:
    std::unique_ptr<seal::Plaintext> plain;
};

class PlaintextTroy : public Plaintext {
public:
    PlaintextTroy();
    troy::Plaintext & get_raw();
private:
    std::unique_ptr<troy::Plaintext> plain;
};
