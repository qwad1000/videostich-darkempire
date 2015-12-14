//
// Created by qwad1000 on 02.12.15.
//

#ifndef VIDEOSTITCH_OPTICALFLOW_H
#define VIDEOSTITCH_OPTICALFLOW_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

struct PanoParts {
    std::vector<Mat> images;
    std::vector<Point2f> imagesShifts;
    std::vector<Point2f> imageFullShifts;


    PanoParts(const std::vector<Mat> &images,
              const std::vector<Point2f> &imagesShifts,
              const std::vector<Point2f> &imageFullShifts) :
            images(images), imagesShifts(imagesShifts), imageFullShifts(imageFullShifts)
    { }
};

class OpticalFlow {
private:
    VideoCapture _videoCapture;
    int _maxFeaturesCount;
    std::vector<Point2f> _prevPoints;
public:
    OpticalFlow(VideoCapture videoCapture);

    void process();
    PanoParts process2();
    Point2f findDirection(std::vector<Point> arrows);
    Point2f createIm(const Mat &img, const _InputOutputArray &img2,
                     const bool drawArrows = false);

    std::vector<Point2f> findFeaturesToTrack(const Mat &img);
};


#endif //VIDEOSTITCH_OPTICALFLOW_H
