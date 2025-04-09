#include "server.h"
#include "utils.h"

Server::Server(PirParams &param):
    pirParam(param)
{
    // initialize encryption stuff
    context = HeContext::create(param.encryption_params, true, SecurityLevel::Classical128);
    encoder = std::make_unique<BatchEncoder>(BatchEncoder(context));

    context->to_device_inplace();
    encoder->to_device_inplace();
    evaluator = std::make_unique<Evaluator>(Evaluator(context));

    // initialize db
    processDB();
}

void Server::processDB() {
    // initialize raw db with entry id
    db.resize(pirParam.num_entries);
    uint64_t n = 0;
    auto increment_f = [&] {
        return n++;
    };
    std::generate(db.begin(), db.end(), increment_f);

    // process db to plaintext
    size_t dim0_size = pirParam.dimensions[0];
    for(int i = 0; i < pirParam.num_entries; i += dim0_size) {
        vector<uint64_t> entry(db.begin() + i, db.begin() + i + dim0_size);
        // early rotation, optimize for rotate & sum operation
        rotate_vector_in_place(entry, (i / dim0_size) % dim0_size);
        Plaintext row;
        encoder->encode(entry, row);
        db_plain.emplace_back(row);
    }
}

void Server::client_connect(MockClient &client)
{
    if(client_connected) {
        throw std::runtime_error("Already connected to a client");
    }

    client_connected = true;

    client_public_key = std::make_unique<PublicKey>(client.get_public_key());
    client_galois_key = std::make_unique<GaloisKeys>(client.get_galois_key());
    client_relin_key = std::make_unique<RelinKeys>(client.get_relin_key());

    // Cheat client decryption for debugging
    this->client = std::make_unique<MockClient>(client);
}

void Server::client_disconnet() 
{
    if(!client_connected) {
        throw std::runtime_error("Not connected to a client");
    }

    client_connected = false;

    client_public_key.reset();
    client_galois_key.reset();
}

void Server::generate_response_serialized(const vector<Ciphertext> &query, Ciphertext &dest)
{
    vector<Ciphertext> dim1_result = process_first_dim( query[0]);

    Ciphertext dim2_result = process_second_dim(query[1], dim1_result);

    Ciphertext dim3_result = process_last_dim(query[2], dim2_result);

    dest = dim3_result;
}

