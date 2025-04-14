#include "utils.h"

void rotate_vector_in_place(std::vector<uint64_t> &vec, int steps) {
    std::rotate(vec.begin(), vec.end() - steps, vec.end());
}

void print_vec(const std::vector<uint64_t> &vec, size_t n, std::string msg) {
    std::cout << msg << ": ";
    for (size_t i = 0; i < n && i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}
