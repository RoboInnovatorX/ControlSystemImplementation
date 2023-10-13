#ifndef DISCRETESYSTEM_H
#define DISCRETESYSTEM_H

#include <QString>
#include <QVector>
#include "ReadingWritingXml.h"

class DiscreteSystem
{
public:
    DiscreteSystem();

    bool Initialize(const QString& pol_b, const QString& pol_a);    // Function to store the given coefficients a and b in a string
    float CalculateStep(const QVector<float>& x, const QVector<float>& y);   // Function to calculate the output
    QVector<float> a;   // Coefficients a
    QVector<float> b;   // Coefficients b
};

#endif // DISCRETESYSTEM_H
