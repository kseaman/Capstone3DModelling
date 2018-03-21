#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <iostream>
#include <fstream>
using namespace std;

/* Windows environment detected */
#if defined(_WIN32)
    #include <direct.h>
    #include <windows.h>
    #include <io.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <tchar.h>
    //#include <shlwapi.h>

/* Mac/Linux environment detected */
#else
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString sourceFile;
    QString targetFile;
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

    //create argument list
    QStringList argv;

    //argument 0: program name
    //this is done automatically

    //argument 1: Client_Name
    QLineEdit* cname = findChild<QLineEdit*>("Client_Name");
    argv << cname->text();

    //argument 2: Patient_Name
    QLineEdit* pname = findChild<QLineEdit*>("Patient_Name");
    argv << pname->text();

    //argument 3: File_Description
    QLineEdit* fdesc = findChild<QLineEdit*>("File_Description");
    argv << fdesc->text();

    //argument 4: Save_Location
    QLineEdit* sloc = findChild<QLineEdit*>("Save_Location");
    argv << sloc->text();

    //argument 5: File_Name
    QLineEdit* fname = findChild<QLineEdit*>("File_Name");
    argv << fname->text();

    //argument 6: Technician_Name
    QLineEdit* tname = findChild<QLineEdit*>("Technician_Name");
    argv << tname->text();

    //argument 7: Description
    QTextEdit* pdesc = findChild<QTextEdit*>("Product_Description");
    argv << pdesc->toPlainText();

    //argument 8: Report_Type
    QComboBox* rtype = findChild<QComboBox*>("Report_Type");
    argv << rtype->currentText();

    //argument 9: Confidence_Level
    QSpinBox* clevel = findChild<QSpinBox*>("Confidence_Level");
    argv << clevel->cleanText();

    //argument 10: Error_Bound
    QSpinBox* ebound = findChild<QSpinBox*>("Error_Bound");
    argv << ebound->cleanText();

    //argument 11: Error_Unit
    QComboBox* eunit = findChild<QComboBox*>("Error_Unit");
    argv << eunit->currentText();

    //argument 12: Alignment_Type
    QComboBox* atype = findChild<QComboBox*>("Alignment_Type");
    argv << atype->currentText();

    //argument 13: Camera_Orientation
    QComboBox* camera_orientation = findChild<QComboBox*>("camera_options");
    argv << QString::number(camera_orientation->currentIndex());

    //argument 14: source file
    QLineEdit* fileSource = findChild<QLineEdit*>("Source_File_Text");
    argv << fileSource->text();

    //argument 15+: target file(s)
    QTextEdit* fileTarget = findChild<QTextEdit*>("Target_File_Text");

    //insert multiple target files
    QString target_files = fileTarget->toPlainText();
    QStringList pFileList = target_files.split(QRegularExpression("\n"), QString::SkipEmptyParts);
    foreach(QString line, pFileList){
        argv << line;
    }

    //launch the vtk program, then hide the UI until it closes
    QProcess *VTK = new QProcess(parent);
    VTK->start(program, argv);
    VTK->waitForStarted();
    window()->hide();
    VTK->waitForFinished(-1);
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

void MainWindow::on_Source_File_Button_clicked()
{
    //get source file
    QString filepathS = fileDialog();
    QLineEdit* fileSource = findChild<QLineEdit*>("Source_File_Text");
    fileSource->setText(filepathS);

    MainWindow::userInfo info = getInfoFields(fileSource->text());

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
    saveFile->setText(newFileName);
}

