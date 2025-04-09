#include "encryption_params.h"

/*
 * Constructor
 */

EncryptionParametersSeal::EncryptionParametersSeal()
{
    ep = std::make_unique<seal::EncryptionParameters>(
        seal::EncryptionParameters(seal::scheme_type::bfv)
    );
}

EncryptionParametersTroy::EncryptionParametersTroy()
{
    ep = std::make_unique<troy::EncryptionParameters>(
        troy::EncryptionParameters(troy::SchemeType::BFV)
    );
}

/*
 * Set Parameters
 */

void EncryptionParametersSeal::setParameters(
    size_t poly_modulus_degree,
    size_t plain_modulus_degree
) {
    ep->set_poly_modulus_degree(poly_modulus_degree);
    ep->set_coeff_modulus(
        seal::CoeffModulus::BFVDefault(
            poly_modulus_degree,
            seal::sec_level_type::tc128
        )
    );
    ep->set_plain_modulus(
        seal::PlainModulus::Batching(poly_modulus_degree, plain_modulus_degree)
    );
}

void EncryptionParametersTroy::setParameters(
    size_t poly_modulus_degree,
    size_t plain_modulus_degree
) {
    ep->set_poly_modulus_degree(poly_modulus_degree);
    ep->set_coeff_modulus(
        troy::CoeffModulus::bfv_default(
            poly_modulus_degree,
            troy::SecurityLevel::Classical128
        )
    );
    ep->set_plain_modulus(
        troy::PlainModulus::batching(poly_modulus_degree, plain_modulus_degree)
    );
}

/*
 * Get Raw
 */

std::unique_ptr<seal::EncryptionParameters> & EncryptionParametersSeal::get_raw()
{
    return ep;
}

std::unique_ptr<troy::EncryptionParameters> & EncryptionParametersTroy::get_raw()
{
    return ep;
}
