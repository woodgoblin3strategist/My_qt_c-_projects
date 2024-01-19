#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    QString str_set;
    str.replace(" ","");
    ui->plainTextEdit->clear();
    if(mis_o(str)) return;

    QQueue<QChar> postfix;
    QSet<int> st;

    str_set = ui->lineEdit_2->text();
    zap_set(str_set, st);
    values.insert('A', st);
    st.clear();
//    print(st);

    str_set = ui->lineEdit_3->text();
    zap_set(str_set, st);
    values.insert('B', st);
    st.clear();

    str_set = ui->lineEdit_4->text();
    zap_set(str_set, st);
    values.insert('C', st);
    st.clear();

    str_set = ui->lineEdit_5->text();
    zap_set(str_set, st);
    values.insert('D', st);
    st.clear();


    if(Inf_Post(str, postfix)){
        for(const auto &a: qAsConst(postfix)){
            ui->plainTextEdit->insertPlainText(QString(a) + " ");

        }
        calc(postfix);
    }


}

void Widget::zap_set(const QString &str, QSet<int> &st){
    bool ok;
    int i;
    QList<QString> str_list = str.split(QRegExp("[, ]"));
    for(const auto &a: qAsConst(str_list)){
        i = a.toInt(&ok);
        if(ok){
           st << i;
        }
    }
}

bool Widget::mis_o(const QString str){
    int end = str.length();
    for(int i = 0; i < end; i++){
        if((operations.contains(str[i])) && (str[i + 1] == ')')){
            ui->plainTextEdit->insertPlainText("\n ЗАКРЫВАЮЩАЯ СКОБКА ЗА ОПЕРАТОРОМ");
            return true;
        }
        else if((str[i] == ')') && (str[i + 1] == '(')){
            ui->plainTextEdit->insertPlainText("\n МЕЖДУ СКОБКАМИ НЕТУ ОПЕРАТОРА");
            return true;
        }
        else if((str[i] == '(') && (operations.contains(str[i + 1]))){
            ui->plainTextEdit->insertPlainText("\n ОПЕРАТОР СРАЗУ ЗА ОТКРЫВАЮЩЕЙ СКОБКОЙ");
            return true;
        }
        else if((str[i] == '(') && (str[i + 1] == ')')){
            ui->plainTextEdit->insertPlainText("\n В СКОБКАХ НИЧЕГО НЕТУ");
            return true;
        }

    }
    return false;
}
bool Widget::calc(const QQueue<QChar> &postfix){
    QStack<QSet<int>> result;
    QSet<int> k, l;

    for(auto a: postfix){
        if(values.contains(a)){
            result.push(values[a]);
            continue;
        }
        if(result.count() < 2){
             ui->plainTextEdit->insertPlainText("не хватает множества");
             return false;
        }
        if(a == '+'){
            k = result.pop();
//            if(result.isEmpty()){
//                ui->plainTextEdit->insertPlainText("не хватает множества");
//                return false;
//            }
            l = result.pop();
            result.push(k + l);
            continue;
        }
        if(a == '-'){
            k = result.pop();
//            if(result.isEmpty()){
//                ui->plainTextEdit->insertPlainText("\n не хватает множества");
//                return false;
//            }
            l = result.pop();
            result.push(l - k);
            continue;
        }
        if(a == '*'){
            k = result.pop();
//            if(result.isEmpty()){
//                ui->plainTextEdit->insertPlainText("\n не хватает множества");
//                return false;
//            }
            l = result.pop();
            result.push(k & l);
            continue;
        }
        return false;
    }

    k = result.pop();
    if(!result.isEmpty()){
        ui->plainTextEdit->insertPlainText("\n в стеке не только результат");
        return false;
    }
//    ui->plainTextEdit->insertPlainText("\n РЕЗУЛЬТАТ = " + QString::number(k));
    print(k);
    return true;

}

void Widget::print(const QSet<int> s){
    ui->plainTextEdit->insertPlainText("\n РЕЗУЛЬТАТ: ");
    for(auto a: s){
        ui->plainTextEdit->insertPlainText(QString::number(a) + " ");
    }
}

bool Widget::Inf_Post(const QString &str, QQueue<QChar> &postfix){
    QStack<QChar> helper;

    for(auto a: str){
        if(values.contains(a)){
            postfix << a;
            continue;
        }
        if(a == '('){
            helper.push(a);
            continue;
        }
        if(operations.contains(a)){
            while((!helper.isEmpty()) && (helper.top() != '(') && (operations[a] <= operations[helper.top()])){
                postfix << helper.pop();
            }
            helper.push(a);
            continue;
        }
        if(a == ')'){
            while((!helper.isEmpty()) && (helper.top() != '(')){
                postfix << helper.pop();
            }
            if(helper.isEmpty()){
                ui->plainTextEdit->insertPlainText("\n НЕТ (");
                return false;
            }
            helper.pop();
            continue;
        }
        ui->plainTextEdit->insertPlainText("\n НЕТ СИМВОЛА - " + QString(a));
        return false;

    }
    while(!helper.empty()){
        if(helper.top() == '('){
            ui->plainTextEdit->insertPlainText("\n ЛИШНЯЯ ( ");
            return false;
        }
        postfix << helper.pop();
    }
    return true;
}
