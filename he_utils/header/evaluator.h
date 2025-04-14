#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "hecontext.h"
#include "ciphertext.h"
#include "plaintext.h"
#include "keys.h"

class Evaluator {
public:
    static std::unique_ptr<Evaluator> create(HeContext &);

    virtual void add(Ciphertext &, Ciphertext &) = 0;
    virtual void rotate_rows(Ciphertext &, int32_t steps, PublicKeys &) = 0;
    virtual void multiply_plain(Ciphertext &, Plaintext &) = 0;
    virtual void multiply_cipher(Ciphertext &, Ciphertext &) = 0;
    virtual void relinearize(Ciphertext &, PublicKeys &) = 0;
};

class EvaluatorSeal : public Evaluator {
public:
    EvaluatorSeal(HeContextSeal &);
    seal::Evaluator & get_raw();

    void add(Ciphertext &, Ciphertext &) override;
    void rotate_rows(Ciphertext &, int32_t steps, PublicKeys &) override;
    void multiply_plain(Ciphertext &, Plaintext &) override;
    void multiply_cipher(Ciphertext &, Ciphertext &) override;
    void relinearize(Ciphertext &, PublicKeys &) override;
private:
    std::unique_ptr<seal::Evaluator> evaluator;
};

class EvaluatorTroy : public Evaluator {
public:
    EvaluatorTroy(HeContextTroy &);
    troy::Evaluator & get_raw();

    void add(Ciphertext &, Ciphertext &) override;
    void rotate_rows(Ciphertext &, int32_t steps, PublicKeys &) override;
    void multiply_plain(Ciphertext &, Plaintext &) override;
    void multiply_cipher(Ciphertext &, Ciphertext &) override;
    void relinearize(Ciphertext &, PublicKeys &) override;
private:
    std::unique_ptr<troy::Evaluator> evaluator;
};

