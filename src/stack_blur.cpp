#include "stack_blur.hpp"
#include <iostream>
#include <thread>
#include <vector>

StackBlur::StackBlur(const int& width, const int& height, const int& channels,
                     const int& kernel_size, const int& cores)
    : BaseFilter("StackBlur", width, height, channels, kernel_size),
      cores_(cores) {}

void* StackBlur::execute(void* input) {
  int radius = (kernel_size_ - 1) / 2;
  if (radius < 1 || radius > 254) {
    std::cerr << "Invalid radius: " << radius << std::endl;
    return input;
  }

  unsigned int div = (kernel_size_ * 2) + 1;
  auto stack = new unsigned char[div * 3 * cores_];

  if (cores_ == 1) {
    // no multi-threading
    StackBlurJob((unsigned char*)input, width_, height_, radius, 1, 0, 1,
                 stack);
    StackBlurJob((unsigned char*)input, width_, height_, radius, 1, 0, 2,
                 stack);
  } else {
    std::vector<std::thread*> workers(cores_);
    for (int i = 0; i < cores_; i++) {
      workers[i] = new std::thread(StackBlurJob, (unsigned char*)input, width_,
                                   height_, radius, cores_, i, 1, stack);
    }
    for (int i = 0; i < cores_; i++) {
      workers[i]->join();
    }

    for (int i = 0; i < cores_; i++) {
      workers[i] = new std::thread(StackBlurJob, (unsigned char*)input, width_,
                                   height_, radius, cores_, i, 2, stack);
    }
    for (int i = 0; i < cores_; i++) {
      workers[i]->join();
    }
  }

  return input;
}
