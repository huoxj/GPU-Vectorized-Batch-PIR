#include "server.h"

Ciphertext Server::process_second_dim(const Ciphertext query1, const vector<Ciphertext> dim1_result) {
    // Dim 2 multiplication and rotation
    Ciphertext dim2_result;

    size_t dim0_size = pirParam.dimensions[0];
    
    bool sum_empty = true;
    for(int i = 0; i < pirParam.dimensions[2]; i++) {
        Ciphertext tmp = evaluator->multiply_new(query1, dim1_result[i]);
        evaluator->relinearize_inplace(tmp, *client_relin_key);
        
        if(sum_empty) {
            dim2_result = tmp;
            sum_empty = false;
        } else {
            evaluator->rotate_rows_inplace(tmp, -i, *client_galois_key);
            evaluator->add_inplace(dim2_result, tmp);
        }
    }

    std::cout << "Server: Second dim processing done. " << std::endl;
    return dim2_result;
}
