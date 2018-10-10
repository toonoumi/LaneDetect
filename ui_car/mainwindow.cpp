#include "view.hpp"

view::view(QWidget * parent)
{
    //front
    button_front = new QPushButton();
    button_front->setText("Front");
    button_front->setMinimumSize(100, 50);
    //back
    button_back = new QPushButton();
    button_back->setText("Back");
    button_back->setMinimumSize(100, 50);
    //stop
    button_stop = new QPushButton();
    button_stop->setText("Stop");
    button_stop->setMinimumSize(100,50);
    //detect
    button_detect = new QPushButton();
    button_detect->setText("Lane-Detect");
    button_detect->setMinimumSize(100,50);
    //set lable size
    disp = new QLabel();
    disp ->setMinimumSize(1000, 500);
    //set layout
    QGridLayout *layout = new QGridLayout();
    layout->setRowStretch(4, 100);
    layout->setColumnStretch(2, 50);
    layout->addWidget(button_front);
    layout->addWidget(button_back);
    layout->addWidget(button_stop);
    layout->addWidget(button_detect);
    layout->addWidget(disp);
    setLayout(layout);
    //thread and thread slot
    t1 = new Thread_back();
    t2 = new Thread_front();
    t3 = new LaneDetector();
    QObject::connect(t1, SIGNAL(processedImage(QImage )),
                     this, SLOT(updateUI(QImage )));
    QObject::connect(t2, SIGNAL(processedImage(QImage )),
                     this, SLOT(updateUI(QImage )));
    QObject::connect(t3, SIGNAL(processedImage(QImage )),
                     this, SLOT(updateUI(QImage )));
    //button and button slot
    QObject::connect(button_front, SIGNAL (clicked()),this, SLOT (handleButtonFront()));
    QObject::connect(button_back, SIGNAL (clicked()),this, SLOT (handleButtonBack()));
    QObject::connect(button_stop, SIGNAL (clicked()),this, SLOT (handleButtonStop()));
    QObject::connect(button_detect, SIGNAL (clicked()),this, SLOT (handleButtonDetect()));
}

void view::handleButtonStop()
{
    if(t1->isRunning())
        t1->terminate();
    if(t2->isRunning())
        t2->terminate();
    if(t3->isRunning())
        t3->terminate();
}

void view::handleButtonDetect()
{
    if(t1 != nullptr)
    {
        if(t1->isRunning())
            t1->terminate();
    }
    if(t2 != nullptr)
    {
        if(t2->isRunning())
            t2->terminate();
    }
    if(t3 != nullptr)
    {
        if(!t3->isRunning())
        {
            t3->start();
        }
    }
}

void view::handleButtonFront()
{
    if(t1 != nullptr)
    {
        if(t1->isRunning())
        {
            t1->terminate();
        }
    }
    if(t3 != nullptr)
    {
        if(t3->isRunning())
        {
            t3->terminate();
        }
    }
    if(t2 != nullptr)
    {
        if(!t2->isRunning())
        {
            t2->start();
        }
    }
}

void view::handleButtonBack()
{
    if(t2 != nullptr)
    {
        if(t2->isRunning())
        {
            t2->terminate();
        }
    }
    if(t3 != nullptr)
    {
        if(t3->isRunning())
        {
            t3->terminate();
        }
    }
    if(!t1->isRunning())
    {
        t1->start();
    }
}

void view::updateUI(QImage img)
{
    if (!img.isNull())
    {
        disp->setAlignment(Qt::AlignCenter);
        disp->setPixmap(QPixmap::fromImage(img).scaled(disp->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}
