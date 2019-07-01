#pragma once
#include "base.hpp"

class CVBlur : public BaseFilter {
 public:
  CVBlur(const int& width, const int& height, const int& channels,
                 const int& kernel_size = 3);
  void* execute(void* input) override;
};
