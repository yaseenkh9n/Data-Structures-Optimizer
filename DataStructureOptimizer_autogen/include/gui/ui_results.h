/********************************************************************************
** Form generated from reading UI file 'results.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTS_H
#define UI_RESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Results
{
public:
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContentWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pageTitle;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportButton;
    QPushButton *newAnalysisButton;
    QLabel *pageSubtitle;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QFrame *topPerformerCard;
    QVBoxLayout *verticalLayout_3;
    QLabel *recommendationLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *recommendationText;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *performanceLabel;
    QLabel *performanceValue;
    QLabel *warningText;
    QFrame *analysisInfoCard;
    QVBoxLayout *verticalLayout_4;
    QLabel *analysisInfoLabel;
    QSpacerItem *verticalSpacer_6;
    QGridLayout *gridLayout;
    QLabel *datasetLabel;
    QLabel *datasetValue;
    QLabel *sizeLabel;
    QLabel *sizeValue;
    QLabel *operationsLabel;
    QLabel *operationsValue;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *graphGroup;
    QVBoxLayout *verticalLayout_5;
    QLabel *graphHint;
    QFrame *graphPlaceholder;
    QVBoxLayout *verticalLayout_6;
    QLabel *graphText;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *detailedResultsGroup;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *resultsGrid;
    QFrame *resultCard;
    QVBoxLayout *verticalLayout_8;
    QLabel *dsTag1;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QLabel *hashScore;
    QLabel *hashNotes;
    QFrame *resultCard_2;
    QVBoxLayout *verticalLayout_9;
    QLabel *dsTag2;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_12;
    QLabel *bstScore;
    QLabel *bstNotes;
    QFrame *resultCard_3;
    QVBoxLayout *verticalLayout_10;
    QLabel *dsTag3;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_14;
    QLabel *arrayScore;
    QLabel *arrayNotes;
    QSpacerItem *verticalSpacer_12;

    void setupUi(QWidget *Results)
    {
        if (Results->objectName().isEmpty())
            Results->setObjectName("Results");
        Results->resize(1058, 1280);
        Results->setStyleSheet(QString::fromUtf8("/* Main Widget - Deep Space Gradient (matches dashboard) */\n"
"Results {\n"
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
"    font-size: 38px;\n"
"    font-weight: 700;\n"
"    letter-spacing: -0.5px;\n"
"}\n"
"\n"
"#pageSubtitle {\n"
"    color: rgba(160, 180, 210, 0.8);\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Group Boxes - Frosted Glass */\n"
"QGroupBox {\n"
"    background: rgba(255, 255, 255, 0.04);\n"
"    border: 1px solid rgba(255, 255, 255, 0.08);\n"
"    border-radius: 16px;\n"
"    padding: 20px;\n"
"    margin-top: 15px;\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
" "
                        "   padding: 4px 12px;\n"
"    background: #1f2333;\n"
"    border-radius: 8px;\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Labels */\n"
"QLabel {\n"
"    color: rgba(200, 210, 230, 0.9);\n"
"}\n"
"\n"
"/* Result Cards - Frosted Glass */\n"
"QFrame#resultCard, QFrame#resultCard_2, QFrame#resultCard_3, QFrame#resultCard_4 {\n"
"    background: rgba(255, 255, 255, 0.04);\n"
"    border: 1px solid rgba(255, 255, 255, 0.08);\n"
"    border-radius: 16px;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"/* Top Performer Card - Glowing Glass */\n"
"QFrame#topPerformerCard {\n"
"    background: rgba(0, 212, 255, 0.08);\n"
"    border: 1px solid rgba(0, 212, 255, 0.3);\n"
"    border-radius: 16px;\n"
"    padding: 20px;\n"
"}\n"
"\n"
"/* Analysis Info Card */\n"
"QFrame#analysisInfoCard {\n"
"    background: rgba(255, 255, 255, 0.04);\n"
"    border: 1px solid rgba(255, 255, 255, 0.08);\n"
"    border-radius: 16px;\n"
"    padding: 20px;\n"
"}\n"
"\n"
"/* New Analysis Button - Glowing Primary */\n"
"QPushBut"
                        "ton#newAnalysisButton {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #00d4ff,\n"
