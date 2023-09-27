// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp> 
using namespace std;
using namespace cv;

Mat imageNegative(Mat src) {
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            src.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);
    return src;

}

Mat logTransform(Mat src) {
    Mat dst(src.rows, src.cols, CV_32FC1);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            dst.at<float>(i, j) = log(src.at<uchar>(i, j) + 1);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    convertScaleAbs(dst, dst);
    return dst;
}

Mat powerLaw(Mat src, float gamma) {
    Mat dst(src.rows, src.cols, CV_32FC1);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            dst.at<float>(i, j) = powf(src.at<uchar>(i, j), gamma);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    convertScaleAbs(dst, dst);
    return dst;
}

Mat bitPlane(Mat src) {
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++) {
            if (src.at<uchar>(i, j) & 64)
                src.at<uchar>(i, j) = 255;
            else
                src.at<uchar>(i, j) = 0;
        }
    return src;
}

Mat grayLevel(Mat src) {
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++) {
            if (src.at<uchar>(i, j) && src.at<uchar>(i, j) < 200)
                src.at<uchar>(i, j) = 255;
            else
                src.at<uchar>(i, j) = src.at<uchar>(i, j);
        }
    return src;
}

Mat imageSkewing(Mat src_S) {
    // Skewing
    Mat img_DS;
    Point2f src_p[3];
    src_p[0] = Point2f(0, 0);
    src_p[1] = Point2f(src_S.cols, 0);
    src_p[2] = Point2f(0, src_S.rows);

    Point2f dst_p[3];
    dst_p[0] = Point2f(125, 0);
    dst_p[1] = Point2f(src_S.cols - 125, 0);
    dst_p[2] = Point2f(0, src_S.rows);

    Mat SM = getAffineTransform(src_p, dst_p);
    warpAffine(src_S, img_DS, SM, src_S.size());

    return img_DS;
}

int main()
{
    Mat src = imread("essay.png", 0);
    if (src.empty()) {
        cout << "no Image" << endl;
        system("pause");
        return -1;
    }
    namedWindow("display", 0);
    imshow("display", src);

    Mat skewedImage = imageSkewing(src);
    namedWindow("D_skewing", 0);
    imshow("D_skewing", skewedImage);

    //Mat output = imageNegative(skewedImage);
    //Mat output = logTransform(skewedImage);
    Mat output = powerLaw(skewedImage, 1.5);
    //Mat output = bitPlane(skewedImage);
    //Mat output = grayLevel(skewedImage);
    namedWindow("Output", 0);
    imshow("Output", output);
    waitKey(0);
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
