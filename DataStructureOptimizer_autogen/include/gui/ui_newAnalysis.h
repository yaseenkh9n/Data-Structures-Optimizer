/********************************************************************************
** Form generated from reading UI file 'newAnalysis.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWANALYSIS_H
#define UI_NEWANALYSIS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "newAnalysis.h"

QT_BEGIN_NAMESPACE

class Ui_NewAnalysis
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFrame *contentArea;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *headerLayout;
    QVBoxLayout *titleLayout;
    QLabel *pageTitle;
    QLabel *pageSubtitle;
    QSpacerItem *headerSpacer;
    QPushButton *settingsButton;
    QSpacerItem *verticalSpacer_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *scrollLayout;
    QGroupBox *dataConfigGroup;
    QVBoxLayout *dataConfigLayout;
    QGridLayout *dataGridLayout;
    QLabel *dataSourceLabel;
    QComboBox *dataSourceCombo;
    QLabel *dataTypeLabel;
    QComboBox *dataTypeCombo;
    QLabel *dataSizeLabel;
    QSpinBox *dataSizeSpinBox;
    QLabel *dataSizeHintLabel;
    QPushButton *uploadFileButton;
    QGroupBox *operationProfileGroup;
    QVBoxLayout *operationLayout;
    QLabel *operationHintLabel;
    QGridLayout *sliderGridLayout;
    QLabel *searchOperationLabel;
    QSlider *searchSlider;
    QLabel *searchValueLabel;
    QLabel *insertOperationLabel;
    QSlider *insertSlider;
    QLabel *insertValueLabel;
    QLabel *deleteOperationLabel;
    QSlider *deleteSlider;
    QLabel *deleteValueLabel;
    QLabel *totalPercentageLabel;
    QGroupBox *constraintsGroup;
    QVBoxLayout *constraintsLayout;
    QLabel *constraintsHintLabel;
    QGridLayout *constraintsGridLayout;
    QCheckBox *speedCriticalCheck;
    QCheckBox *memoryConstrainedCheck;
    QCheckBox *rangeQueriesCheck;
    QCheckBox *prefixSearchCheck;
    QCheckBox *priorityQueueCheck;
    QCheckBox *sortedDataCheck;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *buttonLayout;
    QPushButton *backButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *startAnalysisButton;

    void setupUi(NewAnalysis *NewAnalysis)
    {
        if (NewAnalysis->objectName().isEmpty())
            NewAnalysis->setObjectName("NewAnalysis");
        NewAnalysis->resize(1058, 652);
        NewAnalysis->setStyleSheet(QString::fromUtf8("/* Main Window - Deep Space Gradient (matches dashboard) */\n"
"NewAnalysis {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #0d1117,\n"
"        stop:0.5 #151b25,\n"
"        stop:1 #0d1117\n"
"    );\n"
"}\n"
"\n"
"/* Content Area */\n"
"#contentArea {\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* Page Title */\n"
"#pageTitle {\n"
"    color: #ffffff;\n"
"    font-size: 32px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#pageSubtitle {\n"
"    color: #8b92a7;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Group Boxes */\n"
"QGroupBox {\n"
"    background-color: #1f2333;\n"
"    border: 1px solid #2a2d3e;\n"
"    border-radius: 12px;\n"
"    padding: 12px;\n"
"    margin-top: 15px;\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 3px 10px;\n"
"    background-color: #1f2333;\n"
"    border-radius: 4px;\n"
""
                        "    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Labels */\n"
"QLabel {\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QLabel[font-style=\"italic\"] {\n"
"    color: #8b92a7;\n"
"    font-style: italic;\n"
"}\n"
"\n"
"/* Combo Boxes */\n"
"QComboBox {\n"
"    background-color: #2a2d3e;\n"
"    border: 1px solid #353847;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    color: #ffffff;\n"
"    selection-background-color: #00d4ff;\n"
"    min-height: 32px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border-color: #00d4ff;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    border-left: 5px solid transparent;\n"
"    border-right: 5px solid transparent;\n"
"    border-top: 5px solid #8b92a7;\n"
"    margin-right: 10px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #2a2d3e;\n"
"    border: 1px solid #353847;\n"
"    border-radius: 8px;\n"
"    color: #ffffff;\n"
"    selection-background-color: "
                        "#00d4ff;\n"
