#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <iostream>
#include <fstream>
using namespace std;

#if !defined(_WIN32)
    #include <sys/types.h>
    #include <sys/stat.h>
#else
    #include <direct.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString refFile;
    QString prodFile;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RunVTK_clicked()
{
    QObject *parent;

    QString program = "./VSVTK.exe";
    QStringList argv;
    QLineEdit* fileReference = findChild<QLineEdit*>("Reference_File_Text");
    QTextEdit* fileProduction = findChild<QTextEdit*>("Production_File_Text");
    argv << fileReference->text();
    QString productionfiles = fileProduction->toPlainText();
    //qInfo() << productionfiles;
    QStringList pFileList = productionfiles.split(QRegularExpression("\n"),QString::SkipEmptyParts);
    foreach(QString line, pFileList){
        //qInfo() << line;
        argv << line;
    }

    QProcess *VTK = new QProcess(parent);
    VTK->start(program, argv);
    VTK->waitForStarted();
    window()->hide();
    VTK->waitForFinished();
    window()->show();
    VTK->close();

}

MainWindow::userInfo getInfoFields(QString rFilePath) {

    MainWindow::userInfo info;

    /* Save beginning of filepath for determining save location */
    QString copy = rFilePath;
    int final_pos;
    int pos = copy.indexOf("/") + 1;
    final_pos = pos;
    copy = copy.mid(pos, copy.length());
    pos = copy.indexOf("/") + 1;
    final_pos += pos;
    copy = copy.mid(pos, copy.length());
    pos = copy.indexOf("/");
    final_pos += pos;
    info.filePath = rFilePath.mid(0, final_pos);

    /* Parse file path to find client name */
    /* Assumption: client name in format of Dr.Name */
    rFilePath = rFilePath.mid(rFilePath.lastIndexOf("/") + 1, rFilePath.length());
    QString client = rFilePath.left(rFilePath.indexOf("_"));
    info.client = client.left(client.indexOf(".") + 1);
    client = client.mid(client.indexOf(".") + 1, client.length());
    info.client.append(" " + client);

    /* Parse file path to find patient name */
    /* Assumption: patient name in format Last_First */
    rFilePath = rFilePath.mid(rFilePath.indexOf("_") + 1, rFilePath.length());
    QString patient_last = rFilePath.mid(0, rFilePath.indexOf("_"));
    rFilePath = rFilePath.mid(rFilePath.indexOf("_") + 1, rFilePath.length());
    QString patient_first = rFilePath.mid(0, rFilePath.indexOf("_"));
    info.patient = patient_first;
    info.patient.append(" " + patient_last);

    /* Parse file path to find file description */
    /* Assumption: file description exists following a space after file time */
    rFilePath = rFilePath.mid(rFilePath.indexOf("_") + 1, rFilePath.length());

    if (rFilePath.contains(".")) {
        rFilePath = rFilePath.mid(rFilePath.indexOf(" ") + 1, rFilePath.length());
        info.fileDescription = rFilePath.left(rFilePath.indexOf("."));
    }
    else {
        info.fileDescription = rFilePath.mid(rFilePath.indexOf(" ") + 1, rFilePath.length());
    }

    return info;
}

void MainWindow::on_Reference_File_Button_clicked()
{
    QString filepathR = fileDialog();
    QLineEdit* fileReference = findChild<QLineEdit*>("Reference_File_Text");
    fileReference->setText(filepathR);

    MainWindow::userInfo info = getInfoFields(fileReference->text());

    QLineEdit* clientRef = MainWindow::findChild<QLineEdit*>("Client_Name");
    clientRef->setText(info.client);
    QLineEdit* patientRef = MainWindow::findChild<QLineEdit*>("Patient_Name");
    patientRef->setText(info.patient);
    QLineEdit* fileDescRef = MainWindow::findChild<QLineEdit*>("File_Description");
    fileDescRef->setText(info.fileDescription);

    QLineEdit* savePath = MainWindow::findChild<QLineEdit*>("Save_Location");
    savePath->setText(info.filePath + "/Comparisoft/Reports/");

    QLineEdit* saveFile = MainWindow::findChild<QLineEdit*>("File_Name");
    QDate date = QDate::currentDate();
    QString newFileName = "Report_";
    newFileName.append(QString::number(date.year()));
    newFileName.append("-");
    newFileName.append(QString::number(date.month()));
    newFileName.append("-");
    newFileName.append(QString::number(date.day()));
    newFileName.append("_");
    newFileName.append(info.client.replace(" ", ""));
    newFileName.append("_");
    newFileName.append(info.patient.replace(" ", ""));
    newFileName.append("_");
    newFileName.append(info.fileDescription.replace(" ", ""));
    newFileName.append(".txt");
    saveFile->setText(newFileName);
}

