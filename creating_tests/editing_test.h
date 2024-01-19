#ifndef EDITING_TEST_H
#define EDITING_TEST_H

#include <QWidget>
#include <QtWidgets> //подключаем все виджеты
#include <QtXml> // для работы с xml файлами
#define max_N 10 //максимальное колличество динамически-созданных виджетов

namespace Ui {
class EditingTest;
}

class EditingTest : public QWidget
{
    Q_OBJECT

public:
    explicit EditingTest(QWidget *parent = nullptr);
    ~EditingTest();

signals:
    void window_teach();  // Сигнал для открытия учительского окна

private slots:
    void on_proverka_batton_clicked();

    void traverseNode(const QDomNode& node); //вспомогательная функция для функции openTestData()

    void openTestData(QString str); //записываем тест в структуру

    void deleteTestRubbish();// очищение массива структур

    void on_openTestButton_clicked();

    void on_chooseQuestionButton_clicked();

    void on_createAnswerButton_clicked();

    void on_deleteAnswerButton_clicked();

    void on_saveQuestionButton_clicked();

    void on_createQuestionButton_clicked();

    void deleteQuestion();

    void on_saveTestButton_clicked();

    QDomElement question(QDomDocument& domDoc,
                         const QString&  testPage,
                         int quantityAnswer,
                         const QString&  quantityTrueAnswer,
                         const QString&  numberTruAnswer,
                         QString el[10]);

    void on_deleteQuestionButton_clicked();

    void on_backButton_clicked();

    void on_next_clicked();

    bool complected_question();

private:
    Ui::EditingTest *ui;


    QLineEdit *le[max_N]; // создаём массив lineEdit
    QRadioButton *rb[max_N]; // создаём массив radioButton
    QCheckBox *cb[max_N]; // создаём массив checkBox
    QHBoxLayout *hl[max_N];// создаём массив horizontalLayout в который потом пихаем другие виджеты
    int i_widget = 0; // индекс динамически-созданного виджета
    int N_widget = 0; // колличество динамечески-созданных виджетов

    int i_question = 0;
    int N_question = 0; // колличество вопросов

    bool save_q = false; //переменная для проверки был ли сохранён добавленный вопрос

    struct QuestionData{//структура в которую пихаем все данные вопроса
        QString testPage;//текст самого вопроса
        int quantityAnswer;//количество ответов в вопросе
        QString quantityTrueAnswer;//количество верных ответов в вопросе
        QString numberTruAnswer;//номер или номера правельных ответов
        QString *el;// массив текстов ответов
    };
    QuestionData *question_data[max_N]; //массив данных вопроса

};

#endif // EDITING_TEST_H
