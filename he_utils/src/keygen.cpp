#include "keygen.h"

KeyGenSeal::KeyGenSeal(std::unique_ptr<HeContextSeal> &context) {
    keygen = std::make_unique<seal::KeyGenerator>(*context->getRaw());
}

std::unique_ptr<seal::KeyGenerator> & KeyGenSeal::getRaw() {
    return keygen;
}

KeyGenTroy::KeyGenTroy(std::unique_ptr<HeContextTroy> &context) {
    keygen = std::make_unique<troy::KeyGenerator>(context->getRaw());
}

std::unique_ptr<troy::KeyGenerator> & KeyGenTroy::getRaw() {
    return keygen;
}
