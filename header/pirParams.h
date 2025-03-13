#pragma once

#include <vector>
#include "troy/troy.h"

using namespace troy;
using std::vector;

class PirParams {
public:
    PirParams(size_t poly_modulus_degree,
              size_t plain_modulus,
              size_t batchsize):
        poly_modulus_degree(poly_modulus_degree),
        plain_modulus(plain_modulus),
        batchsize(batchsize)
    {
        encryption_params = EncryptionParameters(SchemeType::BFV);
        encryption_params.set_poly_modulus_degree(poly_modulus_degree);
        encryption_params.set_coeff_modulus(CoeffModulus::bfv_default(
                poly_modulus_degree,
                SecurityLevel::Classical128
        ));
        encryption_params.set_plain_modulus(plain_modulus);

        // TODO: this is just a mock
        dimensions = {128, 128, 5};
    }


    EncryptionParameters encryption_params;

    size_t batchsize;
    vector<size_t> dimensions;

private:
    size_t poly_modulus_degree;
    size_t plain_modulus;
};
