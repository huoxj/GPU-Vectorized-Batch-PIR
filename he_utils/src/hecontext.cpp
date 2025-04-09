#include "hecontext.h"

HeContextSeal::HeContextSeal(std::unique_ptr<EncryptionParametersSeal> &ep)
{
    context = std::make_unique<seal::SEALContext>(
        seal::SEALContext(*ep->get_raw())
    );
}

std::shared_ptr<seal::SEALContext> & HeContextSeal::get_raw()
{
    return context;
}

void HeContextSeal::to_device() {}

HeContextTroy::HeContextTroy(std::unique_ptr<EncryptionParametersTroy> &ep):
    context(troy::HeContext::create(*ep->get_raw(), true, troy::SecurityLevel::Classical128))
{

}

std::shared_ptr<troy::HeContext> HeContextTroy::get_raw() {
    return context;
}

void HeContextTroy::to_device() {
    context->to_device_inplace();
}
