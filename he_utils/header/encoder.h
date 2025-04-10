#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "hecontext.h"
#include "plaintext.h"

class EncoderSeal;
class EncoderTroy;

class Encoder {
public:
    static std::unique_ptr<Encoder> create(HeContext &);
    virtual void to_device() = 0;
    virtual void encode(const std::vector<uint64_t> &, Plaintext &) = 0;
    virtual void decode(Plaintext &, std::vector<uint64_t> &) = 0;
};

class EncoderSeal : public Encoder {
public:
    EncoderSeal(HeContextSeal &context);
    seal::BatchEncoder & get_raw();
    void to_device() override;

    void encode(const std::vector<uint64_t> &, Plaintext &) override;
    void decode(Plaintext &, std::vector<uint64_t> &) override;

private:
    std::unique_ptr<seal::BatchEncoder> encoder;
};

class EncoderTroy : public Encoder {
public:
    EncoderTroy(HeContextTroy &context);
    troy::BatchEncoder & get_raw();
    void to_device() override;

    void encode(const std::vector<uint64_t> &, Plaintext &) override;
    void decode(Plaintext &, std::vector<uint64_t> &) override;

private:
    std::unique_ptr<troy::BatchEncoder> encoder;
};
