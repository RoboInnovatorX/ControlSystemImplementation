#ifndef READINGWRITINGXML_H
#define READINGWRITINGXML_H

#endif // READINGWRITINGXML_H

#include <QString>
#include <QVector>
#include <QList>

QString XmlCreateTag(const QString& xml_tag,bool is_start_tag); // Creating XML Tag
QString XmlGetStr(const QString& xml_str,const QString& xml_tag,bool* found); // Getting String from XML
int XmlGetInt(const QString& xml_str,const QString& xml_tag,bool* found); // Getting int from XML
float XmlGetFloat(const QString& xml_str,const QString& xml_tag,bool* found); // Getting float froam XML
QVector<float> XmlGetVector(const QString& xml,bool* found); // Getting Vector from XML
