#include "batch_utils.h"

BatchPlaintext::BatchPlaintext(
    const BatchVector &batch_vector,
    Encoder &encoder
):
    poly_degree(batch_vector.poly_degree),
    batch_size(batch_vector.batch_size),
    bucket_size(batch_vector.bucket_size)
{
    gap = batch_vector.gap;
    num_batchedpts = batch_vector.num_batchedvecs;

    for (int i = 0; i < num_batchedpts; i++) {
        auto &bv = batch_vector.batched_vecs[i];
        batched_pts.emplace_back(
            Plaintext::create()
        );
        
        encoder.encode(bv, *batched_pts[i]);
    }
}

BatchPlaintext::BatchPlaintext(
    const BatchCiphertext &batch_ciphertext,
    Decryptor &decryptor
):
    poly_degree(batch_ciphertext.poly_degree),
    batch_size(batch_ciphertext.batch_size),
    bucket_size(batch_ciphertext.bucket_size)
{
    gap = batch_ciphertext.gap;
    num_batchedpts = batch_ciphertext.num_batchedcts;

    for (int i = 0; i < num_batchedpts; i++) {
        auto &bc = batch_ciphertext.batched_cts[i];
        batched_pts.emplace_back(
            Plaintext::create()
        );
        
        decryptor.decrypt(*bc, *batched_pts[i]);
    }
}

BatchPlaintext::BatchPlaintext(BatchPlaintext &other):
    poly_degree(other.poly_degree),
    batch_size(other.batch_size),
    bucket_size(other.bucket_size),
    gap(other.gap),
    num_batchedpts(other.num_batchedpts)
{
    for(int i = 0; i < num_batchedpts; i++) {
        batched_pts.emplace_back(
            other.batched_pts[i]->clone()
        );
    }
}

void BatchPlaintext::print(Encoder &encoder) {
    vector<uint64_t> decoded;
    std::cout << "BatchPlaintext: " << std::endl;
    for (int i = 0; i < num_batchedpts; i++) {
        auto &bv = batched_pts[i];
        encoder.decode(*bv, decoded);
        std::cout << "Batch " << i << ": " << std::endl;
        std::cout << "    ";
        for (int j = 0; j < std::min<int>(poly_degree / 2, 10); j++) {
            std::cout << decoded[j] << " ";
        }
        std::cout << std::endl << "    ";
        for (int j = poly_degree / 2; j < std::min<int>(poly_degree, poly_degree / 2 + 10); j++) {
            std::cout << decoded[j] << " ";
        }
        std::cout << std::endl;
    }
}
