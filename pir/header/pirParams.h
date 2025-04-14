#pragma once

#include <vector>
#include <algorithm>
#include "myhe.h"

using std::vector;

class PirParams {
public:
    PirParams(size_t poly_modulus_degree,
              size_t batchsize):
        poly_modulus_degree(poly_modulus_degree),
        batchsize(batchsize)
    {
        encryption_params = EncryptionParameters::create();
        encryption_params->setParameters(poly_modulus_degree, 20);

        dimensions = {128, 128, 64};
        // dimensions = {32, 32, 5};
        num_entries = 1;
        std::for_each(dimensions.begin(), dimensions.end(), [this](size_t dim) {
            num_entries *= dim;
        });
    }

    std::unique_ptr<EncryptionParameters> encryption_params;

    size_t batchsize;
    vector<size_t> dimensions;
    size_t num_entries;

private:
    size_t poly_modulus_degree;
};
