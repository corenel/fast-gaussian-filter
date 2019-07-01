#include "fastest_blur.hpp"

FastestBlur::FastestBlur(const int& width, const int& height,
                         const int& channels, const int& kernel_size)
    : BaseFilter("Fastest", width, height, channels, kernel_size) {}

void* FastestBlur::execute(void* source) {
  auto target = new unsigned char[width_ * height_ * channels_];

  int radius = (kernel_size_ - 1) / 2;
  int* bxs = boxes_for_gauss(radius, 3);
  box_blur((unsigned char*)source, target, width_, height_, (bxs[0] - 1) / 2);
  box_blur(target, (unsigned char*)source, width_, height_, (bxs[1] - 1) / 2);
  box_blur((unsigned char*)source, target, width_, height_, (bxs[2] - 1) / 2);

  free(bxs);
  return source;
}
