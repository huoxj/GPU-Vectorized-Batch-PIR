#include "pirParams.h"
#include "mockClient.h"
#include "server.h"
#include <iostream>

using namespace troy; 

int main() {

    PirParams params(8192, 1024, 32);

    // MockClient client(params);
    Server server(params);

    troy::utils::MemoryPool::Destroy();
}
