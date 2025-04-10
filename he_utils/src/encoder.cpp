#include "encoder.h"

std::unique_ptr<Encoder> Encoder::create(HeContext &context)
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<EncoderSeal>(
            dynamic_cast<HeContextSeal &>(context)
        );
    case TROY:
        return std::make_unique<EncoderTroy>(
            dynamic_cast<HeContextTroy &>(context)
        );
    default:
        throw std::runtime_error("Invalid HE library type");
    }
}

// ==========================================================
// SEAL Encoder
// ==========================================================

EncoderSeal::EncoderSeal(HeContextSeal &context)
{
    encoder = std::make_unique<seal::BatchEncoder>(
        context.get_raw()
    );
}

seal::BatchEncoder & EncoderSeal::get_raw()
{
    return *encoder;
}

void EncoderSeal::to_device() {}

void EncoderSeal::encode(const std::vector<uint64_t> &data, Plaintext &plain)
{
    auto *plain_seal = dynamic_cast<PlaintextSeal *>(&plain);
    if (!plain_seal) {
        throw std::runtime_error("Invalid Plaintext type");
    }

    encoder->encode(
        data,
        plain_seal->get_raw()
    );

}

void EncoderSeal::decode(Plaintext &plain, std::vector<uint64_t> &data)
{
    auto *plain_seal = dynamic_cast<PlaintextSeal *>(&plain);
    if (!plain_seal) {
        throw std::runtime_error("Invalid Plaintext type");
    }

    encoder->decode(
        plain_seal->get_raw(),
        data
    );
}

// ==========================================================
// Troy Encoder
// ==========================================================

EncoderTroy::EncoderTroy(HeContextTroy &context)
{
    encoder = std::make_unique<troy::BatchEncoder>(
        context.get_raw()
    );
}

troy::BatchEncoder & EncoderTroy::get_raw()
{
    return *encoder;
}

void EncoderTroy::to_device()
{
    encoder->to_device_inplace();
}

void EncoderTroy::encode(const std::vector<uint64_t> &data, Plaintext &plain)
{
    auto *plain_troy = dynamic_cast<PlaintextTroy *>(&plain);
    if (!plain_troy) {
        throw std::runtime_error("Invalid Plaintext type");
    }

    encoder->encode(
        data,
        plain_troy->get_raw()
    );
}

void EncoderTroy::decode(Plaintext &plain, std::vector<uint64_t> &data)
{
    auto *plain_troy = dynamic_cast<PlaintextTroy *>(&plain);
    if (!plain_troy) {
        throw std::runtime_error("Invalid Plaintext type");
    }

    encoder->decode(
        plain_troy->get_raw(),
        data
    );
}
