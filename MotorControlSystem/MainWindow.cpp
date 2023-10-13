#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimerFunction()));   // Set up the timer signal

    //Connecting all the slots to the button
    QObject::connect(ui->ParamsButton, &QPushButton::clicked, this, &MainWindow::on_qParamsButton_clicked);
    QObject::connect(ui->TorqueButton, &QPushButton::clicked, this, &MainWindow::on_qTorqueButton_clicked);
    QObject::connect(ui->OutputButton, &QPushButton::clicked, this, &MainWindow::on_qOutputButton_clicked);
    QObject::connect(ui->CalculateButton, &QPushButton::clicked, this, &MainWindow::on_qCalculateButton_clicked);
    QObject::connect(ui->OpenButton, &QPushButton::clicked, this, &MainWindow::on_qOpenButton_clicked);
    QObject::connect(ui->PauseBox, &QCheckBox::clicked, this, &MainWindow::on_PauseBox_clicked);

    Force_to_speed_SI.Initialize("[200,-200]", "[3]"); // Initialize coeffiecients for force to speed transformation
    Speed_to_pos_SI.Initialize("[200,-200]", "[3]"); // Initialize coeffiecients for speed to position transformation

    torque_Nm.initialize(2); // Define maximum number of torque data
    force_N.initialize(2); // Define Maximum number of force data to store
    speed_m_s.initialize(2); // Define Maximum number of speed data to store
    position_m.initialize(2); // Define Maximum number of position data to store
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_qParamsButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "TextEditor-Open File", tr("Text files (*.txt);;XML files (*.xml)"));    // Open file dialog to select a file

    if (!fileName.isEmpty())    // If a valid file name is selected
    {
        QFile fileParams(fileName); // Define the file
        fileParams.open(QIODevice::ReadOnly);   // Open the file for reading
        QString params_xml = fileParams.readAll();    // Read the entire file
        fileParams.close(); // Close the file

        // Booleans to check if parameters are found in the file
        bool found_diam = true, found_mass = true, found_friction = true, found_reduction = true, found_voltage = true, found_tm = true;

        wheel_diameter_m = XmlGetFloat(params_xml, "WheelDiam_mm", &found_diam) / 1000;
        mass_Kg = XmlGetFloat(params_xml, "Mass_Kg", &found_mass);
        friction_coeff_ = XmlGetFloat(params_xml, "Friction_B_N__m_s", &found_friction);
        reduction_ratio = XmlGetFloat(params_xml, "Reduction", &found_reduction);
        voltage_V= XmlGetFloat(params_xml, "Voltage_V", &found_voltage);
        time_constant_s = XmlGetFloat(params_xml, "Tm_ms", &found_tm);

        // If all parameters are found:
        if (found_diam && found_mass && found_friction && found_reduction && found_voltage && found_tm)
        {
            ui->ParamsLabel->setText("XML file added");
            ui->ParamsLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
            params_valid = true; // Set the flag to indicate that the parameter file and parameters are valid
            QMessageBox::information(this, "Message", "Valid parameters");
        }
        else
        {
            ui->ParamsLabel->setText("Missing parameters");
            params_valid = false; // Error
        }
    }
    else
    {
        ui->ParamsLabel->setText("No file selected");
        params_valid = false; // Error
    }
}


void MainWindow::on_qTorqueButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "TextEditor-Open File", tr("Text files (*.txt);;XML files (*.xml)"));    // Open file dialog to select a file

    if (!fileName.isEmpty())    // If the file name is not empty
    {

        ui->label->setText("Torque data added");
        ui->label->setStyleSheet("QLabel { background-color : green; color : white; }");
        inputFileName = fileName;    // Save the file name

        input_valid = true;    // Set the flag to indicate that the input file is valid
        inputFile.setFileName(inputFileName);  // Set the file name
        inputFile.open(QIODevice::ReadOnly);
        QMessageBox::information(this, "Message", "Valid input sample file");
    }
    else
    {
        ui->label->setText("No file selected");
        input_valid = false;    // Error
    }
}


void MainWindow::on_qOutputButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "TextEditor-Open File", tr("Text files (*.txt);;XML files (*.xml)"));    // Open file dialog to select a file

    if (!fileName.isEmpty())
    {
        ui->InsertOutLabel->setText("File Added");
        ui->InsertOutLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
        outputFileName = fileName;   // Save the output file name
        output_valid = true;
        outputFile.setFileName(outputFileName);    // Set the output file
        outputFile.open(QIODevice::WriteOnly);  // Open the output file and close it again to clear its contents
        outputFile.close();
        QMessageBox::information(this, "Message", "Ready to save data to the output file");
    }
    else
    {
        ui->InsertOutLabel->setText("No file selected");
        output_valid= false; // Error
    }
}


