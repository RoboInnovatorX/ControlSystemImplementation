#include <QtXml>
#include <QTextStream>
#include "ReadingWritingXml.h"


// Function for creating XML tag
QString XmlCreateTag(const QString& xml_tag,bool is_start_tag)
{

    QString ret;

    if(is_start_tag){
        ret = "<" + xml_tag + ">";
    }

    else{
        ret = "</" + xml_tag + ">";
    }

    return ret;
}

// Function for getting string
QString XmlGetStr(const QString& xml_str,const QString& xml_tag,bool* found)
{

    QString ret;

    QString tag_open = XmlCreateTag(xml_tag, true);
    QString tag_close = XmlCreateTag(xml_tag, false);

    int iStart = xml_str.indexOf(tag_open);
    int iEnd = xml_str.indexOf(tag_close);

    if((iStart<0)||(iEnd<0)){
        *found = false;
        return ret = "";
    }
    else{
        *found = true;
        return ret = xml_str.mid(iStart+tag_open.size(),iEnd-(iStart+tag_open.size()));
    }
}

// Function for getting string
int XmlGetInt(const QString& xml_str,const QString& xml_tag,bool* found)
{
    int ret;
    QString num=XmlGetStr(xml_str,xml_tag,found);
    ret=num.toInt();

    return ret;

}

// Function for Getting float
float XmlGetFloat(const QString& xml_str,const QString& xml_tag,bool* found)
{
    float ret;
    QString num=XmlGetStr(xml_str,xml_tag,found);
    ret=num.toFloat();

    return ret;
}

// Function for Getting vector
QVector<float> XmlGetVector(const QString& xml,bool* found)
{
    QString num=xml;
    num=num.trimmed();  // Remove whitespace
    if ((*found==true)&&(num.startsWith("["))&&(num.endsWith("]")))
    {
        num=num.mid(1,num.length()-2);
        QStringList num_list = num.split(",");

        float lista=num_list.size();

        QVector<float> reales((int)lista);

        for (int i=0;i<lista;i++)
        {
            reales[i]=num_list[i].toFloat();
        }
        return reales;
    }
    else
    {
        QVector<float> reales(1);
        reales[0]=0;
        *found=false;
        return reales;
    }

}
