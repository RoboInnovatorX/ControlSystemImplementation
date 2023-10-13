#ifndef READWRITEXML_H
#define READWRITEXML_H

#include <QString>

class ReadWriteXml
{
public:
    ReadWriteXml();
    QString WriteXml(const QString& Root_tag, const QString& Tg1, int Vl1,const QString& Tg2, int Vl2, const QString& Tg3,int Vl3, const QString& Tg4, int Vl4);
    QString XmlCreateTag (const QString& xml_tag, bool is_start_tag);
    QString XmlGetStr(const QString& xml_str, const QString& xml_tag);
    int XmlGetInt(const QString& xml_str, const QString& xml_tag);
    float XmlGetFloat(const QString& xml_str, const QString& xml_tag);
    QVector<float> XmlGetVector(const QString& xml_str, const QString& xml_tag);
    QVector<float> XmlGetVectorRequired(const QString& xml,bool* found);

};

#endif // READWRITEXML_H
