#include "encoder.h"

EncoderSeal::EncoderSeal(std::unique_ptr<HeContextSeal> &context)
{
    encoder = std::make_unique<seal::BatchEncoder>(
        *context->get_raw()
    );
}

std::unique_ptr<seal::BatchEncoder> & EncoderSeal::get_raw()
{
    return encoder;
}

EncoderTroy::EncoderTroy(std::unique_ptr<HeContextTroy> &context)
{
    encoder = std::make_unique<troy::BatchEncoder>(
        context->get_raw()
    );
} 

std::unique_ptr<troy::BatchEncoder> & EncoderTroy::get_raw()
{
    return encoder;
}