"}\n"
"\n"
"/* Spin Box */\n"
"QSpinBox {\n"
"    background-color: #2a2d3e;\n"
"    border: 1px solid #353847;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    color: #ffffff;\n"
"    min-height: 32px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QSpinBox:hover {\n"
"    border-color: #00d4ff;\n"
"}\n"
"\n"
"QSpinBox::up-button, QSpinBox::down-button {\n"
"    background-color: #353847;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    width: 24px;\n"
"}\n"
"\n"
"/* Sliders */\n"
"QSlider::groove:horizontal {\n"
"    height: 8px;\n"
"    background: #2a2d3e;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #00d4ff;\n"
"    width: 24px;\n"
"    height: 24px;\n"
"    margin: -8px 0;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"    background: #00b8e6;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: #00d4ff;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"/* Check Boxes */\n"
"QCheckBox {\n"
""
                        "    color: #ffffff;\n"
"    spacing: 12px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 22px;\n"
"    height: 22px;\n"
"    border: 2px solid #353847;\n"
"    border-radius: 6px;\n"
"    background-color: #2a2d3e;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #00d4ff;\n"
"    border-color: #00d4ff;\n"
"}\n"
"\n"
"QCheckBox::indicator:hover {\n"
"    border-color: #00d4ff;\n"
"}\n"
"\n"
"/* Buttons */\n"
"QPushButton {\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    padding: 12px 24px;\n"
"}\n"
"\n"
"QPushButton#uploadFileButton {\n"
"    background-color: #2a2d3e;\n"
"    color: #ffffff;\n"
"    border: 1px solid #353847;\n"
"    min-height: 32px;\n"
"}\n"
"\n"
"QPushButton#uploadFileButton:hover {\n"
"    background-color: #353847;\n"
"    border-color: #00d4ff;\n"
"}\n"
"\n"
"QPushButton#uploadFileButton:disabled {\n"
"    background-color: #1f2333;\n"
"    color: #5a5f6e;\n"
"    border-color: #2a2d3e;\n"
"}"
                        "\n"
"\n"
"QPushButton#backButton {\n"
"    background-color: #2a2d3e;\n"
"    color: #ffffff;\n"
"    border: 1px solid #353847;\n"
"    min-width: 120px;\n"
"    min-height: 35px;\n"
"}\n"
"\n"
"QPushButton#backButton:hover {\n"
"    background-color: #353847;\n"
"    border-color: #ff6b6b;\n"
"}\n"
"\n"
"QPushButton#startAnalysisButton {\n"
"    background-color: #00d4ff;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    min-width: 200px;\n"
"    min-height: 35px;\n"
"}\n"
"\n"
"QPushButton#startAnalysisButton:hover {\n"
"    background-color: #00b8e6;\n"
"}\n"
"\n"
"/* Scroll Area */\n"
"QScrollArea {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QScrollArea > QWidget > QWidget {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    background-color: #2a2d3e;\n"
"    width: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background-color: #353847;\n"
"    border-radius: 5px;\n"
""
                        "    min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background-color: #00d4ff;\n"
