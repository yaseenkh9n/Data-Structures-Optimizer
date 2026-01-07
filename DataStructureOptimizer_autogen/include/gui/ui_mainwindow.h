/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebar;
    QVBoxLayout *verticalLayout;
    QFrame *logoFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *logoIcon;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QListWidget *sidebarList;
    QSpacerItem *sidebarVerticalSpacer;
    QFrame *userProfileFrame;
    QHBoxLayout *userProfileLayout;
    QLabel *userAvatarLabel;
    QLabel *userNameLabel;
    QSpacerItem *userProfileSpacer;
    QFrame *contentArea;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *settingsButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *welcomeTitle;
    QLabel *welcomeSubtitle;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *primaryButton;
    QPushButton *secondaryButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QFrame *card;
    QVBoxLayout *verticalLayout_3;
    QLabel *cardTitle;
    QSpacerItem *verticalSpacer_6;
    QLabel *cardText;
    QSpacerItem *verticalSpacer_7;
    QLabel *cardText_2;
    QLabel *cardTitle_2;
    QSpacerItem *verticalSpacer_8;
    QFrame *card_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *cardTitle_3;
    QSpacerItem *verticalSpacer_9;
    QLabel *highlightText;
    QSpacerItem *verticalSpacer_10;
    QLabel *cardText_3;
    QSpacerItem *verticalSpacer_11;
    QFrame *card_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *cardTitle_4;
    QSpacerItem *verticalSpacer_12;
    QLabel *cardText_4;
    QLabel *cardText_5;
    QLabel *cardText_6;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *verticalSpacer_14;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1058, 652);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"/* \342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\n"
"   DATA STRUCTURE OPTIMIZER - GLASSMORPHISM DASHBOARD\n"
"   Frosted glass effects with cyan/teal glowing accents\n"
"   \342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342"
                        "\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220 */\n"
"\n"
"/* Main Window - Unified Deep Space Background */\n"
"QMainWindow {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #0d1117,\n"
"        stop:0.5 #151b25,\n"
"        stop:1 #0d1117\n"
"    );\n"
"}\n"
"\n"
"/* Sidebar - Same Background, Subtle Border */\n"
"#sidebar {\n"
"    background: transparent;\n"
"    border-right: 1px solid r"
                        "gba(0, 212, 255, 0.15);\n"
"}\n"
"\n"
"/* Sidebar List - Interactive Glass Items */\n"
"QListWidget#sidebarList {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"    color: rgba(160, 180, 210, 0.85);\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 10px 5px;\n"
"}\n"
"\n"
"QListWidget#sidebarList::item {\n"
"    background: transparent;\n"
"    border: 1px solid transparent;\n"
"    border-radius: 10px;\n"
"    color: rgba(160, 180, 210, 0.8);\n"
"    padding: 14px 18px;\n"
"    margin: 3px 8px;\n"
"    height: 22px;\n"
"}\n"
"\n"
"QListWidget#sidebarList::item:hover {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:0,\n"
"        stop:0 rgba(0, 212, 255, 0.15),\n"
"        stop:0.8 rgba(0, 212, 255, 0.05),\n"
"        stop:1 transparent\n"
"    );\n"
"    border: 1px solid rgba(0, 212, 255, 0.25);\n"
"    border-left: 3px solid rgba(0, 212, 255, 0.6);\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QListWidget#sidebarList::ite"
                        "m:selected {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:0,\n"
"        stop:0 rgba(0, 212, 255, 0.25),\n"
"        stop:0.6 rgba(0, 212, 255, 0.1),\n"
"        stop:1 transparent\n"
"    );\n"
"    border: 1px solid rgba(0, 212, 255, 0.4);\n"
"    border-left: 4px solid #00d4ff;\n"
"    color: #00d4ff;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* Content Area - Transparent */\n"
"#contentArea {\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* Welcome Title */\n"
"#welcomeTitle {\n"
"    color: #ffffff;\n"
"    font-size: 38px;\n"
"    font-weight: 700;\n"
"    letter-spacing: -0.5px;\n"
"}\n"
"\n"
"#welcomeSubtitle {\n"
"    color: rgba(160, 180, 210, 0.8);\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* Primary Button - Glowing Cyan */\n"
"QPushButton#primaryButton {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #00d4ff,\n"
"        stop:0.5 #00b8e6,\n"
"        stop:1 #0099cc\n"
"    );\n"
"    color: #ffffff;\n"
"  "
                        "  border: none;\n"
