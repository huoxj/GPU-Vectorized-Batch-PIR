#pragma once

#include <algorithm>

#include "pirParams.h"
#include "mockClient.h"

using namespace troy;

class Server {
public:
    Server(PirParams &);

    void client_connect(MockClient &client);
    void generate_response_serialized(const vector<Ciphertext> &query, Ciphertext &dest);
    void client_disconnet();

private:

    void processDB();

    vector<Ciphertext> process_first_dim(const Ciphertext query0);
    Ciphertext process_second_dim(const Ciphertext query1, const vector<Ciphertext> dim1_result);
    Ciphertext process_last_dim(const Ciphertext query2, const Ciphertext dim2_result);

    PirParams &pirParam;

    vector<uint64_t> db;
    vector<Plaintext> db_plain;

    // Cheating for debugging
    std::unique_ptr<MockClient> client;
    
    // encryption utils
    std::shared_ptr<HeContext> context;
    std::unique_ptr<BatchEncoder> encoder;
    std::unique_ptr<Evaluator> evaluator;

    // client info
    bool client_connected = false;
    std::unique_ptr<PublicKey> client_public_key;
    std::unique_ptr<GaloisKeys> client_galois_key;
    std::unique_ptr<RelinKeys> client_relin_key;
    
};
