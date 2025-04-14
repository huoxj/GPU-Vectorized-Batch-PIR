#pragma once

#include<vector>

#include"pirParams.h"
#include "utils.h"

using std::vector;

class MockClient {
public:
    MockClient(PirParams &);

    vector<std::unique_ptr<Ciphertext>> query_generation(size_t);

    vector<uint64_t> decrypt_ciphertext(Ciphertext &ct);

    PublicKeys *get_public_keys();

private:

    PirParams &pirparams;
    std::unique_ptr<HeContext> context;
    std::unique_ptr<Encoder> encoder;
    std::unique_ptr<KeyGen> keygen;
    std::unique_ptr<PublicKeys> public_keys;
    std::unique_ptr<SecretKeys> secret_keys;
};
