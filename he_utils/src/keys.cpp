#include "keys.h"

// Public keys

PublicKeysSeal::PublicKeysSeal(std::unique_ptr<KeyGenSeal> &keygen) {
    keygen->getRaw()->create_galois_keys(galois_keys);
    keygen->getRaw()->create_relin_keys(relin_keys);
}

seal::GaloisKeys &PublicKeysSeal::getGaloisKeys() {
    return galois_keys;
}

seal::RelinKeys &PublicKeysSeal::getRelinKeys() {
    return relin_keys;
}

PublicKeysTroy::PublicKeysTroy(std::unique_ptr<KeyGenTroy> &keygen) {
    galois_keys = keygen->getRaw()->create_galois_keys(false);
    relin_keys = keygen->getRaw()->create_relin_keys(false);
}

troy::GaloisKeys &PublicKeysTroy::getGaloisKeys() {
    return galois_keys;
}

troy::RelinKeys &PublicKeysTroy::getRelinKeys() {
    return relin_keys;
}

// Secret keys

SecretKeysSeal::SecretKeysSeal(std::unique_ptr<KeyGenSeal> &keygen) {
    secret_key = keygen->getRaw()->secret_key();
}

seal::SecretKey &SecretKeysSeal::getSecretKey() {
    return secret_key;
}

SecretKeysTroy::SecretKeysTroy(std::unique_ptr<KeyGenTroy> &keygen) {
    secret_key = keygen->getRaw()->secret_key();
}

troy::SecretKey &SecretKeysTroy::getSecretKey() {
    return secret_key;
}
