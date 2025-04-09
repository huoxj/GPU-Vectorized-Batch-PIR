#include "mockClient.h"

MockClient::MockClient(PirParams &pirParams):
    pirparams(pirParams)
{
    context = HeContext::create(pirParams.encryption_params, true, SecurityLevel::Classical128);
    encoder = std::make_shared<BatchEncoder>(BatchEncoder(context));

    context->to_device_inplace();
    encoder->to_device_inplace();

    keygen = std::make_shared<KeyGenerator>(KeyGenerator(context));

    public_key = keygen->create_public_key(false);
    secret_key = keygen->secret_key();
    galois_key = keygen->create_galois_keys(false);
    relin_key = keygen->create_relin_keys(false);

}

vector<Ciphertext> MockClient::query_generation(size_t entry = 0)
{
    Encryptor encryptor(context);
    encryptor.set_public_key(public_key);

    size_t num_dim = pirparams.dimensions.size();

    vector<size_t> plain_idx(num_dim, 0);

    // Transform linear idx to dimensional idx
    size_t dim_tmp = 1;
    for(int i = 0; i < num_dim; i++) {
        plain_idx[i] = (entry / dim_tmp) % pirparams.dimensions[i];
        dim_tmp *= pirparams.dimensions[i];
    }

    // debug
    for (int i = 0; i < num_dim; i++) {
        std::cout << "plain_idx[" << i << "]: " << plain_idx[i] << std::endl;
    }

    // Prefix sum on idx, because of rotation
    size_t prefix_sum = plain_idx[0];
    for(int i = 1; i < num_dim; i++) {
        size_t tmp = plain_idx[i];
        plain_idx[i] += prefix_sum;
        prefix_sum += tmp;
    }


    // query gen
    size_t dim0 = pirparams.dimensions[0];
    vector<Ciphertext> query;

    for(int i = 0; i < pirparams.dimensions.size(); i++) {
        // Currently every query is (1,0,0,0,...,0)-like
        auto one_hot = vector<uint64_t>(dim0, 0);
        one_hot[plain_idx[i] % dim0] = 1;
        
        Plaintext query_pt;
        encoder->encode(one_hot, query_pt);

        Ciphertext query_ct;
        encryptor.encrypt_asymmetric(query_pt, query_ct);
        query.emplace_back(query_ct);
    }

    return query;
}

vector<uint64_t> MockClient::decrypt_ciphertext(Ciphertext ct) {
    Decryptor decryptor(context, secret_key);
    Plaintext decrypted;
    
    decryptor.decrypt(ct, decrypted);

    vector<uint64_t> decrypted_vec;
    encoder->decode(decrypted, decrypted_vec);
    
    return decrypted_vec;
}

PublicKey & MockClient::get_public_key() {
    return public_key;
}

GaloisKeys & MockClient::get_galois_key() {
    return galois_key;
}

RelinKeys & MockClient::get_relin_key() {
    return relin_key;
}
