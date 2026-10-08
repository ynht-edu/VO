#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "feature_method.hpp"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "usaage visual_odometry img1 img2" << std::endl;
    return 1;
  }
  cv::Mat img_1 = cv::imread(argv[1], cv::IMREAD_COLOR);
  cv::Mat img_2 = cv::imread(argv[2], cv::IMREAD_COLOR);
  visual_odometry::Feature feat;
  feat.processImages(img_1, img_2);
  feat.visualizeMatches();
  return 0;
}
