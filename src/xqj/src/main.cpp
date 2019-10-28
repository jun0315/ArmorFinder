#include <ros/ros.h>
#include <stdlib.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "find_light_blobs.h"
#include "light_blobs.h"

using namespace std;
using namespace cv;

int main() {
    //从摄像头获取图片
//    VIDEOCAPTURE VIDEOCAPTURE(0);
//    VIDEOCAPTURE.SET(CV_CAP_PROP_FRAME_WIDTH, SRC_WIDTH);
//    VIDEOCAPTURE.SET(CV_CAP_PROP_FRAME_HEIGHT, SRC_HEIGHT);
//    ARMORFINDER ARMORFINDER;
//    MAT SRC;
//
//    WHILE (1) {
//        LIGHTBLOBS LIGHTBLOBS;
//        VIDEOCAPTURE >> SRC;
//        IMSHOW("TEST", SRC);
//        ARMORFINDER.FINDLIGHTBLOBS(SRC, LIGHTBLOBS);
//        ARMORFINDER.MATCHARMORBOXES(SRC, LIGHTBLOBS);
//        WAITKEY(100);
//    }

//从相册拿图片
    Mat src = imread("/home/xqj/catkin_ws/src/xqj/image/image1.jpeg", CV_LOAD_IMAGE_UNCHANGED);
    resize(src,src,Size(600,480));
    imshow("src",src);
    LightBlobs lightBlobs;
    ArmorFinder armorFinder;
    armorFinder.findLightBlobs(src, lightBlobs);
    armorFinder.matchArmorBoxes(src, lightBlobs);
    waitKey(0);
}