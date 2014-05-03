/*****************************************************************************
 * enumtype.cpp:
 *****************************************************************************
 * Authors: panuins <panuins@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GPLv2 or later as published by the Free Software
 * Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *****************************************************************************/
#include "enumtype.h"

EnumType::EnumType() :
    p_name(),
    p_prefix(),
    p_suffix(),
    p_vars(),
    p_firstValue(0),
    p_enabled(true)
{
}

EnumType::EnumType(const QString &name) :
    p_name(name),
    p_prefix(),
    p_suffix(),
    p_vars(),
    p_firstValue(0),
    p_enabled(true)
{
}

EnumType::EnumType(const EnumType &var) :
    p_name(var.p_name),
    p_prefix(var.p_prefix),
    p_suffix(var.p_suffix),
    p_vars(var.p_vars),
    p_firstValue(var.p_firstValue),
    p_enabled(var.p_enabled)
{
}

EnumType::~EnumType()
{
}

QStringList EnumType::varList() const
{
    QStringList list;
    foreach (QString str, p_vars)
    {
        list.append(p_prefix + str + p_suffix);
    }
    return list;
}

QString EnumType::declear() const
{
    QStringList list(varList());
    QString d("    enum %1\n"
              "    {\n"
              "%2"
              "    };\n");
    QString dvs("        %1 = %2,\n");
    int i = 1;
    {
        dvs = dvs.arg(list.at(0)).arg(p_firstValue);
    }
    for (; i < list.size(); i++)
    {
        QString v = QString("        %1,\n").arg(list.at(i));
        dvs.append(v);
    }
    d = d.arg(p_name).arg(dvs);
    return d;
}

QStringList EnumType::parseEnumDefinesName(const QString &var)
{
    //QList<EnumType> enumList;
    /*QStringList nameList;
    QStringList defineList = var.split(QString(" enum "));
    foreach (QString eNumDefine, defineList)
    {
        QString name = eNumDefine;
    }*/
    return QStringList();
}
