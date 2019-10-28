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
    VideoCapture videoCapture(0);
    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, SRC_WIDTH);
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, SRC_HEIGHT);
    ArmorFinder armorFinder;
    Mat src;

    while (1) {
        LightBlobs lightBlobs;
        videoCapture >> src;
        imshow("test", src);
        armorFinder.findLightBlobs(src, lightBlobs);
        armorFinder.matchArmorBoxes(src, lightBlobs);
        waitKey(100);
    }
}