/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_12;
    QStackedWidget *View_Holder;
    QWidget *Main_Page;
    QVBoxLayout *verticalLayout_13;
    QWidget *widget;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QPushButton *Settings_Button;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Referance_File_Text;
    QPushButton *Referance_File_Button;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *Production_File_Text;
    QPushButton *Production_File_Button;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *Ref_Attempt;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *Prod_Attempt;
    QFrame *line;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QLineEdit *Client_Name;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QLineEdit *Patient_Name;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_6;
    QLineEdit *File_Description;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_7;
    QLineEdit *Save_Location;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_8;
    QLineEdit *File_Name;
    QVBoxLayout *verticalLayout_10;
    QPushButton *Config_Button;
    QWidget *Config_Page;
    QPushButton *RunVTK;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1305, 683);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_12 = new QVBoxLayout(centralWidget);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        View_Holder = new QStackedWidget(centralWidget);
        View_Holder->setObjectName(QStringLiteral("View_Holder"));
        Main_Page = new QWidget();
        Main_Page->setObjectName(QStringLiteral("Main_Page"));
        Main_Page->setEnabled(true);
        verticalLayout_13 = new QVBoxLayout(Main_Page);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        widget = new QWidget(Main_Page);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 100));
        verticalLayout_14 = new QVBoxLayout(widget);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 50));
        label->setTextFormat(Qt::RichText);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label);

        Settings_Button = new QPushButton(widget);
        Settings_Button->setObjectName(QStringLiteral("Settings_Button"));
        Settings_Button->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(Settings_Button);


        verticalLayout_14->addLayout(horizontalLayout_6);


        verticalLayout_13->addWidget(widget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Referance_File_Text = new QLineEdit(Main_Page);
        Referance_File_Text->setObjectName(QStringLiteral("Referance_File_Text"));
        Referance_File_Text->setMinimumSize(QSize(700, 0));

        horizontalLayout->addWidget(Referance_File_Text);

        Referance_File_Button = new QPushButton(Main_Page);
        Referance_File_Button->setObjectName(QStringLiteral("Referance_File_Button"));

        horizontalLayout->addWidget(Referance_File_Button);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Production_File_Text = new QLineEdit(Main_Page);
        Production_File_Text->setObjectName(QStringLiteral("Production_File_Text"));

        horizontalLayout_2->addWidget(Production_File_Text);

        Production_File_Button = new QPushButton(Main_Page);
        Production_File_Button->setObjectName(QStringLiteral("Production_File_Button"));

        horizontalLayout_2->addWidget(Production_File_Button);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(Main_Page);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        Ref_Attempt = new QLineEdit(Main_Page);
        Ref_Attempt->setObjectName(QStringLiteral("Ref_Attempt"));

        horizontalLayout_4->addWidget(Ref_Attempt);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(Main_Page);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        Prod_Attempt = new QLineEdit(Main_Page);
        Prod_Attempt->setObjectName(QStringLiteral("Prod_Attempt"));

        horizontalLayout_5->addWidget(Prod_Attempt);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout_5);

        line = new QFrame(Main_Page);
        line->setObjectName(QStringLiteral("line"));
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_4 = new QLabel(Main_Page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setTextFormat(Qt::RichText);

        verticalLayout_7->addWidget(label_4);

        Client_Name = new QLineEdit(Main_Page);
        Client_Name->setObjectName(QStringLiteral("Client_Name"));

        verticalLayout_7->addWidget(Client_Name);


        horizontalLayout_7->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_5 = new QLabel(Main_Page);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_6->addWidget(label_5);

        Patient_Name = new QLineEdit(Main_Page);
        Patient_Name->setObjectName(QStringLiteral("Patient_Name"));

        verticalLayout_6->addWidget(Patient_Name);


        horizontalLayout_7->addLayout(verticalLayout_6);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_6 = new QLabel(Main_Page);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_8->addWidget(label_6);

        File_Description = new QLineEdit(Main_Page);
        File_Description->setObjectName(QStringLiteral("File_Description"));

        verticalLayout_8->addWidget(File_Description);


        horizontalLayout_8->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_7 = new QLabel(Main_Page);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_9->addWidget(label_7);

        Save_Location = new QLineEdit(Main_Page);
        Save_Location->setObjectName(QStringLiteral("Save_Location"));

        verticalLayout_9->addWidget(Save_Location);


        horizontalLayout_8->addLayout(verticalLayout_9);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_8 = new QLabel(Main_Page);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_11->addWidget(label_8);

        File_Name = new QLineEdit(Main_Page);
        File_Name->setObjectName(QStringLiteral("File_Name"));

        verticalLayout_11->addWidget(File_Name);


        horizontalLayout_9->addLayout(verticalLayout_11);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        Config_Button = new QPushButton(Main_Page);
        Config_Button->setObjectName(QStringLiteral("Config_Button"));

        verticalLayout_10->addWidget(Config_Button);


        horizontalLayout_9->addLayout(verticalLayout_10);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_13->addLayout(verticalLayout_2);

        View_Holder->addWidget(Main_Page);
        Config_Page = new QWidget();
        Config_Page->setObjectName(QStringLiteral("Config_Page"));
        RunVTK = new QPushButton(Config_Page);
        RunVTK->setObjectName(QStringLiteral("RunVTK"));
        RunVTK->setGeometry(QRect(330, 540, 347, 28));
        View_Holder->addWidget(Config_Page);

        verticalLayout_12->addWidget(View_Holder);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1318, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        View_Holder->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:26pt; font-weight:600; color:#b6fd01;\">Comparisoft</span></p></body></html>", Q_NULLPTR));
        Settings_Button->setText(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        Referance_File_Button->setText(QApplication::translate("MainWindow", "Referance File", Q_NULLPTR));
        Production_File_Button->setText(QApplication::translate("MainWindow", "Prodiction File", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Attempt:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Attempt:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "<b>Client Name</b>", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "<b>Patient Name</b>", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "<b>File Description</b>", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "<b>Save Location</b>", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "<b>File Name</b>", Q_NULLPTR));
        Config_Button->setText(QApplication::translate("MainWindow", "Configure", Q_NULLPTR));
        RunVTK->setText(QApplication::translate("MainWindow", "Run VTK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
