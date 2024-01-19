#include "student_window.h"
#include "ui_student_window.h"

StudentWindow::StudentWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentWindow)
{
    ui->setupUi(this);

    window_student_testing = new StudentTesting();
    connect(window_student_testing, &StudentTesting::studentWindow, this, &StudentWindow::show_studentWindow);
}

StudentWindow::~StudentWindow()
{
    delete ui;
    delete window_student_testing;
}

void StudentWindow::show_studentWindow(){
    this->show();
    ui->nameTestEdit->clear();
    ui->StudentNameEdit->clear();
}


void StudentWindow::on_proverka_batton_clicked()
{
    ui->StudentNameEdit->clear();
    ui->nameTestEdit->clear();
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void StudentWindow::on_startButton_clicked()//начало работы теста
{
    if((!name_test.isEmpty()) && (!str.isEmpty()) && (!ui->StudentNameEdit->text().isEmpty())){//Если все данные введены
        window_student_testing->show(); //показываем окно теста
        window_student_testing->str = str; //переменная места и названия теста
        window_student_testing->name_test = name_test; // переменная названия теста
        window_student_testing->name_student = ui->StudentNameEdit->text();// записываем имя студента
        str = nullptr;
        name_test = nullptr;

        window_student_testing->openTestData(); //запись в масссив структур данные теста из xml файла
        window_student_testing->createAnswerButton(); //создаём первый вопрос,чтоб он сразу отабразился на форме при открытии
        this->close(); //закрываем нынешнее окно
    }
}

void StudentWindow::on_openFile_clicked()//выбор нужного теста
{
    str = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты",
                "xml files (*.xml)"
                );
    QFile file(str);
    name_test = QFileInfo(file).baseName();
    ui->nameTestEdit->setText(name_test);
}
