//
// Created by xqj on 2019/10/26.
//

#ifndef CATKIN_WS_ARMOR_FIND_H
#define CATKIN_WS_ARMOR_FIND_H

#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "pic_porcess.h"

using namespace std;
using namespace cv;

class ArmorFinder {
public:
    bool findLightBlobs(Mat &src);


private:
    Mat threshold_pic;//threshold处理的图片

    //判断是否是一个灯条
    bool isVaildLightBlob(const vector<Point> &contour, const RotatedRect &rect);

    //旋转矩形的长宽比
    double lw_rate(const RotatedRect &rect);

    //轮廓面积和其最小外接矩形面积之比
    double areaRatio(const vector<Point> &contour, const RotatedRect &rect);

};


#endif //CATKIN_WS_ARMOR_FIND_H
