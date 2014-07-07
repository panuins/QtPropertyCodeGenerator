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
#include "paraments.h"
#include "property.h"
#include <QStringList>

bool Property::operator==(const Property &p) const
{
    if (m_d == p.m_d)
    {
        return true;
    }
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
    if (m_d == p.m_d)
    {
        return false;
    }
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
        if (m_d->p_typeStringName.isEmpty()
                || (m_d->p_typeStringName == QString("int")))
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
        else
        {
            s = replaceFisrtLetterToLower(s);
        }
    }
    else if (typeId == QVariant::List)
    {
        s = "qList";
    }
    else if (typeId == QVariant::Map)
    {
        s = "qMap";
    }
    else if (typeId == QVariant::Hash)
    {
        s = "qHash";
    }
    else
    {
        if (s.endsWith("*"))
        {
            s.chop(1);
        }
        if (s.endsWith(" "))
        {
            s.chop(1);
        }
        int seat = s.indexOf(QChar('<'));
        if (seat > 0)
        {
            s = s.left(seat);
        }
        s = replaceFisrtLetterToLower(s);
    }
    return s;
}

QString Property::doxygenCommentMemberVariable() const
{
    QString s;
    if (!docName().isEmpty())
    {
        s = CODESCHEME_Doxygen_MemberVariable;
        s = replacePercentToSepecialString(s);
    }
    else
    {
        s = QString("");
    }
    return s;
}

QString Property::doxygenCommentPreventReentrantMemberVariable() const
{
    QString s;
    if (!docName().isEmpty())
    {
        s = CODESCHEME_Doxygen_PreventReentrantMemberVariable;
        s = replacePercentToSepecialString(s);
    }
    else
    {
        s = QString("");
    }
    return s;
}

