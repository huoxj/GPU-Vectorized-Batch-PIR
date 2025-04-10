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

seal::Ciphertext & CiphertextSeal::get_raw() {
    return *cipher;
}


// ==========================
// CiphertextTroy
// ==========================

troy::Ciphertext & CiphertextTroy::get_raw() {
    return *cipher;
}
