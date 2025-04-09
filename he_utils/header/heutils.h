#pragma once

#include <string>

#include "encryption_params.h"

enum HeLibType {
    SEAL = 0,
    TROY
};

class EncryptionFactory {
public:

    EncryptionFactory(HeLibType lib_type): lib_type(lib_type) {}

    std::unique_ptr<EncryptionParameters> make_encryption_parameters()
    {
        switch (lib_type) {
        case SEAL:
            return std::make_unique<EncryptionParametersSeal>(
                EncryptionParametersSeal()
            );
        case TROY:
            return std::make_unique<EncryptionParametersTroy>(
                EncryptionParametersTroy()
            );
        }
    }

private:
    HeLibType lib_type;
};
