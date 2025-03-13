#include "server.h"

void Server::processDim1(const MockClient &client, const Ciphertext query0, vector<Ciphertext> &result)
{
    // Dim 1 rotation
    vector<Ciphertext> rotated_query0;
    
    rotated_query0.emplace_back(query0);
    for(int i = 1; i < pirParam.dimensions[0]; i++) {
        
    }
}
