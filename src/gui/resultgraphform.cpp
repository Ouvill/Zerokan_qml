#include "resultgraphform.h"
#include "ui_resultgraphform.h"

resultGraphForm::resultGraphForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resultGraphForm)
{
    ui->setupUi(this);
}

resultGraphForm::~resultGraphForm()
{
    delete ui;
}
