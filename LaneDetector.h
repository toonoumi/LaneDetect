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


#define AIM_OFFSET 45      //Setting
#define WARNGING_THRESH 120
#define WHITE_THRESH 25
#define YELLOW_THRESH 100
#define WHITE_RANGE 200
#define DELTA_THRESH 80
#define STORE_SIZE 3
using namespace cv;
using namespace std;
class LaneDetector{
public:
	LaneDetector();
	LaneDetector(string filename);
	~LaneDetector();
	bool StartCapturing();
	bool readInfo(string filename);
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
	thread *t1;
	
};
