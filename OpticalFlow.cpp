//
// Created by qwad1000 on 02.12.15.
//

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include "OpticalFlow.h"
#include <algorithm>
#include <iostream>

OpticalFlow::OpticalFlow(VideoCapture videoCapture)
        : _maxFeaturesCount(100), _prevPoints(100)
{
    _videoCapture = videoCapture;
}

Point2f OpticalFlow::createIm(InputOutputArray img, InputOutputArray img2) {

    std::vector<Point2f> keypoints(_maxFeaturesCount);
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);

    goodFeaturesToTrack(gray, keypoints, _maxFeaturesCount, 0.5, 1);

    std::vector<uchar> status;
    std::vector<float> err;
    calcOpticalFlowPyrLK(img, img2, _prevPoints, keypoints, status, err);

    std::vector<Point> arrows(keypoints.size());

    for(int i=0; i<keypoints.size(); i++){
        if (status[i] == 0) continue;
        arrowedLine(img2, _prevPoints[i], keypoints[i], Scalar(255,0,0), 1);
        arrows.push_back(_prevPoints[i] - keypoints[i]);
    }

    Point2f shift = findDirection(arrows);

//    _prevPoints = keypoints;
    return shift;
}

void OpticalFlow::process() {
    namedWindow("Flow");

    Mat img, img2;
    _videoCapture.read(img);
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);
    goodFeaturesToTrack(gray, _prevPoints, _maxFeaturesCount, 0.1, 1);
    Point2f shift;
    while(_videoCapture.read(img2)){
        Point2f shift2 = createIm(img, img2);
        shift += shift2;
        if(hypot(shift.x, shift.y) > 100)
            waitKey(0);
        imshow("Flow", img2);
        img2.copyTo(img);
        if(waitKey(1)>=0) break;
    }
}

Point2f OpticalFlow::findDirection(std::vector<Point> arrows) {
    Point2f p =  std::accumulate(arrows.begin(), arrows.end(), Point(0, 0), [](const Point &p1, const Point &p2){
        return p1 + p2;
    });

    return p/(int)arrows.size();
}
