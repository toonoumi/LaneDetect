#pragma once
#include<string>
#include<fstream>
#include<stack>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc.hpp"
#include <thread>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>

#define IDENTIFIER_NUM 1000
#define CROSS_WIDTH 15
#define BORDER_TOL 765-20
#define RED_OFFSET 30
#define RANGE 10
#define JUMP 60
#define MIN_LENGTH 5
#define PAIRING_TOL 30
#define AIM_OFFSET 45      //setting
#define WARNGING_THRESH 120
using namespace cv;
using namespace std;
class LaneDetector{
	struct TargetIdentifier {
		Point start;
		Point end;
		Scalar color;
		bool ispaired;
		TargetIdentifier *pair;
		
	};
public:
	LaneDetector();
	LaneDetector(string filename);
	~LaneDetector();
	bool StartCapturing();
	void findBar(Mat&frame, char letterColor);
	void drawIdentifier(Mat&frame);
	bool readInfo(string filename);
	bool isRed(Vec3b color);
	bool isBlue(Vec3b color);
	void fillNotRed(Mat frame);
	bool findObj(Mat frame);
	bool findObj_cp(Mat frame);
	void printPoint(Mat frame);
	void printPoint_cp(Mat frame);
	static void beep();
private:
	Point lborder[6];
	int lborderPointCount = 0;
	int lborderPointCount_cp = 0;
	Point rborder[6];
	int rborderPointCount = 0;
	int rborderPointCount_cp = 0;
	//Point aim;
	int ldx[30], rdx[30];
	int ldxcount = 0, rdxcount = 0;
	int ldxindex = 0, rdxindex = 0;
	int fails = 0;

	int ldx_cp[30], rdx_cp[30];
	int ldxcount_cp = 0, rdxcount_cp = 0;
	int ldxindex_cp = 0, rdxindex_cp = 0;
	int fails_cp = 0;

	int aim = 0;
	string videoFileName;
	TargetIdentifier identifier[IDENTIFIER_NUM];
	int identifiercount = 0;
	int redToGreenDiff = 30;
	int redToBlueDiff = 80;
	thread *t1;
	
};
