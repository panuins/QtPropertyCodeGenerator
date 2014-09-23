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
            && (m_d->p_docBrief == p.m_d->p_docBrief)
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
             && (m_d->p_docBrief == p.m_d->p_docBrief)
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

QString Property::docComment(const QString &className) const
{
    QString s;
    s = CODESCHEME_Doxygen_Property;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::docCommentBrief() const
{
    QString s("");
    if (!docBrief().isEmpty())
    {
        s = CODESCHEME_Doxygen_Property_Brief;
    }
    return s;
}

QString Property::docCommentDetail() const
{
    QString detail(""),rwOnly("");
    bool readOnly = (!m_d->p_write) && m_d->p_read && (!m_d->p_member);
    if (readOnly)
    {
        rwOnly = CODESCHEME_DocComment_ReadOnlyProperty;
    }
    bool writeOnly = (!m_d->p_read) && m_d->p_write && (!m_d->p_member);
    if (writeOnly)
    {
        rwOnly = CODESCHEME_DocComment_WriteOnlyProperty;
    }

    if ((!rwOnly.isEmpty()) && (!docDetail().isEmpty()))
    {
        detail += QString("%1" CODESCHEME_DocComment_Comma "%2" CODESCHEME_DocComment_Period)
                .arg(rwOnly).arg(docDetail());
    }
    else if ((rwOnly.isEmpty()) && (!docDetail().isEmpty()))
    {
        if (docDetail().at(0).isLetter())
        {
            detail += QString("%1" CODESCHEME_DocComment_Period)
                    .arg(replaceFisrtLetterToUpper(docDetail()));
        }
        else
        {
            detail += QString("%1" CODESCHEME_DocComment_Period).arg(docDetail());
        }
    }
    else if ((!rwOnly.isEmpty()) && (docDetail().isEmpty()))
    {
        detail += QString("%1" CODESCHEME_DocComment_Period).arg(rwOnly);
    }
    else if ((rwOnly.isEmpty()) && (docDetail().isEmpty()))
    {
        detail = QString("");
    }
    return detail;
}

QString Property::docCommentMemberVariable() const
{
    if (docName().isEmpty())
    {
        return QString("");
    }
    QString s;
    s = CODESCHEME_Doxygen_MemberVariable;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::docCommentPreventReentrantMemberVariable() const
{
    if (docName().isEmpty())
    {
        return QString("");
    }
    QString s;
    s = CODESCHEME_Doxygen_PreventReentrantMemberVariable;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::docCommentReadFunction(const QString &className,
                                         bool isInline) const
{
    if (docName().isEmpty())
    {
        return QString("");
    }
    QString s;
    s = CODESCHEME_Doxygen_ReadFunction;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::docCommentResetFunction(const QString &className,
                                          bool isInline) const
{
    if (docName().isEmpty())
    {
        return QString("");
    }
    QString s;
    s = CODESCHEME_Doxygen_ResetFunction;
    s = replacePercentToSepecialString(s);
    return s;
}

QString Property::docCommentWriteFunction(const QString &className,
        bool emitSignal,
        bool isInline,
        bool preventReentrant) const
{
    if (docName().isEmpty())
    {
        return QString("");
    }
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
                                     const QString &strStatements,
                                     bool isInline) const
{
    QString s("");
    s = docCommentReadFunction(className, isInline)
            + CODESCHEME_Property_ReadFunctionDefine;
    return s;
}

QString Property::resetFunctionDefine(const QString &className,
                                      const QString &strBeforeReset,
                                      const QString &strAfterReset,
                                      bool isInline) const
{
    QString s("");
    s = docCommentResetFunction(className, isInline)
            + CODESCHEME_Property_ResetFunctionDefine;
    return s;
}

QString Property::writeFunctionDefine(const QString &className,
                                      const QString &strBeforeSetValue,
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
    if (preventReentrant)
    {
        s = docCommentWriteFunction(className,
                                    emitSignal,
                                    isInline,
                                    preventReentrant)
                + CODESCHEME_Property_WriteFunctionDefine_PreventReentrant;
    }
    else
    {
        s = docCommentWriteFunction(className,
                                    emitSignal,
                                    isInline,
                                    preventReentrant)
                + CODESCHEME_Property_WriteFunctionDefine;
    }
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

QDomElement Property::toXMLNode(QDomDocument *doc) const
{
    QDomElement element = doc->createElement("Property");
#define SETATTRIBUTE(NAME) element.setAttribute(#NAME, NAME())
#define SETATTRIBUTE_BOOL(NAME) element.setAttribute(#NAME, (NAME() ? QString("true") : QString("false")))
    SETATTRIBUTE(name);
    SETATTRIBUTE(docName);
    SETATTRIBUTE(docBrief);
    SETATTRIBUTE(docDetail);
    SETATTRIBUTE(type);
    SETATTRIBUTE(typeStringName);
    element.setAttribute("defaultValue", defaultValue().toString());
    SETATTRIBUTE(revision);
    SETATTRIBUTE_BOOL(member);
    SETATTRIBUTE_BOOL(read);
    SETATTRIBUTE_BOOL(write);
    SETATTRIBUTE_BOOL(reset);
    SETATTRIBUTE_BOOL(notify);
    SETATTRIBUTE_BOOL(enabled);
    SETATTRIBUTE_BOOL(designable);
    SETATTRIBUTE_BOOL(scriptable);
    SETATTRIBUTE_BOOL(stored);
    SETATTRIBUTE_BOOL(user);
    SETATTRIBUTE_BOOL(constant);
    SETATTRIBUTE_BOOL(final);
    return element;
}

Property Property::fromXMLNode(const QDomElement &element)
{
    if (element.tagName() == "Property")
    {
        Property p;
        p.setName(element.attribute("name"));
        p.setDocName(element.attribute("docName"));
        p.setDocBrief(element.attribute("docBrief"));
        p.setDocDetail(element.attribute("docDetail"));
        p.setType(element.attribute("type"));
        p.setTypeStringName(element.attribute("typeStringName"));
        p.setDefaultValue(QVariant(element.attribute("defaultValue")));
        p.setRevision(element.attribute("revision").toInt());
        p.setMember(stringToBool(element.attribute("member")));
        p.setRead(stringToBool(element.attribute("read")));
        p.setWrite(stringToBool(element.attribute("write")));
        p.setReset(stringToBool(element.attribute("reset")));
        p.setNotify(stringToBool(element.attribute("notify")));
        p.setEnabled(stringToBool(element.attribute("enabled")));
        p.setDesignable(stringToBool(element.attribute("designable")));
        p.setScriptable(stringToBool(element.attribute("scriptable")));
        p.setStored(stringToBool(element.attribute("stored")));
        p.setUser(stringToBool(element.attribute("user")));
        p.setConstant(stringToBool(element.attribute("constant")));
        p.setFinal(stringToBool(element.attribute("final")));
        return p;
    }
    else
    {
        return Property();
    }
}
