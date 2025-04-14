#include "server.h"

std::unique_ptr<Ciphertext> Server::process_last_dim(Ciphertext &query2, Ciphertext &dim2_result)
{
    auto dim3_result = query2.clone();
    evaluator->multiply_cipher(*dim3_result, dim2_result);

    std::cout << "Server: Last dim processing done. " << std::endl;
    return dim3_result;
}
