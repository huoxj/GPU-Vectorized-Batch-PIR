#pragma once

#include<vector>

#include"pirParams.h"

using std::vector;
using namespace troy;

class MockClient {
public:
    MockClient(PirParams &);

    vector<Ciphertext> query_generation(size_t);

    vector<uint64_t> decrypt_ciphertext(Ciphertext ct);

    PublicKey & get_public_key();
    GaloisKeys & get_galois_key();
    RelinKeys & get_relin_key();

private:

    PirParams &pirparams;
    std::shared_ptr<HeContext> context;
    std::shared_ptr<BatchEncoder> encoder;
    std::shared_ptr<KeyGenerator> keygen;
    PublicKey public_key;
    SecretKey secret_key;
    GaloisKeys galois_key;
    RelinKeys relin_key;
};
