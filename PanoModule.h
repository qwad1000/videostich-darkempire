//
// Created by qwad1000 on 15.12.15.
//

#ifndef VIDEOSTITCH_PANOMODULE_H
#define VIDEOSTITCH_PANOMODULE_H

#include <opencv2/stitching.hpp>
using namespace cv;

class PanoModule {
public:
    const static bool TryUseGPUFlag = false;
    static Mat createPano(std::vector<Mat> &images);
};


#endif //VIDEOSTITCH_PANOMODULE_H
