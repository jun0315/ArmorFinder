//
// Created by xqj on 2019/10/27.
//

#ifndef CATKIN_WS_ARMOR_FINDER_H
#define CATKIN_WS_ARMOR_FINDER_H

#include "find_light_blobs.h"

class  ArmorFinder{
public:
    const uint8_t enemy_color = 0;                                  //敌方颜色
    bool findLightBlobs(Mat &src, LightBlobs &lightBlobs);
    bool matchArmorBoxes(Mat &src,LightBlobs &lightBlobs);
};


#endif //CATKIN_WS_ARMOR_FINDER_H
