#include "another_window.h"
#include "ui_another_window.h"

AnotherWindow::AnotherWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnotherWindow)
{
    ui->setupUi(this);
}

AnotherWindow::~AnotherWindow()
{
    delete ui;
}

void AnotherWindow::on_proverka_batton_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}
