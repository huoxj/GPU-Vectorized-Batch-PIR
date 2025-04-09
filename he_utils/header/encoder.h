#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "hecontext.h"

class Encoder {
public:
    virtual void to_device() = 0;
};

class EncoderSeal : public Encoder {
public:
    EncoderSeal(std::unique_ptr<HeContextSeal> &);
    std::unique_ptr<seal::BatchEncoder> & get_raw();
    void to_device() override;
private:
    std::unique_ptr<seal::BatchEncoder> encoder;
};

class EncoderTroy : public Encoder {
    EncoderTroy(std::unique_ptr<HeContextTroy> &);
    std::unique_ptr<troy::BatchEncoder> & get_raw();
    void to_device() override;
private:
    std::unique_ptr<troy::BatchEncoder> encoder;
};
