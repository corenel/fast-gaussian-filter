#include "cv_blur.hpp"
#include <opencv2/opencv.hpp>

CVBlur::CVBlur(const int& width, const int& height,
                               const int& channels, const int& kernel_size)
    : BaseFilter("OpenCV", width, height, channels, kernel_size) {}

void* CVBlur::execute(void* input) {
  cv::Mat source(height_, width_, CV_8UC3, input), target;
  cv::GaussianBlur(source, target, cv::Size(kernel_size_, kernel_size_), 0, 0);
  return target.data;
}
