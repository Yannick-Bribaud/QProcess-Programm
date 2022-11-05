#include "Process_prog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Process_prog w;
    w.show();
    return a.exec();
}
