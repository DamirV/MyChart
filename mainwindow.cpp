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
    double width = std::min(ui->centralwidget->width(),ui->centralwidget->height());

    QPainter painter(&labelPixmap);
    painter.drawPixmap(0, 0, plot);

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(width/2, 0, width / 2, width);
    painter.drawLine(0, width/2, width, width/2);

    painter.setPen(QPen(Qt::red, 4));
    double h = (xEnd - xStart)/pointCount;
    double yStart = a * std::pow(xStart, b) + c;
    double yEnd;
    double step = xStart + h;

    double xScale = width / (xEnd - xStart);
    double maxY = std::max( std::abs(a * pow(xStart, b) + c), std::abs(a * pow(xEnd, b) + c));
    double yScale = (width/2) / (maxY);

    for(int i = 0; i < pointCount; ++i){
        yEnd = a * std::pow(step, b) + c;
        painter.drawLine(width/2 + step * xScale, width/2 - yStart * yScale,
                         width/2 + step * xScale + h * xScale, width/2 - yEnd * yScale);
        yStart = yEnd;
        step += h;
    }

    painter.setPen(QPen(Qt::black, 2));
    painter.drawText((width/2 + xStart * xScale) < 0 ? 0 : width/2 + xStart * xScale,
                     width/2 + 15, QString::number(xStart));
    painter.drawText(width/2 + xEnd * xScale + h * xScale >= width ? width - 20 : width/2 + xEnd * xScale + h * xScale,
                     width/2 + 15, QString::number(xEnd));
    painter.drawText(width/2, width/2 - maxY * yScale + 20, QString::number(maxY));

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

