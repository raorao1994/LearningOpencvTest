// Demo.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("2.jpg");
	Mat img;
	cvtColor(src, img,COLOR_BGR2GRAY);
	blur(img, img, Size(3, 3));
	Mat edge;
	Canny(img, edge, 20, 50, 3);
	Mat local;
	//adaptiveThreshold(img, local, 255, BORDER_REPLICATE, THRESH_BINARY_INV, 13, 11);
	
	//画直线
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(edge, lines, 1, CV_PI / 180, 70, 30, 10);
	// Draw lines  
	for (int i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		int x = abs(v[0]- v[2]);
		int y = abs(v[1] - v[3]);
		if (0.3*x > y)
		{
		
		}
		cv::line(src, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(0, 255, 0));
	}
	imshow("Canny", edge);
	imshow("src", src);
	waitKey(0);
	system("pause");
	return 0;
}

