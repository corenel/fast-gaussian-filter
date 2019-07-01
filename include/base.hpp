#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class BaseFilter {
 public:
  BaseFilter(std::string name, const int& width, const int& height,
             const int& channels, const int& kernel_size = 3);
  virtual void* execute(void* input) = 0;
  cv::Mat measure(const cv::Mat& input, const int& count = 1);

  std::string name_;
  int width_;
  int height_;
  int channels_;
  int kernel_size_ = 3;
};
