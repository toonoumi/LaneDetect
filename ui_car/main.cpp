#include <QApplication>
#include "view.hpp"
int main(int argc, char * argv[])
{
    //Thread_back* t1;
    QApplication app(argc, argv);
    view widget;
    
//    t1 = new Thread_back();
//    QObject::connect(t1, SIGNAL(processedImage(QImage )),
//                     &widget, SLOT(updateUI(QImage )));
    widget.show();
return app.exec();
}
