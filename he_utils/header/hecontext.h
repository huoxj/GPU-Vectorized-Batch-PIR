#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "encryption_params.h"

class HeContext {
public:
    virtual void to_device() = 0;
};

class HeContextSeal: public HeContext {
public:
    HeContextSeal(std::unique_ptr<EncryptionParametersSeal> &);
    std::shared_ptr<seal::SEALContext> & get_raw();
    void to_device() override;
private:
    std::shared_ptr<seal::SEALContext> context;
};

class HeContextTroy: public HeContext {
public:
    HeContextTroy(std::unique_ptr<EncryptionParametersTroy> &);
    std::shared_ptr<troy::HeContext> get_raw();
    void to_device() override;
private:
    std::shared_ptr<troy::HeContext> context;
};

