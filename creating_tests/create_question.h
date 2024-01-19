#ifndef CREATE_QUESTION_H
#define CREATE_QUESTION_H

#include <QWidget>
#include <QtWidgets> //подключаем все виджеты
#include <QtXml> // для работы с xml файлами
#define max_N 10 //максимальное колличество динамически-созданных виджетов

namespace Ui {
class CreateQuestionWindow;
}

class CreateQuestionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateQuestionWindow(QWidget *parent = 0);
    ~CreateQuestionWindow();

    QLineEdit *le[max_N]; // создаём массив lineEdit
    QRadioButton *rb[max_N]; // создаём массив radioButton
    QCheckBox *cb[max_N]; // создаём массив checkBox
    QHBoxLayout *hl[max_N];// создаём массив horizontalLayout в который потом пихаем другие виджеты
    int i_widget = 0; // индекс динамически-созданного виджета
    int N_widget = 0; // колличество динамечески-созданных виджетов
    int N_question = 0; // колличество вопросов

    struct QuestionData{//структура в которую пихаем все данные вопроса
        QString testPage;//текст самого вопроса
        int quantityAnswer;//количество ответов в вопросе
        QString quantityTrueAnswer;//количество верных ответов в вопросе
        QString numberTruAnswer;//номер или номера правельных ответов
        QString *el;// массив текстов ответов
    };
    QuestionData *question_data[max_N]; //массив данных вопроса

signals:
    void window_teach();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_proverka_batton_clicked();

    void on_createAnswerButton_clicked();

    void on_saveQuestionButton_clicked();

    void on_deleteAnswerButton_clicked();

    QDomElement question(QDomDocument& domDoc,
                         const QString&  testPage,
                         int quantityAnswer,
                         const QString&  quantityTrueAnswer,
                         const QString&  numberTruAnswer,
                         QString el[max_N]);

    void on_saveTestButton_clicked();

    void deleteQuestion();
    void deleteTestRubbish();

    bool complected_question();

private:
    Ui::CreateQuestionWindow *ui;
};

#endif // CREATE_QUESTION_H



