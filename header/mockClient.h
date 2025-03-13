#pragma once

#include<vector>

#include"pirParams.h"

using std::vector;
using namespace troy;

class MockClient {
public:
    MockClient(PirParams &);
    
    vector<Ciphertext> get_query();
    Plaintext decrypt_ciphertext(Ciphertext ct);

    std::shared_ptr<BatchEncoder> get_encoder();
    std::shared_ptr<HeContext> get_context();
    PublicKey & get_public_key();
    GaloisKeys & get_galois_key();

private:
    PirParams &pirparams;
    std::shared_ptr<HeContext> context;
    std::shared_ptr<BatchEncoder> encoder;
    std::shared_ptr<KeyGenerator> keygen;
    PublicKey public_key;
    SecretKey secret_key;
    GaloisKeys galois_key;
};
