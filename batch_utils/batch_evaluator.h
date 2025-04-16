#pragma once

#include "batch_data.h"

class BatchEvaluator {
public:
    BatchEvaluator(std::unique_ptr<Evaluator> evaluator);

    void add(BatchCiphertext &a, BatchCiphertext &b);
    void rotate_rows(BatchCiphertext &a, int32_t steps, PublicKeys &pk);
    void multiply_plain(BatchCiphertext &a, BatchPlaintext &b);
    void multiply_cipher(BatchCiphertext &a, BatchCiphertext &b);
    void relinearize(BatchCiphertext &a, PublicKeys &pk);

private:
    std::unique_ptr<Evaluator> evaluator;
};
