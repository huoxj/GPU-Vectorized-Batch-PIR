#include "server.h"

std::unique_ptr<Ciphertext> Server::process_second_dim(Ciphertext &query1, vector<std::unique_ptr<Ciphertext>> &dim1_result) {
    // Dim 2 multiplication and rotation
    auto dim2_result = query1.clone();
    evaluator->multiply_cipher(*dim2_result, *dim1_result[0]);
    evaluator->relinearize(*dim2_result, *client_public_keys);

    size_t dim0_size = pirParam.dimensions[0];
    
    for(int i = 1; i < pirParam.dimensions[2]; i++) {
        auto tmp = query1.clone();
        evaluator->multiply_cipher(*tmp, *dim1_result[i]);
        evaluator->relinearize(*tmp, *client_public_keys);
        
        evaluator->rotate_rows(*tmp, -i, *client_public_keys);
        evaluator->add(*dim2_result, *tmp);
    }

    std::cout << "Server: Second dim processing done. " << std::endl;
    return dim2_result;
}
