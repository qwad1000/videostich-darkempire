//
// Created by qwad1000 on 15.12.15.
//

#include <opencv2/highgui.hpp>
#include <iostream>
#include "PanoModule.h"

Mat PanoModule::createPano(std::vector<Mat> &images) {

    Ptr<Stitcher> stitcher = createStitcher(TryUseGPUFlag);
    Ptr<WarperCreator> wc = makePtr<SphericalWarper>();
    if(!wc){ return Mat(); }
    stitcher->setWarper(wc);
    Mat out;

    Stitcher::Status status = stitcher->stitch(images, out);

    if(status == Stitcher::Status::OK) {
        namedWindow("Pano",  WINDOW_NORMAL);
        imshow("Pano", out);
        resizeWindow("Pano", 800, 700);
        waitKey(0);
    }else{
        std::cout<< status << "<- stich status";
    }
    return out;
}
