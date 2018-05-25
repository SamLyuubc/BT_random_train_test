cmake_minimum_required (VERSION 2.6)

cmake_policy(SET CMP0015 NEW)

project (BT_random_leaning)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")


# The version number
set (BT_random_leaning_VERSION_MAJOR 1)
set (BT_random_leaning_VERSION_MINOR 0)
find_package( OpenCV REQUIRED )
set(OpenCV_DIR /home/automationlab/workspace/opencv-3.2.0)
include_directories ( ${OpenCV_DIR}/include )
link_directories ( ${OpenCV_DIR}/build/lib )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


# link Eigen
set(Eigen_DIR /usr/include/eigen3)
include_directories (${Eigen_DIR})


# link Flann

#set(FLANN_DIR /home/ial/workspace/flann-1.8.4-src)
#include_directories ( ${FLANN_DIR}/src/cpp)
#link_directories ( ${FLANN_DIR}/build/lib)
set(FLANN_DIR /home/automationlab/workspace/flann-1.8.4-src)
include_directories ( ${FLANN_DIR}/include)
link_directories ( ${FLANN_DIR}/build/lib)


# add source files
include_directories (./src ./src/DTR ./src/DTC ./src/BTDTR ./src/RF_BT_RND ./src/RND ./src/opencv_util ./src/Walsh_Hadamard ./src/opencv_util/Kabsch)

set(TRAIN_SRC ./src/main_bt_rnd_train.cpp)
set(TEST_SRC ./src/main_bt_rnd_test.cpp)
set(POSE_SRC ./src/main_bt_pose_estimation.cpp)
set(ERROR_SRC ./src/main_pose_error.cpp)

# .cpp in src
set(SOURCE_CODE1 ./src/DTUtil_IO.cpp ./src/ParameterParser.cpp ./src/yael_io.cpp)

# .cpp in opencv_util
set(SOURCE_CODE_OPENCV_UTIL ./src/opencv_util/cvxWalshHadamard.cpp ./src/opencv_util/ms7ScenesUtil.cpp ./src/opencv_util/cvxUtil.cpp ./src/opencv_util/cvxIO.cpp ./src/opencv_util/cvxPoseEstimation.cpp ./src/opencv_util/cvxCalib3d.cpp)

# .cpp in Kabsch
set(SOURCE_CODE_KABSCH ./src/opencv_util/Kabsch/Kabsch.cpp)

# DTR decision tree for regression
set(SOURCE_CODE_DTR ./src/DTR/DTRNode.cpp ./src/DTR/DTRTree.cpp ./src/DTR/DTRUtil.cpp ./src/DTR/DTRegressor.cpp ./src/DTR/DTRegressorBuilder.cpp)

# DTC decision tree for classification
set(SOURCE_CODE_DTC ./src/DTC/DTCNode.cpp ./src/DTC/DTCTree.cpp ./src/DTC/DTCUtil.cpp ./src/DTC/DTClassifier.cpp ./src/DTC/DTClassifierBuilder.cpp)

# BTDTR
set(SOURCE_CODE_BTDTR ./src/BTDTR/BTDTRUtil.cpp)

# Walsh hadamard feature
set(SOURCE_CODE_WH ./src/Walsh_Hadamard/defs.c ./src/Walsh_Hadamard/image.c ./src/Walsh_Hadamard/matrix.c ./src/Walsh_Hadamard/wh.c)

# RF_BT_RND backtracking random feature + WH feature
set(SOURCE_CODE_BT_RND ./src/RF_BT_RND/bt_rnd_util.cpp ./src/RF_BT_RND/bt_rnd_tree.cpp ./src/RF_BT_RND/bt_rnd_tree_node.cpp ./src/RF_BT_RND/bt_rnd_regressor.cpp ./src/RF_BT_RND/bt_rnd_regressor_builder.cpp)

# RND random number generator
set(SOURCE_CODE_RND ./src/RND/vnl_random.cxx ./src/RND/DTRandom.cpp)

set(SOURCE_CODE ${SOURCE_CODE1} ${SOURCE_CODE_OPENCV_UTIL} ${SOURCE_CODE_KABSCH} ${SOURCE_CODE_DTR} ${SOURCE_CODE_RND} ${SOURCE_CODE_DTC} ${SOURCE_CODE_BTDTR} ${SOURCE_CODE_BT_RND} ${SOURCE_CODE_WH})

# add the executable
add_executable(BT_random_train ${TRAIN_SRC} ${SOURCE_CODE})
add_executable(BT_random_test ${TEST_SRC} ${SOURCE_CODE})
add_executable(BT_random_pose_estimation ${POSE_SRC} ${SOURCE_CODE})
add_executable(BT_random_pose_error ${ERROR_SRC} ${SOURCE_CODE})


target_link_libraries(BT_random_train opencv_core opencv_highgui opencv_imgproc opencv_calib3d flann)
target_link_libraries(BT_random_test opencv_core opencv_highgui opencv_imgproc opencv_calib3d flann)
target_link_libraries(BT_random_pose_estimation opencv_core opencv_highgui opencv_imgproc opencv_calib3d flann)
target_link_libraries(BT_random_pose_error opencv_core opencv_highgui opencv_imgproc opencv_calib3d flann)














