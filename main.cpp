/* --Sparse Optical Flow Demo Program--
 * Written by David Stavens (david.stavens@ai.stanford.edu)
 */
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "OpticalFlow.h"

static const double pi = 3.14159265358979323846;
const int number_of_features_desired = 50;

void draw_arrow(IplImage *frame1, CvPoint2D32f *frame1_features, CvPoint2D32f *frame2_features, int i);

/* This is just an inline that allocates images.  I did this to reduce clutter in the
 * actual computer vision algorithmic code.  Basically it allocates the requested image
 * unless that image is already non-NULL.  It always leaves a non-NULL image as-is even
 * if that image's size, depth, and/or channels are different than the request.
 */
inline static void allocateOnDemand( IplImage **img, CvSize size, int depth, int channels )
{
    if ( *img != NULL )	return;

    *img = cvCreateImage( size, depth, channels );
    if ( *img == NULL )
    {
        fprintf(stderr, "Error: Couldn't allocate image.  Out of memory?\n");
        exit(-1);
    }
}


int main(int argc, char *argv[]){
    using namespace cv;
    std::string fileName = "/home/qwad1000/test.mp4";
    VideoCapture videoCapture(fileName);
    if(!videoCapture.isOpened()) {
        std::cerr << "Can't open video " << fileName;
        return -1;
    }

    OpticalFlow opticalFlow(videoCapture);
    auto x = opticalFlow.process2();
    for(int i=0; i<x.images.size(); i++){
        std::string writeName = "/home/qwad1000/test/" + std::to_string(i) + ".png";
        imwrite(writeName, x.images[i]);
        std::cout << i << "  " << x.imagesShifts[i] << std::endl;
    }

    return 0;
}

