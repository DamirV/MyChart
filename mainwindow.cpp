#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , xStart(-10)
    , xEnd(10)
    , a(1)
    , b(2)
    , c(0)
    , pointCount(100)
{
    ui->setupUi(this);

    labelPixmap = QPixmap(ui->centralwidget->width(),ui->centralwidget->height());
    plot = QPixmap(ui->centralwidget->width(),ui->centralwidget->height());

    ui->label->setPixmap(labelPixmap);
    connect(&myDialog, &MyDialog::signal, this, &MainWindow::repaint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *pEvent)
{
    if(xEnd <= xStart){
        return;
    }
    QPainter painter(&labelPixmap);
    painter.drawPixmap(0, 0, plot);

    double width = ui->label->width();
    painter.setPen(QPen(Qt::black, 2));
    //double width = std::max(xStart, xEnd);
    painter.drawLine(width/2, 0, width / 2, width);
    painter.drawLine(0, width/2, width, width/2);
    //painter.draw

    painter.setPen(QPen(Qt::red, 4));

    double h = (xEnd - xStart)/pointCount;
    double y1 = a * std::pow(xStart, b) + c;
    double y2;
    double step = xStart;
    for(int i = 0; i < pointCount; ++i){
        y2 = a * std::pow(step, b) + c;
        painter.drawLine(width/2.f + step, width/2.f - y1, width/2.f + step + h, width/2.f - y2);
        y1 = y2;
        step += h;
    }


    ui->label->setPixmap(labelPixmap);
}

void MainWindow::resizeEvent(QResizeEvent *pEvent){
    double plotSize = std::min(ui->centralwidget->width(),ui->centralwidget->height());
    plot = QPixmap(plotSize,plotSize);
    labelPixmap = QPixmap(plotSize,plotSize);
    ui->label->resize(plotSize, plotSize);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionAbout_program_triggered()
{
    QMessageBox::information(this, tr("Just graph"), tr("some info"));
}


void MainWindow::on_actionData_triggered()
{
    myDialog.show();
}

void MainWindow::repaint(double _xStart, double _xEnd, double _a, double _b, double _c){
    xStart = _xStart;
    xEnd = _xEnd;
    a = _a;
    b = _b;
    c = _c;
}