void MainWindow::on_Production_File_Button_clicked()
{
    QStringList filepathPlist = fileDialogMulti();
    QTextEdit* fileProduction = findChild<QTextEdit*>("Production_File_Text");
    foreach (QString filepath, filepathPlist) {
        fileProduction->append(filepath);
    }

}

QString MainWindow::fileDialog()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("STL (*.stl)"));
    return filename;
}

QStringList MainWindow::fileDialogMulti()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Select File"), "", tr("STL (*.stl)"));
    return filenames;
}

void MainWindow::on_Config_Button_clicked()
{
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(1);

    std::string sPath = "/tmp/test";

    QString savePath = MainWindow::findChild<QLineEdit*>("Save_Location")->text();

    int error = 0;

    QString rFilePath = MainWindow::findChild<QLineEdit*>("Reference_File_Text")->text();
    QString copy = rFilePath;
    int final_pos;
    int pos = copy.indexOf("/") + 1;
    final_pos = pos;
    copy = copy.mid(pos, copy.length());
    pos = copy.indexOf("/") + 1;
    final_pos += pos;
    copy = copy.mid(pos, copy.length());
    pos = copy.indexOf("/");
    final_pos += pos;
    rFilePath = rFilePath.mid(0, final_pos);

    QString default_path = rFilePath;
    QString home = rFilePath;
    default_path.append("/Comparisoft/Reports/");

    if (savePath.contains(default_path)) {
        QMessageBox msgBox;
        msgBox.setText("The directory specified does not exist.");
        msgBox.setInformativeText("Do you want to create a new Reports directory?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Ok:
            /* For Windows environments */
            #if defined(_WIN32)
                error = _mkdir(home.append("/Comparisoft").toStdString().c_str());

                /* Error has occurred */
                if (error != 0) {
                    qInfo( "Error occurred creating directory:");
                    perror ("The following error occurred");
                }

                error = _mkdir(home.append("/Reports").toStdString().c_str());

                /* Error has occurred */
                if (error != 0) {
                    qInfo( "Error occurred creating directory:");
                    perror ("The following error occurred");
                }
            /* For Mac/Linux environments */
            #else
                error = mkdir(home.append("/Comparisoft").toStdString().c_str(), 0777);

                /* Error has occurred */
                if (error != 0) {
                    qInfo( "Error occurred creating directory:");
                    perror ("The following error occurred");
                }

                error = mkdir(home.append("/Reports").toStdString().c_str(), 0777);

                /* Error has occurred */
                if (error != 0) {
                    qInfo( "Error occurred creating directory:");
                    perror ("The following error occurred");
                }
            #endif
            break;
          case QMessageBox::Cancel:
              /* User returns to Settings page */
            view_holder->setCurrentIndex(0);
              break;
          default:
              break;
        }
    }

    QString saveFile = MainWindow::findChild<QLineEdit*>("File_Name")->text();
    QString client = MainWindow::findChild<QLineEdit*>("Client_Name")->text();
    QString patient = MainWindow::findChild<QLineEdit*>("Patient_Name")->text();

    ofstream comparison_report;
    QString filepath = savePath;
    filepath.append("/");
    filepath.append(saveFile);
    comparison_report.open (filepath.toLatin1().data());
    comparison_report << "Comparisoft\n";
    comparison_report << "Client: " << client.toStdString() << "\n";
    comparison_report << "Patient: " << patient.toStdString() << "\n";
    comparison_report.close();
}

void MainWindow::on_saveLocation_clicked()
{
    QString fileSavePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly);
    QLineEdit* fileSave = findChild<QLineEdit*>("Save_Location");
    fileSave->setText(fileSavePath);
}

void MainWindow::on_ReturnToMainPage_clicked()
{
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(0);
}

void MainWindow::on_Settings_Button_clicked()
{
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(2);
}

void MainWindow::on_Settings_Button_2_clicked()
{
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(2);
}

void MainWindow::on_Return_to_Setup_Button_clicked()
{
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(0);
}

void MainWindow::on_Return_to_Configuration_Button_clicked()
{
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(1);
}

void MainWindow::on_Clear_Production_Files_clicked()
{
    QTextEdit* fileProduction = findChild<QTextEdit*>("Production_File_Text");
    fileProduction->clear();
}
