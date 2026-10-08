# VO (PCD)

This is a simple visual odometry.

## Dependency

1. Eigen
2. OpenCV
3. CMake

## Setup

1. Clone the repo

```bash
git clone https://github.com/ynht-edu/VO.git
```

2. build

```bash
cd VO && mkdir build && cd build
cmake ..
make
```

## Usage

1. currently the camera intrinsic parameters in simple pinhole parser
   are hardcoded so you have to change it in `src/main.cpp`:
   ```cpp

   ```

// change this
double fx = 3035;
double fy = 3028;
double cx = 2016;
double cy = 1512;

```

```

2. compile

```bash
cd build
make
```

3. run the simple camera motion (yeah still basic)

```bash
./slam_technologies/visual_odometry/visual_odometry img1.jpg img2.jpg
```

## Docs

For the detailed explanation navigate to [docs](./docs/)
