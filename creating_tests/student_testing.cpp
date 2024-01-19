#include "student_testing.h"
#include "ui_student_testing.h"

StudentTesting::StudentTesting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentTesting)
{
    ui->setupUi(this);
    //ui->NameTestEdit->setText(nameTest);

}

StudentTesting::~StudentTesting()
{
    delete ui;
    deleteQuestion();
    deleteTestRubbish();
    name_student = nullptr;
    result_test = nullptr;
}

void StudentTesting::on_proverka_batton_clicked()//возращение к окну студента
{
    this->close();      // Закрываем окно
    deleteQuestion(); // удаляем вопрос
    deleteTestRubbish();
    name_student = nullptr;
    result_test = nullptr;
    i_question = 0;
    N_question = 0;
    emit studentWindow(); // И вызываем сигнал на открытие главного окна
}

void StudentTesting::deleteTestRubbish(){//очищаем структуру
    for(int i = 0; i < N_question; i++){
        delete question_data[i];
    }
}

void StudentTesting::traverseNode(const QDomNode& node) //рекурсивная функция для записи в структуру данных вопроса
{
   int i = 0;
   QDomNode domNode = node.firstChild();
   while(!domNode.isNull()) {
       if(domNode.isElement()) {// isElement() проверяет на элемент
          QDomElement domElement = domNode.toElement(); // toElement() преобразует к типу QDomElement
          if(!domElement.isNull()) {
              if(domElement.tagName() == "question") {
                  N_question = domElement.attribute("number", "").toInt();
                  question_data[N_question] = new QuestionData;
                  i = 0;

                  qDebug() << "question: "
                           << N_question;
              }
              else if(domElement.tagName() == "testPage"){
                  question_data[N_question]->testPage = domElement.text();
                  qDebug() << "TagName: " << domElement.tagName()
                           << "\tText: " << question_data[N_question]->testPage;
              }
              else if(domElement.tagName() == "quantityAnswer"){
                  question_data[N_question]->quantityAnswer = domElement.text().toInt();
                  question_data[N_question]->el = new QString[question_data[N_question]->quantityAnswer]; // массив текстов ответов
                  qDebug() << "TagName: " << domElement.tagName()
                           << "\tText: " << question_data[N_question]->quantityAnswer;
              }
              else if(domElement.tagName() == "quantityTrueAnswer"){
                  question_data[N_question]->quantityTrueAnswer = domElement.text();
                  qDebug() << "TagName: " << domElement.tagName()
                           << "\tText: " << question_data[N_question]->quantityTrueAnswer;
              }
              else if(domElement.tagName() == "numberTrueAnswer"){
                  question_data[N_question]->numberTruAnswer = domElement.text();
                  qDebug() << "TagName: " << domElement.tagName()
                           << "\tText: " << question_data[N_question]->numberTruAnswer;
              }
              else if (domElement.tagName() == "answer"){
                  question_data[N_question]->el[i] = domElement.text();
                  qDebug() << "TagName: " << domElement.tagName() << domElement.attribute("number", "")
                           << "\tText: " << question_data[N_question]->el[i];
                  i++;
              }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();/*Если метод nextSibling () возвращает нулевое значение, то это значит, что узлов больше
нет.*/
    }
}

void StudentTesting::openTestData(){ //открывам xml файл с данными теста
    QDomDocument domDoc; //объект класса QDomDocument представляет собой XML документ
    QFile        file(str);

    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) { /*Для считывания
            ХМL-документа в метод setContext () объекта класса QDomDocument необходимо передать
            объект, созданный от класса, унаследованного от QIODevice.*/
            QDomElement domElement= domDoc.documentElement(); /*для получения объекта класса QDomElement выполняется вызов метода
documentElement () объекта класса QDomDocument, возвращающий корневой элемент ХМL­
документа.*/
            traverseNode(domElement);/*Полученный объект передается в функцию traverseNode (), которая обеспечива­
ет прохождение по всем элементам ХМL-документа.*/
        }
        file.close();
    }
}

