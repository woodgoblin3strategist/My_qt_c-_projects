#ifndef STUDENT_WINDOW_H
#define STUDENT_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include "student_testing.h"

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

    QString str = nullptr;
    QString name_test = nullptr;

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_proverka_batton_clicked();

    void show_studentWindow();

    void on_startButton_clicked();

    void on_openFile_clicked();

private:
    Ui::StudentWindow *ui;

    StudentTesting *window_student_testing;
};

#endif // STUDENT_WINDOW_H
