#include "pirParams.h"
#include "mockClient.h"
#include "server.h"
#include "utils.h"
#include "myhe.h"
#include <iostream>

auto HeLib::lib_type = HeLibType::SEAL;

int main() {

    PirParams params(8192, 32);

    MockClient client(params);
    Server server(params);

    server.client_connect(client);

    size_t query_idx = 0;
    auto query = client.query_generation(query_idx);

    auto response = server.generate_response_serialized(query);

    server.client_disconnet();

    auto decrypted_pt = client.decrypt_ciphertext(*response);

    for (int i = 0; i < decrypted_pt.size(); i++) {
        if (decrypted_pt[i] == 0) continue;
        std::cout << decrypted_pt[i] << " ";
    }

    troy::utils::MemoryPool::Destroy();
}
