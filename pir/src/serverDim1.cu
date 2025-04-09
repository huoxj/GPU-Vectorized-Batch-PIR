#include "server.h"

vector<Ciphertext> Server::process_first_dim(const Ciphertext query0)
{
    size_t dim0_size = pirParam.dimensions[0];


    // Query rotation
    vector<Ciphertext> rotated_query0;
    rotated_query0.push_back(query0);

    for(int i = 1; i < dim0_size; i++) {
        Ciphertext rotated = 
            evaluator->rotate_rows_new(query0, -i, *client_galois_key);
        rotated_query0.push_back(rotated);
    }

    // First dim: CtPtMul and sum
    vector<Ciphertext> dim1_result;
    for(int i = 0; i < pirParam.num_entries / dim0_size; i += dim0_size) {
        // Lib troy has an efficient way to do Multiply and accumlate,
        // but here implements it in a naive way
        Ciphertext sum = evaluator->multiply_plain_new(rotated_query0[0], db_plain[i]);
        for(int j = 1; j < dim0_size; j++) {
            Ciphertext tmp = evaluator->multiply_plain_new(rotated_query0[j], db_plain[i + j]);
            evaluator->add_inplace(sum, tmp);
        }
        dim1_result.push_back(sum);
    }

    std::cout << "Server: First dim processing done. " << std::endl;

    // Debug
    // auto decrypted_vec = client->decrypt_ciphertext(dim1_result[0]);
    // for(int i = 0; i < 10; i++) {
    //     std::cout << "decrypted_vec[" << i << "]: " << decrypted_vec[i] << std::endl;
    // }

    return dim1_result;
}
