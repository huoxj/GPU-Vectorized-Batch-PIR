#pragma once

#include <algorithm>

#include "pirParams.h"
#include "mockClient.h"

using namespace troy;

class Server {
public:
    Server(PirParams &);

    void generate_response_serialized(const MockClient &client, const vector<Ciphertext> &query, Ciphertext &dest);

private:

    void processDim1(const MockClient &client, const Ciphertext query0, vector<Ciphertext> &result);
    void processDim2(const MockClient &client, const Ciphertext query1, const vector<Ciphertext> dim1_result, vector<Ciphertext> &reuslt);
    void processDim3(const MockClient &client, const Ciphertext query2, const vector<Ciphertext> dim2_result, Ciphertext &result);

    PirParams &pirParam;

    vector<uint64_t> db;
    
};
