#include <opencv2/opencv.hpp>
#include "VideoService.h"
#include <thread>

using namespace cv;
using namespace std;
using namespace chrono;
using namespace this_thread;

int sliderValue;
int main(int argc, char* argv[])
{
    sliderValue = 0;

    VideoService videoService = VideoService();
    sleep_for(seconds(2));

    videoService.SettingsPanel(sliderValue);
    videoService.SetTrackVariables();

    videoService.NextFrame();
    videoService.TestBackGroundFrame();

    while (true)
    {
        videoService.NextFrame();
        videoService.TestBackGroundFrame();
        videoService.UpdateBackGround();
        videoService.CompareFrame();
        videoService.ShowFrame();
        videoService.TestSettings();
		videoService.SetVariables();
        if (videoService.TestDestroy())
        {
            return 0;
        }
    }
}




//int main(int argc, char* argv[])
//{
//    videoService = VideoService();
//    sliderValue = 0;
//    sleep_for(seconds(2));
//
//    videoService.NextFrame();
//    videoService.TestBackGroundFrame();
//
//    SettingsPanel(sliderValue);
//    SetVariables();
//
//    while (true)
//    {
//        videoService.NextFrame();
//        videoService.TestBackGroundFrame();
//        videoService.UpdateBackGround();
//        videoService.CompareFrame();
//        videoService.ShowFrame();
//        videoService.TestSettings();
//
//        if (videoService.TestDestroy())
//        {
//            return 0;
//        }
//    }
//}
