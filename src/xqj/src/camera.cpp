//
// Created by xqj on 2019/10/28.
//

#include "camera.h"

Mat getPicFromCamera() {
    VideoCapture videoCapture(0);
    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, SRC_WIDTH);
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, SRC_HEIGHT);
    Mat src;
    videoCapture >> src;
    return src;
}
