#include "batch_utils.h"

BatchCiphertext::BatchCiphertext(
    const BatchPlaintext &batch_plaintext,
    Encryptor &encryptor
):
    poly_degree(batch_plaintext.poly_degree),
    batch_size(batch_plaintext.batch_size),
    bucket_size(batch_plaintext.bucket_size)
{
    gap = batch_plaintext.gap;
    num_batchedcts = batch_plaintext.num_batchedpts;

    for (int i = 0; i < num_batchedcts; i++) {
        auto &bp = batch_plaintext.batched_pts[i];
        batched_cts.emplace_back(
            Ciphertext::create()
        );
        
        encryptor.encrypt_symmetric(*bp, *batched_cts[i]);
    }
}

BatchCiphertext::BatchCiphertext(BatchCiphertext &other):
    poly_degree(other.poly_degree),
    batch_size(other.batch_size),
    bucket_size(other.bucket_size),
    gap(other.gap),
    num_batchedcts(other.num_batchedcts)
{
    for (int i = 0; i < num_batchedcts; i++) {
        batched_cts.emplace_back(
            other.batched_cts[i]->clone()
        );
    }
}
    
