#include <vector>
#include <cstdint>
#include <chrono>
#include <string>
#include <iostream>

void rotate_vector_in_place(std::vector<uint64_t> &vec, int steps);

class TimingClock{
    public:
        TimingClock() : 
            start_(std::chrono::high_resolution_clock::now()),
            duration_(std::chrono::high_resolution_clock::duration::zero()) {}
        void reset() {
            start_ = std::chrono::high_resolution_clock::now();
            duration_ = std::chrono::high_resolution_clock::duration::zero(); 
        }
        void tick() { start_ = std::chrono::high_resolution_clock::now(); }
        void tock() { duration_ += std::chrono::high_resolution_clock::now() - start_; }
        void print(std::string msg) {
            tock();
            std::cout << "Timing for " << msg << ": " <<
                std::chrono::duration_cast<std::chrono::milliseconds>(duration_).count() << " ms" << std::endl;
            reset();
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
        std::chrono::high_resolution_clock::duration duration_;
};
