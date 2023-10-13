#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <cmath>
#include <DiscreteSystem.h>
#include <SignalData.h>
#include <QMessageBox>
#include <QDialog>
#include <QDesktopServices>
#include <QUrl>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_qParamsButton_clicked(); //Function to obtain initial parameters from a file

    void on_qTorqueButton_clicked(); //Function to select the input file

    void on_qOutputButton_clicked(); // Function to select the output file

    void on_qCalculateButton_clicked(); // Function to calculate all variables and save

    void on_qOpenButton_clicked(); // Function to open the output file

    void OnTimerFunction(); // Timer interrupt function


    void on_PauseBox_clicked(bool checked);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timer;   //Timer
    QString inputFileName;  //Name of Input File
    QString outputFileName; //Name of Output File
    QFile inputFile;    //Input File
    QFile outputFile;   //Output File

    SignalData torque_Nm,force_N, speed_m_s, position_m; // Variables to study

    float speed_rpm, speed_kmh, angular_speed_ms, power_W, current_A; // Intermediate variable to study
    float wheel_diameter_m, wheel_radius_m, friction_coeff_,mass_Kg, reduction_ratio, voltage_V, time_constant_s; // All Given parameters

    DiscreteSystem Force_to_speed_SI, Speed_to_pos_SI;   //Transfer function to calculate

    bool input_valid = false, output_valid = false, params_valid = false; // Flags to check the requirments

};
#endif // MAINWINDOW_H
