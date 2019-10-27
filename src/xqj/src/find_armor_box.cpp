//
// Created by xqj on 2019/10/27.
//

#include "find_armor_box.h"

bool isCoupleLight(const LightBlob &light_blob_i, const LightBlob &light_blob_j, uint8_t enemy_color) {
    return light_blob_i.blob_color == enemy_color &&
           light_blob_j.blob_color == enemy_color &&
           lengthRatioJudge(light_blob_i, light_blob_j);


}

bool lengthRatioJudge(const LightBlob &lightBlob_i, const LightBlob &lightBlob_j) {
    return (lightBlob_i.length / lightBlob_i.length < 2.5 &&
            lightBlob_i.length / lightBlob_j.length > 0.4);
}

bool ArmorFinder::matchArmorBoxes(Mat &src, LightBlobs &lightBlobs) {
    Mat result_pic_blank( 480, 640, CV_8UC1, Scalar(0));
    for (int i = 0; i < lightBlobs.size(); i++) {
        for (int j = i + 1; j < lightBlobs.size(); j++) {
            if (!isCoupleLight(lightBlobs.at(i), lightBlobs.at(j), enemy_color)) {
                continue;
            }
            Rect2d rect_i = lightBlobs.at(static_cast<unsigned long>(i)).rect.boundingRect();
            Rect2d rect_j = lightBlobs.at(static_cast<unsigned long>(j)).rect.boundingRect();
            double min_x, max_x, min_y, max_y;
            min_x = fmin(rect_i.x, rect_j.y);
            max_x = fmax(rect_i.x + rect_i.width, rect_j.width);
            min_y = fmin(rect_i.y, rect_j.y);
            max_y = fmax(rect_i.y + rect_i.height, rect_j.y + rect_j.height);
            if (min_x < 0 || max_x > src.cols || min_y < 0 || max_y > src.rows) {
                continue;
            }
            rectangle(result_pic_blank,Point(min_x,min_y),Point(max_x,max_y),Scalar(255));
        }
    }
    imshow("blank",result_pic_blank);
}
