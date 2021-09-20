#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>

#include "mydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QPixmap labelPixmap;
    QPixmap plot;

    MyDialog myDialog;

    void paintEvent(QPaintEvent *pEvent);
    void resizeEvent(QResizeEvent *pEvent);

private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_program_triggered();

    void on_actionData_triggered();

    void repaint(double, double, double, double, double);

private:
    Ui::MainWindow *ui;
    double xStart;
    double xEnd;
    double a, b, c;
    int pointCount;
};
#endif // MAINWINDOW_H
