#pragma once

#include <algorithm>

#include "pirParams.h"
#include "mockClient.h"
#include "utils.h"

class Server {
public:
    Server(PirParams &);

    void client_connect(MockClient &client);
    std::unique_ptr<Ciphertext> generate_response_serialized(const vector<std::unique_ptr<Ciphertext>> &query);
    void client_disconnet();

private:

    void processDB();

    vector<std::unique_ptr<Ciphertext>> process_first_dim(Ciphertext &query0);
    std::unique_ptr<Ciphertext> process_second_dim(Ciphertext &query1, vector<std::unique_ptr<Ciphertext>> &dim1_result);
    std::unique_ptr<Ciphertext> process_last_dim(Ciphertext &query2, Ciphertext &dim2_result);

    PirParams &pirParam;

    vector<uint64_t> db;
    vector<std::unique_ptr<Plaintext>> db_plain;

    // encryption utils
    std::shared_ptr<HeContext> context;
    std::unique_ptr<Encoder> encoder;
    std::unique_ptr<Evaluator> evaluator;

    // client info
    bool client_connected = false;
    PublicKeys *client_public_keys = nullptr;
    
    // Cheating for debugging
    MockClient *client = nullptr;
};
