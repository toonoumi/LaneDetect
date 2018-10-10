#include "thread_back.hpp"
#include <QTimer>
Thread_back::Thread_back(QObject *parent)
: QThread(parent)
{
    //start();
}
void Thread_back::run()
{
    VideoCapture cap(2);
    Mat frame;
    while(1)
    {
        cap >> frame;
        if(!frame.empty())
        {
            image = Mat2QImage(frame);
            if(!image.isNull())
            {
                emit processedImage(image);
            }
            this->msleep(50);
        }
        //imshow("hi", frame);

    }
    
}

QImage Thread_back::Mat2QImage(const cv::Mat3b &src)
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