"        stop:0.5 #00b8e6,\n"
"        stop:1 #0099cc\n"
"    );\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    padding: 12px 24px;\n"
"    font-size: 15px;\n"
"    font-weight: 600;\n"
"    min-width: 180px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QPushButton#newAnalysisButton:hover {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #33dfff,\n"
"        stop:0.5 #00c8f5,\n"
"        stop:1 #00a8dd\n"
"    );\n"
"}\n"
"\n"
"/* Export Button - Frosted Glass */\n"
"QPushButton#exportButton {\n"
"    background: rgba(255, 255, 255, 0.06);\n"
"    color: rgba(220, 230, 245, 0.9);\n"
"    border: 1px solid rgba(255, 255, 255, 0.12);\n"
"    border-radius: 12px;\n"
"    padding: 12px 24px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    min-width: 150px;\n"
"    min-height: 30p"
                        "x;\n"
"}\n"
"\n"
"QPushButton#exportButton:hover {\n"
"    background: rgba(0, 212, 255, 0.12);\n"
"    border: 1px solid rgba(0, 212, 255, 0.35);\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* Settings Button - Icon Glow */\n"
"QPushButton#settingsButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"}\n"
"\n"
"QPushButton#settingsButton:hover {\n"
"    background: rgba(0, 212, 255, 0.12);\n"
"}\n"
"\n"
"/* Graph Placeholder */\n"
"QFrame#graphPlaceholder {\n"
"    background: rgba(255, 255, 255, 0.02);\n"
"    border: 1px solid rgba(255, 255, 255, 0.05);\n"
"    border-radius: 12px;\n"
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
"/* Scrollbar - Glass Style */\n"
"QScrollBar:vertical {\n"
"    background: rgba(255, 255, 255, 0.02);\n"
"    width: 8px;\n"
"    border-radius: 4px;\n"
""
                        "}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: rgba(0, 212, 255, 0.3);\n"
