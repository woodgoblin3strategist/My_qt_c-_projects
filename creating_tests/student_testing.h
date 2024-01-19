#ifndef STUDENT_TESTING_H
#define STUDENT_TESTING_H

#include <QWidget>
#include <QtXml>
#include <QtWidgets> //подключаем все виджеты
#include <QMessageBox>
#define max_N 10 //максимальное колличество динамически-созданных виджетов

namespace Ui {
class StudentTesting;
}

class StudentTesting : public QWidget
{
    Q_OBJECT

public:
    explicit StudentTesting(QWidget *parent = nullptr);
    ~StudentTesting();

    QString nameTest = nullptr;
    QLineEdit *le[max_N]; // создаём массив lineEdit
    QRadioButton *rb[max_N]; // создаём массив radioButton
    QCheckBox *cb[max_N]; // создаём массив checkBox
    QHBoxLayout *hl[max_N];// создаём массив horizontalLayout в который потом пихаем другие виджеты

    int N_question = 0; // колличество вопросов
    int i_question = 0;

    QString student_choice = nullptr;
    QString str = nullptr;
    QString name_student = nullptr; //имя студента
    QString result_test = nullptr; // результат студента
    QString name_test = nullptr; //имя теста

    bool arr_student_answer[max_N];

    struct QuestionData{//структура в которую пихаем все данные вопроса
        QString testPage;//текст самого вопроса
        int quantityAnswer;//количество ответов в вопросе
        QString quantityTrueAnswer;//количество верных ответов в вопросе
        QString numberTruAnswer;//номер или номера правельных ответов
        QString *el;// массив текстов ответов
    };
    QuestionData *question_data[max_N]; //массив данных вопроса

    void createAnswerButton();

    void openTestData();

signals:
    void studentWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_proverka_batton_clicked();

    void traverseNode(const QDomNode& node);

    void deleteTestRubbish();

    void on_nextQuestionButton_clicked();

    void deleteQuestion();

    bool findStudentChoice();

    void saveResult();


private:
    Ui::StudentTesting *ui;
};

#endif // STUDENT_TESTING_H
