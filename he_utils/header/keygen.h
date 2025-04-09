#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "hecontext.h"

class KeyGen {
};

class KeyGenSeal : public KeyGen {
public:
    KeyGenSeal(std::unique_ptr<HeContextSeal> &);
    std::unique_ptr<seal::KeyGenerator> & get_raw();
private:
    std::unique_ptr<seal::KeyGenerator> keygen;
};

class KeyGenTroy : public KeyGen {
public:
    KeyGenTroy(std::unique_ptr<HeContextTroy> &);
    std::unique_ptr<troy::KeyGenerator> & get_raw();
private:
    std::unique_ptr<troy::KeyGenerator> keygen;
};

