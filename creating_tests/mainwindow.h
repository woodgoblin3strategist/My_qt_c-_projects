#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <another_window.h> //подключаем проверочный файл для новых форм
#include <student_window.h>
#include <teacher_window.h>
#include <create_question.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слоты от кнопок главного окна
    void on_teacher_batton_clicked();

    void on_student_batton_clicked();

private:
    Ui::MainWindow *ui;
    // второе и третье окна
    TeacherWindow *window_teach;
    StudentWindow *window_student;
};
#endif // MAINWINDOW_H
