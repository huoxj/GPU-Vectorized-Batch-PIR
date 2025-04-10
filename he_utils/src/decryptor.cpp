#include "decryptor.h"

std::unique_ptr<Decryptor> Decryptor::create(HeContext &context, SecretKeys &secret_key)
{
    switch(HeLib::lib_type) {
        case SEAL:
            return std::make_unique<DecryptorSeal>(
                dynamic_cast<HeContextSeal &>(context),
                dynamic_cast<SecretKeysSeal &>(secret_key)
            );
        case TROY:
            return std::make_unique<DecryptorTroy>(
                dynamic_cast<HeContextTroy &>(context),
                dynamic_cast<SecretKeysTroy &>(secret_key)
            );
        default:
            throw std::runtime_error("Invalid HeLib type");
    }
}

// =============================================================
// SEAL Decryptor
// =============================================================

DecryptorSeal::DecryptorSeal(HeContextSeal &context, SecretKeysSeal &secret_key)
{
    decryptor = std::make_unique<seal::Decryptor>(
        context.get_raw(),
        secret_key.getSecretKey()
    );
}

void DecryptorSeal::decrypt(Ciphertext &cipher, Plaintext &plain)
{
    auto *cipher_seal = dynamic_cast<CiphertextSeal *>(&cipher);
    if (!cipher_seal) {
        throw std::runtime_error("Invalid Ciphertext type");
    }

    auto *plain_seal = dynamic_cast<PlaintextSeal *>(&plain);
    if (!plain_seal) {
        throw std::runtime_error("Invalid Plaintext type");
    }

    decryptor->decrypt(
        cipher_seal->get_raw(),
        plain_seal->get_raw()
    );
}

// =============================================================
// Troy Decryptor
// =============================================================

DecryptorTroy::DecryptorTroy(HeContextTroy &context, SecretKeysTroy &secret_key)
{
    decryptor = std::make_unique<troy::Decryptor>(
        context.get_raw(),
        secret_key.getSecretKey()
    );
}

void DecryptorTroy::decrypt(Ciphertext &cipher, Plaintext &plain)
{
    auto *cipher_troy = dynamic_cast<CiphertextTroy *>(&cipher);
    if (!cipher_troy) {
        throw std::runtime_error("Invalid Ciphertext type");
    }

    auto *plain_troy = dynamic_cast<PlaintextTroy *>(&plain);
    if (!plain_troy) {
        throw std::runtime_error("Invalid Plaintext type");
    }

    decryptor->decrypt(
        cipher_troy->get_raw(),
        plain_troy->get_raw()
    );
}
