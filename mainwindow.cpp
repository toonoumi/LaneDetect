#include "view.hpp"

view::view(QWidget * parent)
{
	//setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	this->setWindowState(Qt::WindowMaximized);
	//this->setWindowState(Qt::WindowMaximized);
    //front
    button_front = new QPushButton();
    button_front->setText("Front");
    button_front->setMinimumSize(50, 200);
    //back
    button_back = new QPushButton();
    button_back->setText("Back");
    button_back->setMinimumSize(50, 200);
    //stop
    button_stop = new QPushButton();
    button_stop->setText("Stop");
    button_stop->setMinimumSize(50,200);
    //detect
    button_detect = new QPushButton();
    button_detect->setText("Lane-A");
    button_detect->setMinimumSize(50,200);
    //set lable size
    disp = new QLabel();
    disp ->setMinimumSize(1800, 1000);
    //set layout button
    QVBoxLayout *layout0 = new QVBoxLayout();
    layout0->addWidget(button_front);
    layout0->addWidget(button_back);
    layout0->addWidget(button_stop);
    layout0->addWidget(button_detect);
    //set layout display
	QVBoxLayout *layout1 = new QVBoxLayout();
	layout1->addWidget(disp);
	//set two layouts
	QHBoxLayout *toplayout = new QHBoxLayout();
	toplayout->addLayout(layout0);
	toplayout->addLayout(layout1);
	//set layouts
	//setLayout(layout0);
    //setLayout(layout1);
	setLayout(toplayout);
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
