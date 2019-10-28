//
// Created by xqj on 2019/10/27.
//

#include "find_armor_box.h"

bool isCoupleLight(const LightBlob &light_blob_i, const LightBlob &light_blob_j, uint8_t enemy_color) {
    return light_blob_i.blob_color == enemy_color &&
           light_blob_j.blob_color == enemy_color &&
           lengthRatioJudge(light_blob_i, light_blob_j) &&
           lenghtJudge(light_blob_i, light_blob_j) &&
           angelJudge(light_blob_i, light_blob_j);
}

bool lengthRatioJudge(const LightBlob &lightBlob_i, const LightBlob &lightBlob_j) {
    printf("ratio %lf ", lightBlob_i.length / lightBlob_i.length);
    return (lightBlob_i.length / lightBlob_i.length < 1.5 &&
            lightBlob_i.length / lightBlob_j.length > 1 / 1.5);
}

bool lenghtJudge(const LightBlob &lightBlob_i, const LightBlob &lightBlob_j) {
    double side_lenght;
    Point2f center = lightBlob_i.rect.center - lightBlob_j.rect.center;
    side_lenght = sqrt(center.ddot(center));
    return (side_lenght / lightBlob_i.length < 10 && side_lenght / lightBlob_i.length
            && side_lenght / lightBlob_j.length < 10 && side_lenght / lightBlob_j.length);
}

bool angelJudge(const LightBlob &lightBlob_i, const LightBlob &lightBlob_j) {
    float angle_i = lightBlob_i.rect.size.width > lightBlob_i.rect.size.height ? lightBlob_i.rect.angle :
                    lightBlob_i.rect.angle - 90;
    float angle_j = lightBlob_j.rect.size.width > lightBlob_j.rect.size.height ? lightBlob_j.rect.angle :
                    lightBlob_j.rect.angle - 90;
    return abs(angle_i - angle_j) < 20;

}

bool ArmorFinder::matchArmorBoxes(Mat &src, LightBlobs &lightBlobs) {
    Mat result_pic_blank(480, 640, CV_8UC1, Scalar(0));
    LightBlobs lightBlobsTemp;
    lightBlobsTemp.swap(lightBlobs);
    for (int i = 0; i < lightBlobsTemp.size(); i++) {
        for (int j = i + 1; j < lightBlobsTemp.size(); j++) {
            if (!isCoupleLight(lightBlobsTemp.at(i), lightBlobsTemp.at(j), enemy_color)) {
                continue;
            }
            Rect2d rect_i = lightBlobsTemp.at(static_cast<unsigned long>(i)).rect.boundingRect();
            Rect2d rect_j = lightBlobsTemp.at(static_cast<unsigned long>(j)).rect.boundingRect();
            double min_x, max_x, min_y, max_y;
            min_x = fmin(rect_i.x, rect_j.x);
            max_x = fmax(rect_i.x + rect_i.width, rect_j.x + rect_j.width);
            min_y = fmin(rect_i.y, rect_j.y);
            max_y = fmax(rect_i.y + rect_i.height, rect_j.y + rect_j.height);
            if (min_x < 0 || max_x > src.cols || min_y < 0 || max_y > src.rows) {
                continue;
            }
            lightBlobs.push_back(lightBlobsTemp.at(i));
            lightBlobs.push_back(lightBlobsTemp.at(j));
            Point pt[4];
            //顺时针
            pt[0] = Point(min_x, min_y);
            pt[1] = Point(max_x, min_y);
            pt[2] = Point(max_x, max_y);
            pt[3] = Point(min_x, max_y);
            printf("minx %lf,miny %lf, maxx %lf,maxy %lf\n", min_x, min_y, max_x, max_y);
            line(result_pic_blank, pt[0], pt[1], Scalar(255), 1);
            line(result_pic_blank, pt[1], pt[2], Scalar(255), 1);
            line(result_pic_blank, pt[2], pt[3], Scalar(255), 1);
            line(result_pic_blank, pt[3], pt[0], Scalar(255), 1);
        }
    }
    imshow("blank", result_pic_blank);
    PictureProcess::imshowLightBlosForRect(lightBlobs, "select blob");
}
