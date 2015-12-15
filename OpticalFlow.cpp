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
        : _maxFeaturesCount(MaxFeaturesCount), _prevPoints(MaxFeaturesCount)
{
    _videoCapture = videoCapture;
}

Point2f OpticalFlow::createIm(const Mat &img, const InputOutputArray img2,
                              const bool drawArrows) {
    std::vector<Point2f> keypoints_save;
    std::vector<Point2f> keypoints = keypoints_save = findFeaturesToTrack(img);

    std::vector<uchar> status;
    std::vector<float> err;
    calcOpticalFlowPyrLK(img, img2, _prevPoints, keypoints, status, err);

    std::vector<Point> arrows(keypoints.size());

    for (int i = 0; i < keypoints.size(); i++) {
        if (status[i] == 0) continue;
        if(drawArrows) arrowedLine(img2, _prevPoints[i], keypoints[i], Scalar(255, 0, 0), 1);

        arrows.push_back(_prevPoints[i] - keypoints[i]);
    }

    _prevPoints = keypoints_save;
    return findDirection(arrows);
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
        Point2f shift2 = createIm(img, img2, true);
        shift += shift2;
        if(hypot(shift.x, shift.y) > 100)
            waitKey(0);
        imshow("Flow", img2);
        img2.copyTo(img);
        if(waitKey(1)>=0) break;
    }
}

Point2f OpticalFlow::findDirection(std::vector<Point> arrows) {
    Point2f p =  std::accumulate(arrows.begin(), arrows.end(), Point(0, 0),
                                 [](const Point &p1, const Point &p2){
        return p1 + p2;
    });

    return p/(int)arrows.size();
}

PanoParts OpticalFlow::process2() {
    using namespace std;
    Size videoSize = Size((int)_videoCapture.get(CAP_PROP_FRAME_WIDTH),
                          (int)_videoCapture.get(CAP_PROP_FRAME_HEIGHT));
    int minSize = min(videoSize.width, videoSize.height);

    Mat img, img2, temp;
    _videoCapture.read(img);

    img.copyTo(temp);
    vector<Mat> imagesToPano(1, temp);
    Point2f shift, fullShift;
    vector<Point2f> imagesShifts(1, shift);
    vector<Point2f> imagesFullShifts(1, fullShift);

    _prevPoints = findFeaturesToTrack(img);
    int i = 1;
    while(_videoCapture.read(img2)){
        Point2f currentShift = createIm(img, img2);
        shift += currentShift;
        fullShift += currentShift;
        /*std::cout<< "("<< i << ", "<< _prevPoints.size() <<")"<< "\t"<<
                currentShift << "\t"
                << shift << "\t"
                << fullShift << std::endl;*/


        if(hypot(shift.x, shift.y) > minSize/6.0){
            Mat temp2;
            img2.copyTo(temp2);
            imagesToPano.push_back(temp2);

            imagesShifts.push_back(shift);
            shift = Point2f(0,0);
            imagesFullShifts.push_back(fullShift);

//            imshow("x", img2);
//            waitKey(0);
        }
        img2.copyTo(img);
        i++;
    }
    imagesToPano.push_back(img);
    imagesShifts.push_back(shift);
    imagesFullShifts.push_back(fullShift);


    return PanoParts(imagesToPano, imagesShifts, imagesFullShifts);
}

std::vector<Point2f> OpticalFlow::findFeaturesToTrack(const Mat &img) {
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);
    _maxFeaturesCount = MaxFeaturesCount;
    std::vector<Point2f> keypoints(_maxFeaturesCount);

    double qualityLevel = 0.3;
    double minDistance = 5;

    goodFeaturesToTrack(gray, keypoints, _maxFeaturesCount, qualityLevel, minDistance);

//    std::cout<< _maxFeaturesCount << std::endl;

    return keypoints;
}
