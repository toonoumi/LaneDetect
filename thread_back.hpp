#ifndef QTHREADBACK
#define QTHREADBACK
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
#include <QThread>
using namespace std;
using namespace cv;

class Thread_back : public QThread
{
     Q_OBJECT
public:
    Thread_back(QObject *parent = 0);
    QImage Mat2QImage(const cv::Mat3b &src);
    protected:
        void run();
    QTimer *timer;
    QImage image;
signals:
    void processedImage(const QImage image);
};

#endif
