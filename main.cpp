/* --Sparse Optical Flow Demo Program--
 * Written by David Stavens (david.stavens@ai.stanford.edu)
 */
#include <stdio.h>
#include <cv.h>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include "OpticalFlow.h"
#include "PanoModule.h"

namespace po = boost::program_options;

int main(int argc, char *argv[]){
    po::options_description description("Allowed options");

    description.add_options()
            ("help", "produce help message")
            ("input", po::value<std::string>(), "input video")
            ("output-dir", po::value<std::string>()->default_value("./"), "output dir" )
            ;

    po::positional_options_description p;
    p.add("input", 1);
    p.add("output-dir", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << "\n";
        return 1;
    }

    if (!vm.count("input")){
        std::cout << "Please, specify input video file";
        return -1;
    }

    using namespace cv;
    std::string fileName = vm["input"].as<std::string>();
    std::string outputDir = vm["output-dir"].as<std::string>();
    VideoCapture videoCapture(fileName);
    if(!videoCapture.isOpened()) {
        std::cerr << "Can't open video " << fileName;
        return -1;
    }

    OpticalFlow opticalFlow(videoCapture);
//    opticalFlow.process();
    auto x = opticalFlow.process2();
    for(int i=0; i<x.images.size(); i++){
        std::string writeName = outputDir + std::to_string(i) + ".png";
        imwrite(writeName, x.images[i]);
        std::cout << i << "  " << x.imageFullShifts[i] << std::endl;
    }

    PanoModule::createPano(x.images);
    return 0;
}