QString Property::doxygenCommentReadFunction() const
{
    QString s;
    s = CODESCHEME_Doxygen_ReadFunction;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::doxygenCommentResetFunction() const
{
    QString s;
    s = CODESCHEME_Doxygen_ResetFunction;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::doxygenCommentWriteFunction(bool emitSignal) const
{
    QString s;
    QString customDetail(""), signalDetail("");
    if (!docDetail().isEmpty())
    {
        customDetail = QString(CODESCHEME_DocComment_Comma) + docDetail();
    }
    if (emitSignal && notify())
    {
        signalDetail = QString(CODESCHEME_DocComment_Comma)
                + CODESCHEME_DocComment_WriteFunction_SignalDetail;
    }
    s = CODESCHEME_Doxygen_WriteFunction;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::qPropertyString() const
{
    QString str;
    str = QString("Q_PROPERTY(%1 %2")
            .arg(realTypeName())
            .arg(replaceFisrtLetterToLower(m_d->p_name));
#define AddBoolProperty(MEMBER, MARCO, QTNAME) \
    if (MEMBER() != PropertyDefault##MARCO) \
    { \
    str += QString(" ") + #QTNAME + QString(" ") \
    + ((MEMBER()) ? "true" : "false"); \
}
    if (member())
    {
        str += QString(" MEMBER ") + memberVariableName();
    }
    if (read())
    {
        str += QString(" READ ") + readFunctionName();
    }
    if (write())
    {
        str += QString(" WRITE ") + writeFunctionName();
    }
    if (reset() != PropertyDefaultReset)
    {
        str += QString(" RESET ") + ((reset()) ? "true" : "false");
    }
    //AddBoolProperty(reset, Reset, RESET);
    if (notify())
    {
        str += QString(" NOTIFY ") + signalName();
    }
    if (revision() != PropertyDefaultRevision)
    {
        str += QString(" REVISION %1").arg(revision());
    }
    AddBoolProperty(designable, Designable, DESIGNABLE);
    AddBoolProperty(scriptable, Scriptable, SCRIPTABLE);
    AddBoolProperty(stored, Stored, STORED);
    AddBoolProperty(user, User, USER);
    if (constant() != PropertyDefaultConstant)
    {
        str += QString(" CONSTANT");
    }
    if (final() != PropertyDefaultFinal)
    {
        str += QString(" FINAL");
    }
    str += QString(")");
    return str;
}

QString Property::readFunctionDefine(const QString &className,
                                     bool isInline) const
{
    QString s("");
    if (!m_d->p_docName.isEmpty())
    {
        s += doxygenCommentReadFunction();
    }
    if (isInline)
    {
        s += "inline ";
    }
    s += CODESCHEME_Property_ReadFunctionDefine;
    return s;
}

QString Property::resetFunctionDefine(const QString &className,
                                      bool isInline) const
{
    QString s("");
    if (!m_d->p_docName.isEmpty())
    {
        s += doxygenCommentResetFunction();
    }
    if (isInline)
    {
        s += "inline ";
    }
    s += CODESCHEME_Property_ResetFunctionDefine;
    return s;
}

QString Property::writeFunctionDefine(const QString &className,
                                      const QString &strBeforSetValue,
                                      const QString &strBetweenSetValueAndEmit,
                                      const QString &strAfterEmit,
                                      bool emitSignal,
                                      bool isInline,
                                      bool preventReentrant) const
{
    QString s("");
    QString emitSignalStatement("");
    if (emitSignal && notify())
    {
        emitSignalStatement = CODESCHEME_Property_WriteFunction_EmitSignalStatement;
    }
    if (!m_d->p_docName.isEmpty())
    {
        s += doxygenCommentWriteFunction(emitSignal);
    }
    if (isInline)
    {
        s += "inline ";
    }
    if (preventReentrant)
    {
        s += CODESCHEME_Property_WriteFunctionDefine_PreventReentrant;
    }
    else
    {
        s += CODESCHEME_Property_WriteFunctionDefine;
    }
    return s;
}

QString Property::doxygenComment(const QString &className) const
{
    QString s;
    QString detail(""),rwOnly("");
    bool readOnly = (!m_d->p_write) && m_d->p_read && (!m_d->p_member);
    if (readOnly)
    {
        rwOnly = QString(CODESCHEME_DocComment_ReadOnlyProperty);
    }
    bool writeOnly = (!m_d->p_read) && m_d->p_write && (!m_d->p_member);
    if (writeOnly)
    {
        rwOnly = QString(CODESCHEME_DocComment_WriteOnlyProperty);
    }
    if ((!rwOnly.isEmpty()) && (!docDetail().isEmpty()))
    {
        detail += QString("%1" CODESCHEME_DocComment_Comma "%2" CODESCHEME_DocComment_Period)
                .arg(rwOnly).arg(docDetail());
    }
    else if ((rwOnly.isEmpty()) && (!docDetail().isEmpty()))
    {
        detail += QString("%1" CODESCHEME_DocComment_Period).arg(docDetail());
    }
    else if ((!rwOnly.isEmpty()) && (docDetail().isEmpty()))
    {
        detail += QString("%1" CODESCHEME_DocComment_Period).arg(rwOnly);
    }
    else if ((rwOnly.isEmpty()) && (docDetail().isEmpty()))
    {
        detail = QString("");
    }
    s = CODESCHEME_Doxygen_Property;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::writeFunctionArgumentName() const
{
    QString s;
    s = CODESCHEME_Property_WriteFunctionArgumentName;
    return s;
}

QString Property::readFunctionName() const
{
    QString s;
    s = CODESCHEME_Property_ReadFunctionName;
    return s;
}

QString Property::resetFunctionName() const
{
    QString s;
    s = CODESCHEME_Property_ResetFunctionName;
    return s;
}

QString Property::writeFunctionName() const
{
    QString s;
    s = CODESCHEME_Property_WriteFunctionName;
    return s;
}

QString Property::signalName() const
{
    QString s;
    s = CODESCHEME_Property_SignalName;
    return s;
}

QString Property::memberVariableName() const
{
    QString s;
    s = CODESCHEME_Property_MemberVariableName;
    return s;
}

QString Property::preventReentrantVarName() const
{
    QString s;
    s = CODESCHEME_Property_PreventReentrantVarName;
    return s;
}

QString Property::readDeclear() const
{
    QString s;
    s = CODESCHEME_Property_ReadDeclear;
    return s;
}

QString Property::resetDeclear() const
{
    QString s;
    s = CODESCHEME_Property_ResetDeclear;
    return s;
}

QString Property::writeDeclear() const
{
    QString s;
    s = CODESCHEME_Property_WriteDeclear;
    return s;
}

QString Property::signalDeclear() const
{
    QString s;
    s = CODESCHEME_Property_SignalDeclear;
    return s;
}

QString Property::memberVariableDeclear() const
{
    QString s;
    s = CODESCHEME_Property_MemberVariableDeclear;
    return s;
}

QString Property::preventReentrantVarDeclear() const
{
    QString s;
    s = CODESCHEME_Property_PreventReentrantVarDeclear;
    return s;
}

/*QString Property::preventReentrantVarInitialStatement() const
{
    QString s;
    s = CODESCHEME_Property_PreventReentrantVarInitialStatement;
    return s;
}

QString Property::initialToDefaultValueStatement() const
{
    QString s;
    s = CODESCHEME_Property_InitialToDefaultValueStatement;
    return s;
}

QString Property::initialToSpecifyValueStatement(const QString &str) const
{
    QString s;
    s = CODESCHEME_Property_InitialToSpecifyValueStatement;
    return s;
}*/
