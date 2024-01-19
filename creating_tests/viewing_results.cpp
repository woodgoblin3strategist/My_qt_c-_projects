#include "viewing_results.h"
#include "ui_viewing_results.h"

ViewingResults::ViewingResults(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewingResults)
{
    ui->setupUi(this);
}

ViewingResults::~ViewingResults()
{
    delete ui;
}

void ViewingResults::on_proverka_batton_clicked()
{
    ui->ResultEdit->clear();
    this->close();      // Закрываем окно
    emit window_teach(); // И вызываем сигнал на открытие учительского окна
}

void ViewingResults::traverseNode(const QDomNode& node) //рекурсивная функция для записи в структуру данных вопроса
{
   QDomNode domNode = node.firstChild();
   while(!domNode.isNull()) {
       if(domNode.isElement()) {// isElement() проверяет на элемент
          QDomElement domElement = domNode.toElement(); // toElement() преобразует к типу QDomElement
          if(!domElement.isNull()) {
              qDebug() << "TagName: " << domElement.tagName()
                       << "\tText: " << domElement.text();
              all_results += domElement.tagName() + ": " + domElement.text() + "\n";
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();
    }
}

void ViewingResults::openResultTest(QString str){ //открывам xml файл с данными теста
    QDomDocument domDoc; //объект класса QDomDocument представляет собой XML документ
    QFile        file(str);

    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement);
        }
        file.close();
    }
    ui->ResultEdit->setPlainText(all_results);
    all_results = nullptr;
}

void ViewingResults::on_chooseTestButton_clicked()
{
    ui->ResultEdit->clear();
    QString str = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home/woodgoblin/Рабочий стол/герцена/c++ qt/тесты/result_tests/",
                "xml files (*.xml)"
                );
    openResultTest(str);
}
