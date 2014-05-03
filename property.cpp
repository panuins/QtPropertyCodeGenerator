/*****************************************************************************
 * property.cpp:
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
#include "property.h"
#include <QStringList>
#define SaveSeperator "\t"

bool Property::operator==(const Property &p) const
{
    return (m_d->p_name == p.m_d->p_name)
            && (m_d->p_docName == p.m_d->p_docName)
            && (m_d->p_docDetail == p.m_d->p_docDetail)
            && (m_d->p_typeStringName == p.m_d->p_typeStringName)
            && (m_d->p_type == p.m_d->p_type)
            && (m_d->p_revision == p.m_d->p_revision)
            && (m_d->p_member == p.m_d->p_member)
            && (m_d->p_read == p.m_d->p_read)
            && (m_d->p_write == p.m_d->p_write)
            && (m_d->p_reset == p.m_d->p_reset)
            && (m_d->p_notify == p.m_d->p_notify)
            && (m_d->p_designable == p.m_d->p_designable)
            && (m_d->p_scriptable == p.m_d->p_scriptable)
            && (m_d->p_stored == p.m_d->p_stored)
            && (m_d->p_user == p.m_d->p_user)
            && (m_d->p_constant == p.m_d->p_constant)
            && (m_d->p_final == p.m_d->p_final)
            && (m_d->p_enabled == p.m_d->p_enabled)
            && (m_d->p_defaultValue == p.m_d->p_defaultValue);
}

bool Property::operator!=(const Property &p) const
{
    return !((m_d->p_name == p.m_d->p_name)
             && (m_d->p_docName == p.m_d->p_docName)
             && (m_d->p_docDetail == p.m_d->p_docDetail)
             && (m_d->p_typeStringName == p.m_d->p_typeStringName)
             && (m_d->p_type == p.m_d->p_type)
             && (m_d->p_revision == p.m_d->p_revision)
             && (m_d->p_member == p.m_d->p_member)
             && (m_d->p_read == p.m_d->p_read)
             && (m_d->p_write == p.m_d->p_write)
             && (m_d->p_reset == p.m_d->p_reset)
             && (m_d->p_notify == p.m_d->p_notify)
             && (m_d->p_designable == p.m_d->p_designable)
             && (m_d->p_scriptable == p.m_d->p_scriptable)
             && (m_d->p_stored == p.m_d->p_stored)
             && (m_d->p_user == p.m_d->p_user)
             && (m_d->p_constant == p.m_d->p_constant)
             && (m_d->p_final == p.m_d->p_final)
             && (m_d->p_enabled == p.m_d->p_enabled)
             && (m_d->p_defaultValue == p.m_d->p_defaultValue));
}

QString Property::typePrefix() const
{
    std::string strTypeName = m_d->p_type.toStdString();
    const char *typeName = strTypeName.c_str();
    QVariant::Type typeId = QVariant::nameToType(typeName);
    QString s = m_d->p_typeStringName.isEmpty()
            ? m_d->p_type : m_d->p_typeStringName;
    if (typeId == QVariant::Bool)
    {
        s = QString("b");
    }
    else if (typeId == QVariant::Double)
    {
        if (m_d->p_typeStringName.isEmpty())
        {
            s = QString("d");
        }
        else if (m_d->p_typeStringName == QString("float"))
        {
            s = QString("f");
        }
        else
        {
            s = replaceFisrtLetterToLower(s);
        }
    }
    else if (typeId == QVariant::Int)
    {
        if (m_d->p_typeStringName.isEmpty())
        {
            s = QString("n");
        }
        else if ((m_d->p_typeStringName == QString("char"))
                 || (m_d->p_typeStringName == QString("qint8")))
        {
            s = QString("c");
        }
        else if ((m_d->p_typeStringName == QString("unsigned char"))
                 || (m_d->p_typeStringName == QString("quint8")))
        {
            s = QString("uc");
        }
        else if ((m_d->p_typeStringName == QString("short"))
                 || (m_d->p_typeStringName == QString("qint16")))
        {
            s = QString("st");
        }
        else if ((m_d->p_typeStringName == QString("quint16")))
        {
            s = QString("w");
        }
        else if ((m_d->p_typeStringName == QString("qint32")))
        {
            s = QString("l");
        }
        else if ((m_d->p_typeStringName == QString("quint32")))
        {
            s = QString("dw");
        }
        else if ((m_d->p_typeStringName == QString("qint64")))
        {
            s = QString("nl");
        }
        else if ((m_d->p_typeStringName == QString("quint64")))
        {
            s = QString("unl");
        }
    }
    else
    {
        s = replaceFisrtLetterToLower(s);
    }
    return s;
}

QString Property::toString() const
{
    QString str;
    str = QString("%1"SaveSeperator
                  "%2"SaveSeperator
                  "%3"SaveSeperator
                  "%4"SaveSeperator
                  "%5"SaveSeperator)
            .arg(m_d->p_type)
            .arg(m_d->p_name)
            .arg(m_d->p_typeStringName)
            .arg(m_d->p_docName)
            .arg(m_d->p_docDetail);
    str += boolToStr(m_d->p_member);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_read);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_write);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_reset);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_notify);
    str += QString(SaveSeperator);
    str += QString::number(m_d->p_revision);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_designable);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_scriptable);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_stored);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_user);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_constant);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_final);
    str += QString(SaveSeperator);
    str += boolToStr(m_d->p_enabled);
    str += QString(SaveSeperator);
    str += m_d->p_defaultValue.toString();
    return str;
}

/*bool Property::writeToSql(QSqlQuery &query)
{
    query.addBindValue(m_d->p_name);
    query.addBindValue(m_d->p_type);
    query.addBindValue(m_d->p_typeStringName);
    query.addBindValue(m_d->p_docName);
    query.addBindValue(m_d->p_docDetail);
    query.addBindValue(m_d->p_member);
    query.addBindValue(m_d->p_read);
    query.addBindValue(m_d->p_write);
    query.addBindValue(m_d->p_reset);
    query.addBindValue(m_d->p_notify);
    query.addBindValue(m_d->p_revision);
    query.addBindValue(m_d->p_designable);
    query.addBindValue(m_d->p_scriptable);
    query.addBindValue(m_d->p_stored);
    query.addBindValue(m_d->p_user);
    query.addBindValue(m_d->p_constant);
    query.addBindValue(m_d->p_final);
    query.addBindValue(m_d->p_enabled);
    return query.exec();
}*/

