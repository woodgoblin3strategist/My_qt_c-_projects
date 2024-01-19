#include "editing_test.h"
#include "ui_editing_test.h"

EditingTest::EditingTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditingTest)
{
    ui->setupUi(this);

    deleteTestRubbish();
}

EditingTest::~EditingTest()
{
    delete ui;
    deleteTestRubbish();
}

void EditingTest::deleteTestRubbish(){ //очищаем структуру
    for(int i = 0; i < N_question; i++){
        delete question_data[i];
        question_data[i] = nullptr;
    }
}

void EditingTest::on_proverka_batton_clicked() //возращение к окну тичера
{
    this->close();      // Закрываем окно
    emit window_teach(); // И вызываем сигнал на открытие учительского окна
    deleteTestRubbish();
    deleteQuestion();

    i_widget = 0;
    N_widget = 0;
    i_question = 0;
    N_question = 0;
    ui->quantityAnswerEdit->clear();
    ui->chooseQuestionEdit->clear();
    ui->nameTestEdit->clear();
    ui->numberAnswerEdit->clear();
    ui->questionEdit->clear();
    ui->quantityQuestionEdit->clear();
}

void EditingTest::traverseNode(const QDomNode& node) //рекурсивная функция для записи в структуру данных вопроса
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
              }
              else if(domElement.tagName() == "testPage"){
                  question_data[N_question]->testPage = domElement.text();
              }
              else if(domElement.tagName() == "quantityAnswer"){
                  question_data[N_question]->quantityAnswer = domElement.text().toInt();
                  question_data[N_question]->el = new QString[question_data[N_question]->quantityAnswer]; // массив текстов ответов
              }
              else if(domElement.tagName() == "quantityTrueAnswer"){
                  question_data[N_question]->quantityTrueAnswer = domElement.text();
              }
              else if(domElement.tagName() == "numberTrueAnswer"){
                  question_data[N_question]->numberTruAnswer = domElement.text();
              }
              else if (domElement.tagName() == "answer"){
                  question_data[N_question]->el[i] = domElement.text();
                  i++;
              }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();/*Если метод nextSibling () возвращает нулевое значение, то это значит, что узлов больше
нет.*/
    }
}

void EditingTest::openTestData(QString str){ //открывам xml файл с данными теста
    QDomDocument domDoc; //объект класса QDomDocument представляет собой XML документ
    QFile        file(str);

    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement);
        }
        file.close();
    }
}

void EditingTest::on_openTestButton_clicked() //открываем тест для редактирования
{
    QString str = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты",
                "xml files (*.xml)"
                );
    QFile file(str);
    QString name_test = QFileInfo(file).baseName(); //имя теста без адресса и расширения
    ui->nameTestEdit->setText(name_test);

    openTestData(str); //запись данных с XML в структуру
    ui->quantityQuestionEdit->setText(QString::number(N_question+1));

    ui->chooseQuestionEdit->setText("0");
    on_chooseQuestionButton_clicked(); //открываем нулевой вопрос
}

