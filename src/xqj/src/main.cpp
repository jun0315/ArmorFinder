#include <ros/ros.h>
#include <stdlib.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "armor_find.h"

using namespace std;
using namespace cv;

int main() {
    VideoCapture videoCapture(0);
    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 640 );
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 480 );
    ArmorFinder armorFinder;
    Mat src;
    while (1) {
        videoCapture >> src;
        imshow("test", src);
        armorFinder.findLightBlobs(src);
        waitKey(20);
    }
}