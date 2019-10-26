#include <ros/ros.h>
#include <stdlib.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "armor_find.h"

using namespace std;
using namespace cv;

//#define THRESHOLD_WINDOW "threshold"
//#define PIC_WIDTH 640
//#define PIC_HEIGHT 480
//const int g_light_threshold_max = 255;
//int g_light_threshold = 254;
//
//Mat color_channel;
//Mat threshold_pic;
//
//void findLightBlobs(Mat src);
//
//void on_Trackbar(int, void *);
//
//void imageProcess(Mat &src);
//
//void imshowRect(const vector<RotatedRect> &rotatedRects);
//
////判断是否是一个灯条
//bool isVaildLightBlob(const vector<Point> &contour, const RotatedRect &rect);
//
////旋转矩形的长宽比
//double lw_rate(const RotatedRect &rect);
//
////轮廓面积和其最小外接矩形面积之比
//double areaRatio(const vector<Point> &contour, const RotatedRect &rect);
//
//int main() {
//    VideoCapture videoCapture(0);
//    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, PIC_WIDTH);
//    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, PIC_HEIGHT);
//    Mat src;
//    while (1) {
//        videoCapture >> src;
//        imshow("test", src);
//        findLightBlobs(src);
//        waitKey(20);
//    }
//}
//
//void findLightBlobs(Mat src) {
//    vector<Mat> channels;//通道拆分
//    split(src, channels);
//    color_channel = channels[2];
//    imshow("split_red", color_channel);
//    namedWindow(THRESHOLD_WINDOW, 1);
//    char TrackbarName[50];
//    sprintf(TrackbarName, "threshold %d", g_light_threshold_max);
//    createTrackbar(TrackbarName, THRESHOLD_WINDOW, &g_light_threshold, g_light_threshold_max, on_Trackbar);
//    on_Trackbar(g_light_threshold, 0);
//    imageProcess(threshold_pic);
//    imshow("process_pic", threshold_pic);
//    vector<vector<Point>> light_contours;
//    vector<Vec4i> hierarchy;
//    findContours(threshold_pic, light_contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
//    vector<RotatedRect> rotatedRects;
//    for (int i = 0; i < light_contours.size(); i++) {
//        //此时没有父轮廓，是最大的轮廓
//        if (hierarchy[i][2] == -1) {
//            RotatedRect rect = minAreaRect(light_contours[i]);
//            if(isVaildLightBlob(light_contours[i],rect)){
//                rotatedRects.push_back(rect);
//            }
////            printf("contour area:%lf rect area:%lf chufa%lf\n",contourArea(light_contours[i]),rect.size.area(),
////            contourArea(light_contours[i])/rect.size.area() );
//        }
//    }
//    imshowRect(rotatedRects);
//}
//
//void on_Trackbar(int, void *) {
//    threshold_pic;
//    threshold(color_channel, threshold_pic, g_light_threshold, g_light_threshold_max, CV_THRESH_BINARY);
//    imshow(THRESHOLD_WINDOW, threshold_pic);
//}
//
//void imageProcess(Mat &src) {
//    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 5));
//    erode(src, src, kernel_erode);
//
//    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(3, 5));
//    dilate(src, src, kernel_dilate);
//
//    Mat kernel_dilate2 = getStructuringElement(MORPH_RECT, Size(3, 5));
//    dilate(src, src, kernel_dilate2);
//
//    Mat kernel_erode2 = getStructuringElement(MORPH_RECT, Size(3, 5));
//    erode(src, src, kernel_erode2);
//
//}
//
//void imshowRect(const vector<RotatedRect> &rotatedRects) {
//    Mat result_pic(PIC_HEIGHT, PIC_WIDTH, CV_8UC1, Scalar(0));
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
//
//double lw_rate(const RotatedRect &rect) {
//    return rect.size.height > rect.size.width ?
//            rect.size.height / rect.size.width :
//            rect.size.width / rect.size.height;
//}
//
//double areaRatio(const vector<Point> &contour,const RotatedRect & rect){
//    return contourArea(contour) / rect.size.area();
//}
//
//bool isVaildLightBlob(const vector<Point> &contour, const RotatedRect &rect) {
//    return (1.2 < lw_rate(rect) && lw_rate(rect) < 10) &&
//           ((rect.size.area() < 50 && areaRatio(contour, rect) > 0.4) ||
//            rect.size.area() >= 50 && areaRatio(contour, rect) > 0.6);
//}
int main() {
    VideoCapture videoCapture(0);
    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 640 );
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 480 );
    ArmorFinder armorFinder;
    Mat src;
    while (1) {
        videoCapture >> src;
        imshow("test", src);
        armorFinder.findLightBlobs(src);
        waitKey(20);
    }
}