void EditingTest::on_chooseQuestionButton_clicked() //выбор вопроса и отображение его на виджет
{
    if(save_q){ //если мы решили отобразить другой вопрос, не сохранив новосозданный
        N_question--;
        save_q = false;
    }
    deleteQuestion();
    i_question = ui->chooseQuestionEdit->text().toInt();//узнаём номер вопроса

//    qDebug() << i_question <<" :"
//            << question_data[i_question]->testPage;
    ui->questionEdit->setText(question_data[i_question]->testPage);//помещаем вопрос

    if(question_data[i_question]->quantityTrueAnswer.toInt() == 1){
        ui->oneTrueAnswerButton->setChecked(true); //ставим галочку, если в тесте один правильный ответ
        int i_number_tru_answer = question_data[i_question]->numberTruAnswer.toInt();// индекс правильного ответа

        for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
            hl[i] = new QHBoxLayout(); //создаём horizontalLayout

            rb[i] = new QRadioButton(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива RadioButton
            hl[i]->addWidget(rb[i]); //помещаем элемент массива RadioButton в horizontalLayout

            le[i] = new QLineEdit(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива lineEdit
            hl[i]->addWidget(le[i]); //помещаем элемент массива lineEdit в horizontalLayout

            ui->verticalLayout->addLayout(hl[i]); //помещаем horizontalLayout в verticalLayout

            le[i]->setText(question_data[i_question]->el[i]);//записываем в lineEdit ответ

            if(i == i_number_tru_answer){ //ставим галочку в RadioButton правильного ответа
                rb[i]->setChecked(true);
            }
        }
    }
    else{
        ui->severalTruAnswerButton->setChecked(true);//ставим галочку, если в тесте несколько правильных ответов
        int N = question_data[i_question]->quantityTrueAnswer.toInt(); //от сюда
        QString s = question_data[i_question]->numberTruAnswer;
        int i_true[N];
        int k = 0;
        for(k = 0; k < N; k++){
            i_true[k] = s.mid(k, 1).toInt(); //до сюда разбиваем на массив индексов правильных ответов
        }
        k = 0;

        for(int i = 0; i < question_data[i_question]->quantityAnswer; i++){
            hl[i] = new QHBoxLayout(); //создаём horizontalLayout

            cb[i] = new QCheckBox(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива QCheckBox
            hl[i]->addWidget(cb[i]); //помещаем элемент массива QCheckBox в horizontalLayout

            le[i] = new QLineEdit(ui->verticalLayoutWidget); //создаём и приравниваем элементу массива lineEdit
            hl[i]->addWidget(le[i]); //помещаем элемент массива lineEdit в horizontalLayout

            ui->verticalLayout->addLayout(hl[i]); //помещаем horizontalLayout в verticalLayout

            le[i]->setText(question_data[i_question]->el[i]);//записываем в lineEdit ответ

            if(i == i_true[k]){
                cb[i]->setChecked(true);
                k++;
            }
        }
    }
    N_widget = question_data[i_question]->quantityAnswer; //колличество виджетов(ответов)
    if(N_widget != 0){
        ui->oneTrueAnswerButton->hide();
        ui->severalTruAnswerButton->hide();
    }//скрываем виджеты множества ответов, если уже создан ответ
}

void EditingTest::on_createAnswerButton_clicked() //создание ответа
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

void EditingTest::on_deleteAnswerButton_clicked() //удаление ответа
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
    else if((ui->severalTruAnswerButton->isChecked())&& (N_widget != 0)){//если элемент массива с виджетом не равен нулю
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

bool EditingTest::complected_question()//проверяем заполнен ли вопрос
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

void EditingTest::on_saveQuestionButton_clicked() //сохранение вопроса
{
    if(!complected_question()){
        return;
    }
    if(save_q){
        save_q = false; //значит мы сохранили вопрос
    }

    question_data[i_question] = new QuestionData;
    question_data[i_question]->quantityAnswer = N_widget; //количество ответов в вопросе

    if(ui->oneTrueAnswerButton->isChecked()){// если один правильный ответ
        question_data[i_question]->quantityTrueAnswer = "1";
        for(int i = 0; i < N_widget; i++) {
            if(rb[i]->isChecked()){
                question_data[i_question]->numberTruAnswer = QString::number(i);
            }
        }
    }
    else{
        int qTA = 0;
        for(int i = 0; i < N_widget; i++){// если несколько правильных ответов
            if(cb[i]->isChecked()){
                question_data[i_question]->numberTruAnswer += QString::number(i);
                qTA++;
            }
        }
        question_data[i_question]->quantityTrueAnswer = QString::number(qTA);
    }

    question_data[i_question]->el = new QString[question_data[i_question]->quantityAnswer]; // массив текстов ответов
    for(int i = 0; i < N_widget; i++){
        question_data[i_question]->el[i] = le[i]->text();
    }

    question_data[i_question]->testPage = ui->questionEdit->toPlainText(); //текст самого вопроса

    ui->chooseQuestionEdit->setText(QString::number(i_question));
    ui->quantityQuestionEdit->setText(QString::number(N_question+1));
}

void EditingTest::deleteQuestion(){ //удаление вороса c виджета
    ui->questionEdit->clear();
    while(N_widget != 0){
        on_deleteAnswerButton_clicked();
    }
}

void EditingTest::on_createQuestionButton_clicked() //создание вопроса
{
    if(question_data[N_question] == nullptr){
        return;
    }
    save_q = true; //вопрос создан
    deleteQuestion();
    N_question++;
    ui->chooseQuestionEdit->setText(QString::number(N_question));
    i_question = N_question;
}

QDomElement edit_makeElement(      QDomDocument& domDoc,
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

QDomElement EditingTest::question(QDomDocument& domDoc,
                     const QString&  testPage,
                     int quantityAnswer,
                     const QString&  quantityTrueAnswer,
                     const QString&  numberTruAnswer,
                     QString *el){ //функция создания вопроса
    static int nNumber = 0; // номер вопроса

    QDomElement domElement = edit_makeElement(domDoc,
                                         "question",
                                         QString().setNum((nNumber))
                                         ); //создаём вопрос

    //добавляем в него детей, тоесть добавляем данные вопроса в него
    domElement.appendChild(edit_makeElement(domDoc, "testPage", "", testPage));
    domElement.appendChild(edit_makeElement(domDoc, "quantityAnswer", "", QString().setNum((quantityAnswer))));
    domElement.appendChild(edit_makeElement(domDoc, "quantityTrueAnswer", "", quantityTrueAnswer));
    domElement.appendChild(edit_makeElement(domDoc, "numberTrueAnswer", "", numberTruAnswer));

    for(int i = 0; i < quantityAnswer; i++){
        domElement.appendChild(edit_makeElement(domDoc, "answer", QString().setNum(i), el[i]));
    }
    nNumber++;
    return domElement;
}

void EditingTest::on_saveTestButton_clicked() //сохраняем изменения в тесте
{
    if(question_data[0] == nullptr){
       return;
    }
    QString str = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты/test№");
    if(str.isEmpty()){
        return;
    }
    str += ".xml";
    QDomDocument doc("test");// задаём имя теста
    QDomElement  domElement = doc.createElement("test");
    doc.appendChild(domElement);

    QDomElement set_question;
    for(int i = 0; i <= N_question; i++){
        set_question = question(doc,
                                   question_data[i]->testPage,
                                   question_data[i]->quantityAnswer,
                                   question_data[i]->quantityTrueAnswer,
                                   question_data[i]->numberTruAnswer,
                                   question_data[i]->el);// создаём вопрос
        domElement.appendChild(set_question);// добавляем его в в наш документ
    }

    QFile red_file(str);// создаём файл
    QString name_test = "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты/result_tests/" + QFileInfo(red_file).fileName();//записываем имя теста
    if(red_file.open(QIODevice::WriteOnly)) {
        QTextStream(&red_file) << doc.toString(); //записываем в него полученную структуру
        red_file.close();
    }
    QFile file_answer(name_test);//
    if(file_answer.open(QIODevice::WriteOnly)) {
        file_answer.close();
    }
    //deleteTestRubbish();
    on_proverka_batton_clicked();
}

void EditingTest::on_deleteQuestionButton_clicked() //удаление вопроса
{
    if(ui->quantityQuestionEdit->text().toInt() == 0){
        return;
    }
    deleteQuestion();
    //delete question_data[i_question];
    question_data[i_question] = nullptr;

    for(int i = i_question; i < N_question; i++){
        question_data[i] = question_data[i+1];
    }
    if(question_data[N_question] != nullptr){
        //delete question_data[N_question];
        question_data[N_question] = nullptr;
    }
    if(i_question == N_question){ //если удаляли последний по нумеровке вопрос
        if(i_question != 0){ //если это был последний вопрос
            i_question--;
            ui->chooseQuestionEdit->setText(QString::number(i_question));
        }
    }

    if(ui->quantityQuestionEdit->text().toInt() == 1){ //если удалили последний вопрос
        deleteQuestion();
        ui->quantityQuestionEdit->setText("0");
        return;
    }
    N_question--;
    ui->quantityQuestionEdit->setText(QString::number(N_question+1));
    on_chooseQuestionButton_clicked();
}

void EditingTest::on_backButton_clicked() //открыть предыдущий вопрос
{
    i_question = ui->chooseQuestionEdit->text().toInt();
    if(i_question != 0){
        i_question--;
    }
    ui->chooseQuestionEdit->setText(QString::number(i_question));
    on_chooseQuestionButton_clicked();
}

void EditingTest::on_next_clicked() //открыть следующий вопрос
{
    i_question = ui->chooseQuestionEdit->text().toInt();
    if(i_question != N_question){
        i_question++;
    }
    ui->chooseQuestionEdit->setText(QString::number(i_question));
    on_chooseQuestionButton_clicked();
}
