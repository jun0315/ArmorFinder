//
// Created by xqj on 2019/10/26.
//

#ifndef CATKIN_WS_FIND_LIGHT_BLOBS_H
#define CATKIN_WS_FIND_LIGHT_BLOBS_H

#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "pic_porcess.h"
#include "light_blobs.h"
#include "armor_finder.h"
#include "constants.h"
#include "show_pic.h"
using namespace std;
using namespace cv;

#define BLOB_BLUE ENEMY_BLUE
#define BLOB_RED ENEMY_RED



//判断是否是一个灯条
bool isVaildLightBlob(const vector<Point> &contour, const RotatedRect &rect);

//旋转矩形的长宽比
double lw_rate(const RotatedRect &rect);

//轮廓面积和其最小外接矩形面积之比
double areaRatio(const vector<Point> &contour, const RotatedRect &rect);

uint8_t get_blob_color(Mat &src,RotatedRect &blobRect);
#endif //CATKIN_WS_FIND_LIGHT_BLOBS_H
