//
// Created by xqj on 2019/10/28.
//

#include "show_pic.h"

void imshowLightBlosByRect(LightBlobs lightBlobs,String fileName) {
    Mat result_pic(SRC_HEIGHT, SRC_WIDTH, CV_8UC1, Scalar(0));
    CvPoint2D32f point[4];
    Point pt[4];
    for (int i = 0; i < lightBlobs.size(); i++) {
        RotatedRect rect = lightBlobs[i].rect;
        cvBoxPoints(rect, point);
        for (int j = 0; j < 4; j++) {
            pt[j].x = (int) point[j].x;
            pt[j].y = (int) point[j].y;
        }
        line(result_pic, pt[0], pt[1], Scalar(255), 1);
        line(result_pic, pt[1], pt[2], Scalar(255), 1);
        line(result_pic, pt[2], pt[3], Scalar(255), 1);
        line(result_pic, pt[3], pt[0], Scalar(255), 1);
    }
    imshow(fileName,result_pic);
}
