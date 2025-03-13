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

}

vector<Ciphertext> MockClient::get_query()
{
    Encryptor encryptor(context);
    encryptor.set_public_key(public_key);

    size_t slot_count = encoder->slot_count();
    size_t row_size = slot_count / 2;

    vector<Ciphertext> query;

    for(size_t dim_size: pirparams.dimensions) {
        // Currently every query is (1,0,0,0,...,0)-like
        auto one_hot = vector<uint64_t>(row_size, 0);
        one_hot[0] = 1;
        
        Plaintext query_pt;
        encoder->encode_polynomial(one_hot, query_pt);

        Ciphertext query_ct;
        encryptor.encrypt_asymmetric(query_pt, query_ct);
        query.emplace_back(query_ct);
    }

    return query;
}

Plaintext MockClient::decrypt_ciphertext(Ciphertext ct) {
    Decryptor decryptor(context, secret_key);
    Plaintext decrypted;
    
    decryptor.decrypt(ct, decrypted);
    
    return decrypted;
}

std::shared_ptr<HeContext> MockClient::get_context() {
    return context;
}

std::shared_ptr<BatchEncoder> MockClient::get_encoder() {
    return encoder;
}

PublicKey & MockClient::get_public_key() {
    return public_key;
}

GaloisKeys & MockClient::get_galois_key() {
    return galois_key;
}