void MainWindow::on_qCalculateButton_clicked()
{
    // If the calclate button has been clicked and the files are selected correctly, start  the timer
    if (params_valid && output_valid && input_valid)
    {
        timer.start(100);   // Set a timer interval of 100ms
        ui->CalculateLabel->setText("Calculating");
        ui->CalculateLabel->setStyleSheet("QLabel { background-color : Orange; color : white; }");
    }
    else
    {
        QMessageBox::information(this, "Message", "Upload all input file!");
    }
}


void MainWindow::on_qOpenButton_clicked()
{
    // Path of the text file.
    QString filePath = "C:/Users/shofi/OneDrive/Desktop/Project/MotorControlSystem/output.txt";

    // Convert the file path to a QUrl object
    QUrl fileUrl = QUrl::fromLocalFile(filePath);

    // Open the text file with the default text editor (e.g., Notepad on Windows)
    QDesktopServices::openUrl(fileUrl);
}

void MainWindow::OnTimerFunction()
{
    outputFile.open(QIODevice::Append); // Open the output file to append lines
    // Shift all signals one step older
    torque_Nm.shift();
    force_N.shift();
    speed_m_s.shift();
    position_m.shift();

    QString lineIn = inputFile.readLine();    // Read the input file line by line
    torque_Nm.setActualValue(lineIn.toFloat()); // Store the new torque data

    force_N.setActualValue((torque_Nm.getActualValue()*reduction_ratio)/wheel_diameter_m); // Calculate force
    speed_m_s.setActualValue(Force_to_speed_SI.CalculateStep(force_N.getData(),speed_m_s.getData())); // Calculate speed in m/s
    angular_speed_ms = speed_m_s.getActualValue()/wheel_diameter_m; //Calculate angular velocity
    speed_rpm=(angular_speed_ms/(2*3.1416))*60*reduction_ratio; // Calculate motor rpm
    speed_kmh= speed_m_s.getActualValue()*3.6;// Calcualate speed in kmh
    position_m.setActualValue(Speed_to_pos_SI.CalculateStep(speed_m_s.getData(),position_m.getData())); // Calculate the position
    power_W = torque_Nm.getActualValue()*reduction_ratio*angular_speed_ms; // Calculate Power
    current_A = power_W/voltage_V; // Calcualte Voltage

    // Write all the data into a QString
    QString line = XmlCreateTag("Force_N", 1) + QString::number(force_N.getActualValue()) + XmlCreateTag("Force_N", 0);
    line = line + "  " + XmlCreateTag("Speed_rpm", 1) + QString::number(speed_rpm) + XmlCreateTag("Speed_rpm", 0);
    line = line + "  " + XmlCreateTag("Speed_kmh", 1) + QString::number(speed_kmh) + XmlCreateTag("Speed_kmh", 0);
    line = line + "  " + XmlCreateTag("Pos_m", 1) + QString::number(position_m.getActualValue()) + XmlCreateTag("pos_m", 0);
    line = line + "  " + XmlCreateTag("Power_W", 1) + QString::number(power_W) + XmlCreateTag("Pot_W", 0);
    line = line + "  " + XmlCreateTag("Current_A", 1) + QString::number(current_A) + XmlCreateTag("I_A", 0);

    outputFile.write(line.toLatin1() + "\n");    // Write the QString to the output file

    outputFile.close(); // Close the output file
}


void MainWindow::on_PauseBox_clicked(bool checked)
{
    if(checked)
    {
        timer.stop();
        ui->PauseLabel->setText("Paused");
        ui->PauseLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
        ui->CalculateButton->setAutoDefault(false);
        ui->CalculateLabel->setText("Start again");
    }
    if(!checked)
    {
        ui->PauseLabel->setText("Realesed");
        ui->PauseLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString filePath = "C:/Users/shofi/OneDrive/Desktop/Project/MotorControlSystem/output.txt";
    // Open the file in write mode
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // Truncate the file, effectively deleting its contents
        file.resize(0);

        // Close the file after truncating its contents
        file.close();
    }
    else
    {
        // Handle error if the file cannot be opened or truncated
        qDebug() << "Error opening or truncating the file:" << file.errorString();
    }

}

