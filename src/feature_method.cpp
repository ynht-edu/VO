#include "feature_method.hpp"

// I hereby declare that these works are mine, no LLM
// model writes these
namespace visual_odometry {
Feature::Feature() { initialize(); }

void Feature::processImages(const cv::Mat &img1, const cv::Mat &img2) {
  img1_ = img1;
  img2_ = img2;
  detectOrientedFAST();
  computeBRIEF();
  matchKeypoints();
}

std::vector<cv::KeyPoint> Feature::getKeypoints(int i) {
  if (i == 1) {
    return keypoints_1_;

  } else {
    return keypoints_2_;
  }
}

std::vector<cv::DMatch> Feature::getMatchedKeypoints() { return good_matches_; }

void Feature::visualizeMatches() {
  cv::Mat img_match, img_good_match;
  cv::drawMatches(img1_, keypoints_1_, img2_, keypoints_2_, matches_,
                  img_match);
  cv::drawMatches(img1_, keypoints_1_, img2_, keypoints_2_, good_matches_,
                  img_good_match);
  cv::imshow("all matches", img_match);
  cv::imshow("good matches", img_good_match);
  cv::waitKey(0);
}

void Feature::initialize() {
  detector_ = cv::ORB::create();
  descriptor_ = cv::ORB::create();
  matcher_ = cv::DescriptorMatcher::create("BruteForce-Hamming");
}

void Feature::detectOrientedFAST() {
  detector_->detect(img1_, keypoints_1_);
  detector_->detect(img2_, keypoints_2_);
}

void Feature::computeBRIEF() {
  descriptor_->compute(img1_, keypoints_1_, descriptors_1_);
  descriptor_->compute(img2_, keypoints_2_, descriptors_2_);
}

void Feature::matchKeypoints() {
  matcher_->match(descriptors_1_, descriptors_2_, matches_);

  // sort and remove outliers
  auto min_max =
      std::minmax_element(matches_.begin(), matches_.end(),
                          [](const cv::DMatch &m1, const cv::DMatch &m2) {
                            return m1.distance < m2.distance;
                          });
  double min_dist = min_max.first->distance;

  for (int i = 0; i < descriptors_1_.rows; i++) {
    if (matches_[i].distance <= std::max(2 * min_dist, 30.0)) {
      good_matches_.push_back(matches_[i]);
    }
  }
}

}  // namespace visual_odometry
