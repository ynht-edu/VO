#pragma once

#include <opencv2/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
namespace visual_odometry {
class Feature {
 public:
  Feature();
  void processImages(const cv::Mat &img1, const cv::Mat &img2);
  std::vector<cv::KeyPoint> getKeypoints(int i);
  std::vector<cv::DMatch> getMatchedKeypoints();
  void visualizeMatches();

 private:
  void initialize();
  void detectOrientedFAST();
  void computeBRIEF();
  void matchKeypoints();

  std::vector<cv::KeyPoint> keypoints_1_, keypoints_2_;
  cv::Mat descriptors_1_, descriptors_2_;
  cv::Mat img1_, img2_;
  cv::Ptr<cv::FeatureDetector> detector_;
  cv::Ptr<cv::DescriptorExtractor> descriptor_;
  cv::Ptr<cv::DescriptorMatcher> matcher_;
  std::vector<cv::DMatch> matches_, good_matches_;
};

}  // namespace visual_odometry
