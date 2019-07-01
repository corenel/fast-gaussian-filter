#include "base.hpp"
#include <chrono>
#include <iostream>

BaseFilter::BaseFilter(std::string name, const int& width, const int& height,
                       const int& channels, const int& kernel_size)
    : name_(std::move(name)),
      width_(width),
      height_(height),
      channels_(channels),
      kernel_size_(kernel_size) {}

cv::Mat BaseFilter::measure(const cv::Mat& input, const int& count) {
  // initialize
  void* target = nullptr;
  long long microseconds(0);
  // execute
  for (auto i = 0; i < count; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    target = execute(input.data);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds +=
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
  }
  // print execution time
  std::cout << name_ << ": " << microseconds / count << "ms" << std::endl;
  // convert back to cv::Mat and return
  cv::Mat target_cv(height_, width_, CV_8UC3, target);
  return target_cv;
}
