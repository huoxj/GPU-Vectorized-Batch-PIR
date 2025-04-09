#pragma once

#include "seal/seal.h"
#include "troy/troy.h"

class EncryptionParameters {
public:
    virtual void setParameters(
        size_t poly_modulus_degree,
        size_t plain_modulus_degree
    ) = 0;
};

class EncryptionParametersSeal: public EncryptionParameters {
public:
    EncryptionParametersSeal();
    void setParameters(size_t, size_t) override;
    std::unique_ptr<seal::EncryptionParameters> & get_raw();
private:
    std::unique_ptr<seal::EncryptionParameters> ep;
};

class EncryptionParametersTroy: public EncryptionParameters {
public:
    EncryptionParametersTroy();
    void setParameters(size_t, size_t) override;
    std::unique_ptr<troy::EncryptionParameters> & get_raw();
private:
    std::unique_ptr<troy::EncryptionParameters> ep;
};