QString Property::qPropertyString() const
{
    QString str;

    str = QString("Q_PROPERTY(%1 %2")
            .arg(realTypeName())
            .arg(replaceFisrtLetterToLower(m_d->p_name));
#define AddBoolProperty(MEMBER, MARCO, QTNAME) \
    if (m_d->p_##MEMBER != PropertyDefault##MARCO) \
    { \
    str += QString(" ") + #QTNAME + QString(" ") \
    + ((m_d->p_##MEMBER) ? "true" : "false"); \
}
    AddBoolProperty(member, Member, MEMBER);
    if (m_d->p_member)
    {
        str += QString(" MEMBER ") + memberVariableName();
    }
    if (m_d->p_read)
    {
        str += QString(" READ ") + readFunctionName();
    }
    if (m_d->p_write)
    {
        str += QString(" WRITE ") + writeFunctionName();
    }
    AddBoolProperty(reset, Reset, RESET);
    if (m_d->p_notify)
    {
        str += QString(" NOTIFY ") + signalName();
    }
    if (m_d->p_revision != PropertyDefaultRevision)
    {
        str += QString(" REVISION %1").arg(m_d->p_revision);
    }
    AddBoolProperty(designable, Designable, DESIGNABLE);
    AddBoolProperty(scriptable, Scriptable, SCRIPTABLE);
    AddBoolProperty(stored, Stored, STORED);
    AddBoolProperty(user, User, USER);
    if (m_d->p_constant != PropertyDefaultConstant)
    {
        str += QString(" CONSTANT");
    }
    if (m_d->p_final != PropertyDefaultFinal)
    {
        str += QString(" FINAL");
    }
    str += QString(")\n");
    return str;
}

QString Property::readFunctionDefine(const QString &className,
                                     bool isInline) const
{
    QString s("");
    if (!m_d->p_docName.isEmpty())
    {
        s += QString("/**\n"
                     " * @brief 返回属性%1的值\n"
                     " * @return 属性%2的值\n"
                     " * @details 返回属性%3的值\n"
                     " */\n")
                .arg(m_d->p_docName)
                .arg(m_d->p_docName)
                .arg(m_d->p_docName);
    }
    if (isInline)
    {
        s += "inline ";
    }
    s += QString("%1 %2::%3() const\n"
                 "{\n"
                 "    return %4;\n"
                 "}\n")
            .arg(realTypeName())
            .arg(className)
            .arg(readFunctionName())
            .arg(memberVariableName());
    return s;
}

QString Property::writeFunctionDefine(const QString &className,
                                      const QString &strBeforSetValue,
                                      const QString &strBetweenSetValueAndEmit,
                                      const QString &strAfterEmit,
                                      bool emitSignal,
                                      bool isInline) const
{
    QString s("");
    if (!m_d->p_docName.isEmpty())
    {
        s += QString("/**\n"
                     " * @brief 设置属性%1的值\n"
                     " * @param %2 %3\n"
                     " * @details 设置属性%4的值")
                .arg(m_d->p_docName)
                .arg(writeFunctionArgumentName())
                .arg(m_d->p_docName)
                .arg(m_d->p_docName);
        if (!m_d->p_docDetail.isEmpty())
        {
            s += QString("，") + m_d->p_docDetail;
        }
        if (emitSignal && m_d->p_notify)
        {
            s += "，并发射信号" + signalName();
        }
        s += "。\n"
                " */\n";
    }
    if (isInline)
    {
        s += "inline ";
    }
    s += QString("void %1::%2(const %3 &%4)\n"
                 "{\n"
                 "%5"
                 "    %6 = %7;\n"
                 "%8")
            .arg(className)
            .arg(writeFunctionName())
            .arg(realTypeName())
            .arg(writeFunctionArgumentName())
            .arg(strBeforSetValue)
            .arg(memberVariableName())
            .arg(writeFunctionArgumentName())
            .arg(strBetweenSetValueAndEmit);
    if (emitSignal && m_d->p_notify)
    {
        s += QString("    emit %1();\n").arg(signalName());
    }
    s += strAfterEmit;
    s += QString("}\n");
    return s;
}

Property Property::fromString(const QString &str)
{
    QStringList list = str.split(QChar(SaveSeperator[0]));
    Property p(list.at(1),
               list.at(0),
               list.at(2));
    int i = 3;
    p.setDocName(list.at(i));
    i++;
    p.setDocDetail(list.at(i));
    i++;
    p.setMember(strTobool(list.at(i)));
    i++;
    p.setRead(strTobool(list.at(i)));
    i++;
    p.setWrite(strTobool(list.at(i)));
    i++;
    p.setReset(strTobool(list.at(i)));
    i++;
    p.setNotify(strTobool(list.at(i)));
    i++;
    p.setRevision(list.at(i).toInt());
    i++;
    p.setDesignable(strTobool(list.at(i)));
    i++;
    p.setScriptable(strTobool(list.at(i)));
    i++;
    p.setStored(strTobool(list.at(i)));
    i++;
    p.setUser(strTobool(list.at(i)));
    i++;
    p.setConstant(strTobool(list.at(i)));
    i++;
    p.setFinal(strTobool(list.at(i)));
    i++;
    p.setEnabled(strTobool(list.at(i)));
    return p;
}
