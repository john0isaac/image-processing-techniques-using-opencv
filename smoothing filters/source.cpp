// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp> 
using namespace std;
using namespace cv;

int main()
{
    Mat dst, dst2;
    Mat src = imread("eslam.png");
    if (src.empty()) {
        cout << "no Image" << endl;
        system("pause");
        return -1;
    }
    namedWindow("display", 0);
    imshow("display", src);

    
    Mat kernel_T = (Mat_<float>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
    cout << endl << kernel_T << endl;

    kernel_T = kernel_T / 9; 
    cout << endl << kernel_T << endl;
    filter2D(src, dst, CV_8UC1, kernel_T);

    namedWindow("after 3*3 smoothing", 0);
    imshow("after 3*3 smoothing", dst);

    // Pyramidal Filter
    Mat kernel_P = (Mat_<float>(5, 5) << 1, 2, 3, 2, 1, 2, 4, 6, 4, 2, 3, 6, 9, 6, 3, 2, 4, 6, 4, 2, 1, 2, 3, 2, 1);
    cout << endl << kernel_P << endl;

    kernel_P = kernel_P / 81;
    cout << endl << kernel_P << endl;
    filter2D(src, dst2, CV_8UC1, kernel_P);

    namedWindow("after Pyramidal smoothing filter", 0);
    imshow("after Pyramidal smoothing filter", dst2);
    waitKey(0);
  
}
