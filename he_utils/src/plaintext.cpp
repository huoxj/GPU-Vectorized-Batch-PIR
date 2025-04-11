#include "plaintext.h"

std::unique_ptr<Plaintext> Plaintext::create()
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<PlaintextSeal>();
    case TROY:
        return std::make_unique<PlaintextTroy>();
    default:
        throw std::runtime_error("Invalid HeLib Type");
    }
}

// ============================
// SEAL Plaintext
// ============================

PlaintextSeal::PlaintextSeal()
{
    plain = std::make_unique<seal::Plaintext>();
}

seal::Plaintext & PlaintextSeal::get_raw()
{
    return *plain;
}

// ============================
// TROY Plaintext
// ============================

PlaintextTroy::PlaintextTroy()
{
    plain = std::make_unique<troy::Plaintext>();
}

troy::Plaintext & PlaintextTroy::get_raw()
{
    return *plain;
}
