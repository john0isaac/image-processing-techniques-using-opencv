// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;


int main()

{

	Mat src = imread("eslam.png", 0);

	Mat dst = src;

	namedWindow("image", 0);
	imshow("image", src);

	waitKey(0);

	cout << "image pixels=" << src.total() << endl;

	float hist[256] = { 0 };

	cout << "non zero pixel intensites and its count" << endl;

	for (int amp = 0; amp < 256; amp++){

		for (int r = 0; r < src.rows; r++)

			for (int c = 0; c < src.cols; c++){

				if (src.at<uchar>(r, c) == amp)
					hist[amp] = hist[amp] + 1;
			}
		if (hist[amp] != 0)
			cout << "Histogram[" << amp << "] = " << hist[amp] << endl;
	}

	//equalizeHist(src, dst)
	//namedWindow("histogram equalization", 0);
	//imshow("histogram equalization", src);
	
	
	///////////visualizing histogram////////////////


	Mat hist_img(20000, 510, CV_8UC1, Scalar(0));
	for (int s = 0; s < 256; s++){
		float bin_val = hist[s];
		line(hist_img, Point(s * 2, 20000), Point(s * 2, 20000 - bin_val), Scalar(255), 1);
	}
	namedWindow("Histogram", 0);
	imshow("Histogram", hist_img);

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
