// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp> 
using namespace std;
using namespace cv;

Mat flipImage(Mat mm, Mat new_img) {
    for (int i = 0; i < mm.cols; i++)
        for (int j = 0; j < mm.rows; j++) {
            new_img.at<uchar>(Point2f(i, j)) = mm.at<uchar>(Point2f((mm.cols - 1) - i, j));
        }

    return new_img;
}

int main()
{  

    Mat img_T, img_R, img_DS, img_S, img_F;
    Mat src = imread("eslam.png", 0);
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
    /// <summary>
    /// Translation
    /// </summary>
    /// <returns></returns>

    int tx = 10, ty = 6;
    Mat TM = (Mat_<float>(2, 3) << 1, 0, tx, 0, 1, ty);

    warpAffine(src, img_T, TM, src.size());
    //cout << "image translation =" << endl << img_T << endl;
    namedWindow("Translation", 0);
    imshow("Translation", img_T);
    waitKey(0);
    // Rotation
    Mat RM = getRotationMatrix2D(Point2f(src.cols / 2, src.rows / 2), 180, 0.5);
    warpAffine(src, img_R, RM, src.size());
    namedWindow("Rotation", 0);
    imshow("Rotation", img_R);
    waitKey(0);

    // Skewing
    Mat src_S = src;
    namedWindow("original", 0);

    imshow("original", src_S);

    Point2f src_p[3];
    src_p[0] = Point2f(0, 0);
    src_p[1] = Point2f(src_S.cols, 0);
    src_p[2] = Point2f(0, src_S.rows);

    Point2f dst_p[3];
    dst_p[0] = Point2f(0, 0);
    dst_p[1] = Point2f(src_S.cols - 10, 0);
    dst_p[2] = Point2f(100, src_S.rows - 10);

    Mat SM = getAffineTransform(src_p, dst_p);
    warpAffine(src_S, img_DS, SM, src_S.size());
    namedWindow("D_skewing", 0);
    imshow("D_skewing", img_DS);
    waitKey(0);

    // Scaling
    resize(src, img_S, Size(), 2, 2, 0);
    namedWindow("Scaling", 0);
    imshow("Scaling", img_S);
    waitKey(0);

    //Flipping
    Mat mm = imread("quala.png", 0);

    flip(mm, img_F, -1);
    namedWindow("Flipping", 0);
    imshow("Flipping", img_F);
    waitKey(0);

    Mat new_img= mm.clone();
    new_img = flipImage(mm, new_img);
    new_img = new_img.t();
    
    Mat new_img2 = new_img.clone();
    new_img2 = flipImage(new_img, new_img2);
    new_img2 = new_img2.t();
   

    namedWindow("Orignal", 0);
    imshow("Orignal", mm);
    namedWindow("MFlipping", 0);
    imshow("MFlipping", new_img2);

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
