//
// Created by qwad1000 on 02.12.15.
//

#ifndef VIDEOSTITCH_OPTICALFLOW_H
#define VIDEOSTITCH_OPTICALFLOW_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

class OpticalFlow {
private:
    VideoCapture _videoCapture;
    int _maxFeaturesCount;
    std::vector<Point2f> _prevPoints;
public:
    OpticalFlow(VideoCapture videoCapture);

    void process();
    Point2f findDirection(std::vector<Point> arrows);
    Point2f createIm(InputOutputArray img, InputOutputArray img2);
};


#endif //VIDEOSTITCH_OPTICALFLOW_H
