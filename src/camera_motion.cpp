#include "camera_motion.hpp"

#include <eigen3/Eigen/src/Geometry/Transform.h>

namespace visual_odometry {

Camera::Camera(cv::Mat K) { K_ = K; }

Eigen::Isometry3d Camera::getCameraPose(std::vector<cv::KeyPoint> keypoints_1,
                                        std::vector<cv::KeyPoint> keypoints_2,
                                        std::vector<cv::DMatch> matches) {
  keypoints_1_ = keypoints_1;
  keypoints_2_ = keypoints_2;
  matches_ = matches;
  estimatePose();
  return camera_pose_;
}

void Camera::estimatePose() {
  // convert matches to vector
  std::vector<cv::Point2f> points1, points2;
  for (int i = 0; i < (int)matches_.size(); i++) {
    points1.push_back(keypoints_1_[matches_[i].queryIdx].pt);
    points2.push_back(keypoints_2_[matches_[i].queryIdx].pt);
  }

  // fundamental matrix
  fundamental_matrix_ = cv::findFundamentalMat(points1, points2, cv::FM_8POINT);

  // essential matrix
  essential_matrix_ = cv::findEssentialMat(points1, points2, K_);

  // hommography matrix
  homography_matrix_ = cv::findHomography(points1, points2, cv::RANSAC, 3);

  // recover pose from the essential matrix
  cv::Mat R, t;
  Eigen::Matrix3d R_eigen;
  Eigen::Vector3d t_eigen;
  cv::recoverPose(essential_matrix_, points1, points2, R, t, K_);
  cv::cv2eigen(R, R_eigen);
  cv::cv2eigen(t, t_eigen);
  camera_pose_ = Eigen::Isometry3d::Identity();
  camera_pose_.translation() = t_eigen;
  camera_pose_.linear() = R_eigen;
}

}  // namespace visual_odometry
