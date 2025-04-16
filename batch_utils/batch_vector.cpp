#include "batch_utils.h"
#include <algorithm>


BatchVector::BatchVector(
    const vector<intvec_t> &vectors,
    const size_t poly_degree,
    const size_t batch_size,
    const size_t bucket_size
):
    poly_degree(poly_degree),
    batch_size(batch_size),
    bucket_size(bucket_size)
{
    // param validation
    if (bucket_size & 1) {
        throw std::invalid_argument("Bucket size must be even");
    }
    if (vectors.size() != batch_size) {
        throw std::invalid_argument("Batch size does not match the number of vectors");
    }
    
    gap = poly_degree / 2 / bucket_size;
    num_batchedvecs = (batch_size + 2 * gap - 1) / (2 * gap);

    // batch vectors
    batched_vecs.resize(num_batchedvecs);
    for (int i = 0; i < batch_size; i += 2 * gap) {
        auto &bv = batched_vecs[i / (2 * gap)];
        bv.resize(poly_degree);

        // first row
        for (int j = i; j < std::min(batch_size, i + gap); j++) {
            auto &vec = vectors[j];
            for (int k = 0; k < bucket_size; k++) {
                bv[k * gap + j - i] = vec[k];
            }
        }
        // second row
        for (int j = i + gap; j < std::min(batch_size, i + 2 * gap); j++) {
            auto &vec = vectors[j];
            for (int k = 0; k < bucket_size; k++) {
                bv[k * gap + (poly_degree >> 1) + j - i - gap] = vec[k];
            }
        }
    }

}

void BatchVector::print() {
    std::cout << "Batch vector: " << std::endl;
    std::cout << "gap: " << gap << std::endl;
    std::cout << "num vecs: " << num_batchedvecs << std::endl;
    for (int i = 0; i < num_batchedvecs; i++) {
        std::cout << "Batched vector " << i << ": " << std::endl;
        std::cout << "    ";
        for (int j = 0; j < std::min<int>(poly_degree / 2, 10); j++) {
            std::cout << batched_vecs[i][j] << " ";
        }
        std::cout << std::endl << "    ";
        for (int j = poly_degree / 2; j < std::min<int>(poly_degree, poly_degree / 2 + 10); j++) {
            std::cout << batched_vecs[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
