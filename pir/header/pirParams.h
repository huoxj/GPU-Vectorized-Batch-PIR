#pragma once

#include <vector>
#include <algorithm>
#include "troy/troy.h"

using namespace troy;
using std::vector;

class PirParams {
public:
    PirParams(size_t poly_modulus_degree,
              size_t batchsize):
        poly_modulus_degree(poly_modulus_degree),
        batchsize(batchsize)
    {
        encryption_params = EncryptionParameters(SchemeType::BFV);
        encryption_params.set_poly_modulus_degree(poly_modulus_degree);
        encryption_params.set_coeff_modulus(CoeffModulus::bfv_default(
                poly_modulus_degree,
                SecurityLevel::Classical128
        ));

        encryption_params.set_plain_modulus(PlainModulus::batching(poly_modulus_degree, 20));

        dimensions = {1024, 1024, 60};
        num_entries = 1;
        std::for_each(dimensions.begin(), dimensions.end(), [this](size_t dim) {
            num_entries *= dim;
        });
    }

    EncryptionParameters encryption_params;

    size_t batchsize;
    vector<size_t> dimensions;
    size_t num_entries;

private:
    size_t poly_modulus_degree;
};
