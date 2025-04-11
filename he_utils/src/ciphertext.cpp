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

troy::Ciphertext & CiphertextTroy::get_raw() {
    return *cipher;
}
