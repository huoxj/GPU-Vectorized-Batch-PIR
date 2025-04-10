#include "encryptor.h"

std::unique_ptr<Encryptor> Encryptor::create(HeContext &context, SecretKeys &sk)
{
    switch(HeLib::lib_type) {
    case SEAL:
        return std::make_unique<EncryptorSeal>(
            dynamic_cast<HeContextSeal &>(context),
            dynamic_cast<SecretKeysSeal &>(sk)
        );
    case TROY:
        return std::make_unique<EncryptorTroy>(
            dynamic_cast<HeContextTroy &>(context),
            dynamic_cast<SecretKeysTroy &>(sk)
        );
    default:
        throw std::runtime_error("Invalid HeLib Type");
    }
}

// ============================
// SEAL Encryptor
// ============================

EncryptorSeal::EncryptorSeal(HeContextSeal &context, SecretKeysSeal &sk)
{
    encryptor = std::make_unique<seal::Encryptor>(context.get_raw(), sk.getSecretKey());
}

void EncryptorSeal::encrypt_symmetric(Plaintext &plain, Ciphertext &cipher)
{
    auto plain_seal = dynamic_cast<PlaintextSeal *>(&plain);
    auto cipher_seal = dynamic_cast<CiphertextSeal *>(&cipher);

    if (!plain_seal) {
        throw std::runtime_error("Invalid Plaintext Type");
    }

    if (!cipher_seal) {
        throw std::runtime_error("Invalid Ciphertext Type");
    }

    encryptor->encrypt_symmetric(plain_seal->get_raw(), cipher_seal->get_raw());

}

// ============================
// Troy Encryptor
// ============================

EncryptorTroy::EncryptorTroy(HeContextTroy &context, SecretKeysTroy &sk)
{
    encryptor = std::make_unique<troy::Encryptor>(context.get_raw());
    encryptor->set_secret_key(sk.getSecretKey());
}

void EncryptorTroy::encrypt_symmetric(Plaintext &plain, Ciphertext &cipher)
{
    auto plain_troy = dynamic_cast<PlaintextTroy *>(&plain);
    auto cipher_troy = dynamic_cast<CiphertextTroy *>(&cipher);

    if (!plain_troy) {
        throw std::runtime_error("Invalid Plaintext Type");
    }

    if (!cipher_troy) {
        throw std::runtime_error("Invalid Ciphertext Type");
    }

    encryptor->encrypt_symmetric(plain_troy->get_raw(), false, cipher_troy->get_raw());
}
