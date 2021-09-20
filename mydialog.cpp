#include "mydialog.h"
#include "ui_mydialogwindow.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_xStart_valueChanged(double arg1)
{
    emitSignal();
}

void MyDialog::on_xEnd_valueChanged(double arg1)
{
    emitSignal();
}

void MyDialog:: emitSignal(){
    emit signal(ui->xStart->value()
                , ui->xEnd->value()
                , ui->aBox->value()
                , ui->bBox->value()
                , ui->cBox->value());
}

void MyDialog::on_aBox_valueChanged(double arg1)
{
    emitSignal();
}


void MyDialog::on_bBox_valueChanged(double arg1)
{
    emitSignal();
}


void MyDialog::on_cBox_valueChanged(double arg1)
{
    emitSignal();
}

