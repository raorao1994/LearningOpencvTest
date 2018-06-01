// Demo.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class LineFinder {

private:
	Mat img;    //ԭͼ  
	vector<Vec4i>lines;   //�����м�⵽��ֱ�ߵĶ˵�  
						  //�ۼ����ķֱ���  
	double deltaRho;
	double deltaTheta;
	int minVote;    //ֱ�߱�����ʱ�������СͶƱ��  
	double minLength;   //ֱ�ߵ���С����  
	double maxGap;  //����ֱ�߷�������ȱ��  
public:
	//Ĭ�ϵ��ۼ����ķֱ���Ϊ�������ؼ�1  ������ȱ�ڼ���С���ȵ�ֵ  
	LineFinder() :deltaRho(1), deltaTheta(CV_PI / 180), minVote(10), minLength(0.), maxGap(0.) {};

	//�����ۼ����ķֱ���  
	void setAccResolution(double dRho, double dTheta) {

		deltaRho = dRho;
		deltaTheta = dTheta;
	}

	//������СͶƱ��  
	void setMinVote(int minv) {

		minVote = minv;
	}

	//����ȱ�ڼ���С����  
	void setLineLengthAndGap(double length, double gap) {

		minLength = length;
		maxGap = gap;
	}

	//ʹ�ø��ʻ���任  
	vector<Vec4i>findLines(Mat &binary) {

		lines.clear();
		HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);
		return lines;
	}

	//���Ƽ�⵽��ֱ��  
	void drawDetectedLines(Mat &image, Scalar color = Scalar(2, 0, 255)) {

		//����  
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
	
	system("pause");
	return 0;
}

