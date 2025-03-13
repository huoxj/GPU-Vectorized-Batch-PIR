#include "server.h"

Server::Server(PirParams &param):
    pirParam(param)
{

    // initialize db with entry id
    uint64_t n = 0;
    auto increment_f = [&] {
        return n++;
    };
    std::generate(db.begin(), db.end(), increment_f);
    std::cout<<db[0]<<" "<<db[1];
}

void Server::generate_response_serialized(const MockClient &client, const vector<Ciphertext> &query, Ciphertext &dest)
{
    vector<Ciphertext> dim1_result;
    processDim1(client, query[0], dim1_result);

    vector<Ciphertext> dim2_result;
    // processDim2(client, query[1], dim1_result, dim2_result);

    // processDim3(client, query[2], dim2_result, dest);
}
