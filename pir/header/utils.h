#pragma once

#include <vector>
#include <cstdint>
#include <chrono>
#include <string>
#include <iostream>
#include "myhe.h"

#define TIMING
#define DEBUG

void rotate_vector_in_place(std::vector<uint64_t> &vec, int steps);

void print_vec(const std::vector<uint64_t> &vec, size_t n, std::string msg = "");

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
            std::cout << "[Timing] time for " << msg << ": " <<
                std::chrono::duration_cast<std::chrono::milliseconds>(duration_).count() << " ms" << std::endl;
            reset();
        }
        std::string getmsg(std::string msg) {
            tock();
            std::string result = "[Timing] time for " + msg + ": " +
                std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(duration_).count()) + " ms";
            reset();
            return result;
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
        std::chrono::high_resolution_clock::duration duration_;
};
