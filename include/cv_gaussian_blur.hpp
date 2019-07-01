#pragma once
#include "base.hpp"

class CVGaussianBlur : public BaseFilter {
 public:
  CVGaussianBlur(const int& width, const int& height, const int& channels,
                 const int& kernel_size = 3);
  void* execute(void* input) override;
};
