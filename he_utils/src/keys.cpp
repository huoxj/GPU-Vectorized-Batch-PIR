#include "keys.h"

// Public keys

std::unique_ptr<PublicKeys> PublicKeys::create(KeyGen &keygen)
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<PublicKeysSeal>(
            dynamic_cast<KeyGenSeal &>(keygen)
        );
    case TROY:
        return std::make_unique<PublicKeysTroy>(
            dynamic_cast<KeyGenTroy &>(keygen)
        );
    default:
        throw std::runtime_error("Invalid HeLib type");
    }
}

PublicKeysSeal::PublicKeysSeal(KeyGenSeal &keygen) {
    keygen.get_raw().create_galois_keys(galois_keys);
    keygen.get_raw().create_relin_keys(relin_keys);
}

seal::GaloisKeys &PublicKeysSeal::getGaloisKeys() {
    return galois_keys;
}

seal::RelinKeys &PublicKeysSeal::getRelinKeys() {
    return relin_keys;
}

PublicKeysTroy::PublicKeysTroy(KeyGenTroy &keygen) {
    galois_keys = keygen.get_raw().create_galois_keys(false);
    relin_keys = keygen.get_raw().create_relin_keys(false);
}

troy::GaloisKeys &PublicKeysTroy::getGaloisKeys() {
    return galois_keys;
}

troy::RelinKeys &PublicKeysTroy::getRelinKeys() {
    return relin_keys;
}

// Secret keys

std::unique_ptr<SecretKeys> SecretKeys::create(KeyGen &keygen)
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<SecretKeysSeal>(
            dynamic_cast<KeyGenSeal &>(keygen)
        );
    case TROY:
        return std::make_unique<SecretKeysTroy>(
            dynamic_cast<KeyGenTroy &>(keygen)
        );
    default:
        throw std::runtime_error("Invalid HeLib type");
    }
}

SecretKeysSeal::SecretKeysSeal(KeyGenSeal &keygen) {
    secret_key = keygen.get_raw().secret_key();
}

seal::SecretKey &SecretKeysSeal::getSecretKey() {
    return secret_key;
}

SecretKeysTroy::SecretKeysTroy(KeyGenTroy &keygen) {
    secret_key = keygen.get_raw().secret_key();
}

troy::SecretKey &SecretKeysTroy::getSecretKey() {
    return secret_key;
}
