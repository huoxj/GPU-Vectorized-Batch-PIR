#include "batch_evaluator.h"

BatchEvaluator::BatchEvaluator(std::unique_ptr<Evaluator> evaluator) : evaluator(std::move(evaluator)) {}

void BatchEvaluator::add(BatchCiphertext &a, BatchCiphertext &b) {
    if (a.batch_size != b.batch_size) {
        throw std::invalid_argument("CtCtAdd Batch sizes do not match");
    }
    if (a.bucket_size != b.bucket_size) {
        throw std::invalid_argument("CtCtAdd Bucket sizes do not match");
    }
    if (a.poly_degree != b.poly_degree) {
        throw std::invalid_argument("CtCtAdd Poly degrees do not match");
    }

    for (int i = 0; i < a.num_batchedcts; i++) {
        evaluator->add(*a.batched_cts[i], *b.batched_cts[i]);
    }
}

void BatchEvaluator::rotate_rows(BatchCiphertext &a, int32_t steps, PublicKeys &pk) {
    for (int i = 0; i < a.num_batchedcts; i++) {
        evaluator->rotate_rows(*a.batched_cts[i], steps, pk);
    }
}

void BatchEvaluator::multiply_plain(BatchCiphertext &a, BatchPlaintext &b) {
    if (a.batch_size != b.batch_size) {
        throw std::invalid_argument("CtPtMul Batch sizes do not match");
    }
    if (a.bucket_size != b.bucket_size) {
        throw std::invalid_argument("CtPtMul Bucket sizes do not match");
    }
    if (a.poly_degree != b.poly_degree) {
        throw std::invalid_argument("CtPtMul Poly degrees do not match");
    }

    for (int i = 0; i < a.num_batchedcts; i++) {
        evaluator->multiply_plain(*a.batched_cts[i], *b.batched_pts[i]);
    }
}

void BatchEvaluator::multiply_cipher(BatchCiphertext &a, BatchCiphertext &b) {
    if (a.batch_size != b.batch_size) {
        throw std::invalid_argument("CtCtMul Batch sizes do not match");
    }
    if (a.bucket_size != b.bucket_size) {
        throw std::invalid_argument("CtCtMul Bucket sizes do not match");
    }
    if (a.poly_degree != b.poly_degree) {
        throw std::invalid_argument("CtCtMul Poly degrees do not match");
    }

    for (int i = 0; i < a.num_batchedcts; i++) {
        evaluator->multiply_cipher(*a.batched_cts[i], *b.batched_cts[i]);
    }
}

void BatchEvaluator::relinearize(BatchCiphertext &a, PublicKeys &pk) {
    for (int i = 0; i < a.num_batchedcts; i++) {
        evaluator->relinearize(*a.batched_cts[i], pk);
    }
}
