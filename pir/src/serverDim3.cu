#include "server.h"

Ciphertext Server::process_last_dim(const Ciphertext query2, const Ciphertext dim2_result)
{
    Ciphertext dim3_result = evaluator->multiply_new(query2, dim2_result);

    evaluator->relinearize_inplace(dim3_result, *client_relin_key);

    std::cout << "Server: Last dim processing done. " << std::endl;
    return dim3_result;
}
