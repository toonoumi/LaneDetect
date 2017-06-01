#include "thread_front.hpp"
#include <QTimer>
Thread_front::Thread_front(QObject *parent)
: QThread(parent)
{
    //start();
}
void Thread_front::run()
{
    VideoCapture cap(1);
    Mat frame;
    while(3)
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

QImage Thread_front::Mat2QImage(const cv::Mat3b &src)
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
