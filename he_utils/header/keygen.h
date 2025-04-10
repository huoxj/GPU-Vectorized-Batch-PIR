#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "hecontext.h"

class KeyGen {
public:
    static std::unique_ptr<KeyGen> create(HeContext &context);
    virtual ~KeyGen() = 0;
};

class KeyGenSeal : public KeyGen {
public:
    KeyGenSeal(HeContextSeal &);
    seal::KeyGenerator & get_raw();
private:
    std::unique_ptr<seal::KeyGenerator> keygen;
};

class KeyGenTroy : public KeyGen {
public:
    KeyGenTroy(HeContextTroy &);
    troy::KeyGenerator & get_raw();
private:
    std::unique_ptr<troy::KeyGenerator> keygen;
};