"    border-radius: 12px;\n"
"    padding: 15px 40px;\n"
"    font-size: 15px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#primaryButton:hover {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #33dfff,\n"
"        stop:0.5 #00c8f5,\n"
"        stop:1 #00a8dd\n"
"    );\n"
"}\n"
"\n"
"QPushButton#primaryButton:pressed {\n"
"    background: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #00a8dd,\n"
"        stop:1 #0088bb\n"
"    );\n"
"}\n"
"\n"
"/* Secondary Button - Frosted Glass */\n"
"QPushButton#secondaryButton {\n"
"    background: rgba(255, 255, 255, 0.06);\n"
"    color: rgba(220, 230, 245, 0.9);\n"
"    border: 1px solid rgba(255, 255, 255, 0.12);\n"
"    border-radius: 12px;\n"
"    padding: 15px 40px;\n"
"    font-size: 15px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton#secondaryButton:hover {\n"
"    background: rgba(0, 212, 255, 0.12);\n"
"    border: 1px solid rgba(0, 21"
                        "2, 255, 0.35);\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* Cards - Frosted Glass Panels */\n"
"QFrame#card, QFrame#card_2, QFrame#card_3 {\n"
"    background: rgba(255, 255, 255, 0.04);\n"
"    border: 1px solid rgba(255, 255, 255, 0.08);\n"
"    border-radius: 16px;\n"
"    padding: 20px;\n"
"}\n"
"\n"
"QFrame#card:hover, QFrame#card_2:hover, QFrame#card_3:hover {\n"
"    background: rgba(0, 212, 255, 0.06);\n"
"    border: 1px solid rgba(0, 212, 255, 0.25);\n"
"}\n"
"\n"
"/* Card Titles */\n"
"QLabel#cardTitle, QLabel#cardTitle_2, QLabel#cardTitle_3, QLabel#cardTitle_4 {\n"
"    color: #ffffff;\n"
"    font-size: 15px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* Card Text */\n"
"QLabel#cardText, QLabel#cardText_2, QLabel#cardText_3, QLabel#cardText_4, QLabel#cardText_5, QLabel#cardText_6 {\n"
"    color: rgba(160, 180, 210, 0.75);\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Highlight Text - Glowing Cyan */\n"
"QLabel#highlightText {\n"
"    color: #00d4ff;\n"
"    font-size: 52px;\n"
"    font-weight: 700;\n"
""
                        "}\n"
