#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Инициализируем второе окно
    window_teach = new TeacherWindow();
    connect(window_teach, &TeacherWindow::firstWindow, this, &MainWindow::show);

    // Инициализируем третье окно
    window_student = new StudentWindow();
    // подключаем к слоту запуска главного окна по кнопке в третьем окне
    connect(window_student, &StudentWindow::firstWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete window_student;
    delete window_teach;
}


void MainWindow::on_teacher_batton_clicked()
{
    window_teach->show();
    this->close();
}

void MainWindow::on_student_batton_clicked()
{
    window_student->show();
    this->close();
}
