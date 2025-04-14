#include "server.h"

vector<std::unique_ptr<Ciphertext>> Server::process_first_dim(Ciphertext &query0)
{
    size_t dim0_size = pirParam.dimensions[0];

    TimingClock tc;

    tc.tick();
    // Query rotation
    vector<std::unique_ptr<Ciphertext>> rotated_query0;
    rotated_query0.emplace_back(query0.clone());

    for(int i = 1; i < dim0_size; i++) {
        auto tmp = query0.clone();
        evaluator->rotate_rows(*tmp, -i, *client_public_keys);
        rotated_query0.emplace_back(std::move(tmp));
    }

#ifdef DEBUG
    // print rotated query
    std::cout<<"Rotated query: " << std::endl;
    for (int i = 0; i < 5; i++) {
        print_vec(client->decrypt_ciphertext(*rotated_query0[i]), 10, "    " + std::to_string(i));
    }
#endif // DEBUG

    tc.tock();
    auto rotation_msg = tc.getmsg("Dim 1 rotation");

    tc.reset();
    tc.tick();
    // First dim: CtPtMul and sum
    vector<std::unique_ptr<Ciphertext>> dim1_result;
    dim1_result.reserve(pirParam.num_entries / dim0_size);
    for(int i = 0; i < pirParam.num_entries / dim0_size; i += dim0_size) {
        auto sum = rotated_query0[0]->clone();
        evaluator->multiply_plain(*sum, *db_plain[i]);
        for(int j = 1; j < dim0_size; j++) {
            auto tmp = rotated_query0[j]->clone();
            evaluator->multiply_plain(*tmp, *db_plain[i + j]);
            evaluator->add(*sum, *tmp);
        }
        dim1_result.emplace_back(std::move(sum));
    }
    tc.tock();
    auto mulsum_msg = tc.getmsg("Dim 1 mul and sum");

    std::cout << "Server: First dim processing done. " << std::endl;

#ifdef TIMING
    std::cout << rotation_msg << std::endl;
    std::cout << mulsum_msg << std::endl;
#endif // TIMING

#ifdef DEBUG
    // print dim1 result
    std::cout<<"Dim1 result: " << std::endl;
    for (int i = 0; i < 5; i++) {
        print_vec(client->decrypt_ciphertext(*dim1_result[i]), 10, "    " + std::to_string(i));
    }
#endif // DEBUG

    return dim1_result;
}