void StudentTesting::createAnswerButton(){ //отображаем вопрос и ответы
    ui->questionEdit->setText(question_data[i_question]->testPage);//помещаем вопрос

    if(question_data[i_question]->quantityTrueAnswer.toInt() == 1){
        for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
            hl[i] = new QHBoxLayout(); //создаём horizontalLayout

            rb[i] = new QRadioButton(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива RadioButton
            hl[i]->addWidget(rb[i]); //помещаем элемент массива RadioButton в horizontalLayout

            le[i] = new QLineEdit(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива lineEdit
            hl[i]->addWidget(le[i]); //помещаем элемент массива lineEdit в horizontalLayout

            ui->verticalLayout->addLayout(hl[i]); //помещаем horizontalLayout в verticalLayout

            le[i]->setText(question_data[i_question]->el[i]);//записываем в lineEdit ответ
        }
    }
    else{
        for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
            hl[i] = new QHBoxLayout(); //создаём horizontalLayout

            cb[i] = new QCheckBox(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива QCheckBox
            hl[i]->addWidget(cb[i]); //помещаем элемент массива QCheckBox в horizontalLayout

            le[i] = new QLineEdit(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива lineEdit
            hl[i]->addWidget(le[i]); //помещаем элемент массива lineEdit в horizontalLayout

            ui->verticalLayout->addLayout(hl[i]); //помещаем horizontalLayout в verticalLayout

            le[i]->setText(question_data[i_question]->el[i]);//записываем в lineEdit ответ
        }
    }
}

void StudentTesting::deleteQuestion(){//удаляем ответы и вопрос с формы
        ui->questionEdit->clear();//очищаем форму вопроса

        if(question_data[i_question]->quantityTrueAnswer.toInt() == 1){
            for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
                ui->verticalLayout->removeWidget(le[i]); // удаляем с формы виджет
                ui->verticalLayout->removeWidget(rb[i]);
                ui->verticalLayout->removeItem(hl[i]);
                delete le[i]; //очищаем память элемента массива с виджетом
                delete rb[i];
                delete hl[i];
                le[i] = nullptr; //приравниваем нулю элемент массива для дальнейших проверок
                rb[i] = nullptr;
                hl[i] = nullptr;
            }
        }
        else{
            for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
                ui->verticalLayout->removeWidget(le[i]); // удаляем с формы виджет
                ui->verticalLayout->removeWidget(cb[i]);
                ui->verticalLayout->removeItem(hl[i]);
                delete le[i]; //очищаем память элемента массива с виджетом
                delete cb[i];
                delete hl[i];
                le[i] = nullptr; //приравниваем нулю элемент массива для дальнейших проверок
                cb[i] = nullptr;
                hl[i] = nullptr;
            }
        }
}

bool StudentTesting::findStudentChoice(){// записываем ответы ученика
    if(question_data[i_question]->quantityTrueAnswer.toInt() == 1){
        for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
            if(rb[i]->isChecked()){
                student_choice = QString::number(i);
            }
        }
    }
    else{
        for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
            if(cb[i]->isChecked()){
                student_choice += QString::number(i);
            }
        }
    }
    if(student_choice != nullptr){
        if(student_choice == question_data[i_question]->numberTruAnswer){
            arr_student_answer[i_question] = true;
        }
        else{
            arr_student_answer[i_question] = false;
        }
        student_choice = nullptr;
        return true;
    }
    else return false;
}

QDomElement my_createElement(      QDomDocument& domDoc,
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

void StudentTesting::saveResult(){//сохраниение результатов тестов
    int int_result_test = 0;
    for(int i = 0; i <= N_question; i++){
        if(arr_student_answer[i]){
            int_result_test++;
            arr_student_answer[i] = false;
        }
    }
    result_test = QString::number(int_result_test);
    name_student.replace(" ", "_"); //заменяем пробелы на _ чтобы атрибуты были корректны
    if(name_student.mid(0,1).toInt()){ // добавляем _ в начало ,если оно начинается с цифры
        name_student.prepend("_");
    }

    QString name_test_result = "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты/result_tests/" + name_test + ".xml";

    QDomDocument domDoc; //объект класса QDomDocument представляет собой XML документ
    QFile        file(name_test_result);//открываем файл с результатами

    if(file.open(QIODevice::ReadOnly)) {
        QDomElement domElement;
        if(domDoc.setContent(&file)) {
            domElement = domDoc.documentElement();
        }
        else{
            domElement = domDoc.createElement("result_test");
            domDoc.appendChild(domElement);
        }
        QDomElement student_result;

        student_result = my_createElement(domDoc, name_student, "", result_test);
        domElement.appendChild(student_result);

        file.close();
    }
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << domDoc.toString(); //записываем в него полученную структуру
        file.close();
    }

    QMessageBox::warning(this, "ТЕСТ ЗАКОНЧЕН", "правильных ответов:" + result_test, "закончить"); //выводим окно с результатом
    name_student = nullptr;
    result_test = nullptr;
}


void StudentTesting::on_nextQuestionButton_clicked()//следующий вопрос или завершение теста
{
    if(i_question == N_question - 1){ //если это будет последний вопрос
        ui->nextQuestionButton->setText("завершить тест");
    }
    if((i_question == N_question) && (findStudentChoice())){//завершение теста
        saveResult(); //сохраняем результаты теста

        ui->nextQuestionButton->setText("следующий вопрос");
        on_proverka_batton_clicked();
    }

    else if(findStudentChoice()){// переход на следующий вопрос
        deleteQuestion();
        i_question++;
        createAnswerButton();
    }
}
