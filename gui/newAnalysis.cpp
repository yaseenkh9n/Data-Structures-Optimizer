

#include "newAnalysis.h"
#include "gui/ui_newAnalysis.h"
#include <QSlider>
#include <QLabel>
#include <QEvent>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

NewAnalysis::NewAnalysis(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::NewAnalysis)
{
    ui->setupUi(this);

    QSlider* searchSlider = findChild<QSlider*>("searchSlider");
    QSlider* insertSlider = findChild<QSlider*>("insertSlider");
    QSlider* deleteSlider = findChild<QSlider*>("deleteSlider");
    
    if (searchSlider) searchSlider->installEventFilter(this);
    if (insertSlider) insertSlider->installEventFilter(this);
    if (deleteSlider) deleteSlider->installEventFilter(this);

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

    updatePercentages();
}

void NewAnalysis::onDataSourceChanged(int index)
{
    QPushButton* uploadBtn = findChild<QPushButton*>("uploadFileButton");
    if (!uploadBtn) return;

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
        QFileInfo fileInfo(fileName);
        QString ext = fileInfo.suffix().toLower();

        if (ext != "csv" && ext != "txt") {
            QMessageBox::critical(this, "Invalid File Type", 
                "The selected file type is not supported.\nPlease select a .csv or .txt file.");
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
             QMessageBox::critical(this, "Read Error", "Could not open file for reading.");
             return;
        }

        if (file.size() == 0) {
             QMessageBox::critical(this, "Msg", "The selected file is empty.");
             file.close();
             return;
        }

        QByteArray chunk = file.read(1024);
        if (chunk.contains('\0')) {
             QMessageBox::critical(this, "Invalid Content", "The file appears to be binary. Please upload a valid text dataset.");
             file.close();
             return;
        }
        file.close();

        uploadedFilePath = fileName;
        
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

bool NewAnalysis::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel) {
        if (qobject_cast<QSlider*>(obj)) {
            event->ignore();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}
