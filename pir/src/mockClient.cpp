#include "mockClient.h"

MockClient::MockClient(PirParams &pirParams):
    pirparams(pirParams)
{
    // context = HeContext::create(pirParams.encryption_params, true, SecurityLevel::Classical128);
    context = HeContext::create(*pirparams.encryption_params);
    // encoder = std::make_shared<BatchEncoder>(BatchEncoder(context));
    encoder = Encoder::create(*context);

    context->to_device();
    encoder->to_device();

    // keygen = std::make_shared<KeyGenerator>(KeyGenerator(context));
    keygen = KeyGen::create(*context);

    // public_key = keygen->create_public_key(false);
    // secret_key = keygen->secret_key();
    // galois_key = keygen->create_galois_keys(false);
    // relin_key = keygen->create_relin_keys(false);
    public_keys = PublicKeys::create(*keygen);
    secret_keys = SecretKeys::create(*keygen);

}

vector<std::unique_ptr<Ciphertext>> MockClient::query_generation(size_t entry = 0)
{
    // Encryptor encryptor(context);
    // encryptor.set_public_key(public_key);
    auto encryptor = Encryptor::create(*context, *secret_keys);

    size_t num_dim = pirparams.dimensions.size();

    vector<size_t> plain_idx(num_dim, 0);

    // Transform linear idx to dimensional idx
    size_t dim_tmp = 1;
    for(int i = 0; i < num_dim; i++) {
        plain_idx[i] = (entry / dim_tmp) % pirparams.dimensions[i];
        dim_tmp *= pirparams.dimensions[i];
    }

#ifdef DEBUG
    std::cout << "Query idx: (";
    for (int i = 0; i < num_dim; i++) {
        std::cout << plain_idx[i] << " ";
    }
    std::cout << ")" << std::endl;
#endif // DEBUG

    // Prefix sum on idx, because of rotation
    size_t prefix_sum = plain_idx[0];
    for(int i = 1; i < num_dim; i++) {
        size_t tmp = plain_idx[i];
        plain_idx[i] += prefix_sum;
        prefix_sum += tmp;
    }

    // query gen
    size_t dim0 = pirparams.dimensions[0];
    vector<std::unique_ptr<Ciphertext>> query;

    for(int i = 0; i < pirparams.dimensions.size(); i++) {
        // Currently every query is (1,0,0,0,...,0)-like
        auto one_hot = vector<uint64_t>(dim0, 0);
        one_hot[plain_idx[i] % dim0] = 1;

        auto query_pt = Plaintext::create();
        encoder->encode(one_hot, *query_pt);

        auto query_ct = Ciphertext::create();
        encryptor->encrypt_symmetric(*query_pt, *query_ct);
        query.emplace_back(std::move(query_ct));
    }

    return query;
}

vector<uint64_t> MockClient::decrypt_ciphertext(Ciphertext &ct) {
    auto decryptor = Decryptor::create(*context, *secret_keys);
    auto decrypted = Plaintext::create();
    
    decryptor->decrypt(ct, *decrypted);

    vector<uint64_t> decrypted_vec;
    encoder->decode(*decrypted, decrypted_vec);
    
    return decrypted_vec;
}

PublicKeys * MockClient::get_public_keys() {
    return public_keys.get();
}
