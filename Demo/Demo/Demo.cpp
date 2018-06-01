// Demo.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class LineFinder {

private:
	Mat img;    //原图  
	vector<Vec4i>lines;   //向量中检测到的直线的端点  
						  //累加器的分辨率  
	double deltaRho;
	double deltaTheta;
	int minVote;    //直线被接受时所需的最小投票数  
	double minLength;   //直线的最小长度  
	double maxGap;  //沿着直线方向的最大缺口  
public:
	//默认的累加器的分辨率为单个像素即1  不设置缺口及最小长度的值  
	LineFinder() :deltaRho(1), deltaTheta(CV_PI / 180), minVote(10), minLength(0.), maxGap(0.) {};

	//设置累加器的分辨率  
	void setAccResolution(double dRho, double dTheta) {

		deltaRho = dRho;
		deltaTheta = dTheta;
	}

	//设置最小投票数  
	void setMinVote(int minv) {

		minVote = minv;
	}

	//设置缺口及最小长度  
	void setLineLengthAndGap(double length, double gap) {

		minLength = length;
		maxGap = gap;
	}

	//使用概率霍夫变换  
	vector<Vec4i>findLines(Mat &binary) {

		lines.clear();
		HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);
		return lines;
	}

	//绘制检测到的直线  
	void drawDetectedLines(Mat &image, Scalar color = Scalar(2, 0, 255)) {

		//画线  
		vector<Vec4i>::const_iterator it2 = lines.begin();
		while (it2 != lines.end())
		{
			Point pt1((*it2)[0], (*it2)[1]);
			Point pt2((*it2)[2], (*it2)[3]);
			line(image, pt1, pt2, color);
			++it2;
		}
	}
};

int main()
{
	Mat image = imread("2.jpg");

	Mat result;
	cvtColor(image, result, COLOR_BGR2GRAY);
	//应用Canny算法  
	Mat contours;
	Canny(result,   //灰度图  
		contours,   //输出轮廓  
		125,    //低阈值  
		350);   //高阈值  

				//创建LineFinder实例  
	LineFinder finder;
	//设置概率Hough参数  
	finder.setLineLengthAndGap(100, 20);
	finder.setMinVote(80);
	//检测并绘制直线  
	vector<Vec4i>lines = finder.findLines(contours);
	finder.drawDetectedLines(image);
	imshow("Detected Lines with HoughP", image);
	waitKey(0);
	waitKey(10000);
	system("pause");
	return 0;
}

