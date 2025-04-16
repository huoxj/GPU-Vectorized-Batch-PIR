#pragma once

#include <vector>
#include "myhe.h"

using std::vector;
using intvec_t = vector<uint64_t>;

class BatchPlaintext;
class BatchCiphertext;

class BatchVector {
public:
    BatchVector(const vector<intvec_t> &vectors, const size_t poly_degree, const size_t batch_size, const size_t bucket_size);
    BatchVector(BatchPlaintext &);

    void print();

    const size_t poly_degree;
    const size_t batch_size;
    const size_t bucket_size;
    
private:
    size_t gap;
    size_t num_batchedvecs;

    vector<intvec_t> batched_vecs;

    friend class BatchPlaintext;
};

class BatchPlaintext {
public:
    BatchPlaintext(BatchPlaintext &);
    BatchPlaintext(const BatchVector &, Encoder &);
    BatchPlaintext(const BatchCiphertext &, Decryptor &);

    void print(Encoder &encoder);

    const size_t poly_degree;
    const size_t batch_size;
    const size_t bucket_size;

private:
    size_t gap;
    size_t num_batchedpts;

    vector<std::unique_ptr<Plaintext>> batched_pts;

    friend class BatchCiphertext;
    friend class BatchEvaluator;
};

class BatchCiphertext {
public:
    BatchCiphertext(BatchCiphertext &);
    BatchCiphertext(const BatchPlaintext &, Encryptor &);

    const size_t poly_degree;
    const size_t batch_size;
    const size_t bucket_size;

private:
    size_t gap;
    size_t num_batchedcts;

    vector<std::unique_ptr<Ciphertext>> batched_cts;

    friend class BatchPlaintext;
    friend class BatchEvaluator;
};
