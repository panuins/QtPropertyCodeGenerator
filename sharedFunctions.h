/*****************************************************************************
 * sharedFunctions.h:
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
#ifndef SHAREDFUNCTIONS_H
#define SHAREDFUNCTIONS_H

#include "paraments.h"
#include <QChar>
#include <QDateTime>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <iostream>

inline QStringList allTypes(const QString &type)
{
    if (type.indexOf(QChar(':')) < 0)
    {
        QRegExp regExp("[ *<>]");
        QStringList list = type.split(regExp);
        list.sort();
        list.removeDuplicates();
        if (list.length() > 0)
        {
            if (list.at(0).isEmpty())
            {
                list.removeAt(0);
            }
        }
        return list;
    }
    else
    {
        return QStringList();
    }
}

inline QString currentDateTimeString()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString(CODESCHEME_DateTimeFormat);
}

inline QString indentCode(const QString &source, int indentCount)
{
    QStringList list = source.split(QChar('\n'));
    QString indented("");
    foreach (QString code, list)
    {
        int i = 0;
        for (; i < indentCount; i++)
        {
            indented += QString(CODESCHEME_Indent);
        }
        indented += code;
        indented += "\n";
    }
    return indented;
}

inline QString inlineNotation(bool b)
{
    if (b)
    {
        return QString(CODESCHEME_InlineNotation);
    }
    else
    {
        return QString("");
    }
}

inline bool nameIsCIndentifier(const QString &name)
{
    QRegExp exp(QString("[0-9a-zA-Z_]*"));
    if (!exp.exactMatch(name))
    {
        std::cerr << "nameIsCIndentifier: class name "
                  << name.toStdString() << " is not a valid c++ identifier."
                  << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

inline QString primaryType(const QString &type)
{
    QString ret = type;
    if (ret.contains(QChar('<')))
    {
        ret = ret.left(ret.indexOf(QChar('<')));
    }
    if (ret.contains(QChar(' ')))
    {
        ret = ret.left(ret.indexOf(QChar(' ')));
    }
    if (ret.contains(QChar('*')))
    {
        ret = ret.left(ret.indexOf(QChar('*')));
    }
    return ret;
}

inline QString replaceFisrtLetterToLower(const QString &str)
{
    if (!str.isEmpty())
    {
        QString dest = str;
        QString firstLetter = QString(dest.at(0).toLower());
        dest.replace(0, 1, firstLetter);
        return dest;
    }
    else
    {
        return str;
    }
}

inline QString replaceFisrtLetterToUpper(const QString &str)
{
    if (!str.isEmpty())
    {
        QString dest = str;
        QString firstLetter = QString(dest.at(0).toUpper());
        dest.replace(0, 1, firstLetter);
        return dest;
    }
    else
    {
        return str;
    }
}

inline QString replacePercentToSepecialString(const QString &str)
{
    QString s = str;
    s.replace(QString("%"), QString("_____PercentNotation_____"));
    return s;
}

inline QString replaceSepecialStringToPercent(const QString &str)
{
    QString s = str;
    s.replace(QString("_____PercentNotation_____"), QString("%"));
    return s;
}

inline bool stringToBool(const QString &string)
{
    if (string == "true")
    {
        return true;
    }
    else
    {
        return false;
    }
}


#endif // SHAREDFUNCTIONS_H
