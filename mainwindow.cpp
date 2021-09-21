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
    , pointCount(1000)
{
    ui->setupUi(this);

    firstPixmap = QPixmap(ui->centralwidget->width(),ui->centralwidget->height());
    secondPixmap = QPixmap(ui->centralwidget->width(),ui->centralwidget->height());

    ui->label->setPixmap(firstPixmap);
    connect(&myDialog, &MyDialog::signal, this, &MainWindow::repaint);


    QString msg = "y = ";
    msg += QString::number(a);
    msg += " * x^";
    msg += QString::number(b);
    msg += " + ";
    msg += QString::number(c);
    ui->statusbar->showMessage(msg);
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

    double width = std::min(ui->centralwidget->width(), ui->centralwidget->height());

    QPainter painter(&firstPixmap);
    painter.drawPixmap(0, 0, secondPixmap);

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(width/2, 0, width / 2, width);
    painter.drawLine(0, width/2, width, width/2);

    painter.setPen(QPen(Qt::red, 4));
    double h = (xEnd - xStart)/pointCount;
    double step = xStart;
    double xScale = width / (xEnd - xStart);
    double maxY = DBL_MIN;
    double minY = DBL_MAX;

    std::vector<std::pair<double, double>> points;

    for(int i = 0; i <= pointCount; ++i){
        if((b < 0 && step > -0.01 && step < 0.01) ||
           (b > -1 && b < 0 && step <= 0) ||
           (b > 0 && b < 1 && step < 0)){
            step += h;
            continue;
        }

        double y = a * std::pow(step, b) + c;

        if(maxY < y){
            maxY = y;
        }

        if(minY > y){
            minY = y;
        }

        points.push_back(std::pair(step, y));
        step += h;
    }

    double yScale = (width / 2)  / (maxY - minY);

    for(int i = 0; i < points.size() - 1; ++i){
        painter.drawLine(width/2 + points[i].first * xScale, width/2 - (points[i].second * yScale),
                         width/2 + points[i + 1].first * xScale, width/2 - (points[i + 1].second * yScale));
    }

    painter.setPen(QPen(Qt::black, 2));
    painter.drawText((width/2 + xStart * xScale) < 0 ? 0 : width/2 + xStart * xScale,
                     width/2 + 15, QString::number(xStart));
    painter.drawText(width/2 + xEnd * xScale + h * xScale >= width ? width - 20 : width/2 + xEnd * xScale + h * xScale,
                     width/2 + 15, QString::number(xEnd));
    painter.drawText(width/2 + 5,
                     width/2 - maxY * yScale < 20 ? 20 : width/2 - maxY * yScale, QString::number(maxY));
    painter.drawText(width/2 + 5,
                     width/2 - minY * yScale > width - 20 ? width - 20 : width/2 - minY * yScale, QString::number(minY));

    ui->label->setPixmap(firstPixmap);
}

void MainWindow::resizeEvent(QResizeEvent *pEvent){
    double plotSize = std::min(ui->centralwidget->width(),ui->centralwidget->height());
    secondPixmap = QPixmap(plotSize,plotSize);
    firstPixmap = QPixmap(plotSize,plotSize);
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
    QString msg = "y = ";
    msg += QString::number(a);
    msg += " * x^";
    msg += QString::number(b);
    msg += " + ";
    msg += QString::number(c);
    ui->statusbar->showMessage(msg);
}

