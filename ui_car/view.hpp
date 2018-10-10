#ifndef VIEW_HPP
#define VIEW_HPP
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "thread_back.hpp"
#include "thread_front.hpp"
#include "LaneDetector.hpp"
using namespace std;
using namespace cv;
class view: public QWidget
{
    Q_OBJECT
public:
    view(QWidget * parent = nullptr);
    //
    public slots:
    void updateUI(QImage img);
    void handleButtonFront();
    void handleButtonBack();
    void handleButtonStop();
    void handleButtonDetect();
    private:
    QPushButton *button_front;
    QPushButton *button_back;
    QPushButton *button_detect;
    QPushButton *button_stop;
    QLabel *disp;
    Thread_back * t1;
    Thread_front * t2;
    LaneDetector *t3;
};

#endif
