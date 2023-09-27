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
    waitKey(0);

    cout << "total no of pixels=" << src.total() << endl;
    cout << "image rows=" << src.rows << endl;
    cout << "image cols=" << src.cols << endl;
    cout << "image pixel depth=" << src.depth() << endl;
    cout << "image channels=" << src.channels() << endl;
   
    cvtColor(src, g_img, COLOR_BGR2GRAY);
    cout << "gray image channels=" << g_img.channels() << endl;

    namedWindow("display_gray", 1);
    imshow("display_gray", g_img);
    waitKey(0);
    int max = 0;
    int min = 255;
    int sum = 0;
    int average = 0;

    for (int i = 0; i < g_img.rows; i++)
        for (int j = 0; j < g_img.cols; j++){
            if (g_img.at<uchar>(i,j) > max)
                max = g_img.at<uchar>(i, j);
            if (g_img.at<uchar>(i, j) < min)
                min = g_img.at<uchar>(i, j);
            sum += g_img.at<uchar>(i, j);
        }
    
    cout<< endl << "Max amplitude=" << max << endl;
    cout << "Min amplitude=" << min << endl;
    cout << "Average amplitude=" << sum/g_img.total() << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
