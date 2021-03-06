#include "LaneDetector.hpp"


LaneDetector::LaneDetector()
{
	videoFileName = "Cam";
}

LaneDetector::LaneDetector(string filename)
{
	videoFileName = filename;
}

LaneDetector::~LaneDetector()
{
}


bool LaneDetector::readInfo(string filename)
{
	//TODO
	return false;
}


bool isBorder(Mat frame,Point pt) {
	return false;
}
bool isBorder(Vec3b p1, Vec3b p2) {
	int sum1 = p1.val[0] + p1.val[1] + p1.val[2];
	int sum2 = p2.val[0] + p2.val[1] + p2.val[2];
	if (sum2 - sum1 > 40) {
		return true;
	}
	return false;
}

bool isYellowOrWhite(Vec3b color) {
	bool isYellow = false, isWhite = false;
	if (abs(color.val[1] - color.val[2]) < WHITE_THRESH&&abs(color.val[0] - color.val[2]) && abs(color.val[0] - color.val[1])) {
		if (255 - color.val[0] < WHITE_RANGE && 255 - color.val[1] < WHITE_RANGE && 255 - color.val[2] < WHITE_RANGE) {
			isWhite = true;
		}
	}
	if (abs(color.val[1] - color.val[2]) < YELLOW_THRESH&&color.val[2] - color.val[0] > YELLOW_THRESH && color.val[1] - color.val[0] > YELLOW_THRESH) {
		isYellow = true;
	}
	return isYellow || isWhite;
}
void LaneDetector::printPoint(Mat frame) {
	circle(frame, lborder[0], 10, Scalar(0, 0, 255), 2);
	circle(frame, rborder[0], 10, Scalar(255, 0, 255), 2);
}
void LaneDetector::printPoint_cp(Mat frame) {
	circle(frame, lborder[1], 10, Scalar(0, 0, 255), 2);
	circle(frame, rborder[1], 10, Scalar(255, 0, 255), 2);
}

int averageDelta(int*dx) {
	int av = 0;
	for (int i = 0; i < STORE_SIZE; i++) {
		av += dx[i];
	}
	av /= STORE_SIZE;
	int avd = 0;
	for (int i = 0; i < STORE_SIZE; i++) {
		avd += abs(dx[i] - av);
	}
	avd /= 30;
	return avd;
}

bool LaneDetector::findObj_cp(Mat frame)
{
	/*threshold(frame, frame, 50, 255, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//erode(frame, frame, element);
	Mat element2 = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(frame, frame, element2);*/
	bool bordered = false;
	int count = 0;
    int whiteCount=0;
	bool isValid = false;
	bool rNotFail = false;
	bool lNotFail = false;
	int laveragedelta = 0, raveragedelta = 0;
	if (fails_cp > 15) {
		fails_cp = 0;
		ldxcount_cp = 0;
		rdxcount_cp = 0;
	}
	if (ldxcount_cp > STORE_SIZE && rdxcount_cp > STORE_SIZE ) {
		isValid = true;
		laveragedelta = averageDelta(ldx_cp);
		raveragedelta = averageDelta(rdx_cp);
	}
	for (int i = aim; i > 10; i--) {
		if (isBorder(frame.at<Vec3b>(frame.rows / 5*3 , i), frame.at<Vec3b>(frame.rows /5* 3 , i - 1))) {
			//lborder[0] = Point(i, frame.rows / 3 * 2);
			//lborderPointCount++;
			//break;
			bordered = true;
			count = 0;
		}
		if (bordered) {
			count++;
			if (isYellowOrWhite(frame.at<Vec3b>(frame.rows /5* 3 , i - 1))) {
				//TODO: judge Delta
                whiteCount++;
                if(whiteCount>=10){
                    if (isValid&&abs(abs(lborder[1].x - i) - laveragedelta) > DELTA_THRESH) {
                        fails_cp++;
                        break;
                    }
                    ldx_cp[ldxindex_cp] = i;
                    ldxindex_cp++;
                    if (ldxindex_cp >= STORE_SIZE) {
                        ldxindex_cp = 0;
                    }
                    if (ldxcount_cp < STORE_SIZE + 10) {
                        ldxcount_cp++;
                    }

                    lborder[1] = Point(i, frame.rows /5* 3 );
                    if (lborderPointCount_cp<65535)
                        lborderPointCount_cp++;

                    lNotFail = true;
                    break;
                }
			}
		}
		if (count >= 10) {
			count = 0;
			bordered = false;
		}

	}
	bordered = false;
	count = 0;
    whiteCount=0;
	for (int i = aim; i <frame.cols - 10; i++) {
		if (isBorder(frame.at<Vec3b>(frame.rows /5* 3 , i), frame.at<Vec3b>(frame.rows /5* 3 , i + 1))) {

			bordered = true;
			count = 0;
		}
		if (bordered) {
			count++;
			if (isYellowOrWhite(frame.at<Vec3b>(frame.rows /5* 3 , i + 1))) {
				//TODO:judge delta
                whiteCount++;
                if(whiteCount>=10){
                    if (isValid&&abs(abs(rborder[1].x - i) - raveragedelta) > DELTA_THRESH) {
                        fails_cp++;
                        break;
                    }
                    rdx_cp[rdxindex_cp] = i;
                    rdxindex_cp++;
                    if (rdxindex_cp >= STORE_SIZE) {
                        rdxindex_cp = 0;
                    }
                    if (rdxcount_cp < STORE_SIZE + 10) {
                        rdxcount_cp++;
                    }

                    rborder[1] = Point(i, frame.rows /5* 3 );
                    if (rborderPointCount_cp<65535)
                        rborderPointCount_cp++;
                    rNotFail = true;
                    break;
                }
			}
		}
		if (count >= 10) {
			count = 0;
			bordered = false;
		}

	}
	if (rNotFail&&lNotFail) {
		fails_cp = 0;
	}
	if (isValid) {
		printPoint_cp(frame);
	}
	if (lborderPointCount>10 && rborderPointCount>10 && isValid &&fails_cp==0) {
		if (abs(lborder[1].x - aim) < WARNGING_THRESH/10*6&&lNotFail) {
			//left warning
			cout << "Watch Left!" << endl;
		}
		if (abs(rborder[1].x - aim) < WARNGING_THRESH/10*6&&rNotFail) {
			//right warning
			cout << "Watch Right!" << endl;
		}
	}
	return true;
}