"    border-radius: 4px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: rgba(0, 212, 255, 0.5);\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"/* Scroll Content */\n"
"#scrollContentWidget {\n"
"    background: transparent;\n"
"}"));
        mainLayout = new QVBoxLayout(Results);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(Results);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollContentWidget = new QWidget();
        scrollContentWidget->setObjectName("scrollContentWidget");
        verticalLayout_2 = new QVBoxLayout(scrollContentWidget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(40, 30, 40, 30);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pageTitle = new QLabel(scrollContentWidget);
        pageTitle->setObjectName("pageTitle");
        QFont font;
        font.setBold(true);
        pageTitle->setFont(font);

        horizontalLayout_3->addWidget(pageTitle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        exportButton = new QPushButton(scrollContentWidget);
        exportButton->setObjectName("exportButton");
        exportButton->setMinimumSize(QSize(200, 40));

        horizontalLayout_3->addWidget(exportButton);

        newAnalysisButton = new QPushButton(scrollContentWidget);
        newAnalysisButton->setObjectName("newAnalysisButton");
        newAnalysisButton->setMinimumSize(QSize(228, 40));

        horizontalLayout_3->addWidget(newAnalysisButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        pageSubtitle = new QLabel(scrollContentWidget);
        pageSubtitle->setObjectName("pageSubtitle");

        verticalLayout_2->addWidget(pageSubtitle);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        topPerformerCard = new QFrame(scrollContentWidget);
        topPerformerCard->setObjectName("topPerformerCard");
        verticalLayout_3 = new QVBoxLayout(topPerformerCard);
        verticalLayout_3->setObjectName("verticalLayout_3");
        recommendationLabel = new QLabel(topPerformerCard);
        recommendationLabel->setObjectName("recommendationLabel");
        recommendationLabel->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-size: 12px; font-weight: bold;"));

        verticalLayout_3->addWidget(recommendationLabel);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        recommendationText = new QLabel(topPerformerCard);
        recommendationText->setObjectName("recommendationText");
        recommendationText->setStyleSheet(QString::fromUtf8("color: #4ade80; font-size: 20px; font-weight: bold;"));

        verticalLayout_3->addWidget(recommendationText);

        verticalSpacer_5 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        performanceLabel = new QLabel(topPerformerCard);
        performanceLabel->setObjectName("performanceLabel");
        performanceLabel->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-size: 14px;"));

        horizontalLayout_5->addWidget(performanceLabel);

        performanceValue = new QLabel(topPerformerCard);
        performanceValue->setObjectName("performanceValue");
        performanceValue->setStyleSheet(QString::fromUtf8("color: #00d4ff; font-size: 18px; font-weight: bold;"));

        horizontalLayout_5->addWidget(performanceValue);


        verticalLayout_3->addLayout(horizontalLayout_5);

        warningText = new QLabel(topPerformerCard);
        warningText->setObjectName("warningText");
        warningText->setStyleSheet(QString::fromUtf8("color: #ff6b6b; font-size: 12px;"));

        verticalLayout_3->addWidget(warningText);


        horizontalLayout_4->addWidget(topPerformerCard);

        analysisInfoCard = new QFrame(scrollContentWidget);
        analysisInfoCard->setObjectName("analysisInfoCard");
        analysisInfoCard->setStyleSheet(QString::fromUtf8("background-color: #1f2333; border: 1px solid #2a2d3e; border-radius: 12px; padding: 20px;"));
        verticalLayout_4 = new QVBoxLayout(analysisInfoCard);
        verticalLayout_4->setObjectName("verticalLayout_4");
        analysisInfoLabel = new QLabel(analysisInfoCard);
        analysisInfoLabel->setObjectName("analysisInfoLabel");
        analysisInfoLabel->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-size: 12px; font-weight: bold;"));

        verticalLayout_4->addWidget(analysisInfoLabel);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_6);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(30);
        gridLayout->setVerticalSpacing(10);
        datasetLabel = new QLabel(analysisInfoCard);
        datasetLabel->setObjectName("datasetLabel");
        datasetLabel->setStyleSheet(QString::fromUtf8("color: #8b92a7;"));

        gridLayout->addWidget(datasetLabel, 0, 0, 1, 1);

        datasetValue = new QLabel(analysisInfoCard);
        datasetValue->setObjectName("datasetValue");
        datasetValue->setStyleSheet(QString::fromUtf8("color: #ffffff; font-weight: bold;"));

        gridLayout->addWidget(datasetValue, 0, 1, 1, 1);

        sizeLabel = new QLabel(analysisInfoCard);
        sizeLabel->setObjectName("sizeLabel");
        sizeLabel->setStyleSheet(QString::fromUtf8("color: #8b92a7;"));

        gridLayout->addWidget(sizeLabel, 1, 0, 1, 1);

        sizeValue = new QLabel(analysisInfoCard);
        sizeValue->setObjectName("sizeValue");
        sizeValue->setStyleSheet(QString::fromUtf8("color: #ffffff; font-weight: bold;"));

        gridLayout->addWidget(sizeValue, 1, 1, 1, 1);

        operationsLabel = new QLabel(analysisInfoCard);
        operationsLabel->setObjectName("operationsLabel");
        operationsLabel->setStyleSheet(QString::fromUtf8("color: #8b92a7;"));

        gridLayout->addWidget(operationsLabel, 2, 0, 1, 1);

        operationsValue = new QLabel(analysisInfoCard);
        operationsValue->setObjectName("operationsValue");
        operationsValue->setStyleSheet(QString::fromUtf8("color: #ffffff; font-weight: bold;"));

        gridLayout->addWidget(operationsValue, 2, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout);


        horizontalLayout_4->addWidget(analysisInfoCard);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_7 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_7);

        graphGroup = new QGroupBox(scrollContentWidget);
        graphGroup->setObjectName("graphGroup");
        verticalLayout_5 = new QVBoxLayout(graphGroup);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setObjectName("verticalLayout_5");
        graphHint = new QLabel(graphGroup);
        graphHint->setObjectName("graphHint");
        graphHint->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-style: italic; font-size: 12px;"));

        verticalLayout_5->addWidget(graphHint);

        graphPlaceholder = new QFrame(graphGroup);
        graphPlaceholder->setObjectName("graphPlaceholder");
        graphPlaceholder->setMinimumSize(QSize(0, 300));
        verticalLayout_6 = new QVBoxLayout(graphPlaceholder);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(20, 20, 20, 20);
        graphText = new QLabel(graphPlaceholder);
        graphText->setObjectName("graphText");
        graphText->setStyleSheet(QString::fromUtf8("color: #8b92a7; text-align: center; font-size: 14px;"));
        graphText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(graphText);


        verticalLayout_5->addWidget(graphPlaceholder);


        verticalLayout_2->addWidget(graphGroup);

        verticalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_8);

        detailedResultsGroup = new QGroupBox(scrollContentWidget);
        detailedResultsGroup->setObjectName("detailedResultsGroup");
        verticalLayout_7 = new QVBoxLayout(detailedResultsGroup);
        verticalLayout_7->setSpacing(15);
        verticalLayout_7->setObjectName("verticalLayout_7");
        resultsGrid = new QGridLayout();
        resultsGrid->setObjectName("resultsGrid");
        resultsGrid->setHorizontalSpacing(20);
        resultsGrid->setVerticalSpacing(15);
        resultCard = new QFrame(detailedResultsGroup);
        resultCard->setObjectName("resultCard");
        resultCard->setMinimumSize(QSize(0, 200));
        verticalLayout_8 = new QVBoxLayout(resultCard);
        verticalLayout_8->setObjectName("verticalLayout_8");
        dsTag1 = new QLabel(resultCard);
        dsTag1->setObjectName("dsTag1");
        dsTag1->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 212, 255, 0.2); border: 1px solid #00d4ff; border-radius: 16px; padding: 6px 16px; color: #00d4ff; font-size: 13px; font-weight: bold;"));

        verticalLayout_8->addWidget(dsTag1);

        verticalSpacer_9 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_10 = new QLabel(resultCard);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #8b92a7;"));

        horizontalLayout_6->addWidget(label_10);

        hashScore = new QLabel(resultCard);
        hashScore->setObjectName("hashScore");
        hashScore->setStyleSheet(QString::fromUtf8("color: #00d4ff; font-weight: bold;"));

        horizontalLayout_6->addWidget(hashScore);


        verticalLayout_8->addLayout(horizontalLayout_6);

        hashNotes = new QLabel(resultCard);
        hashNotes->setObjectName("hashNotes");
        hashNotes->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-size: 12px;"));

        verticalLayout_8->addWidget(hashNotes);


        resultsGrid->addWidget(resultCard, 0, 0, 1, 1);

        resultCard_2 = new QFrame(detailedResultsGroup);
        resultCard_2->setObjectName("resultCard_2");
        resultCard_2->setMinimumSize(QSize(0, 200));
        verticalLayout_9 = new QVBoxLayout(resultCard_2);
        verticalLayout_9->setObjectName("verticalLayout_9");
        dsTag2 = new QLabel(resultCard_2);
        dsTag2->setObjectName("dsTag2");
        dsTag2->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 212, 255, 0.2); border: 1px solid #00d4ff; border-radius: 16px; padding: 6px 16px; color: #00d4ff; font-size: 13px; font-weight: bold;"));

        verticalLayout_9->addWidget(dsTag2);

        verticalSpacer_10 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_9->addItem(verticalSpacer_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_12 = new QLabel(resultCard_2);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #8b92a7;"));

        horizontalLayout_7->addWidget(label_12);

        bstScore = new QLabel(resultCard_2);
        bstScore->setObjectName("bstScore");
        bstScore->setStyleSheet(QString::fromUtf8("color: #00d4ff; font-weight: bold;"));

        horizontalLayout_7->addWidget(bstScore);


        verticalLayout_9->addLayout(horizontalLayout_7);

        bstNotes = new QLabel(resultCard_2);
        bstNotes->setObjectName("bstNotes");
        bstNotes->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-size: 12px;"));

        verticalLayout_9->addWidget(bstNotes);


        resultsGrid->addWidget(resultCard_2, 0, 1, 1, 1);

        resultCard_3 = new QFrame(detailedResultsGroup);
        resultCard_3->setObjectName("resultCard_3");
        resultCard_3->setMinimumSize(QSize(0, 200));
        verticalLayout_10 = new QVBoxLayout(resultCard_3);
        verticalLayout_10->setObjectName("verticalLayout_10");
        dsTag3 = new QLabel(resultCard_3);
        dsTag3->setObjectName("dsTag3");
        dsTag3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 107, 107, 0.2); border: 1px solid #ff6b6b; border-radius: 16px; padding: 6px 16px; color: #ff6b6b; font-size: 13px; font-weight: bold;"));

        verticalLayout_10->addWidget(dsTag3);

        verticalSpacer_11 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_11);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_14 = new QLabel(resultCard_3);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("color: #8b92a7;"));

        horizontalLayout_8->addWidget(label_14);

        arrayScore = new QLabel(resultCard_3);
        arrayScore->setObjectName("arrayScore");
        arrayScore->setStyleSheet(QString::fromUtf8("color: #ff6b6b; font-weight: bold;"));

        horizontalLayout_8->addWidget(arrayScore);


        verticalLayout_10->addLayout(horizontalLayout_8);

        arrayNotes = new QLabel(resultCard_3);
        arrayNotes->setObjectName("arrayNotes");
        arrayNotes->setStyleSheet(QString::fromUtf8("color: #8b92a7; font-size: 12px;"));

        verticalLayout_10->addWidget(arrayNotes);


        resultsGrid->addWidget(resultCard_3, 0, 2, 1, 1);


        verticalLayout_7->addLayout(resultsGrid);


        verticalLayout_2->addWidget(detailedResultsGroup);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_12);

        scrollArea->setWidget(scrollContentWidget);

        mainLayout->addWidget(scrollArea);


        retranslateUi(Results);

        QMetaObject::connectSlotsByName(Results);
    } // setupUi

    void retranslateUi(QWidget *Results)
    {
        Results->setWindowTitle(QCoreApplication::translate("Results", "Analysis Results - DSA Optimizer", nullptr));
        pageTitle->setText(QCoreApplication::translate("Results", "Analysis Results", nullptr));
        exportButton->setText(QCoreApplication::translate("Results", "\360\237\223\245 Export Results", nullptr));
        newAnalysisButton->setText(QCoreApplication::translate("Results", "+ New Analysis", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("Results", "Detailed performance comparison of data structures based on your configuration", nullptr));
        recommendationLabel->setText(QCoreApplication::translate("Results", "\360\237\217\206 RECOMMENDED DATA STRUCTURE", nullptr));
        recommendationText->setText(QCoreApplication::translate("Results", "Hash Table (Separate Chaining)", nullptr));
        performanceLabel->setText(QCoreApplication::translate("Results", "Performance Score:", nullptr));
        performanceValue->setText(QCoreApplication::translate("Results", "94.2%", nullptr));
        warningText->setText(QCoreApplication::translate("Results", "\342\232\240\357\270\217 Hash collisions may occur with large datasets", nullptr));
        analysisInfoLabel->setText(QCoreApplication::translate("Results", "\360\237\223\212 ANALYSIS DETAILS", nullptr));
        datasetLabel->setText(QCoreApplication::translate("Results", "Dataset:", nullptr));
        datasetValue->setText(QCoreApplication::translate("Results", "user_data_001.csv", nullptr));
        sizeLabel->setText(QCoreApplication::translate("Results", "Size:", nullptr));
        sizeValue->setText(QCoreApplication::translate("Results", "10,000 elements", nullptr));
        operationsLabel->setText(QCoreApplication::translate("Results", "Operations:", nullptr));
        operationsValue->setText(QCoreApplication::translate("Results", "Search 60% | Insert 25% | Delete 15%", nullptr));
        graphGroup->setTitle(QCoreApplication::translate("Results", "\360\237\223\210 Performance Comparison", nullptr));
        graphHint->setText(QCoreApplication::translate("Results", "Relative performance scores across different data structures (higher is better)", nullptr));
        graphText->setText(QCoreApplication::translate("Results", "[Performance Graph Placeholder ]", nullptr));
        detailedResultsGroup->setTitle(QCoreApplication::translate("Results", "\360\237\224\215 Detailed Results by Data Structure", nullptr));
        dsTag1->setText(QCoreApplication::translate("Results", "Hash Table", nullptr));
        label_10->setText(QCoreApplication::translate("Results", "Score:", nullptr));
        hashScore->setText(QCoreApplication::translate("Results", "94.2%", nullptr));
        hashNotes->setText(QCoreApplication::translate("Results", "\342\200\242 Fast search O(1) average\n"
"\342\200\242 Good for mixed operations\n"
"\342\200\242 Memory: Medium", nullptr));
        dsTag2->setText(QCoreApplication::translate("Results", "Balanced BST", nullptr));
        label_12->setText(QCoreApplication::translate("Results", "Score:", nullptr));
        bstScore->setText(QCoreApplication::translate("Results", "87.5%", nullptr));
        bstNotes->setText(QCoreApplication::translate("Results", "\342\200\242 Consistent O(log n)\n"
"\342\200\242 Ordered operations\n"
"\342\200\242 Memory: Low", nullptr));
        dsTag3->setText(QCoreApplication::translate("Results", "Array", nullptr));
        label_14->setText(QCoreApplication::translate("Results", "Score:", nullptr));
        arrayScore->setText(QCoreApplication::translate("Results", "62.3%", nullptr));
        arrayNotes->setText(QCoreApplication::translate("Results", "\342\200\242 Slow insert/delete O(n)\n"
"\342\200\242 Fast sequential access\n"
"\342\200\242 Memory: Very Low", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Results: public Ui_Results {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTS_H