"}\n"
"\n"
"/* Value Labels */\n"
"QLabel.valueLabel {\n"
"    color: #00d4ff;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* Total Percentage Label */\n"
"#totalPercentageLabel {\n"
"    color: #4ade80;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* Settings Button */\n"
"QPushButton#settingsButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    color: #8b92a7;\n"
"    font-size: 20px;\n"
"}\n"
"\n"
"QPushButton#settingsButton:hover {\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* Grid Layout Spacing */\n"
"QGridLayout {\n"
"    spacing: 15px;\n"
"}"));
        verticalLayout = new QVBoxLayout(NewAnalysis);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        contentArea = new QFrame(NewAnalysis);
        contentArea->setObjectName("contentArea");
        verticalLayout_2 = new QVBoxLayout(contentArea);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(40, 30, 40, 30);
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLayout = new QVBoxLayout();
        titleLayout->setSpacing(5);
        titleLayout->setObjectName("titleLayout");
        pageTitle = new QLabel(contentArea);
        pageTitle->setObjectName("pageTitle");
        QFont font;
        font.setBold(true);
        pageTitle->setFont(font);

        titleLayout->addWidget(pageTitle);

        pageSubtitle = new QLabel(contentArea);
        pageSubtitle->setObjectName("pageSubtitle");
        QFont font1;
        pageSubtitle->setFont(font1);

        titleLayout->addWidget(pageSubtitle);


        headerLayout->addLayout(titleLayout);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);

        settingsButton = new QPushButton(contentArea);
        settingsButton->setObjectName("settingsButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/settings_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon);
        settingsButton->setIconSize(QSize(32, 32));

        headerLayout->addWidget(settingsButton);


        verticalLayout_2->addLayout(headerLayout);

        verticalSpacer_3 = new QSpacerItem(20, 2, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        scrollArea = new QScrollArea(contentArea);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 948, 908));
        scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);
        scrollLayout->setSpacing(15);
        scrollLayout->setObjectName("scrollLayout");
        scrollLayout->setContentsMargins(0, -1, 0, -1);
        dataConfigGroup = new QGroupBox(scrollAreaWidgetContents);
        dataConfigGroup->setObjectName("dataConfigGroup");
        dataConfigGroup->setFont(font);
        dataConfigLayout = new QVBoxLayout(dataConfigGroup);
        dataConfigLayout->setSpacing(8);
        dataConfigLayout->setObjectName("dataConfigLayout");
        dataGridLayout = new QGridLayout();
        dataGridLayout->setObjectName("dataGridLayout");
        dataGridLayout->setHorizontalSpacing(20);
        dataGridLayout->setVerticalSpacing(8);
        dataSourceLabel = new QLabel(dataConfigGroup);
        dataSourceLabel->setObjectName("dataSourceLabel");
        QFont font2;
        font2.setPointSize(11);
        dataSourceLabel->setFont(font2);
        dataSourceLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        dataGridLayout->addWidget(dataSourceLabel, 0, 0, 1, 1);

        dataSourceCombo = new QComboBox(dataConfigGroup);
        dataSourceCombo->addItem(QString());
        dataSourceCombo->addItem(QString());
        dataSourceCombo->addItem(QString());
        dataSourceCombo->setObjectName("dataSourceCombo");

        dataGridLayout->addWidget(dataSourceCombo, 0, 1, 1, 2);

        dataTypeLabel = new QLabel(dataConfigGroup);
        dataTypeLabel->setObjectName("dataTypeLabel");
        dataTypeLabel->setFont(font2);

        dataGridLayout->addWidget(dataTypeLabel, 1, 0, 1, 1);

        dataTypeCombo = new QComboBox(dataConfigGroup);
        dataTypeCombo->addItem(QString());
        dataTypeCombo->addItem(QString());
        dataTypeCombo->addItem(QString());
        dataTypeCombo->addItem(QString());
        dataTypeCombo->setObjectName("dataTypeCombo");

        dataGridLayout->addWidget(dataTypeCombo, 1, 1, 1, 2);

        dataSizeLabel = new QLabel(dataConfigGroup);
        dataSizeLabel->setObjectName("dataSizeLabel");
        dataSizeLabel->setFont(font2);

        dataGridLayout->addWidget(dataSizeLabel, 2, 0, 1, 1);

        dataSizeSpinBox = new QSpinBox(dataConfigGroup);
        dataSizeSpinBox->setObjectName("dataSizeSpinBox");
        dataSizeSpinBox->setMinimum(100);
        dataSizeSpinBox->setMaximum(1000000);
        dataSizeSpinBox->setSingleStep(1000);
        dataSizeSpinBox->setValue(10000);

        dataGridLayout->addWidget(dataSizeSpinBox, 2, 1, 1, 1);

        dataSizeHintLabel = new QLabel(dataConfigGroup);
        dataSizeHintLabel->setObjectName("dataSizeHintLabel");
        QFont font3;
        font3.setPointSize(11);
        font3.setItalic(true);
        dataSizeHintLabel->setFont(font3);

        dataGridLayout->addWidget(dataSizeHintLabel, 2, 2, 1, 1);

        uploadFileButton = new QPushButton(dataConfigGroup);
        uploadFileButton->setObjectName("uploadFileButton");
        uploadFileButton->setEnabled(false);

        dataGridLayout->addWidget(uploadFileButton, 3, 1, 1, 2);


        dataConfigLayout->addLayout(dataGridLayout);


        scrollLayout->addWidget(dataConfigGroup);

        operationProfileGroup = new QGroupBox(scrollAreaWidgetContents);
        operationProfileGroup->setObjectName("operationProfileGroup");
        operationProfileGroup->setFont(font);
        operationLayout = new QVBoxLayout(operationProfileGroup);
        operationLayout->setSpacing(15);
        operationLayout->setObjectName("operationLayout");
        operationHintLabel = new QLabel(operationProfileGroup);
        operationHintLabel->setObjectName("operationHintLabel");
        QFont font4;
        font4.setPointSize(9);
        font4.setItalic(true);
        operationHintLabel->setFont(font4);

        operationLayout->addWidget(operationHintLabel);

        sliderGridLayout = new QGridLayout();
        sliderGridLayout->setSpacing(20);
        sliderGridLayout->setObjectName("sliderGridLayout");
        searchOperationLabel = new QLabel(operationProfileGroup);
        searchOperationLabel->setObjectName("searchOperationLabel");
        searchOperationLabel->setFont(font2);

        sliderGridLayout->addWidget(searchOperationLabel, 0, 0, 1, 1);

        searchSlider = new QSlider(operationProfileGroup);
        searchSlider->setObjectName("searchSlider");
        searchSlider->setMinimum(0);
        searchSlider->setMaximum(100);
        searchSlider->setValue(60);
        searchSlider->setOrientation(Qt::Orientation::Horizontal);

        sliderGridLayout->addWidget(searchSlider, 0, 1, 1, 1);

        searchValueLabel = new QLabel(operationProfileGroup);
        searchValueLabel->setObjectName("searchValueLabel");
        searchValueLabel->setMinimumSize(QSize(70, 0));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        searchValueLabel->setFont(font5);
        searchValueLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        sliderGridLayout->addWidget(searchValueLabel, 0, 2, 1, 1);

        insertOperationLabel = new QLabel(operationProfileGroup);
        insertOperationLabel->setObjectName("insertOperationLabel");
        insertOperationLabel->setFont(font2);

        sliderGridLayout->addWidget(insertOperationLabel, 1, 0, 1, 1);

        insertSlider = new QSlider(operationProfileGroup);
        insertSlider->setObjectName("insertSlider");
        insertSlider->setMinimum(0);
        insertSlider->setMaximum(100);
        insertSlider->setValue(25);
        insertSlider->setOrientation(Qt::Orientation::Horizontal);

        sliderGridLayout->addWidget(insertSlider, 1, 1, 1, 1);

        insertValueLabel = new QLabel(operationProfileGroup);
        insertValueLabel->setObjectName("insertValueLabel");
        insertValueLabel->setMinimumSize(QSize(70, 0));
        insertValueLabel->setFont(font5);
        insertValueLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        sliderGridLayout->addWidget(insertValueLabel, 1, 2, 1, 1);

        deleteOperationLabel = new QLabel(operationProfileGroup);
        deleteOperationLabel->setObjectName("deleteOperationLabel");
        deleteOperationLabel->setFont(font2);

        sliderGridLayout->addWidget(deleteOperationLabel, 2, 0, 1, 1);

        deleteSlider = new QSlider(operationProfileGroup);
        deleteSlider->setObjectName("deleteSlider");
        deleteSlider->setMinimum(0);
        deleteSlider->setMaximum(100);
        deleteSlider->setValue(15);
        deleteSlider->setOrientation(Qt::Orientation::Horizontal);

        sliderGridLayout->addWidget(deleteSlider, 2, 1, 1, 1);

        deleteValueLabel = new QLabel(operationProfileGroup);
        deleteValueLabel->setObjectName("deleteValueLabel");
        deleteValueLabel->setMinimumSize(QSize(70, 0));
        deleteValueLabel->setFont(font5);
        deleteValueLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        sliderGridLayout->addWidget(deleteValueLabel, 2, 2, 1, 1);


        operationLayout->addLayout(sliderGridLayout);

        totalPercentageLabel = new QLabel(operationProfileGroup);
        totalPercentageLabel->setObjectName("totalPercentageLabel");
        totalPercentageLabel->setFont(font);
        totalPercentageLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        operationLayout->addWidget(totalPercentageLabel);


        scrollLayout->addWidget(operationProfileGroup);

        constraintsGroup = new QGroupBox(scrollAreaWidgetContents);
        constraintsGroup->setObjectName("constraintsGroup");
        constraintsGroup->setFont(font);
        constraintsLayout = new QVBoxLayout(constraintsGroup);
        constraintsLayout->setSpacing(15);
        constraintsLayout->setObjectName("constraintsLayout");
        constraintsHintLabel = new QLabel(constraintsGroup);
        constraintsHintLabel->setObjectName("constraintsHintLabel");
        constraintsHintLabel->setFont(font4);

        constraintsLayout->addWidget(constraintsHintLabel);

        constraintsGridLayout = new QGridLayout();
        constraintsGridLayout->setObjectName("constraintsGridLayout");
        constraintsGridLayout->setHorizontalSpacing(30);
        constraintsGridLayout->setVerticalSpacing(15);
        speedCriticalCheck = new QCheckBox(constraintsGroup);
        speedCriticalCheck->setObjectName("speedCriticalCheck");
        speedCriticalCheck->setFont(font1);

        constraintsGridLayout->addWidget(speedCriticalCheck, 0, 0, 1, 1);

        memoryConstrainedCheck = new QCheckBox(constraintsGroup);
        memoryConstrainedCheck->setObjectName("memoryConstrainedCheck");
        memoryConstrainedCheck->setFont(font1);

        constraintsGridLayout->addWidget(memoryConstrainedCheck, 0, 1, 1, 1);

        rangeQueriesCheck = new QCheckBox(constraintsGroup);
        rangeQueriesCheck->setObjectName("rangeQueriesCheck");
        rangeQueriesCheck->setFont(font1);

        constraintsGridLayout->addWidget(rangeQueriesCheck, 1, 0, 1, 1);

        prefixSearchCheck = new QCheckBox(constraintsGroup);
        prefixSearchCheck->setObjectName("prefixSearchCheck");
        prefixSearchCheck->setFont(font1);

        constraintsGridLayout->addWidget(prefixSearchCheck, 1, 1, 1, 1);

        priorityQueueCheck = new QCheckBox(constraintsGroup);
        priorityQueueCheck->setObjectName("priorityQueueCheck");
        priorityQueueCheck->setFont(font1);

        constraintsGridLayout->addWidget(priorityQueueCheck, 2, 0, 1, 1);

        sortedDataCheck = new QCheckBox(constraintsGroup);
        sortedDataCheck->setObjectName("sortedDataCheck");
        sortedDataCheck->setFont(font1);

        constraintsGridLayout->addWidget(sortedDataCheck, 2, 1, 1, 1);


        constraintsLayout->addLayout(constraintsGridLayout);


        scrollLayout->addWidget(constraintsGroup);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(15);
        buttonLayout->setObjectName("buttonLayout");
        backButton = new QPushButton(contentArea);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(170, 71));
        QFont font6;
        font6.setBold(false);
        backButton->setFont(font6);

        buttonLayout->addWidget(backButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(horizontalSpacer_2);

        startAnalysisButton = new QPushButton(contentArea);
        startAnalysisButton->setObjectName("startAnalysisButton");
        startAnalysisButton->setMinimumSize(QSize(248, 74));
        startAnalysisButton->setFont(font);

        buttonLayout->addWidget(startAnalysisButton);


        verticalLayout_2->addLayout(buttonLayout);


        horizontalLayout->addWidget(contentArea);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NewAnalysis);

        QMetaObject::connectSlotsByName(NewAnalysis);
    } // setupUi

    void retranslateUi(NewAnalysis *NewAnalysis)
    {
        NewAnalysis->setWindowTitle(QCoreApplication::translate("NewAnalysis", "New Analysis - DSA Optimizer", nullptr));
        pageTitle->setText(QCoreApplication::translate("NewAnalysis", "Create New Analysis", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("NewAnalysis", "Configure your data structure analysis parameters", nullptr));
        settingsButton->setText(QString());
        dataConfigGroup->setTitle(QCoreApplication::translate("NewAnalysis", "\360\237\223\201 Data Configuration", nullptr));
        dataSourceLabel->setText(QCoreApplication::translate("NewAnalysis", "Data Source:", nullptr));
        dataSourceCombo->setItemText(0, QCoreApplication::translate("NewAnalysis", "Generate Random Data", nullptr));
        dataSourceCombo->setItemText(1, QCoreApplication::translate("NewAnalysis", "Upload from File (CSV/TXT)", nullptr));
        dataSourceCombo->setItemText(2, QCoreApplication::translate("NewAnalysis", "Use Sample Dataset", nullptr));

        dataTypeLabel->setText(QCoreApplication::translate("NewAnalysis", "Data Type:", nullptr));
        dataTypeCombo->setItemText(0, QCoreApplication::translate("NewAnalysis", "Integer", nullptr));
        dataTypeCombo->setItemText(1, QCoreApplication::translate("NewAnalysis", "String", nullptr));
        dataTypeCombo->setItemText(2, QCoreApplication::translate("NewAnalysis", "Double", nullptr));
        dataTypeCombo->setItemText(3, QCoreApplication::translate("NewAnalysis", "Mixed", nullptr));

        dataSizeLabel->setText(QCoreApplication::translate("NewAnalysis", "Data Size:", nullptr));
        dataSizeHintLabel->setText(QCoreApplication::translate("NewAnalysis", "elements", nullptr));
        uploadFileButton->setText(QCoreApplication::translate("NewAnalysis", "\360\237\223\201 Browse and Upload File...", nullptr));
        operationProfileGroup->setTitle(QCoreApplication::translate("NewAnalysis", "\342\232\231\357\270\217 Operation Profile", nullptr));
        operationHintLabel->setText(QCoreApplication::translate("NewAnalysis", "Define the percentage distribution of operations (must sum to 100%)", nullptr));
        searchOperationLabel->setText(QCoreApplication::translate("NewAnalysis", "Search:", nullptr));
        searchValueLabel->setText(QCoreApplication::translate("NewAnalysis", "60%", nullptr));
        insertOperationLabel->setText(QCoreApplication::translate("NewAnalysis", "Insert:", nullptr));
        insertValueLabel->setText(QCoreApplication::translate("NewAnalysis", "25%", nullptr));
        deleteOperationLabel->setText(QCoreApplication::translate("NewAnalysis", "Delete:", nullptr));
        deleteValueLabel->setText(QCoreApplication::translate("NewAnalysis", "15%", nullptr));
        totalPercentageLabel->setText(QCoreApplication::translate("NewAnalysis", "Total: 100% \342\234\223", nullptr));
        constraintsGroup->setTitle(QCoreApplication::translate("NewAnalysis", "\360\237\216\257 Constraints & Requirements", nullptr));
        constraintsHintLabel->setText(QCoreApplication::translate("NewAnalysis", "Select specific requirements for your use case", nullptr));
        speedCriticalCheck->setText(QCoreApplication::translate("NewAnalysis", "\342\232\241 Speed Critical (Real-time)", nullptr));
        memoryConstrainedCheck->setText(QCoreApplication::translate("NewAnalysis", "\360\237\222\276 Memory Constrained", nullptr));
        rangeQueriesCheck->setText(QCoreApplication::translate("NewAnalysis", "\360\237\223\212 Needs Range Queries", nullptr));
        prefixSearchCheck->setText(QCoreApplication::translate("NewAnalysis", "\360\237\224\215 Needs Prefix Search", nullptr));
        priorityQueueCheck->setText(QCoreApplication::translate("NewAnalysis", "\360\237\223\213 Needs Priority Queue", nullptr));
        sortedDataCheck->setText(QCoreApplication::translate("NewAnalysis", "\360\237\224\242 Data is Pre-Sorted", nullptr));
        backButton->setText(QCoreApplication::translate("NewAnalysis", "\342\206\220 Back", nullptr));
        startAnalysisButton->setText(QCoreApplication::translate("NewAnalysis", " Start Analysis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewAnalysis: public Ui_NewAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWANALYSIS_H
