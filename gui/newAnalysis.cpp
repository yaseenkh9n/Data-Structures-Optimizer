

#include "newAnalysis.h"
#include "gui/ui_newAnalysis.h"
#include <QSlider>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

NewAnalysis::NewAnalysis(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::NewAnalysis)
{
    ui->setupUi(this);

    // Connect sliders to update percentages
    QSlider* searchSlider = findChild<QSlider*>("searchSlider");
    QSlider* insertSlider = findChild<QSlider*>("insertSlider");
    QSlider* deleteSlider = findChild<QSlider*>("deleteSlider");

    QLabel* searchValue = findChild<QLabel*>("searchValueLabel");
    QLabel* insertValue = findChild<QLabel*>("insertValueLabel");
    QLabel* deleteValue = findChild<QLabel*>("deleteValueLabel");
    QLabel* totalLabel = findChild<QLabel*>("totalPercentageLabel");

    auto updatePercentages = [=]() {
        int search = searchSlider->value();
        int insert = insertSlider->value();
        int delete_ = deleteSlider->value();
        int total = search + insert + delete_;

        searchValue->setText(QString::number(search) + "%");
        insertValue->setText(QString::number(insert) + "%");
        deleteValue->setText(QString::number(delete_) + "%");

        if (total == 100) {
            totalLabel->setText("Total: 100% ✓");
            totalLabel->setStyleSheet("color: #4ade80;");
        } else {
            totalLabel->setText(QString("Total: %1% ✗").arg(total));
            totalLabel->setStyleSheet("color: #ff6b6b;");
        }
    };

    connect(searchSlider, &QSlider::valueChanged, this, updatePercentages);
    connect(insertSlider, &QSlider::valueChanged, this, updatePercentages);
    connect(deleteSlider, &QSlider::valueChanged, this, updatePercentages);

    // Connect Data Source Combo
    QComboBox* dataSourceCombo = findChild<QComboBox*>("dataSourceCombo");
    if (dataSourceCombo) {
        connect(dataSourceCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onDataSourceChanged(int)));
    }

    // Connect Upload Button
    QPushButton* uploadBtn = findChild<QPushButton*>("uploadFileButton");
    if (uploadBtn) {
        connect(uploadBtn, &QPushButton::clicked, this, &NewAnalysis::onUploadFileClicked);
    }

    // Initial update
    updatePercentages();
}

void NewAnalysis::onDataSourceChanged(int index)
{
    QPushButton* uploadBtn = findChild<QPushButton*>("uploadFileButton");
    if (!uploadBtn) return;

    // Index 1 is "Upload from File"
    if (index == 1) {
        uploadBtn->setEnabled(true);
    } else {
        uploadBtn->setEnabled(false);
        uploadBtn->setText("📁 Browse and Upload File...");
        uploadedFilePath.clear();
    }
}

void NewAnalysis::onUploadFileClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Dataset", "", "CSV/Text Files (*.csv *.txt);;All Files (*)");
    
    if (!fileName.isEmpty()) {
        uploadedFilePath = fileName;
        
        QFileInfo fileInfo(fileName);
        QPushButton* uploadBtn = findChild<QPushButton*>("uploadFileButton");
        if (uploadBtn) {
            uploadBtn->setText("📄 " + fileInfo.fileName());
        }
    }
}

NewAnalysis::~NewAnalysis()
{
    delete ui;
}
