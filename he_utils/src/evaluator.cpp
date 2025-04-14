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

void EvaluatorSeal::add(Ciphertext &dest, Ciphertext &src) {
    auto *dest_seal = dynamic_cast<CiphertextSeal *>(&dest);
    auto *src_seal = dynamic_cast<CiphertextSeal *>(&src);
    if (!dest_seal || !src_seal) {
        throw std::runtime_error("Invalid Ciphertext type");
    }

    evaluator->add_inplace(
        dest_seal->get_raw(),
        src_seal->get_raw()
    );
}

void EvaluatorSeal::rotate_rows(Ciphertext &ct, int32_t steps, PublicKeys &pk) {
    auto *ct_seal = dynamic_cast<CiphertextSeal *>(&ct);
    auto *pk_seal = dynamic_cast<PublicKeysSeal *>(&pk);
    if (!ct_seal) {
        throw std::runtime_error("Invalid Ciphertext type in rotate_rows");
    }
    if (!pk_seal) {
        throw std::runtime_error("Invalid PublicKeys type in rotate_rows");
    }

    evaluator->rotate_rows_inplace(
        ct_seal->get_raw(),
        steps,
        pk_seal->getGaloisKeys()
    );
}

void EvaluatorSeal::multiply_plain(Ciphertext &ct, Plaintext &pt) {
    auto *ct_seal = dynamic_cast<CiphertextSeal *>(&ct);
    auto *pt_seal = dynamic_cast<PlaintextSeal *>(&pt);
    if (!ct_seal) {
        throw std::runtime_error("Invalid Ciphertext type in multiply_plain");
    }
    if (!pt_seal) {
        throw std::runtime_error("Invalid Plaintext type in multiply_plain");
    }

    evaluator->multiply_plain_inplace(
        ct_seal->get_raw(),
        pt_seal->get_raw()
    );
}

void EvaluatorSeal::multiply_cipher(Ciphertext &dest, Ciphertext &src) {
    auto *dest_seal = dynamic_cast<CiphertextSeal *>(&dest);
    auto *src_seal = dynamic_cast<CiphertextSeal *>(&src);
    if (!dest_seal) {
        throw std::runtime_error("Invalid dest Ciphertext type in multiply_cipher");
    }
    if (!src_seal) {
        throw std::runtime_error("Invalid src Ciphertext type in multiply_cipher");
    }

    evaluator->multiply_inplace(
        dest_seal->get_raw(),
        src_seal->get_raw()
    );
}

void EvaluatorSeal::relinearize(Ciphertext &ct, PublicKeys &pk) {
    auto *ct_seal = dynamic_cast<CiphertextSeal *>(&ct);
    auto *pk_seal = dynamic_cast<PublicKeysSeal *>(&pk);
    if (!ct_seal) {
        throw std::runtime_error("Invalid Ciphertext type in relinearize");
    }
    if (!pk_seal) {
        throw std::runtime_error("Invalid PublicKeys type in relinearize");
    }

    evaluator->relinearize_inplace(
        ct_seal->get_raw(),
        pk_seal->getRelinKeys()
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

void EvaluatorTroy::add(Ciphertext &dest, Ciphertext &src) {
    auto *dest_troy = dynamic_cast<CiphertextTroy *>(&dest);
    auto *src_troy = dynamic_cast<CiphertextTroy *>(&src);
    if (!dest_troy || !src_troy) {
        throw std::runtime_error("Invalid Ciphertext type in add");
    }

    evaluator->add_inplace(
        dest_troy->get_raw(),
        src_troy->get_raw()
    );
}

void EvaluatorTroy::rotate_rows(Ciphertext &ct, int32_t steps, PublicKeys &pk) {
    auto *ct_troy = dynamic_cast<CiphertextTroy *>(&ct);
    auto *pk_troy = dynamic_cast<PublicKeysTroy *>(&pk);
    if (!ct_troy) {
        throw std::runtime_error("Invalid Ciphertext type in rotate_rows");
    }
    if (!pk_troy) {
        throw std::runtime_error("Invalid PublicKeys type in rotate_rows");
    }

    evaluator->rotate_rows_inplace(
        ct_troy->get_raw(),
        steps,
        pk_troy->getGaloisKeys()
    );
}

void EvaluatorTroy::multiply_plain(Ciphertext &ct, Plaintext &pt) {
    auto *ct_troy = dynamic_cast<CiphertextTroy *>(&ct);
    auto *pt_troy = dynamic_cast<PlaintextTroy *>(&pt);
    if (!ct_troy) {
        throw std::runtime_error("Invalid Ciphertext type in multiply_plain");
    }
    if (!pt_troy) {
        throw std::runtime_error("Invalid Plaintext type in multiply_plain");
    }

    evaluator->multiply_plain_inplace(
        ct_troy->get_raw(),
        pt_troy->get_raw()
    );
}

void EvaluatorTroy::multiply_cipher(Ciphertext &dest, Ciphertext &src) {
    auto *dest_troy = dynamic_cast<CiphertextTroy *>(&dest);
    auto *src_troy = dynamic_cast<CiphertextTroy *>(&src);
    if (!dest_troy || !src_troy) {
        throw std::runtime_error("Invalid Ciphertext type in multiply_cipher");
    }

    evaluator->multiply_inplace(
        dest_troy->get_raw(),
        src_troy->get_raw()
    );
}

void EvaluatorTroy::relinearize(Ciphertext &ct, PublicKeys &pk) {
    auto *ct_troy = dynamic_cast<CiphertextTroy *>(&ct);
    auto *pk_troy = dynamic_cast<PublicKeysTroy *>(&pk);
    if (!ct_troy) {
        throw std::runtime_error("Invalid Ciphertext type in relinearize");
    }
    if (!pk_troy) {
        throw std::runtime_error("Invalid PublicKeys type in relinearize");
    }

    evaluator->relinearize_inplace(
        ct_troy->get_raw(),
        pk_troy->getRelinKeys()
    );
}
