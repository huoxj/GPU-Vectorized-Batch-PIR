#include "utils.h"

void rotate_vector_in_place(std::vector<uint64_t> &vec, int steps) {
    std::rotate(vec.begin(), vec.end() - steps, vec.end());
}
