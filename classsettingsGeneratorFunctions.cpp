/*****************************************************************************
 * classsettingsGeneratorFunctions.cpp:
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
#include "classsettings.h"
#include "paraments.h"
#include "sharedFunctions.h"
#include <QMap>

#define CLASSSETTINGS_FOREACH_PROPERTIES(CONDITIONGROUP, CONDITIONPROPERTY, CODES) \
QString codes; \
if (!sortAllProperties()) \
{ \
    foreach (PropertiesGroup g, m_propertiesGroups) \
    { \
        if (g.enabled() && CONDITIONGROUP) \
        { \
            foreach (Property p, g.properties()) \
            { \
                if (p.enabled() && CONDITIONPROPERTY) \
                { \
                    codes += CODES; \
                } \
            } \
        } \
    } \
} \
else \
{ \
    QStringList l = propertiesName(); \
    foreach (QString name, l) \
    { \
        PropertiesGroup g = m_propertiesGroups[findGroupByPropertyName(name)]; \
        Property p = findProperty(name); \
        if (g.enabled() && CONDITIONGROUP && p.enabled() && CONDITIONPROPERTY) \
        { \
            codes += CODES; \
        } \
    } \
}

QString ClassSettings::generateCode(QString (*f)(Property, PropertiesGroup),
                                    bool conditionGroup,
                                    bool conditionProperty) const
{
    QString codes;
    if (!sortAllProperties())
    {
        foreach (PropertiesGroup g, m_propertiesGroups)
        {
            if (g.enabled() && conditionGroup)
            {
                foreach (Property p, g.properties())
                {
                    if (p.enabled() && conditionProperty)
                    {
                        codes += f(p, g);
                    }
                }
            }
        }
    }
    else
    {
        QStringList l = propertiesName();
        foreach (QString name, l)
        {
            PropertiesGroup g = m_propertiesGroups[findGroupByPropertyName(name)];
            Property p = findProperty(name);
            if (g.enabled() && conditionGroup && p.enabled() && conditionProperty)
            {
                codes += f(p, g);
            }
        }
    }
    return codes;
}

QString ClassSettings::generateEnumsDeclear() const
{
    QString enums("");
    foreach (EnumType e, m_enums)
    {
        if (e.enabled())
        {
            enums.append(e.declear() + "\n");
        }
    }
    return enums;
}

QString ClassSettings::generateQPropertyDeclear() const
{
    //QString qProperty("");
    CLASSSETTINGS_FOREACH_PROPERTIES(true, true,
                QString(CODESCHEME_Indent) + p.qPropertyString() + "\n");
    return codes;
}

QString ClassSettings::generateReadDeclear() const
{
    //QString readDeclear("");
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.read(),
                QString(CODESCHEME_Indent) + p.readDeclear() + "\n");
    return codes;
}

QString ClassSettings::generateResetDeclear() const
{
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.resetIsValid(),
                QString(CODESCHEME_Indent) + p.resetDeclear() + "\n");
    return codes;
}

QString ClassSettings::generateWriteDeclear() const
{
    //QString writeDeclear("");
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.needWrite(),
                QString(CODESCHEME_Indent) + p.writeDeclear() + "\n");
    return codes;
}

QString ClassSettings::generateSignalDeclear() const
{
    //QString signalDeclear("");
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.notify(),
                QString(CODESCHEME_Indent) + p.signalDeclear() + "\n");
    return codes;
}

QString ClassSettings::generateMemberVariableDeclear() const
{
    QString memberVars("");
    foreach (QString s, p_typeOrder)
    {
        QList<Property> listP = propertiesIsType(s);
        foreach (Property p, listP)
        {
            if (p.enabled())
            {
                memberVars.append(QString(CODESCHEME_Indent)
                                  + p.memberVariableDeclear() + "\n");
            }
        }
    }
    if (p_generatePreventReentrantCode)
    {
        CLASSSETTINGS_FOREACH_PROPERTIES(true, p.notify(),
                    QString(CODESCHEME_Indent) + p.preventReentrantVarDeclear() + "\n");
        memberVars += codes;
    }
    return memberVars;
}

QString ClassSettings::generateDocCommentPropertiesComment() const
{
    //QString docs("");
    CLASSSETTINGS_FOREACH_PROPERTIES(true, true,
                p.docComment(className()) + "\n");
    return codes;
}

QString ClassSettings::generateReadFunctionDefine() const
{
    //QString readFunctions("");
    CLASSSETTINGS_FOREACH_PROPERTIES(
                !g.readFunctionIsInline(), p.read(),
                p.readFunctionDefine(className(), false) + "\n");
    return codes;
}

QString ClassSettings::generateResetFunctionDefine() const
{
    CLASSSETTINGS_FOREACH_PROPERTIES(
                !g.resetFunctionIsInline(), p.resetIsValid(),
                p.resetFunctionDefine(className(), false) + "\n");
    return codes;
}

QString ClassSettings::generateWriteFunctionDefine() const
{
    //QString writeFunctions("");
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        bool emitSignal = g.writeFunctionEmitSignal()
                && ((p_typeInderitsInfomation == inherits_QObject)
                    || (p_typeInderitsInfomation == inherits_QWidget)
                    || (p_typeInderitsInfomation == inherits_QQuickItem)
                    || (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile));
        return p.writeFunctionDefine(
                    className(),
                    g.statementsStartWriteProperty(),
                    g.statementsMiddleWriteProperty(),
                    g.statementsAfterWriteProperty(),
                    emitSignal,
                    false,
                    generatePreventReentrantCode())
                + "\n";
    };
    CLASSSETTINGS_FOREACH_PROPERTIES(
                !g.writeFunctionIsInline(), p.needWrite(),
                f(p, g));
    return codes;
}

QString ClassSettings::generateInlineReadFunctionDefine() const
{
    //QString readFunctions("");
    CLASSSETTINGS_FOREACH_PROPERTIES(
                g.readFunctionIsInline(), p.read(),
                p.readFunctionDefine(className(), true) + "\n");
    return codes;
}

QString ClassSettings::generateInlineResetFunctionDefine() const
{
    //QString readFunctions("");
    CLASSSETTINGS_FOREACH_PROPERTIES(
                g.resetFunctionIsInline(), p.resetIsValid(),
                p.resetFunctionDefine(className(), true) + "\n");
    return codes;
}

QString ClassSettings::generateInlineWriteFunctionDefine() const
{
    //QString writeFunctions("");
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        bool emitSignal = g.writeFunctionEmitSignal()
                && ((p_typeInderitsInfomation == inherits_QObject)
                    || (p_typeInderitsInfomation == inherits_QWidget)
                    || (p_typeInderitsInfomation == inherits_QQuickItem)
                    || (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile));
        return p.writeFunctionDefine(
                    className(),
                    g.statementsStartWriteProperty(),
                    g.statementsMiddleWriteProperty(),
                    g.statementsAfterWriteProperty(),
                    emitSignal,
                    true,
                    generatePreventReentrantCode())
                + "\n";
    };
    CLASSSETTINGS_FOREACH_PROPERTIES(
                g.writeFunctionIsInline(), p.needWrite(),
                f(p, g));
    return codes;
}

QString ClassSettings::generateInlineFunctionsDefine() const
{
    QString s;
    /*if (p_readFunctionIsInline)
    {
        s += generateReadFunctionDefine();
    }
    if (p_writeFunctionIsInline)
    {
        s += generateWriteFunctionDefine();
    }*/
    s += generateInlineReadFunctionDefine();
    s += generateInlineWriteFunctionDefine();
    s += generateInlineResetFunctionDefine();
    return s;
}

