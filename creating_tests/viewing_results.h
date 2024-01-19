#ifndef VIEWING_RESULTS_H
#define VIEWING_RESULTS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtXml>
#include <QtWidgets> //подключаем все виджеты
#include <QMessageBox>

namespace Ui {
class ViewingResults;
}

class ViewingResults : public QWidget
{
    Q_OBJECT

public:
    explicit ViewingResults(QWidget *parent = nullptr);
    ~ViewingResults();

     QString all_results = nullptr;

signals:
    void window_teach();  // Сигнал для открытия

private slots:
    // Слот-обработчик нажатия кнопки
    void on_proverka_batton_clicked();

    void on_chooseTestButton_clicked();

    void openResultTest(QString str);

    void traverseNode(const QDomNode& node);

private:
    Ui::ViewingResults *ui;
};

#endif // VIEWING_RESULTS_H
