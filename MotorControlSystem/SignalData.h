#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QVector>
#include "ReadingWritingXml.h"

class SignalData
{
public:
    SignalData();
    void initialize(int maxDataLength);  //Function to set the maximum length of the allowed data
    void shift();   //Function for shifting the vector
    void setActualValue(float newValue);   //Function to set the current value
    const QVector<float>& getData();    //Function to retrieve all the stored data
    float getActualValue(); //Function to get the most recent data

private:
    QVector<float> data; //Stored data
    int maxDataLength; //Maximum number of data points stored

};

#endif // SIGNALDATA_H