QString ClassSettings::docCommentAssignmentOperator() const
{
    QString s;
    s = CODESCHEME_Doxygen_AssignmentOperator;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentClass() const
{
    QString s;
    s = CODESCHEME_Doxygen_Class;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentCopyConstructor() const
{
    QString s;
    s = CODESCHEME_Doxygen_CopyConstructor;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentDefaultConstructor() const
{
    QString s;
    if (p_typeInderitsInfomation == inherits_None)
    {
        s = CODESCHEME_Doxygen_DefaultConstructor_Inherits_None;
    }
    else if (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile)
    {
        s = CODESCHEME_Doxygen_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        s = CODESCHEME_Doxygen_DefaultConstructor_Inherits_QObject;
    }
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentDestructor() const
{
    QString s;
    if (p_typeInderitsInfomation == inherits_None)
    {
        s = CODESCHEME_Doxygen_Destructor_Inherits_None;
    }
    else if (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile)
    {
        s = CODESCHEME_Doxygen_Destructor_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        s = CODESCHEME_Doxygen_Destructor_Inherits_QObject;
    }
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentFileHeader(const QString &fileName,
                                            const QString &brief,
                                            const QString &detail) const
{
    QString s;
    s = CODESCHEME_Doxygen_FileHeader;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::headerFileDocCommentHeader() const
{
    QString str = docCommentFileHeader(headerFileName(),
                                       headerFileDocCommentHeaderBrief(),
                                       headerFileDocCommentHeaderDetail());
    return str;
}

QString ClassSettings::headerFileDocCommentHeaderBrief() const
{
    QString s;
    s = CODESCHEME_Doxygen_FileHeader_HeaderBrief;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::headerFileDocCommentHeaderDetail() const
{
    QString s;
    s = CODESCHEME_Doxygen_FileHeader_HeaderDetail;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::sourceFileDocCommentHeader() const
{
    QString str = docCommentFileHeader(sourceFileName(),
                                       sourceFileDocCommentHeaderBrief(),
                                       sourceFileDocCommentHeaderDetail());
    return str;
}

QString ClassSettings::sourceFileDocCommentHeaderBrief() const
{
    QString s;
    s = CODESCHEME_Doxygen_FileHeader_SourceBrief;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::sourceFileDocCommentHeaderDetail() const
{
    QString s;
    s = CODESCHEME_Doxygen_FileHeader_SourceDetail;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::argumentNameOfThisClass() const
{
    QString s;
    s = CODESCHEME_Class_ArgumentNameOfThisClass;
    return s;
}

QString ClassSettings::classDefine() const
{
    if (p_typeInderitsInfomation == inherits_None)
    {
        if (p_inherits.isEmpty())
        {
            QString s;
            s = CODESCHEME_Class_Define_Inherits_None;
            return s;
        }
        else
        {
            QString s;
            s = CODESCHEME_Class_Define_Inherits_NonQObjectClass;
            return s;
        }
    }
    else if (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile)
    {
        QString s;
        s = CODESCHEME_Class_Define_Inherits_QWidget_AssociateWithUiFile;
        return s;
    }
    else
    {
        QString s;
        s = CODESCHEME_Class_Define_Inherits_QObject;
        return s;
    }
}

QString ClassSettings::qojbectBasedParentArgumentName() const
{
    QString s;
    s = CODESCHEME_Class_QOjbectBasedParentArgumentName;
    return s;
}

QString ClassSettings::includeLocalHeaderFileStatement(const QString &fileName) const
{
    QString s;
    s = CODESCHEME_File_IncludeLocalHeaderFileStatement;
    return s;
}

QString ClassSettings::includeSystemHeaderFileStatement(const QString &fileName) const
{
    QString s;
    s = CODESCHEME_File_IncludeSystemHeaderFileStatement;
    return s;
}

QString ClassSettings::headerFileContent() const
{
    QString s;
    s = CODESCHEME_File_HeaderFileContent;
    s = replaceSepecialStringToPercent(s);
    return s;
}

QString ClassSettings::headerFileIncludeStatements() const
{
    QStringList listIncludeTypes;
    QString type;
    QString includes("");
    QString inheritsType = p_inherits;
    inheritsType = primaryType(inheritsType);
    if (!inheritsType.isEmpty())
    {
        if (inheritsType.startsWith("Q"))
        {
            listIncludeTypes.append(inheritsType);
        }
        else
        {
            includes = includeLocalHeaderFileStatement(inheritsType);
        }
    }
    foreach (type, p_typeOrder)
    {
        QStringList listAllTypes = allTypes(type);
        foreach (QString newType, listAllTypes)
        {
            if (!newType.isEmpty())
            {
                listIncludeTypes.append(newType);
            }
        }
    }
    listIncludeTypes.sort();
    listIncludeTypes.removeDuplicates();
    foreach (type, listIncludeTypes)
    {
        if (type.startsWith("Q"))
        {
            includes += includeSystemHeaderFileStatement(type);
        }
    }
    return includes;
}

QString ClassSettings::headerFileMarco() const
{
    QString s;
    s = CODESCHEME_File_HeaderFileMarco;
    return s;
}

QString ClassSettings::headerFileName() const
{
    QString s;
    s = CODESCHEME_File_HeaderFileName;
    return s;
}

QString ClassSettings::sourceFileAssignmentOperator() const
{
    QString define;
    if (p_typeInderitsInfomation == inherits_None)
    {
        QString memberInit("");
        foreach (QString s, p_typeOrder)
        {
            QList<Property> listP = propertiesIsType(s);
            foreach (Property p, listP)
            {
                if (p.enabled())
                {
                    memberInit.append(CODESCHEME_Class_Function_AssignmentOperator_AssignmentStatements);
                }
            }
        }
        define = docCommentAssignmentOperator()
                + CODESCHEME_Class_Function_AssignmentOperator;
        return define;
    }
    else
    {
        return QString("");
    }
}

QString ClassSettings::sourceFileContent() const
{
    QString c("");
    if (p_typeInderitsInfomation == inherits_None)
    {
        c = CODESCHEME_File_SourceFileContent_Inherits_None;
    }
    else if (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile)
    {
        c = CODESCHEME_File_SourceFileContent_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        c = CODESCHEME_File_SourceFileContent_Inherits_QObject;
    }
    c = replaceSepecialStringToPercent(c);
    return c;
}

QString ClassSettings::sourceFileCopyConstructor() const
{
    QString define;
    if (p_typeInderitsInfomation == inherits_None)
    {
        QString memberInit("");
        foreach (QString s, p_typeOrder)
        {
            QList<Property> listP = propertiesIsType(s);
            foreach (Property p, listP)
            {
                if (p.enabled())
                {
                    memberInit.append(CODESCHEME_Class_Function_CopyConstructor_MemberInitStatements);
                }
            }
        }
        {
            CLASSSETTINGS_FOREACH_PROPERTIES(
                        true, true,
                        CODESCHEME_Class_Function_CopyConstructor_PreventReentrantMemberInitStatements);
            memberInit.append(codes);
        }
        if (memberInit.startsWith(QString(",")))
        {
            memberInit.replace(0, 1, QString(" :"));
        }
        define = docCommentCopyConstructor()
                + CODESCHEME_Class_Function_CopyConstructor;
        return define;
    }
    else
    {
        return QString("");
    }
}

QString ClassSettings::sourceFileDefaultConstructor() const
{
    QString memberInit("");
    QString define;
    foreach (QString s, p_typeOrder)
    {
        QList<Property> listP = propertiesIsType(s);
        foreach (Property p, listP)
        {
            if (p.enabled()
                    && p.defaultValue().canConvert(QMetaType::QString)
                    && !p.defaultValue().toString().isEmpty())
            {
                memberInit.append(CODESCHEME_Class_Function_DefaultConstructor_MemberInitStatements);
            }
        }
    }
    {
        CLASSSETTINGS_FOREACH_PROPERTIES(
                    true, true,
                    CODESCHEME_Class_Function_DefaultConstructor_PreventReentrantMemberInitStatements);
        memberInit.append(codes);
    }
    if (p_typeInderitsInfomation == inherits_None)
    {
        if (memberInit.startsWith(QString(",")))
        {
            memberInit.replace(0, 1, QString(" :"));
        }
    }
    if (p_typeInderitsInfomation == inherits_None)
    {
        define = docCommentDefaultConstructor()
                + CODESCHEME_Class_Function_DefaultConstructor_Inherits_None;
    }
    else if (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile)
    {
        define = docCommentDefaultConstructor()
                + CODESCHEME_Class_Function_DefaultConstructor_Inherits_QObject;
    }
    else
    {
        define = docCommentDefaultConstructor()
                + CODESCHEME_Class_Function_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile;
    }
    return define;
}

QString ClassSettings::sourceFileDestructor() const
{
    QString define;
    if (p_typeInderitsInfomation == inherits_None)
    {
        define = docCommentDestructor()
                + CODESCHEME_Class_Function_Destructor_Inherits_None;
    }
    else if (p_typeInderitsInfomation == inherits_QWidget_AssociateWithUiFile)
    {
        define = docCommentDestructor()
                + CODESCHEME_Class_Function_Destructor_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        define = docCommentDestructor()
                + CODESCHEME_Class_Function_Destructor_Inherits_QObject;
    }
    return define;
}

QString ClassSettings::sourceFileName() const
{
    QString s;
    s = CODESCHEME_File_SourceFileName;
    return s;
}

