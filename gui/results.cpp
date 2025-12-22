#include "results.h"
#include "gui/ui_results.h"

Results::Results(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
}

Results::~Results()
{
    delete ui;
}

