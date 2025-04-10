#pragma once

#include <seal/seal.h>
#include <troy/troy.h>

class Plaintext {
public:
    virtual ~Plaintext() = default;
};

class PlaintextSeal : public Plaintext {
public:
    seal::Plaintext & get_raw();
private:
    std::unique_ptr<seal::Plaintext> plain;
};

class PlaintextTroy : public Plaintext {
public:
    troy::Plaintext & get_raw();
private:
    std::unique_ptr<troy::Plaintext> plain;
};
