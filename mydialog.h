#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_xStart_valueChanged(double arg1);

    void on_xEnd_valueChanged(double arg1);

    void on_aBox_valueChanged(double arg1);

    void on_bBox_valueChanged(double arg1);

    void on_cBox_valueChanged(double arg1);

signals:
    void signal(double, double, double, double, double);

private:
    Ui::MyDialog *ui;
    void emitSignal();
};

#endif // MYDIALOG_H
