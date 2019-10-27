//
// Created by xqj on 2019/10/27.
//

#ifndef CATKIN_WS_FIND_ARMOR_BOX_H
#define CATKIN_WS_FIND_ARMOR_BOX_H
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "armor_finder.h"
using namespace std;
using namespace cv;

//判断两个的灯条长度比是否满足配对条件
bool lengthRatioJudge(const LightBlob & lightBlob_i , const LightBlob &lightBlob_j);

bool isCoupleLight(const LightBlob &lightBlob_i, const LightBlob &lightBlob_j,uint8_t enemy_color);

#endif //CATKIN_WS_FIND_ARMOR_BOX_H
