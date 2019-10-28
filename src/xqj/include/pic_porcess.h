//
// Created by xqj on 2019/10/26.
//

#ifndef CATKIN_WS_PIC_PORCESS_H
#define CATKIN_WS_PIC_PORCESS_H

#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "light_blobs.h"
#include "constants.h"
using namespace std;
using namespace cv;

class PictureProcess {
public:
    static void erodeAndDilte(Mat &src);

    static void imshowLightBlosForRect(LightBlobs &lightBlobs, String fileName);

    static void imshowRect(int srcWidth,int srcHeight,const vector<RotatedRect> &rotatedRects);
};

#endif //CATKIN_WS_PIC_PORCESS_H
