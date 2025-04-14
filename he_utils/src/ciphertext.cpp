#include "ciphertext.h"

std::unique_ptr<Ciphertext> Ciphertext::create() {
    switch (HeLib::lib_type) {
        case SEAL:
            return std::make_unique<CiphertextSeal>();
        case TROY:
            return std::make_unique<CiphertextTroy>();
        default:
            throw std::runtime_error("Unknown HE library type");
    }
}

// ==========================
// CiphertextSeal
// ==========================

CiphertextSeal::CiphertextSeal()
{
    cipher = std::make_unique<seal::Ciphertext>();
}

std::unique_ptr<Ciphertext> CiphertextSeal::clone() const {
    auto clone = std::make_unique<CiphertextSeal>();

    clone->cipher = std::make_unique<seal::Ciphertext>(*cipher);

    return clone;
}

seal::Ciphertext & CiphertextSeal::get_raw() {
    return *cipher;
}


// ==========================
// CiphertextTroy
// ==========================

CiphertextTroy::CiphertextTroy()
{
    cipher = std::make_unique<troy::Ciphertext>();
}

std::unique_ptr<Ciphertext> CiphertextTroy::clone() const {
    auto clone = std::make_unique<CiphertextTroy>();

    clone->cipher = std::make_unique<troy::Ciphertext>(*cipher);

    return clone;
}

troy::Ciphertext & CiphertextTroy::get_raw() {
    return *cipher;
}
