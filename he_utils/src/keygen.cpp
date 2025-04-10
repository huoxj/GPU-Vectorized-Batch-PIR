#include "keygen.h"

std::unique_ptr<KeyGen> KeyGen::create(HeContext &context)
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<KeyGenSeal>(
            dynamic_cast<HeContextSeal &>(context)
        );
    case TROY:
        return std::make_unique<KeyGenTroy>(
            dynamic_cast<HeContextTroy &>(context)
        );
    default:
        throw std::runtime_error("Invalid HE library type");
    }
}

KeyGenSeal::KeyGenSeal(HeContextSeal &context) {
    keygen = std::make_unique<seal::KeyGenerator>(context.get_raw());
}

seal::KeyGenerator & KeyGenSeal::get_raw() {
    return *keygen;
}

KeyGenTroy::KeyGenTroy(HeContextTroy &context) {
    keygen = std::make_unique<troy::KeyGenerator>(context.get_raw());
}

troy::KeyGenerator & KeyGenTroy::get_raw() {
    return *keygen;
}
