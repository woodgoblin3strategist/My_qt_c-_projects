#include "create_question.h"
#include "ui_create_question.h"

CreateQuestionWindow::CreateQuestionWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateQuestionWindow)
{
    ui->setupUi(this);
    ui->quantityQuestionEdit->setText(QString::number(N_question));
    ui->quantityAnswerEdit->setText(QString::number(N_widget));
}

CreateQuestionWindow::~CreateQuestionWindow()
{
    delete ui;
    deleteQuestion();
    deleteTestRubbish();
}

void CreateQuestionWindow::on_proverka_batton_clicked()//переход на предыдущую страницу
{
    deleteQuestion();
    deleteTestRubbish();
    N_question = 0;
    i_widget = 0;
    N_widget = 0;
    ui->quantityQuestionEdit->setText(QString::number(N_question));
    ui->quantityAnswerEdit->setText(QString::number(N_widget));

    this->close();      // Закрываем окно
    emit window_teach(); // И вызываем сигнал на открытие учительского окна
}

void CreateQuestionWindow::on_createAnswerButton_clicked()//Создание виджетов(ответов)
{
    if(ui->oneTrueAnswerButton->isChecked()){
        if(N_widget < max_N){ // если не превышает максимальное колличество виджетов
            ui->quantityAnswerEdit->setText(QString::number(N_widget));

            hl[N_widget] = new QHBoxLayout(); //создаём horizontalLayout

            rb[N_widget] = new QRadioButton(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива RadioButton
            hl[N_widget]->addWidget(rb[N_widget]); //помещаем элемент массива RadioButton в horizontalLayout

            le[N_widget] = new QLineEdit(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива lineEdit
            hl[N_widget]->addWidget(le[N_widget]); //помещаем элемент массива lineEdit в horizontalLayout

            ui->verticalLayout->addLayout(hl[N_widget]); //помещаем horizontalLayout в verticalLayout

            le[N_widget]->setText(QString::number(N_widget));//записываем в lineEdit его индекс

            N_widget++; // добавляем +1 к колличеству виджетов
            ui->quantityAnswerEdit->setText(QString::number(N_widget));//количество виджетов(ответов)
        }
    }
    else if(ui->severalTruAnswerButton->isChecked()){
        if(N_widget < max_N){ // если не превышает максимальное колличество виджетов
            ui->quantityAnswerEdit->setText(QString::number(N_widget));

            hl[N_widget] = new QHBoxLayout(); //создаём horizontalLayout

            cb[N_widget] = new QCheckBox(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива CheckBox
            hl[N_widget]->addWidget(cb[N_widget]); //помещаем элемент массива CheckBox в horizontalLayout

            le[N_widget] = new QLineEdit(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива lineEdit
            hl[N_widget]->addWidget(le[N_widget]); //помещаем элемент массива lineEdit в horizontalLayout

            ui->verticalLayout->addLayout(hl[N_widget]); //помещаем horizontalLayout в verticalLayout

            le[N_widget]->setText(QString::number(N_widget));//записываем в lineEdit его индекс

            N_widget++; // добавляем +1 к колличеству виджетов
            ui->quantityAnswerEdit->setText(QString::number(N_widget));//количество виджетов(ответов)

        }
    }
    if(N_widget != 0){
        ui->oneTrueAnswerButton->hide();
        ui->severalTruAnswerButton->hide();
    }//скрываем виджеты множества ответов, если уже создан ответ
}

void CreateQuestionWindow::on_deleteAnswerButton_clicked()//удаление виджетов(ответов)
{
    i_widget = ui->numberAnswerEdit->text().toInt(); // считываем какой вопрос надо удалить

    if((ui->oneTrueAnswerButton->isChecked()) && (N_widget != 0)){//если элемент массива с виджетом не равен нулю
        ui->verticalLayout->removeWidget(le[i_widget]); // удаляем с формы виджет
        ui->verticalLayout->removeWidget(rb[i_widget]);
        ui->verticalLayout->removeItem(hl[i_widget]);
        delete le[i_widget]; //очищаем память элемента массива с виджетом
        delete rb[i_widget];
        delete hl[i_widget];
        le[i_widget] = nullptr; //приравниваем нулю элемент массива для дальнейших проверок
        rb[i_widget] = nullptr;
        hl[i_widget] = nullptr;
        for (int i = i_widget; i < N_widget-1; i++) { //смещаем элементы массивы
            le[i] = le[i+1];
            rb[i] = rb[i+1];
            hl[i] = hl[i+1];
        }
        N_widget--; // убаваляем на 1 колличество виджетов
        ui->quantityAnswerEdit->setText(QString::number(N_widget)); //количество виджетов(ответов)
    }
    else if((ui->severalTruAnswerButton->isChecked()) && (N_widget != 0)){//если элемент массива с виджетом не равен нулю
        ui->verticalLayout->removeWidget(le[i_widget]); // удаляем с формы виджет
        ui->verticalLayout->removeWidget(cb[i_widget]);
        ui->verticalLayout->removeItem(hl[i_widget]);
        delete le[i_widget]; //очищаем память элемента массива с виджетом
        delete cb[i_widget];
        delete hl[i_widget];
        le[i_widget] = nullptr; //приравниваем нулю элемент массива для дальнейших проверок
        cb[i_widget] = nullptr;
        hl[i_widget] = nullptr;
        for (int i = i_widget; i < N_widget-1; i++) { //смещаем элементы массивы
            le[i] = le[i+1];
            cb[i] = cb[i+1];
            hl[i] = hl[i+1];
        }
    N_widget--; // убаваляем на 1 колличество виджетов
    ui->quantityAnswerEdit->setText(QString::number(N_widget)); //количество виджетов(ответов)
    }
    if(N_widget == 0){
        ui->oneTrueAnswerButton->show();
        ui->severalTruAnswerButton->show();
    }//показываем виджеты множества ответов, если ответов снова ноль
}

void CreateQuestionWindow::deleteQuestion(){
    ui->questionEdit->clear();
    while(N_widget != 0){
        on_deleteAnswerButton_clicked();
    }
}

void CreateQuestionWindow::deleteTestRubbish(){
    for(int i = 0; i < N_question; i++){
        if(question_data[i] != nullptr){
            delete question_data[i];
            question_data[i] = nullptr;
        }
    }
}

bool CreateQuestionWindow::complected_question()//проверяем заполнен ли вопрос
{
    bool existence = false;
    if(N_widget == 0){
        return existence;
    }
    if(ui->oneTrueAnswerButton->isChecked()){
        for(int i = 0; i < N_widget; i++){
            if(rb[i]->isChecked()){
                existence = true;
            }
        }
    }
    else if(ui->severalTruAnswerButton->isChecked()){
        for(int i = 0; i < N_widget; i++){
            if(cb[i]->isChecked()){
                existence = true;
            }
        }
    }
    return existence;
}

void CreateQuestionWindow::on_saveQuestionButton_clicked()//сохранение вопроса
{
    if(!complected_question()){
        return;
    }
    question_data[N_question] = new QuestionData;
    //question_data[N_question] = nullptr;
    question_data[N_question]->quantityAnswer = N_widget; //количество ответов в вопросе

    if(ui->oneTrueAnswerButton->isChecked()){// если один правильный ответ
        question_data[N_question]->quantityTrueAnswer = "1";
        for(int i = 0; i < N_widget; i++) {
            if(rb[i]->isChecked()){
                question_data[N_question]->numberTruAnswer = QString::number(i);
            }
        }
    }
    else{
        int qTA = 0;
        for(int i = 0; i < N_widget; i++){// если несколько правильных ответов
            if(cb[i]->isChecked()){
                question_data[N_question]->numberTruAnswer += QString::number(i);
                qTA++;
            }
        }
        question_data[N_question]->quantityTrueAnswer = QString::number(qTA);
    }

    question_data[N_question]->el = new QString[question_data[N_question]->quantityAnswer]; // массив текстов ответов
    for(int i = 0; i < N_widget; i++){
        question_data[N_question]->el[i] = le[i]->text();
    }

    question_data[N_question]->testPage = ui->questionEdit->toPlainText(); //текст самого вопроса

    N_question++;
    ui->quantityQuestionEdit->setText(QString::number(N_question));

    deleteQuestion();
}

QDomElement makeElement(      QDomDocument& domDoc,
                        const QString&      strName,
                        const QString&      strAttr = QString::null,
                        const QString&      strText = QString::null
                       )//функция создания элемента
{
    QDomElement domElement = domDoc.createElement(strName);  //задаём название элемента

    if (!strAttr.isEmpty()) { //если нужно задаём номер элемента, в нашем случае номер ответа
        QDomAttr domAttr = domDoc.createAttribute("number");
        domAttr.setValue(strAttr);
        domElement.setAttributeNode(domAttr);
    }

    if (!strText.isEmpty()) {//задаём текст атрибута, в нашем случае текст ответа и тд
        QDomText domText = domDoc.createTextNode(strText);
        domElement.appendChild(domText);
    }
    return domElement;
}

QDomElement CreateQuestionWindow::question(QDomDocument& domDoc,
                     const QString&  testPage,
                     int quantityAnswer,
                     const QString&  quantityTrueAnswer,
                     const QString&  numberTruAnswer,
                     QString *el){ //функция создания вопроса
    static int nNumber = 0; // номер вопроса

    QDomElement domElement = makeElement(domDoc,
                                         "question",
                                         QString().setNum((nNumber))
                                         ); //создаём вопрос

    //добавляем в него детей, тоесть добавляем данные вопроса в него
    domElement.appendChild(makeElement(domDoc, "testPage", "", testPage));
    domElement.appendChild(makeElement(domDoc, "quantityAnswer", "", QString().setNum((quantityAnswer))));
    domElement.appendChild(makeElement(domDoc, "quantityTrueAnswer", "", quantityTrueAnswer));
    domElement.appendChild(makeElement(domDoc, "numberTrueAnswer", "", numberTruAnswer));

    for(int i = 0; i < quantityAnswer; i++){
        domElement.appendChild(makeElement(domDoc, "answer", QString().setNum(i), el[i]));
    }
    nNumber++;
    return domElement;
}

void CreateQuestionWindow::on_saveTestButton_clicked()
{
    if(question_data[0] == nullptr){
        return;
    }
    QString str = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты/test");
    if(str.isEmpty()){
        return;
    }
    str += ".xml";
    QDomDocument doc("test");// задаём имя теста
    QDomElement  domElement = doc.createElement("test");
    doc.appendChild(domElement);

    QDomElement set_question;
    for(int i = 0; i < N_question; i++){
        set_question = question(doc,
                                   question_data[i]->testPage,
                                   question_data[i]->quantityAnswer,
                                   question_data[i]->quantityTrueAnswer,
                                   question_data[i]->numberTruAnswer,
                                   question_data[i]->el);// создаём вопрос
        domElement.appendChild(set_question);// добавляем его в в наш документ
    }

    QFile file(str);// создаём файл
    QString name_test = "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты/result_tests/" + QFileInfo(file).fileName();//записываем имя теста
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << doc.toString(); //записываем в него полученную структуру
        file.close();
    }
    QFile file_answer(name_test);//
    if(file_answer.open(QIODevice::WriteOnly)) {
        file_answer.close();
    }
    //deleteTestRubbish();
    on_proverka_batton_clicked();
}
