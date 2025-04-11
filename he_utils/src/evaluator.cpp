#include "evaluator.h"

std::unique_ptr<Evaluator> Evaluator::create(HeContext &context)
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<EvaluatorSeal>(
            dynamic_cast<HeContextSeal &>(context)
        );
    case TROY:
        return std::make_unique<EvaluatorTroy>(
            dynamic_cast<HeContextTroy &>(context)
        );
    default:
        throw std::runtime_error("Invalid HE library type");
    }
}

// ==============================
// SEAL Evaluator
// ==============================

EvaluatorSeal::EvaluatorSeal(HeContextSeal &context) {
    evaluator = std::make_unique<seal::Evaluator>(context.get_raw());
}

seal::Evaluator & EvaluatorSeal::get_raw() {
    return *evaluator;
}

void EvaluatorSeal::rotate_rows(Ciphertext &ct, int32_t steps, PublicKeys &pk) {
    auto *ct_seal = dynamic_cast<CiphertextSeal *>(&ct);
    auto *pk_seal = dynamic_cast<PublicKeysSeal *>(&pk);
    if (!ct_seal || !pk_seal) {
        throw std::runtime_error("Invalid Ciphertext or PublicKeys type");
    }

    evaluator->rotate_rows_inplace(
        ct_seal->get_raw(),
        steps,
        pk_seal->getGaloisKeys()
    );
}

// ==============================
// TROY Evaluator
// ==============================

EvaluatorTroy::EvaluatorTroy(HeContextTroy &context) {
    evaluator = std::make_unique<troy::Evaluator>(
        context.get_raw()
    );
}

troy::Evaluator & EvaluatorTroy::get_raw() {
    return *evaluator;
}

void EvaluatorTroy::rotate_rows(Ciphertext &ct, int32_t steps, PublicKeys &pk) {
    auto *ct_troy = dynamic_cast<CiphertextTroy *>(&ct);
    auto *pk_troy = dynamic_cast<PublicKeysTroy *>(&pk);
    if (!ct_troy || !pk_troy) {
        throw std::runtime_error("Invalid Ciphertext or PublicKeys type");
    }

    evaluator->rotate_rows_inplace(
        ct_troy->get_raw(),
        steps,
        pk_troy->getGaloisKeys()
    );
}
