/*
 * Functions can be automatically added by right clicking elements in the UI editer and selecting slots.
 * This page should only be edited manually when removing a function or changing its name.
 * */
#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    struct userInfo {
        QString client;
        QString patient;
        QString fileDescription;
        QString filePath;
    };

private slots:
    void on_RunVTK_clicked();

    void on_Source_File_Button_clicked();

    void on_Target_File_Button_clicked();

    QString fileDialog();

    QStringList fileDialogMulti();

    void on_Config_Button_clicked();

    void on_ReturnToMainPage_clicked();

    void on_Clear_Target_Files_clicked();

    void on_saveLocationButton_clicked();

private:
    Ui::MainWindow *ui;
};

// MAINWINDOW_H