void MainWindow::on_Target_File_Button_clicked()
{
    //get target files
    QStringList filepathPlist = fileDialogMulti();
    QTextEdit* fileTarget = findChild<QTextEdit*>("Target_File_Text");
    foreach (QString filepath, filepathPlist) {
        fileTarget->append(filepath);
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
    std::string sPath = "/tmp/test";

    //move from setup to config
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");

    /* Find the filepath selected for saving the report */
    QString savePath = MainWindow::findChild<QLineEdit*>("Save_Location")->text();

    int error = 0;

    /* Filepath of the selected source STL file */
    QString rFilePath = MainWindow::findChild<QLineEdit*>("Source_File_Text")->text();
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

    /* Get "home drive" location by parsing the filpath of the selected source STL
        file to 3 '/'s */
    rFilePath = rFilePath.mid(0, final_pos);
    //qInfo() << rFilePath;

    QString default_path = rFilePath;
    QString home = rFilePath;

    /* "Default save location" is the user's "home drive" location with 2 new folders added */
    default_path.append("/Comparisoft/Reports/");

    int ret;                    /* Button selected when user is presented with a pop-up window */
    bool cancel = false;        /* If the user has selected "cancel" when presented with a pop-up window */
    bool setup_default = false; /* Whether the file save path is the default path */
    bool root = false;          /* Whether the root directory of the default file path already exists */
    bool exists = false;        /* Whether the directory selected already exists */
    bool empty = false;         /* Whether the file save path is left empty */

    QString path;               /* The file save path as shown in the save location text field */

    /* Check whether the file save path as shown in the save location text field is the generated default path */
    if (savePath.contains(default_path)) {
        path = default_path;
        setup_default = true;
    }

    else {
        path = savePath;
    }

    /* Check whether the file save path is left empty */
    empty = savePath.trimmed().isEmpty();

    /* Windows environment detected */
    /* Check if the file save path is a directory that already exists */
    #if defined(_WIN32)
       if (_access_s(path.toStdString().c_str(), 0 ) == 0) {
            DWORD ftype = GetFileAttributesA(path.toStdString().c_str());
            exists = ftype & FILE_ATTRIBUTE_DIRECTORY;
        }

        else {
            exists = false;
        }

       /* Check if root folder of default directory exists */
       if (setup_default && !exists) {
           if (_access_s(default_path.mid(0, default_path.indexOf("/Reports")).toStdString().c_str(), 0 ) == 0) {
               DWORD ftype2 = GetFileAttributesA(default_path.mid(0, default_path.indexOf("/Reports")).toStdString().c_str());
               root = ftype2 & FILE_ATTRIBUTE_DIRECTORY;
            }

            else {
                root = false;
            }
       }

    /* Mac/Linux environment detected */
    /* Check if the file save path is a directory that already exists */
    #else
        if (opendir(path.toStdString().c_str())) {
            exists = true;
        }

        /* Check if root folder of default directory exists */
        if (setup_default && !exists) {
            if (opendir(default_path.mid(0, default_path.indexOf("/Reports")).toStdString().c_str())) {
                root = true;
            }
        }
    #endif

    QMessageBox msgBox;

    /* Case: if the directory selected does not exist, but is not an empty field */
    if (exists == false && !empty) {
        msgBox.setText("The directory specified does not exist.");
        if (setup_default) {
            msgBox.setInformativeText("Do you want to create a new Reports directory?");
        }
        else {
            msgBox.setInformativeText("Do you want to create the specified directory?");
        }
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        ret = msgBox.exec();

        bool err = false;

        switch (ret) {
          /* User selected Ok on pop-up window -> try and create directory */
          case QMessageBox::Ok:
                /* Default file path selected */
                if (setup_default && !root) {
                    /* Create directory "Comparisoft" */
                    #if defined(_WIN32)
                        error = _mkdir(home.append("/Comparisoft").toStdString().c_str());
                    #else
                        error = mkdir(home.append("/Comparisoft").toStdString().c_str(), 0777);
                    #endif
                }
                /* Custom non-existant file path selected */
                else if(!setup_default) {
                    /* Create new custom directory */
                    #if defined(_WIN32)
                        error = _mkdir(path.toStdString().c_str());
                    #else
                        error = mkdir(path.toStdString().c_str(), 0777);
                    #endif
                }

                /* Error has occurred */
                if (error != 0) {
                    QMessageBox msgBox2;
                    msgBox2.setText("An error occurred creating the directory.");
                    msgBox2.setInformativeText("Please select a different save location.");
                    msgBox2.setStandardButtons(QMessageBox::Ok);
                    msgBox2.setDefaultButton(QMessageBox::Ok);
                    msgBox2.exec();

                    qInfo( "Error occurred creating directory:");
                    perror ("The following error occurred");
                    if (setup_default) {
                        qDebug("Directory1: %s", home.toStdString().c_str());
                    }
                    else {
                        qDebug("Directory1: %s", path.toStdString().c_str());
                    }
                    cancel = true;
                    err = true;
                }

                /* Create "Reports" directory inside of "Comparisoft" directory
                    (if the default file path is selected and no error occurred creating the first directory) */
                if (setup_default && !err) {

                    //if root already existed, this needs to be added
                    if(root){
                        home.append("/Comparisoft");
                    }
                    #if defined(_WIN32)
                        error = _mkdir(home.append("/Reports").toStdString().c_str());
                    #else
                        error = mkdir(home.append("/Reports").toStdString().c_str(), 0777);
                    #endif

                    /* Error has occurred */
                    if (error != 0) {
                        QMessageBox msgBox2;
                        msgBox2.setText("An error occurred creating the directory.");
                        msgBox2.setInformativeText("Please select a different save location.");
                        msgBox2.setStandardButtons(QMessageBox::Ok);
                        msgBox2.setDefaultButton(QMessageBox::Ok);
                        msgBox2.exec();

                        qInfo( "Error occurred creating directory:");
                        perror ("The following error occurred");
                        if (setup_default) {
                            qDebug("Directory2: %s", home.toStdString().c_str());
                        }
                        else {
                            qDebug("Directory2: %s", path.toStdString().c_str());
                        }
                        cancel = true;
                        err = true;
                    }
                }
            break;
          /* User selected Cancel on pop-up window -> do not move on to configurations page */
          case QMessageBox::Cancel:
              cancel = true;
          default:
              cancel = true;
        }
    }

    /* File path not selected -> field is empty*/
    if (savePath.trimmed().isEmpty()) {
        /* Prompt user to select a directory */
        QMessageBox msgBox;
        msgBox.setText("Please select a save location.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        ret = msgBox.exec();
    }

    /* Only move on to configuration page if the save directory has been selected and no errors occurred */
    if (!savePath.trimmed().isEmpty() && !cancel) {
        view_holder->setCurrentIndex(1);
    }
}

void MainWindow::on_ReturnToMainPage_clicked()
{
    //Move from config to setup
    QStackedWidget* view_holder = findChild<QStackedWidget*>("View_Holder");
    view_holder->setCurrentIndex(0);
}

void MainWindow::on_Clear_Target_Files_clicked()
{
    //clear the target files
    QTextEdit* fileTarget = findChild<QTextEdit*>("Target_File_Text");
    fileTarget->clear();
}

void MainWindow::on_saveLocationButton_clicked()
{
    //browse for a save location
    QString fileSavePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly);
    QLineEdit* fileSave = findChild<QLineEdit*>("Save_Location");
    fileSave->setText(fileSavePath);
}
