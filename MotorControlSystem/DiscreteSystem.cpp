#include "DiscreteSystem.h"


DiscreteSystem::DiscreteSystem()
{

}

bool DiscreteSystem::Initialize(const QString &pol_b, const QString &pol_a)
{
    bool found=1;

    a = XmlGetVector(pol_a,&found);  // Store the coefficients a
    b = XmlGetVector(pol_b,&found);  // Store the coefficients b
    return found;
}

float DiscreteSystem::CalculateStep(const QVector<float> &x, const QVector<float> &y)
{
    float output = 0;
    for (int i = 0; i < b.size(); i++)
    {
        output += x[i] * b[i];
    }

    for (int i = 1; i < a.size(); i++)
    {
        output -= y[i] * a[i];
    }

    output /= a[0];

    return output;
}
