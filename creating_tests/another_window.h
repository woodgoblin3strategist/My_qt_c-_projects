#ifndef ANOTHER_WINDOW_H
#define ANOTHER_WINDOW_H

#include <QWidget>

namespace Ui {
class AnotherWindow;
}

class AnotherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnotherWindow(QWidget *parent = 0);
    ~AnotherWindow();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_proverka_batton_clicked();

private:
    Ui::AnotherWindow *ui;
};

#endif // ANOTHER_WINDOW_H

