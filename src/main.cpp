#include <tclap/CmdLine.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "cv_gaussian_blur.hpp"

int main(int argc, char** argv) {
  // Parse arguments
  std::string image_path;
  // wrap everything in a try block.
  // do this every time, because exceptions will be thrown for problems.
  try {
    TCLAP::CmdLine cmd("Fast Gaussian Filter", ' ', "1.0.0");
    TCLAP::ValueArg<std::string> img_arg("i", "image", "path to image file",
                                         true, "", "string");
    cmd.add(img_arg);
    // parse the argv array.
    cmd.parse(argc, argv);
    // get the value parsed by each arg.
    image_path = img_arg.getValue();
  } catch (TCLAP::ArgException& e) {
    // catch any exceptions
    std::cerr << "Error: " << e.error() << " for arg " << e.argId()
              << std::endl;
  }

  // Read the image file
  auto image = cv::imread(image_path);
  if (image.empty()) {
    std::cerr << "Invalid image path: " << image_path << std::endl;
  } else {
    std::cout << "Image path: " << image_path << std::endl;
  }

  CVGaussianBlur cv_filter(image.cols, image.rows, image.channels());
  auto result_cv = cv_filter.measure(image.clone());

  cv::imshow("Blurred by OpenCV", result_cv);
  // cv::imshow("Original", image);
  cv::waitKey(0);
}
