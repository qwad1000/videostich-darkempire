/* --Sparse Optical Flow Demo Program--
 * Written by David Stavens (david.stavens@ai.stanford.edu)
 */
#include <stdio.h>
#include <cv.h>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "OpticalFlow.h"
#include "PanoModule.h"



int main(int argc, char *argv[]){
    using namespace cv;
    std::string fileName = "/home/qwad1000/VID_15352015_22103537.mp4";
    VideoCapture videoCapture(fileName);
    if(!videoCapture.isOpened()) {
        std::cerr << "Can't open video " << fileName;
        return -1;
    }

    OpticalFlow opticalFlow(videoCapture);
//    opticalFlow.process();
    auto x = opticalFlow.process2();
    for(int i=0; i<x.images.size(); i++){
        std::string writeName = "/home/qwad1000/test/" + std::to_string(i) + ".png";
        imwrite(writeName, x.images[i]);
        std::cout << i << "  " << x.imageFullShifts[i] << std::endl;
    }

    PanoModule::createPano(x.images);

    return 0;
}

