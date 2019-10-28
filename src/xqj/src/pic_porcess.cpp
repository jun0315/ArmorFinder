//
// Created by xqj on 2019/10/26.
//

#include "../include/pic_porcess.h"

void PictureProcess::erodeAndDilte(Mat &src) {
    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 5));
    erode(src, src, kernel_erode);

    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(3, 5));
    dilate(src, src, kernel_dilate);

    Mat kernel_dilate2 = getStructuringElement(MORPH_RECT, Size(3, 5));
    dilate(src, src, kernel_dilate2);

    Mat kernel_erode2 = getStructuringElement(MORPH_RECT, Size(3, 5));
    erode(src, src, kernel_erode2);
}

void PictureProcess::imshowLightBlosForRect(LightBlobs &lightBlobs, String fileName) {
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

//void PictureProcess::imshowRect(int srcWidth,int srcHeight,const vector<RotatedRect> &rotatedRects) {
//    Mat result_pic(srcHeight, srcWidth, CV_8UC1, Scalar(0));
//    CvPoint2D32f point[4];
//    Point pt[4];
//    for (int i = 0; i < rotatedRects.size(); i++) {
//        RotatedRect rect = rotatedRects[i];
//        cvBoxPoints(rect, point);
//        for (int j = 0; j < 4; j++) {
//            pt[j].x = (int) point[j].x;
//            pt[j].y = (int) point[j].y;
//        }
//        line(result_pic, pt[0], pt[1], Scalar(255), 1);
//        line(result_pic, pt[1], pt[2], Scalar(255), 1);
//        line(result_pic, pt[2], pt[3], Scalar(255), 1);
//        line(result_pic, pt[3], pt[0], Scalar(255), 1);
//    }
//    imshow("result", result_pic);
//}