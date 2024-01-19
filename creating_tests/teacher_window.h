#ifndef TEACHER_WINDOW_H
#define TEACHER_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <create_question.h>
#include <viewing_results.h>
#include <editing_test.h>

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = 0);
    ~TeacherWindow();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_proverka_batton_clicked();

    void on_createFile_clicked();

    void show_TeachWindow();

    void on_openFile_clicked();

    void on_editingTestButton_clicked();

private:
    Ui::TeacherWindow *ui;
    CreateQuestionWindow *window_create_question;
    ViewingResults *window_viewing_result;
    EditingTest *window_editing_test;
};

#endif // TEACHER_WINDOW_H
