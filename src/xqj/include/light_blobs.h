//
// Created by xqj on 2019/10/27.
//

#ifndef CATKIN_WS_LIGHT_BLOBS_H
#define CATKIN_WS_LIGHT_BLOBS_H
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace std;
using namespace cv;

//灯条类
class  LightBlob{
public:
   RotatedRect rect;//灯条位置
   double area_ratio;//轮廓面积和其最小外接矩形面积之比
   double length;//灯条长度
   uint8_t blob_color;//灯条颜色
   LightBlob(RotatedRect &rotatedRect,double ratio,uint8_t color):rect(rotatedRect),area_ratio(ratio),blob_color(color){
       length = max(rotatedRect.size.height,rotatedRect.size.width);
   };

   LightBlob()  = default;
};

typedef vector<LightBlob> LightBlobs;

#endif //CATKIN_WS_LIGHT_BLOBS_H
