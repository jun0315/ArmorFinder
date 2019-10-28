//
// Created by xqj on 2019/10/26.
//

#include "find_light_blobs.h"

bool ArmorFinder::findLightBlobs(Mat &src, LightBlobs &lightBlobs) {
    vector<Mat> channels;//通道拆分
    split(src, channels);
    Mat color_channel = channels[2];
    Mat threshold_pic;
    imshow("split_red", color_channel);
    namedWindow("threshold", 1);
    char TrackbarName[50];
    sprintf(TrackbarName, "threshold %d", 255);
    threshold(color_channel, threshold_pic, 245, 255, CV_THRESH_BINARY);
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
            if (isVaildLightBlob(light_contours[i], rect)) {
                rotatedRects.push_back(rect);
                lightBlobs.emplace_back(rect, areaRatio(light_contours[i], rect), get_blob_color(src, rect));
            }
        }
    }
    if (rotatedRects.size() > 0) {
        PictureProcess::imshowLightBlosForRect(lightBlobs, "find lightblobs");
        return true;
    }
    return false;
}

bool isVaildLightBlob(const vector<Point> &contour, const RotatedRect &rect) {
    return (1.2 < lw_rate(rect) && lw_rate(rect) < 10) &&
           ((rect.size.area() < 50 && areaRatio(contour, rect) > 0.4) ||
            rect.size.area() >= 50 && areaRatio(contour, rect) > 0.6);
}

double lw_rate(const RotatedRect &rect) {
    return rect.size.height > rect.size.width ?
           rect.size.height / rect.size.width :
           rect.size.width / rect.size.height;
}

double areaRatio(const vector<Point> &contour, const RotatedRect &rect) {
    return contourArea(contour) / rect.size.area();
}

// 判断灯条颜色(此函数可以有性能优化).
// TODO
uint8_t get_blob_color(Mat &src, RotatedRect &blobPos) {
    auto region = blobPos.boundingRect();
    region.x -= fmax(3, region.width * 0.1);
    region.y -= fmax(3, region.height * 0.05);
    region.width += 2 * fmax(3, region.width * 0.1);
    region.height += 2 * fmax(3, region.height * 0.05);
    region &= cv::Rect(0, 0, src.cols, src.rows);
    cv::Mat roi = src(region);
    int red_cnt = 0, blue_cnt = 0;
    for (int row = 0; row < roi.rows; row++) {
        for (int col = 0; col < roi.cols; col++) {
            red_cnt += roi.at<cv::Vec3b>(row, col)[2];
            blue_cnt += roi.at<cv::Vec3b>(row, col)[0];
        }
    }
    if (red_cnt > blue_cnt) {
        return BLOB_RED;
    } else {
        return BLOB_BLUE;
    }
}