"\n"
"/* Logo Text */\n"
"#logoText {\n"
"    color: #ffffff;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
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
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(250, 0));
        sidebar->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(sidebar);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        logoFrame = new QFrame(sidebar);
        logoFrame->setObjectName("logoFrame");
        logoFrame->setMinimumSize(QSize(0, 100));
        logoFrame->setMaximumSize(QSize(16777215, 100));
        horizontalLayout_2 = new QHBoxLayout(logoFrame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(20, 15, 20, 15);
        logoIcon = new QLabel(logoFrame);
        logoIcon->setObjectName("logoIcon");
        logoIcon->setMinimumSize(QSize(65, 65));
        logoIcon->setMaximumSize(QSize(150, 65));
        logoIcon->setPixmap(QPixmap(QString::fromUtf8(":/Icons/logo.png")));
        logoIcon->setScaledContents(true);
        logoIcon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(logoIcon);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(logoFrame);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        sidebarList = new QListWidget(sidebar);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/home_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(sidebarList);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/analytics_64dp_E3E3E3_FILL0_wght400_GRAD0_opsz48.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(sidebarList);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/bar_chart_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(sidebarList);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/help_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(sidebarList);
        __qlistwidgetitem3->setIcon(icon3);
        sidebarList->setObjectName("sidebarList");
        sidebarList->setStyleSheet(QString::fromUtf8("\n"
"QListWidget#sidebarList{\n"
"border-right: 1px solid rgba(255, 255, 255, 30);\n"
"}\n"
"QListWidget#sidebarList::item { \n"
"    background-color: rgba(255, 255, 255, 30); \n"
"    border-radius: 5px; \n"
"    color: #ffffff; \n"
"    padding: 5px 8px; \n"
"    margin: 2px 5px; \n"
"   height: 40px;\n"
"}"));
        sidebarList->setFrameShadow(QFrame::Shadow::Plain);

        verticalLayout->addWidget(sidebarList);

        sidebarVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(sidebarVerticalSpacer);

        userProfileFrame = new QFrame(sidebar);
        userProfileFrame->setObjectName("userProfileFrame");
        userProfileFrame->setMinimumSize(QSize(0, 60));
        userProfileFrame->setMaximumSize(QSize(16777215, 60));
        userProfileFrame->setStyleSheet(QString::fromUtf8("\n"
"QFrame#userProfileFrame {\n"
"    background: rgba(0, 212, 255, 0.08);\n"
"    border-top: 1px solid rgba(0, 212, 255, 0.2);\n"
"    border-right: 1px solid rgba(255, 255, 255, 30);\n"
"}\n"
"           "));
        userProfileLayout = new QHBoxLayout(userProfileFrame);
        userProfileLayout->setObjectName("userProfileLayout");
        userProfileLayout->setContentsMargins(15, 10, 15, 10);
        userAvatarLabel = new QLabel(userProfileFrame);
        userAvatarLabel->setObjectName("userAvatarLabel");
        userAvatarLabel->setMinimumSize(QSize(36, 36));
        userAvatarLabel->setMaximumSize(QSize(36, 36));
        userAvatarLabel->setStyleSheet(QString::fromUtf8("\n"
"QLabel#userAvatarLabel {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #00d4ff, stop:1 #0099cc);\n"
"    border-radius: 18px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"              "));
        userAvatarLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        userProfileLayout->addWidget(userAvatarLabel);

        userNameLabel = new QLabel(userProfileFrame);
        userNameLabel->setObjectName("userNameLabel");
        userNameLabel->setStyleSheet(QString::fromUtf8("\n"
"QLabel#userNameLabel {\n"
"    color: rgba(220, 230, 245, 0.9);\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    padding-left: 8px;\n"
"}\n"
"              "));

        userProfileLayout->addWidget(userNameLabel);

        userProfileSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        userProfileLayout->addItem(userProfileSpacer);


        verticalLayout->addWidget(userProfileFrame);


        horizontalLayout->addWidget(sidebar);

        contentArea = new QFrame(centralwidget);
        contentArea->setObjectName("contentArea");
        verticalLayout_2 = new QVBoxLayout(contentArea);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(40, 30, 40, 30);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        settingsButton = new QPushButton(contentArea);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setStyleSheet(QString::fromUtf8("color: rgba(62, 71, 255, 245);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/settings_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon4);
        settingsButton->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(settingsButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        welcomeTitle = new QLabel(contentArea);
        welcomeTitle->setObjectName("welcomeTitle");
        welcomeTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout_2->addWidget(welcomeTitle);

        welcomeSubtitle = new QLabel(contentArea);
        welcomeSubtitle->setObjectName("welcomeSubtitle");

        verticalLayout_2->addWidget(welcomeSubtitle);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        primaryButton = new QPushButton(contentArea);
        primaryButton->setObjectName("primaryButton");

        horizontalLayout_4->addWidget(primaryButton);

        secondaryButton = new QPushButton(contentArea);
        secondaryButton->setObjectName("secondaryButton");

        horizontalLayout_4->addWidget(secondaryButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        card = new QFrame(contentArea);
        card->setObjectName("card");
        verticalLayout_3 = new QVBoxLayout(card);
        verticalLayout_3->setObjectName("verticalLayout_3");
        cardTitle = new QLabel(card);
        cardTitle->setObjectName("cardTitle");

        verticalLayout_3->addWidget(cardTitle);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_6);

        cardText = new QLabel(card);
        cardText->setObjectName("cardText");

        verticalLayout_3->addWidget(cardText);

        verticalSpacer_7 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_7);

        cardText_2 = new QLabel(card);
        cardText_2->setObjectName("cardText_2");

        verticalLayout_3->addWidget(cardText_2);

        cardTitle_2 = new QLabel(card);
        cardTitle_2->setObjectName("cardTitle_2");

        verticalLayout_3->addWidget(cardTitle_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);


        horizontalLayout_5->addWidget(card);

        card_2 = new QFrame(contentArea);
        card_2->setObjectName("card_2");
        verticalLayout_4 = new QVBoxLayout(card_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        cardTitle_3 = new QLabel(card_2);
        cardTitle_3->setObjectName("cardTitle_3");

        verticalLayout_4->addWidget(cardTitle_3);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_9);

        highlightText = new QLabel(card_2);
        highlightText->setObjectName("highlightText");
        highlightText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(highlightText);

        verticalSpacer_10 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_10);

        cardText_3 = new QLabel(card_2);
        cardText_3->setObjectName("cardText_3");
        cardText_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(cardText_3);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_11);


        horizontalLayout_5->addWidget(card_2);

        card_3 = new QFrame(contentArea);
        card_3->setObjectName("card_3");
        verticalLayout_5 = new QVBoxLayout(card_3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        cardTitle_4 = new QLabel(card_3);
        cardTitle_4->setObjectName("cardTitle_4");

        verticalLayout_5->addWidget(cardTitle_4);

        verticalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_12);

        cardText_4 = new QLabel(card_3);
        cardText_4->setObjectName("cardText_4");

        verticalLayout_5->addWidget(cardText_4);

        cardText_5 = new QLabel(card_3);
        cardText_5->setObjectName("cardText_5");

        verticalLayout_5->addWidget(cardText_5);

        cardText_6 = new QLabel(card_3);
        cardText_6->setObjectName("cardText_6");

        verticalLayout_5->addWidget(cardText_6);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_13);


        horizontalLayout_5->addWidget(card_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_14);


        horizontalLayout->addWidget(contentArea);

        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DSA Optimizer", nullptr));
        logoIcon->setText(QString());

        const bool __sortingEnabled = sidebarList->isSortingEnabled();
        sidebarList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = sidebarList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = sidebarList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "Analysis", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = sidebarList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "Results", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = sidebarList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        sidebarList->setSortingEnabled(__sortingEnabled);

        userAvatarLabel->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        userNameLabel->setText(QCoreApplication::translate("MainWindow", "User", nullptr));
        settingsButton->setText(QString());
        welcomeTitle->setText(QCoreApplication::translate("MainWindow", "Welcome to \n"
"Data Structure Optimizer", nullptr));
        welcomeSubtitle->setText(QCoreApplication::translate("MainWindow", "Analyze, benchmark, and discover the best data structures intelligently.", nullptr));
        primaryButton->setText(QCoreApplication::translate("MainWindow", "Start New Analysis", nullptr));
        secondaryButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        cardTitle->setText(QCoreApplication::translate("MainWindow", "Last Run Summary", nullptr));
        cardText->setText(QCoreApplication::translate("MainWindow", "dataset_001.csv", nullptr));
        cardText_2->setText(QCoreApplication::translate("MainWindow", "Best Data Structure", nullptr));
        cardTitle_2->setText(QCoreApplication::translate("MainWindow", "HashMap", nullptr));
        cardTitle_3->setText(QCoreApplication::translate("MainWindow", "Top Performing Structure", nullptr));
        highlightText->setText(QCoreApplication::translate("MainWindow", "95%", nullptr));
        cardText_3->setText(QCoreApplication::translate("MainWindow", "Accuracy", nullptr));
        cardTitle_4->setText(QCoreApplication::translate("MainWindow", "Recent Datasets", nullptr));
        cardText_4->setText(QCoreApplication::translate("MainWindow", "dataset_005.csv", nullptr));
        cardText_5->setText(QCoreApplication::translate("MainWindow", "dataset_004.csv", nullptr));
        cardText_6->setText(QCoreApplication::translate("MainWindow", "dataset_003.csv", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
