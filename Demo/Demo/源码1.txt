// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void cornerHarris_demo(InputArray _src,int thresh)
{
	Mat src,dst, dst_norm, dst_norm_scaled;
	src = _src.getMat();
	/// Detector parameters  
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	/// Detecting corners  
	cornerHarris(src, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
	/// Normalizing  
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	/// Drawing a circle around corners  
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
				circle(src, Point(i, j), 5, Scalar(255, 0, 0), -1, 8, 0);
			}
		}
	}
	/// Showing the result  
	imshow("焦点1", dst_norm_scaled);
	imshow("焦点2", src);
}

int main()
{
	Mat src = imread("1.jpg");
	Mat img;
	cvtColor(src, img, COLOR_BGR2GRAY);
	Mat cannyImg;
	Canny(img, cannyImg, 20, 80);
	imshow("Canny", cannyImg);
	Mat threholdImg;
	threshold(img, threholdImg, 100, 255, THRESH_BINARY_INV);
	imshow("threshold", threholdImg);
	int blockSize = 7;
	int constValue = 7;
	Mat local;
	adaptiveThreshold(img, local, 255, BORDER_REPLICATE, THRESH_BINARY_INV, blockSize, constValue);

	imshow("adaptiveThreshold", local);


	cornerHarris_demo(cannyImg,100);

	waitKey(1000000);
	//system("pause");
    return 0;
}