bool LaneDetector::findObj(Mat frame)
{
	/*threshold(frame, frame, 50, 255, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//erode(frame, frame, element);
	Mat element2 = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(frame, frame, element2);*/
    
	bool bordered = false;
	int count = 0;
    int whiteCount=0;
	bool isValid = false;
	bool rNotFail = false;
	bool lNotFail = false;
	int laveragedelta = 0, raveragedelta = 0;
	if (fails > 15) {
		fails = 0;
		ldxcount = 0;
		rdxcount = 0;
	}
	if (ldxcount > STORE_SIZE && rdxcount > STORE_SIZE) {
		isValid = true;
		laveragedelta = averageDelta(ldx);
		raveragedelta = averageDelta(rdx);
	}
	for (int i = aim; i > 10; i--) {
		if (isBorder(frame.at<Vec3b>(frame.rows / 3 * 2, i), frame.at<Vec3b>(frame.rows / 3 * 2, i - 1))) {
			//lborder[0] = Point(i, frame.rows / 3 * 2);
			//lborderPointCount++;
			//break;
			bordered = true;
			count = 0;
		}
		if (bordered) {
			count++;
			if (isYellowOrWhite(frame.at<Vec3b>(frame.rows / 3 * 2, i - 1))) {
				//TODO: judge Delta
                whiteCount++;
                if(whiteCount>=10){
                    if (isValid&&abs(abs(lborder[0].x - i) - laveragedelta) >   DELTA_THRESH){
                        fails++;
                        break;
                    }
                    ldx[ldxindex] = i;
                    ldxindex++;
                    if (ldxindex >= STORE_SIZE) {
                        ldxindex = 0;
                    }
                    if (ldxcount < STORE_SIZE+10) {
                        ldxcount++;
                    }
				
                    lborder[0] = Point(i, frame.rows / 3 * 2);
                    if(lborderPointCount<65535)
                            lborderPointCount++;
				
                    lNotFail = true;
                    break;
                }
			}
		}
		if (count >= 10) {
			count = 0;
			bordered = false;
		}

	}
	bordered = false;
	count = 0;
    whiteCount=0;
	for (int i = aim; i <frame.cols-10; i++) {
		if (isBorder(frame.at<Vec3b>(frame.rows / 3 * 2,i ), frame.at<Vec3b>( frame.rows / 3 * 2,i + 1))) {
			//lborder[0] = Point(i, frame.rows / 3 * 2);
			//lborderPointCount++;
			//break;
			bordered = true;
			count = 0;
		}
		if (bordered) {
			count++;
			if (isYellowOrWhite(frame.at<Vec3b>( frame.rows / 3 * 2,i + 1))) {
				//TODO:judge delta
                whiteCount++;
                if(whiteCount>=10){
                    if (isValid&&abs(abs(rborder[0].x - i) - raveragedelta) > DELTA_THRESH) {
                        fails++;
                        break;
                    }
                    rdx[rdxindex] = i;
                    rdxindex++;
                    if (rdxindex >= STORE_SIZE) {
                        rdxindex = 0;
                    }
                    if (rdxcount < STORE_SIZE+10) {
                        rdxcount++;
                    }
				
                    rborder[0] = Point(i,frame.rows / 3 * 2);
                    if (rborderPointCount<65535)
                        rborderPointCount++;
                    rNotFail = true;
                    break;
                }
			}
		}
		if (count >= 10) {
			count = 0;
			bordered = false;
		}

	}
	if (rNotFail&&lNotFail) {
		fails = 0;
	}
	if (isValid) {
		printPoint(frame);
	}
	if (lborderPointCount>10&&rborderPointCount>10&&isValid&&fails==0) {
		if (abs(lborder[0].x - aim) < WARNGING_THRESH&&lNotFail) {
			//left warning
			cout << "Watch Left! \a" << endl;
		}
		if (abs(rborder[0].x - aim) < WARNGING_THRESH&&rNotFail) {
			//right warning
			cout << "Watch Right! \a" << endl;
		}
	}
	findObj_cp(frame);
	return true;
}


