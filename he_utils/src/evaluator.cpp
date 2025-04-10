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

EvaluatorSeal::EvaluatorSeal(HeContextSeal &context) {
    evaluator = std::make_unique<seal::Evaluator>(context.get_raw());
}

seal::Evaluator & EvaluatorSeal::get_raw() {
    return *evaluator;
}

EvaluatorTroy::EvaluatorTroy(HeContextTroy &context) {
    evaluator = std::make_unique<troy::Evaluator>(
        context.get_raw()
    );
}

troy::Evaluator & EvaluatorTroy::get_raw() {
    return *evaluator;
}
