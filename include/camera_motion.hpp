#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

namespace visual_odometry {
class Camera {
 public:
  explicit Camera(cv::Mat K);
  Eigen::Isometry3d getCameraPose(std::vector<cv::KeyPoint> keypoints_1,
                                  std::vector<cv::KeyPoint> keypoints_2,
                                  std::vector<cv::DMatch> matches);

 private:
  void estimatePose();

  Eigen::Isometry3d camera_pose_;
  cv::Mat K_, fundamental_matrix_, essential_matrix_, homography_matrix_;
  std::vector<cv::KeyPoint> keypoints_1_, keypoints_2_;
  std::vector<cv::DMatch> matches_;
};
}  // namespace visual_odometry
