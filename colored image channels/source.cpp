// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

int main()
{
    Mat g_img;
    Mat src = imread("eslam.png");
    if (src.empty()) {
        cout << "no Image" << endl;
        system("pause");
        return -1;
    }
    namedWindow("display", 0);
    imshow("display", src);
    

    Mat channels[3];
    split(src, channels);
    Mat red_channel = channels[0];
    Mat green_image = channels[1];
    Mat blue_image = channels[2];

    Mat zero_channel = Mat::zeros(Size(src.rows, src.cols), CV_8UC1);

    vector<Mat> vec;
    vec.push_back(red_channel);
    vec.push_back(zero_channel);
    vec.push_back(zero_channel);

    Mat out;
    merge(vec, out);

    namedWindow("display", 0);
    imshow("display", out);
    waitKey(0);

}
