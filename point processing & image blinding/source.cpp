// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp> 
using namespace std;
using namespace cv;

void translateImage(Mat src) {
    Mat dst(src.size(), CV_8UC1, Scalar(0));
    int x, y, xN, yN, tx, ty;
    cout << "Enter shift in x-axis followed by shift in y-axis" << endl;
    cin >> tx >> ty;
    cout << "shifting in x-axis= " << tx << "\t" << "shifting in y-axis= " << ty << endl << endl;
    for (int i = 0; i < src.rows - abs(ty); i++)
        for (int j = 0; j < src.cols - abs(tx); j++)
        {
            if (tx > 0 && ty > 0)
            {
                x = j;
                y = i;
                yN = i + ty;
                xN = j + tx;
                dst.at<uchar>(yN, xN) = src.at<uchar>(y, x);
            }
            else if (tx > 0 && ty < 0)
            {
                x = j;
                y = abs(ty) + i;
                yN = i;
                xN = j + tx;
                dst.at<uchar>(yN, xN) = src.at<uchar>(y, x);
            }
            else if (tx < 0 && ty > 0)
            {
                x = abs(tx) + j;
                y = i;
                yN = i + ty;
                xN = j;
                dst.at<uchar>(yN, xN) = src.at<uchar>(y, x);
            }
            else if (tx < 0 && ty < 0)
            {
                x = abs(tx) + j;
                y = abs(ty) + i;
                yN = i;
                xN = j;
                dst.at<uchar>(yN, xN) = src.at<uchar>(y, x);
            }
        }
    namedWindow("orginal", 0);
    imshow("orginal", src);
    namedWindow("translation", 0);
    imshow("translation", dst);
    waitKey(0);
}

void pointProcessing(Mat src) {
    Mat dst(src.size(), CV_8UC1, Scalar(0));
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            dst.at<uchar>(i, j) = src.at<uchar>(i, j) + 10;
    namedWindow("before", 0);
    imshow("before", src);
    namedWindow("after", 0);
    imshow("after", dst);
    waitKey(0);
}

void imageBlinding(Mat src1, Mat src2) {
    resize(src2, src2, src1.size());
    cout << "scr1.rows" << src1.rows << "\t" << "src1.cols" << src1.cols << endl;
    cout << "scr2.rows" << src2.rows << "\t" << "src2.cols" << src2.cols << endl;
    Mat dst(src1.size(), CV_8UC1, Scalar(0));
    for (int i = 0; i < src1.rows; i++)
        for (int j = 0; j < src1.cols; j++)
            dst.at<uchar>(i, j) = src1.at<uchar>(i, j) * 0.8 + src2.at<uchar>(i, j) * 0.2;
    namedWindow("SRC1", 0);
    imshow("SRC1", src1);
    namedWindow("SRC2", 0);
    imshow("SRC2", src2);
    namedWindow("Blinding", 0);
    imshow("Blinding", dst);
    waitKey(0);

}

int main()
{
    Mat src = imread("family.png", 0);
    if (src.empty()) {
        cout << "no Image" << endl;
        system("pause");
        return -1;
    }
    
    //translateImage(src);
    //pointProcessing(src);

    Mat src2 = imread("eslam.png", 0);
    if (src2.empty()) {
        cout << "no Image" << endl;
        system("pause");
        return -1;
    }

    //imageBlinding(src, src2);
}
