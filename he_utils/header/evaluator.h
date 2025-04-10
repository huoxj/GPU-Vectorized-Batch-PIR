#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "utils.h"
#include "hecontext.h"

class Evaluator {
public:
    static std::unique_ptr<Evaluator> create(HeContext &);
};

class EvaluatorSeal : public Evaluator {
public:
    EvaluatorSeal(HeContextSeal &);
    seal::Evaluator & get_raw();
private:
    std::unique_ptr<seal::Evaluator> evaluator;
};

class EvaluatorTroy : public Evaluator {
public:
    EvaluatorTroy(HeContextTroy &);
    troy::Evaluator & get_raw();
private:
    std::unique_ptr<troy::Evaluator> evaluator;
};

