#include "teacher_window.h"
#include "ui_teacher_window.h"

TeacherWindow::TeacherWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);

    window_create_question = new CreateQuestionWindow();
    connect(window_create_question, &CreateQuestionWindow::window_teach, this, &TeacherWindow::show_TeachWindow);

    window_viewing_result = new ViewingResults();
    connect(window_viewing_result, &ViewingResults::window_teach, this, &TeacherWindow::show_TeachWindow);

    window_editing_test = new EditingTest();
    connect(window_editing_test, &EditingTest::window_teach, this, &TeacherWindow::show_TeachWindow);

}

TeacherWindow::~TeacherWindow()
{
    delete ui;
    delete window_create_question;
    delete window_viewing_result;
    delete window_editing_test;
}

void TeacherWindow::show_TeachWindow(){
    this->show();
}

void TeacherWindow::on_proverka_batton_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void TeacherWindow::on_createFile_clicked()
{
    window_create_question->show();
    this->close();
}

void TeacherWindow::on_openFile_clicked()
{
    window_viewing_result->show();
    this->close();
}

void TeacherWindow::on_editingTestButton_clicked()
{
    window_editing_test->show();
    this->close();
}
