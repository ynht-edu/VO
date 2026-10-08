#include <iostream>
#include <vector>

#include "camera_motion.hpp"
#include "feature_method.hpp"

double fx = 3035;
double fy = 3028;
double cx = 2016;
double cy = 1512;

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "usaage visual_odometry img1 img2" << std::endl;
    return 1;
  }

  cv::Mat_<double> K(3, 3);
  K << fx, 0, cx, 0, fx, cy, 0, 0, 1;
  cv::Mat img_1 = cv::imread(argv[1], cv::IMREAD_COLOR);
  cv::Mat img_2 = cv::imread(argv[2], cv::IMREAD_COLOR);

  // get features
  visual_odometry::Feature feat;
  feat.processImages(img_1, img_2);
  std::vector<cv::KeyPoint> keypoint1, keypoint2;
  std::vector<cv::DMatch> matches;
  keypoint1 = feat.getKeypoints(1);
  keypoint2 = feat.getKeypoints(2);
  matches = feat.getMatchedKeypoints();
  feat.visualizeMatches();

  // initialize camera and get motion
  Eigen::Isometry3d camera_pose;
  visual_odometry::Camera cam(K);
  camera_pose = cam.getCameraPose(keypoint1, keypoint2, matches);
  std::cout << "Camera pose:" << std::endl;
  std::cout << camera_pose.matrix() << std::endl;

  return 0;
}
