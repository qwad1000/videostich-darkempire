//
// Created by qwad1000 on 03.12.15.
//

#ifndef VIDEOSTITCH_VIDEOHELPER_H
#define VIDEOSTITCH_VIDEOHELPER_H


#include <opencv2/videoio.hpp>

class VideoHelper {
public:
    static bool skipFrames(cv::VideoCapture &videoCapture, int framesToSkip){
        for (; framesToSkip >=0; framesToSkip--){
            if(!videoCapture.grab())
                return false;
        }
        return true;
    }
};


#endif //VIDEOSTITCH_VIDEOHELPER_H
