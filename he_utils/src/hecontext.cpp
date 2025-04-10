#include "hecontext.h"

std::unique_ptr<HeContext> HeContext::create(EncryptionParameters &ep)
{
    switch (HeLib::lib_type) {
    case SEAL:
        return std::make_unique<HeContextSeal>(
            dynamic_cast<EncryptionParametersSeal &>(ep)
        );
    case TROY:
        return std::make_unique<HeContextTroy>(
            dynamic_cast<EncryptionParametersTroy &>(ep)
        );
    default:
        throw std::runtime_error("Invalid HE library type");
    }
}

HeContextSeal::HeContextSeal(EncryptionParametersSeal &ep)
{
    context = std::make_unique<seal::SEALContext>(
        seal::SEALContext(ep.get_raw())
    );
}

seal::SEALContext & HeContextSeal::get_raw()
{
    return *context;
}

void HeContextSeal::to_device() {}

HeContextTroy::HeContextTroy(EncryptionParametersTroy &ep):
    context(troy::HeContext::create(ep.get_raw(), true, troy::SecurityLevel::Classical128))
{

}

std::shared_ptr<troy::HeContext> & HeContextTroy::get_raw() {
    return context;
}

void HeContextTroy::to_device() {
    context->to_device_inplace();
}
