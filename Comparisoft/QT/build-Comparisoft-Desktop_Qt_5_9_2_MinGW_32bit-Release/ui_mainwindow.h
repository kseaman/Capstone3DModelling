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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_4;
    QStackedWidget *View_Holder;
    QWidget *Main_Page;
    QVBoxLayout *verticalLayout_13;
    QWidget *widget;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_18;
    QVBoxLayout *verticalLayout_2;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Source_File_Text;
    QSpacerItem *verticalSpacer_6;
    QPushButton *Source_File_Button;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *Target_File_Text;
    QVBoxLayout *verticalLayout_34;
    QPushButton *Target_File_Button;
    QPushButton *Clear_Target_Files;
    QFrame *line;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_2;
    QLineEdit *Technician_Name;
    QLabel *label_4;
    QLineEdit *Client_Name;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QLineEdit *Patient_Name;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_22;
    QLineEdit *File_Description;
    QWidget *widget_9;
    QSpacerItem *verticalSpacer_8;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_17;
    QLineEdit *Save_Location;
    QPushButton *saveLocationButton;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_8;
    QLineEdit *File_Name;
    QVBoxLayout *verticalLayout_10;
    QPushButton *Config_Button;
    QWidget *Config_Page;
    QGridLayout *gridLayout_2;
    QPushButton *ReturnToMainPage;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_18;
    QVBoxLayout *verticalLayout_32;
    QLabel *label_20;
    QTextEdit *Product_Description;
    QVBoxLayout *verticalLayout_33;
    QSpacerItem *verticalSpacer_5;
    QPushButton *RunVTK;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_17;
    QFrame *line_2;
    QLabel *label_15;
    QVBoxLayout *verticalLayout_20;
    QSpacerItem *horizontalSpacer;
    QFrame *line_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_21;
    QComboBox *Report_Type;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_21;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_19;
    QSpinBox *Confidence_Level;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_12;
    QSpinBox *Error_Bound;
    QComboBox *Error_Unit;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_20;
    QComboBox *Alignment_Type;
    QLabel *label_17;
    QComboBox *camera_options;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1318, 729);
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
        verticalLayout_12->setContentsMargins(-1, 7, -1, 7);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        View_Holder = new QStackedWidget(centralWidget);
        View_Holder->setObjectName(QStringLiteral("View_Holder"));
        View_Holder->setMinimumSize(QSize(0, 0));
        Main_Page = new QWidget();
        Main_Page->setObjectName(QStringLiteral("Main_Page"));
        Main_Page->setEnabled(true);
        verticalLayout_13 = new QVBoxLayout(Main_Page);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        widget = new QWidget(Main_Page);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 125));
        widget->setMaximumSize(QSize(16777215, 100));
        verticalLayout_14 = new QVBoxLayout(widget);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        label_18 = new QLabel(widget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(0, 100));
        label_18->setPixmap(QPixmap(QString::fromUtf8("mainlogo.png")));
        label_18->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_18);


        verticalLayout_14->addLayout(horizontalLayout_6);


        verticalLayout_13->addWidget(widget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        line_4 = new QFrame(Main_Page);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_4);

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
        Source_File_Text = new QLineEdit(Main_Page);
        Source_File_Text->setObjectName(QStringLiteral("Source_File_Text"));
        Source_File_Text->setMinimumSize(QSize(600, 0));

        horizontalLayout->addWidget(Source_File_Text);

        verticalSpacer_6 = new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer_6);

        Source_File_Button = new QPushButton(Main_Page);
        Source_File_Button->setObjectName(QStringLiteral("Source_File_Button"));

        horizontalLayout->addWidget(Source_File_Button);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Target_File_Text = new QTextEdit(Main_Page);
        Target_File_Text->setObjectName(QStringLiteral("Target_File_Text"));

        horizontalLayout_2->addWidget(Target_File_Text);

        verticalLayout_34 = new QVBoxLayout();
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setObjectName(QStringLiteral("verticalLayout_34"));
        Target_File_Button = new QPushButton(Main_Page);
        Target_File_Button->setObjectName(QStringLiteral("Target_File_Button"));

        verticalLayout_34->addWidget(Target_File_Button);

        Clear_Target_Files = new QPushButton(Main_Page);
        Clear_Target_Files->setObjectName(QStringLiteral("Clear_Target_Files"));

        verticalLayout_34->addWidget(Clear_Target_Files);


        horizontalLayout_2->addLayout(verticalLayout_34);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);


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
        label_2 = new QLabel(Main_Page);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_7->addWidget(label_2);

        Technician_Name = new QLineEdit(Main_Page);
        Technician_Name->setObjectName(QStringLiteral("Technician_Name"));

        verticalLayout_7->addWidget(Technician_Name);

        label_4 = new QLabel(Main_Page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setTextFormat(Qt::RichText);

        verticalLayout_7->addWidget(label_4);

        Client_Name = new QLineEdit(Main_Page);
        Client_Name->setObjectName(QStringLiteral("Client_Name"));

        verticalLayout_7->addWidget(Client_Name);


        horizontalLayout_7->addLayout(verticalLayout_7);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_7->addItem(verticalSpacer_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_5 = new QLabel(Main_Page);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_6->addWidget(label_5, 0, Qt::AlignBottom);

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
        verticalLayout_8->setContentsMargins(-1, -1, -1, 0);
        label_6 = new QLabel(Main_Page);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_8->addWidget(label_6);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        File_Description = new QLineEdit(Main_Page);
        File_Description->setObjectName(QStringLiteral("File_Description"));

        horizontalLayout_22->addWidget(File_Description);

        widget_9 = new QWidget(Main_Page);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setMinimumSize(QSize(0, 28));
        widget_9->setMaximumSize(QSize(0, 28));

        horizontalLayout_22->addWidget(widget_9);


        verticalLayout_8->addLayout(horizontalLayout_22);


        horizontalLayout_8->addLayout(verticalLayout_8);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_8->addItem(verticalSpacer_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_7 = new QLabel(Main_Page);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_9->addWidget(label_7);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        Save_Location = new QLineEdit(Main_Page);
        Save_Location->setObjectName(QStringLiteral("Save_Location"));

        horizontalLayout_17->addWidget(Save_Location);

        saveLocationButton = new QPushButton(Main_Page);
        saveLocationButton->setObjectName(QStringLiteral("saveLocationButton"));
        saveLocationButton->setMinimumSize(QSize(0, 0));

        horizontalLayout_17->addWidget(saveLocationButton);


        verticalLayout_9->addLayout(horizontalLayout_17);


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
        Config_Button->setMinimumSize(QSize(0, 75));

        verticalLayout_10->addWidget(Config_Button);


        horizontalLayout_9->addLayout(verticalLayout_10);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_13->addLayout(verticalLayout_2);

        View_Holder->addWidget(Main_Page);
        Config_Page = new QWidget();
        Config_Page->setObjectName(QStringLiteral("Config_Page"));
        gridLayout_2 = new QGridLayout(Config_Page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        ReturnToMainPage = new QPushButton(Config_Page);
        ReturnToMainPage->setObjectName(QStringLiteral("ReturnToMainPage"));
        ReturnToMainPage->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(ReturnToMainPage, 1, 0, 1, 1);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setSpacing(6);
        verticalLayout_32->setObjectName(QStringLiteral("verticalLayout_32"));
        label_20 = new QLabel(Config_Page);
        label_20->setObjectName(QStringLiteral("label_20"));

        verticalLayout_32->addWidget(label_20);

        Product_Description = new QTextEdit(Config_Page);
        Product_Description->setObjectName(QStringLiteral("Product_Description"));

        verticalLayout_32->addWidget(Product_Description);


        horizontalLayout_18->addLayout(verticalLayout_32);

        verticalLayout_33 = new QVBoxLayout();
        verticalLayout_33->setSpacing(6);
        verticalLayout_33->setObjectName(QStringLiteral("verticalLayout_33"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_33->addItem(verticalSpacer_5);

        RunVTK = new QPushButton(Config_Page);
        RunVTK->setObjectName(QStringLiteral("RunVTK"));
        RunVTK->setMinimumSize(QSize(100, 75));
        RunVTK->setMaximumSize(QSize(200, 16777215));
        RunVTK->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_33->addWidget(RunVTK);


        horizontalLayout_18->addLayout(verticalLayout_33);


        verticalLayout_19->addLayout(horizontalLayout_18);


        gridLayout_2->addLayout(verticalLayout_19, 5, 0, 1, 3);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        line_2 = new QFrame(Config_Page);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_17->addWidget(line_2);

        label_15 = new QLabel(Config_Page);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_17->addWidget(label_15, 0, Qt::AlignVCenter);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_20->addItem(horizontalSpacer);

        line_3 = new QFrame(Config_Page);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_20->addWidget(line_3);

        label = new QLabel(Config_Page);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_20->addWidget(label);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        Report_Type = new QComboBox(Config_Page);
        Report_Type->setObjectName(QStringLiteral("Report_Type"));

        horizontalLayout_21->addWidget(Report_Type);


        verticalLayout_20->addLayout(horizontalLayout_21);


        verticalLayout_17->addLayout(verticalLayout_20);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        label_9 = new QLabel(Config_Page);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_21->addWidget(label_9);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        Confidence_Level = new QSpinBox(Config_Page);
        Confidence_Level->setObjectName(QStringLiteral("Confidence_Level"));

        horizontalLayout_19->addWidget(Confidence_Level);


        verticalLayout_21->addLayout(horizontalLayout_19);


        horizontalLayout_13->addLayout(verticalLayout_21);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        label_10 = new QLabel(Config_Page);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_22->addWidget(label_10);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(7);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        Error_Bound = new QSpinBox(Config_Page);
        Error_Bound->setObjectName(QStringLiteral("Error_Bound"));

        horizontalLayout_12->addWidget(Error_Bound);

        Error_Unit = new QComboBox(Config_Page);
        Error_Unit->setObjectName(QStringLiteral("Error_Unit"));

        horizontalLayout_12->addWidget(Error_Unit);


        verticalLayout_22->addLayout(horizontalLayout_12);


        horizontalLayout_13->addLayout(verticalLayout_22);


        verticalLayout_17->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        label_11 = new QLabel(Config_Page);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_23->addWidget(label_11);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        Alignment_Type = new QComboBox(Config_Page);
        Alignment_Type->setObjectName(QStringLiteral("Alignment_Type"));

        horizontalLayout_20->addWidget(Alignment_Type);


        verticalLayout_23->addLayout(horizontalLayout_20);

        label_17 = new QLabel(Config_Page);
        label_17->setObjectName(QStringLiteral("label_17"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_17->setFont(font);

        verticalLayout_23->addWidget(label_17);

        camera_options = new QComboBox(Config_Page);
        camera_options->setObjectName(QStringLiteral("camera_options"));

        verticalLayout_23->addWidget(camera_options);


        horizontalLayout_14->addLayout(verticalLayout_23);


        verticalLayout_17->addLayout(horizontalLayout_14);


        horizontalLayout_11->addLayout(verticalLayout_17);


        gridLayout_2->addLayout(horizontalLayout_11, 4, 0, 1, 1);

        label_3 = new QLabel(Config_Page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        label_3->setPixmap(QPixmap(QString::fromUtf8("mainlogo.png")));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1, Qt::AlignHCenter);

        View_Holder->addWidget(Config_Page);

        horizontalLayout_4->addWidget(View_Holder);


        verticalLayout_12->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1318, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        View_Holder->setCurrentIndex(0);
        Report_Type->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_18->setText(QString());
        Source_File_Button->setText(QApplication::translate("MainWindow", "Source File", Q_NULLPTR));
        Target_File_Button->setText(QApplication::translate("MainWindow", "Target File", Q_NULLPTR));
        Clear_Target_Files->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Technician Name:</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Client Name:</span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Patient Name:</span></p></body></html>", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">File Description:</span></p></body></html>", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Save Location:</span></p></body></html>", Q_NULLPTR));
        saveLocationButton->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">File Name:</span></p></body></html>", Q_NULLPTR));
        Config_Button->setText(QApplication::translate("MainWindow", "Configure", Q_NULLPTR));
        ReturnToMainPage->setText(QApplication::translate("MainWindow", "Back", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Description</span></p></body></html>", Q_NULLPTR));
        RunVTK->setText(QApplication::translate("MainWindow", "Align", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">Run Configuration</span></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "<b>Report Type:</b>", Q_NULLPTR));
        Report_Type->clear();
        Report_Type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Error Report", Q_NULLPTR)
        );
        Report_Type->setCurrentText(QApplication::translate("MainWindow", "Error Report", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "<b>Confidence Level:</b>", Q_NULLPTR));
        Confidence_Level->setSuffix(QApplication::translate("MainWindow", "%", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">within +/-</span></p></body></html>", Q_NULLPTR));
        Error_Unit->clear();
        Error_Unit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "nm", Q_NULLPTR)
         << QApplication::translate("MainWindow", "mm", Q_NULLPTR)
        );
        label_11->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Alignment Type:</span></p></body></html>", Q_NULLPTR));
        Alignment_Type->clear();
        Alignment_Type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Standard", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Bounding-Box", Q_NULLPTR)
        );
        label_17->setText(QApplication::translate("MainWindow", "Camera Orientation:", Q_NULLPTR));
        camera_options->clear();
        camera_options->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Matching Files", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Fitting Files", Q_NULLPTR)
        );
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
