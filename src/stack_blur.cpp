#include "stack_blur.hpp"
#include <iostream>

StackBlur::StackBlur(const int& width, const int& height, const int& channels,
                     const int& kernel_size, const int& cores, const int& core)
    : BaseFilter("StackBlur", width, height, channels, kernel_size),
      cores_(cores),
      core_(core) {}

void* StackBlur::execute(void* input) {
  int radius = (kernel_size_ - 1) / 2;
  if (radius < 1 || radius > 254) {
    std::cerr << "Invalid radius: " << radius << std::endl;
    return input;
  }

  unsigned int div = (kernel_size_ * 2) + 1;
  auto stack = new unsigned char[div * 4 * cores_];

  if (cores_ == 1) {
    // no multi-threading
    StackBlurJob((unsigned char*)input, width_, height_, radius, 1, 0, 1,
                 stack);
    StackBlurJob((unsigned char*)input, width_, height_, radius, 1, 0, 2,
                 stack);
    return input;
  } else {
    std::cerr << "Not implemented yet." << std::endl;
    return nullptr;
  }
}
