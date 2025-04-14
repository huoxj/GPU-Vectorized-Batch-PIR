#include "server.h"

Server::Server(PirParams &param):
    pirParam(param)
{
    // initialize encryption stuff
    // context = HeContext::create(param.encryption_params, true, SecurityLevel::Classical128);
    // encoder = std::make_unique<BatchEncoder>(BatchEncoder(context));
    context = HeContext::create(*param.encryption_params);
    encoder = Encoder::create(*context);

    context->to_device();
    encoder->to_device();

    evaluator = Evaluator::create(*context);

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
        auto row = Plaintext::create();
        encoder->encode(entry, *row);
        db_plain.emplace_back(std::move(row));
    }
}

void Server::client_connect(MockClient &client)
{
    if(client_connected) {
        throw std::runtime_error("Already connected to a client");
    }

    client_connected = true;

    client_public_keys = client.get_public_keys();

    // Cheat client decryption for debugging
    this->client = &client;
}

void Server::client_disconnet() 
{
    if(!client_connected) {
        throw std::runtime_error("Not connected to a client");
    }

    client_connected = false;

    client_public_keys = nullptr;
    client = nullptr;
}

std::unique_ptr<Ciphertext> Server::generate_response_serialized(const vector<std::unique_ptr<Ciphertext>> &query)
{
    TimingClock tc;
    tc.reset();

    tc.tick();
    auto dim1_result = process_first_dim(*query[0]);
    tc.tock();
    auto dim1_msg = tc.getmsg("Dim 1");

    tc.tick();
    auto dim2_result = process_second_dim(*query[1], dim1_result);
    tc.tock();
    auto dim2_msg = tc.getmsg("Dim 2");

    tc.tick();
    auto dim3_result = process_last_dim(*query[2], *dim2_result);
    tc.tock();
    auto dim3_msg = tc.getmsg("Dim 3");

#ifdef TIMING
    std::cout << dim1_msg << std::endl;
    std::cout << dim2_msg << std::endl;
    std::cout << dim3_msg << std::endl;
#endif // TIMING

    return std::move(dim3_result);
}

