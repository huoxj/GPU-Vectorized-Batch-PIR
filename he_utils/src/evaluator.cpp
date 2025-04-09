#include "evaluator.h"

EvaluatorSeal::EvaluatorSeal(std::unique_ptr<HeContextSeal> &context) {
    evaluator = std::make_unique<seal::Evaluator>(*context->get_raw());
}

std::unique_ptr<seal::Evaluator> & EvaluatorSeal::get_raw() {
    return evaluator;
}

EvaluatorTroy::EvaluatorTroy(std::unique_ptr<HeContextTroy> &context) {
    evaluator = std::make_unique<troy::Evaluator>(
        context->get_raw()
    );
}

std::unique_ptr<troy::Evaluator> & EvaluatorTroy::get_raw() {
    return evaluator;
}
