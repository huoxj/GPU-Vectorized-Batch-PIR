#include "pirParams.h"
#include "mockClient.h"
#include "server.h"
#include "utils.h"
#include "myhe.h"
#include <iostream>
#include "batch_utils.h"

auto HeLib::lib_type = HeLibType::SEAL;

void pir();
void test();

void testBatch() {
    auto ep = EncryptionParameters::create();
    ep->setParameters(8192, 20);
    auto context = HeContext::create(*ep);
    auto encoder = Encoder::create(*context);

    context->to_device();
    encoder->to_device();
    
    auto keygen = KeyGen::create(*context);
    auto pk = PublicKeys::create(*keygen);
    auto sk = SecretKeys::create(*keygen);

    auto encryptor = Encryptor::create(*context, *sk);
    auto decrpytor = Decryptor::create(*context, *sk);
    auto evaluator = Evaluator::create(*context);

    vector<vector<uint64_t>> data = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8},
        {9, 10}
    };
    auto bv = BatchVector(data, 8192, 5, 2);
    bv.print();

    auto bp = BatchPlaintext(bv, *encoder);
    auto bc = BatchCiphertext(bp, *encryptor);

    auto nbc = bc;

    auto bevaluator = BatchEvaluator(std::move(evaluator));

    bevaluator.rotate_rows(nbc, -2048, *pk);

    auto nbp = BatchPlaintext(nbc, *decrpytor);

    nbp.print(*encoder);
}

int main() {
    pir();
}

void pir() {

    PirParams params(8192, 32);

    MockClient client(params);
    Server server(params);

    server.client_connect(client);

    size_t query_idx = 0;
    auto query = client.query_generation(query_idx);

    auto response = server.generate_response_serialized(query);

    server.client_disconnet();

    auto decrypted_pt = client.decrypt_ciphertext(*response);

    for (int i = 0; i < decrypted_pt.size(); i++) {
        if (decrypted_pt[i] == 0) continue;
        std::cout << decrypted_pt[i] << " ";
    }

    troy::utils::MemoryPool::Destroy();
    
}

void test() {
    auto ep = EncryptionParameters::create();
    ep->setParameters(8192, 20);
    auto context = HeContext::create(*ep);
    auto encoder = Encoder::create(*context);

    context->to_device();
    encoder->to_device();
    
    auto keygen = KeyGen::create(*context);
    auto pk = PublicKeys::create(*keygen);
    auto sk = SecretKeys::create(*keygen);

    auto encryptor = Encryptor::create(*context, *sk);
    auto decrpytor = Decryptor::create(*context, *sk);
    auto evaluator = Evaluator::create(*context);

    std::vector<uint64_t> data(8192);
    int n = 0;
    std::generate(data.begin(), data.end(), [&n]() { return n++; });
    auto pt = Plaintext::create();
    encoder->encode(data, *pt);
    
    auto ct = Ciphertext::create();
    encryptor->encrypt_symmetric(*pt, *ct);

    evaluator->rotate_rows(*ct, -1, *pk);

    auto decrypted_pt = Plaintext::create();
    decrpytor->decrypt(*ct, *decrypted_pt);
    std::vector<uint64_t> decoded_data;
    encoder->decode(*decrypted_pt, decoded_data);

    for(int i = 4086; i < 4096; i++) {
        std::cout << decoded_data[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 4096; i < 4106; i++) {
        std::cout << decoded_data[i] << " ";
    }
}
