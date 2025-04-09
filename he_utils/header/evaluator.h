#pragma once

#include "seal/seal.h"
#include "troy/troy.h"
#include "hecontext.h"

class Evaluator {
};

class EvaluatorSeal : public Evaluator {
public:
    EvaluatorSeal(std::unique_ptr<HeContextSeal> &);
    std::unique_ptr<seal::Evaluator> & get_raw();
private:
    std::unique_ptr<seal::Evaluator> evaluator;
};

class EvaluatorTroy : public Evaluator {
public:
    EvaluatorTroy(std::unique_ptr<HeContextTroy> &);
    std::unique_ptr<troy::Evaluator> & get_raw();
private:
    std::unique_ptr<troy::Evaluator> evaluator;
};