bool LaneDetector::StartCapturing()
{
	bool rtn = false;
	//bool allDataSet = readInfo("data.info");
	

	
	if (videoFileName == "Cam") {
		VideoCapture capture(0);//2
        //capture.set(CAP_PROP_SETTINGS,0);
		//capture.set(CV_CAP_PROP_EXPOSURE,1);
		//capture.set(CAP_PROP_AUTO_EXPOSURE, 0.3);
		//capture.set(CAP_PROP_SETTINGS, 0);
		//capture.set();
		//capture.set(13, 100000);
		rtn = true;
		while (1) {
			Mat frame;
			capture >> frame;
			//frame = frame - Scalar(100, 100, 100);
			if (frame.empty()) {
				break;
			}
			Mat cpy_frame = frame.clone();
			
			//cvtColor(cpy_frame, cpy_frame, CV_BGR2HSV);
			cpy_frame = cpy_frame(Rect(0, frame.rows / 2, frame.cols, frame.rows / 2));
			//blur(cpy_frame, cpy_frame, Size(4, 4));
			//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
			//erode(cpy_frame, cpy_frame,element);
			//cpy_frame = cpy_frame(Rect(5, frame.rows / 2, frame.cols, frame.rows / 2));
			aim = cpy_frame.cols / 2 + AIM_OFFSET;
			findObj(cpy_frame);
			line(cpy_frame, Point(aim, 0), Point(aim, cpy_frame.rows), Scalar(0, 255, 255), 2);
            image = Mat2QImage(cpy_frame);
            if(!image.isNull())
            {
                emit processedImage(image);
            }
            this->msleep(50);
		}
	}
	else {
		VideoCapture capture(videoFileName);

		rtn = true;
		while (1) {
			Mat frame;
			capture >> frame;
			
			if (frame.empty()) {
				break;
			}
			Mat cpy_frame = frame.clone();
			cpy_frame= cpy_frame(Rect(0, frame.rows / 2, frame.cols, frame.rows / 2));
			//cpy_frame = cpy_frame(Rect(5, frame.rows / 2, frame.cols, frame.rows / 2));
			aim = cpy_frame.cols / 2+AIM_OFFSET;
			findObj(cpy_frame);
			line(cpy_frame, Point(aim, 0), Point(aim, cpy_frame.rows), Scalar(0, 255, 255), 2);
			//TODO
			imshow("CamCap", cpy_frame);
			if (waitKey(10) >= 0) {
				break;
			}
		}
	}
	return rtn;
}

void LaneDetector::run()
{
    StartCapturing();
    qDebug()<<"go to detect";
}

QImage LaneDetector::Mat2QImage(const cv::Mat3b &src)
{
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    for (int y = 0; y < src.rows; ++y)
    {
        const cv::Vec3b *srcrow = src[y];
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x)
        {
            destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
        }
    }
    return dest;
}
