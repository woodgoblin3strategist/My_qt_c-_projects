#include "mainwindow.h"
#include "another_window.h"
#include "create_question.h"
#include "student_window.h"
#include "teacher_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
