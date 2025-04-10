#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "encryption_params.h"

class HeContext {
public:
    static std::unique_ptr<HeContext> create(EncryptionParameters &);
    virtual void to_device() = 0;
};

class HeContextSeal: public HeContext {
public:
    HeContextSeal(EncryptionParametersSeal &);
    seal::SEALContext & get_raw();
    void to_device() override;
private:
    std::shared_ptr<seal::SEALContext> context;
};

class HeContextTroy: public HeContext {
public:
    HeContextTroy(EncryptionParametersTroy &);
    std::shared_ptr<troy::HeContext> & get_raw();
    void to_device() override;
private:
    std::shared_ptr<troy::HeContext> context;
};

