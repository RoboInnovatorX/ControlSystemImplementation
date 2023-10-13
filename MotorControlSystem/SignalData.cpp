#include "SignalData.h"

SignalData::SignalData()
{

}

void SignalData::initialize(int maxDataLength)
{
    data.resize(maxDataLength); // Resize the data vector to the specified maximum length
}

void SignalData::shift()
{
    for (int i = data.size() - 1; i > 0; i--)
    {
        data[i] = data[i - 1]; // Shift the values by one position
    }
}

void SignalData::setActualValue(float newValue)
{
    data[0] = newValue; // Set the first element of the data vector to the new value
}

const QVector<float> &SignalData::getData()
{
    return data; // Return a reference to the data vector
}

float SignalData::getActualValue()
{
    return data[0]; // Return the first element of the data vector
}
