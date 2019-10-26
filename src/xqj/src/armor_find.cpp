//
// Created by xqj on 2019/10/26.
//

#include "../include/armor_find.h"

bool ArmorFinder::findLightBlobs(Mat &src) {
    vector<Mat> channels;//通道拆分
    split(src, channels);
    Mat color_channel = channels[2];
    imshow("split_red", color_channel);
    namedWindow("threshold", 1);
    char TrackbarName[50];
    sprintf(TrackbarName, "threshold %d", 255);
    threshold(color_channel, threshold_pic, 245,255, CV_THRESH_BINARY);
    PictureProcess::erodeAndDilte(threshold_pic);
    imshow("process_pic", threshold_pic);
    vector<vector<Point>> light_contours;
    vector<Vec4i> hierarchy;
    findContours(threshold_pic, light_contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
    vector<RotatedRect> rotatedRects;
    for (int i = 0; i < light_contours.size(); i++) {
        //此时没有父轮廓，是最大的轮廓
        if (hierarchy[i][2] == -1) {
            RotatedRect rect = minAreaRect(light_contours[i]);
            if(isVaildLightBlob(light_contours[i],rect)){
                rotatedRects.push_back(rect);
            }
//            printf("contour area:%lf rect area:%lf chufa%lf\n",contourArea(light_contours[i]),rect.size.area(),
//            contourArea(light_contours[i])/rect.size.area() );
        }
    }
    if(rotatedRects.size()>0)
    {
        PictureProcess::imshowRect(src.size().width,src.size().height,rotatedRects);
        return true;
    }
    return false;
}

bool ArmorFinder::isVaildLightBlob(const vector<Point> &contour, const RotatedRect &rect) {
    return (1.2 < lw_rate(rect) && lw_rate(rect) < 10) &&
           ((rect.size.area() < 50 && areaRatio(contour, rect) > 0.4) ||
            rect.size.area() >= 50 && areaRatio(contour, rect) > 0.6);
}

double ArmorFinder::lw_rate(const RotatedRect &rect) {
    return rect.size.height > rect.size.width ?
           rect.size.height / rect.size.width :
           rect.size.width / rect.size.height;
}

double ArmorFinder::areaRatio(const vector<Point> &contour,const RotatedRect & rect){
    return contourArea(contour) / rect.size.area();
}