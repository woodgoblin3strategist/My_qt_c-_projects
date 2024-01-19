#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include<QMap>
#include<QQueue>
#include<QVector>
#include<QStack>
#include<QSet>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QMap<QChar,int> operations = {{'*', 20}, {'+', 10}, {'-', 10}};
//    QMap<QChar,int> values = {{'A', 3}, {'B', 4}, {'C', 5}, {'D', 6}};
    QMap<QChar,QSet<int>> values;// = {{'A', {1, 2, 3}}, {'B', {3, 4, 5}}, {'C', {1, 4 , 6}}, {'D', {5, 7 , 8}}};

    bool Inf_Post(const QString &str, QQueue<QChar> &postfix);
    bool calc(const QQueue<QChar> &postfix);
    void print(const QSet<int> s);
    void zap_set(const QString &str, QSet<int> &st);
    bool mis_o(const QString str);

};
#endif // WIDGET_H
