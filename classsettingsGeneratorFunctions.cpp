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
#include <iostream>

#define CLASSSETTINGS_FOREACH_PROPERTIES(CONDITIONGROUP, CONDITIONPROPERTY, CODES) \
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
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Property_Pos == CODESCHEME_DocComment_Property_InDeclare)
        {
            return CODESCHEME_Format_Declare(p.qPropertyString(), p.docComment(className()));
        }
        else
        {
            return addIndentAndNewLineIfNotEmpty(p.qPropertyString());
        }
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(true, true, f(p, g));
    return codes;
}

QString ClassSettings::generateReadDeclear() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
        {
            return CODESCHEME_Format_Declare(p.readDeclear(),
                                             p.docCommentReadFunction(className(), g.readFunctionIsInline()));
        }
        else
        {
            return addIndentAndNewLineIfNotEmpty(p.readDeclear());
        }
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.read(), f(p, g));
    return codes;
}

QString ClassSettings::generateResetDeclear() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
        {
            return CODESCHEME_Format_Declare(
                        p.resetDeclear(),
                        p.docCommentResetFunction(className(), g.resetFunctionIsInline()));
        }
        else
        {
            return addIndentAndNewLineIfNotEmpty(p.resetDeclear());
        }
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.resetIsValid(), f(p, g));
    return codes;
}

QString ClassSettings::generateWriteDeclear() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
        {
            return CODESCHEME_Format_Declare(
                        p.writeDeclear(),
                        p.docCommentWriteFunction(className(),
                                                  g.writeFunctionEmitSignal(),
                                                  g.writeFunctionIsInline(),
                                                  generatePreventReentrantCode()));
        }
        else
        {
            return addIndentAndNewLineIfNotEmpty(p.writeDeclear());
        }
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.needWrite(), f(p, g));
    return codes;
}

QString ClassSettings::generateSignalDeclear() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        return addIndentAndNewLineIfNotEmpty(p.signalDeclear());
        /*if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
        {
            return CODESCHEME_Format_Declare(
                        p.signalDeclear(),
                        QString());
        }
        else
        {
            return addIndentAndNewLineIfNotEmpty(p.signalDeclear());
        }*/
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(true, p.notify(), f(p, g));
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
                if (CODESCHEME_DocCommentContent_MemberVariable_Pos == CODESCHEME_DocComment_MemberVariable_InDeclare)
                {
                    memberVars.append(CODESCHEME_Format_Declare(p.memberVariableDeclear(),
                                                                p.docCommentMemberVariable(className())));
                }
                else
                {
                    memberVars.append(addIndentAndNewLineIfNotEmpty(p.memberVariableDeclear()));
                }
            }
        }
    }
    if (p_generatePreventReentrantCode)
    {
        auto f = [this](const Property &p, const PropertiesGroup &g)
        {
            if (CODESCHEME_DocCommentContent_MemberVariable_Pos == CODESCHEME_DocComment_MemberVariable_InDeclare)
            {
                return CODESCHEME_Format_Declare(p.preventReentrantVarDeclear(),
                                                 p.docCommentPreventReentrantMemberVariable(className()));
            }
            else
            {
                return addIndentAndNewLineIfNotEmpty(p.preventReentrantVarDeclear());
            }
        };
        QString codes;
        CLASSSETTINGS_FOREACH_PROPERTIES(true, p.notify(), f(p, g));
        memberVars += codes;
    }
    return memberVars;
}

QString ClassSettings::generateDetachedDocCommentFunctions() const
{
    if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_Detached)
    {
        QString codes;
        codes += docCommentDefaultConstructor();
        if (typeInheritsInfomation() == inherits_None)
        {
            codes += docCommentCopyConstructor();
        }
        codes += docCommentDestructor();
        if (typeInheritsInfomation() == inherits_None)
        {
            codes += docCommentAssignmentOperator();
        }
        CLASSSETTINGS_FOREACH_PROPERTIES(true, true,
                    addNewLineIfNotEmpty(p.docCommentReadFunction(className(), g.readFunctionIsInline())));
        CLASSSETTINGS_FOREACH_PROPERTIES(true, p.resetIsValid(),
                    addNewLineIfNotEmpty(p.docCommentResetFunction(className(), g.resetFunctionIsInline())));
        CLASSSETTINGS_FOREACH_PROPERTIES(true, p.needWrite(),
                    addNewLineIfNotEmpty(p.docCommentWriteFunction(className(),
                                                                   g.writeFunctionEmitSignal(),
                                                                   g.writeFunctionIsInline(),
                                                                   generatePreventReentrantCode())));
        return codes;
    }
    else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
    {
        return QString();
    }
    else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
    {
        if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_Any)
        {
            return QString();
        }
        else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InHeaderFileOnly)
        {
            QString codes;
            codes += docCommentDefaultConstructor();
            if (typeInheritsInfomation() == inherits_None)
            {
                codes += docCommentCopyConstructor();
            }
            codes += docCommentDestructor();
            if (typeInheritsInfomation() == inherits_None)
            {
                codes += docCommentAssignmentOperator();
            }
            CLASSSETTINGS_FOREACH_PROPERTIES(!g.readFunctionIsInline(), true,
                        addNewLineIfNotEmpty(p.docCommentReadFunction(className(), g.readFunctionIsInline())));
            CLASSSETTINGS_FOREACH_PROPERTIES(!g.resetFunctionIsInline(), p.resetIsValid(),
                        addNewLineIfNotEmpty(p.docCommentResetFunction(className(), g.resetFunctionIsInline())));
            CLASSSETTINGS_FOREACH_PROPERTIES(!g.writeFunctionIsInline(), p.needWrite(),
                        addNewLineIfNotEmpty(p.docCommentWriteFunction(className(),
                                                                       g.writeFunctionEmitSignal(),
                                                                       g.writeFunctionIsInline(),
                                                                       generatePreventReentrantCode())));
            return codes;
        }
        else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InSourceFileOnly)
        {
            QString codes;
            CLASSSETTINGS_FOREACH_PROPERTIES(g.readFunctionIsInline(), true,
                        addNewLineIfNotEmpty(p.docCommentReadFunction(className(), g.readFunctionIsInline())));
            CLASSSETTINGS_FOREACH_PROPERTIES(g.resetFunctionIsInline(), p.resetIsValid(),
                        addNewLineIfNotEmpty(p.docCommentResetFunction(className(), g.resetFunctionIsInline())));
            CLASSSETTINGS_FOREACH_PROPERTIES(g.writeFunctionIsInline(), p.needWrite(),
                        addNewLineIfNotEmpty(p.docCommentWriteFunction(className(),
                                                                       g.writeFunctionEmitSignal(),
                                                                       g.writeFunctionIsInline(),
                                                                       generatePreventReentrantCode())));
            return codes;
        }
    }
}

QString ClassSettings::generateDetachedDocCommentMemberVariable() const
{
    if (CODESCHEME_DocCommentContent_MemberVariable_Pos == CODESCHEME_DocComment_MemberVariable_InDeclare)
    {
        return QString();
    }
    else
    {
        QString codes;
        CLASSSETTINGS_FOREACH_PROPERTIES(true, true,
                    addNewLineIfNotEmpty(p.docCommentMemberVariable(className())));
        CLASSSETTINGS_FOREACH_PROPERTIES(true, true,
                    addNewLineIfNotEmpty(p.docCommentPreventReentrantMemberVariable(className())));
        return codes;
    }
}

QString ClassSettings::generateDetachedDocCommentProperties() const
{
    if (CODESCHEME_DocCommentContent_Property_Pos == CODESCHEME_DocComment_Property_InDeclare)
    {
        return QString();
    }
    else
    {
        QString codes;
        CLASSSETTINGS_FOREACH_PROPERTIES(true, true,
                    addNewLineIfNotEmpty(p.docComment(className())));
        return codes;
    }
}

QString ClassSettings::generateReadFunctionDefine() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos != CODESCHEME_DocComment_Function_InHeaderFileOnly)
            {
                return CODESCHEME_Format_Define(
                            p.readFunctionDefine(className(),
                                                 g.statementsInReadProperty(),
                                                 false),
                            p.docCommentReadFunction(className(), g.readFunctionIsInline()));
            }
        }
        return addNewLineIfNotEmpty(p.readFunctionDefine(
                                        className(),
                                        g.statementsInReadProperty(),
                                        false));
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(!g.readFunctionIsInline(), p.read(), f(p, g));
    return codes;
}

QString ClassSettings::generateResetFunctionDefine() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos != CODESCHEME_DocComment_Function_InHeaderFileOnly)
            {
                return CODESCHEME_Format_Define(
                            p.resetFunctionDefine(className(),
                                                  g.statementsAfterResetProperty(),
                                                  g.statementsBeforeResetProperty(),
                                                  false),
                            p.docCommentResetFunction(className(), g.resetFunctionIsInline()));
            }
        }
        return addNewLineIfNotEmpty(p.resetFunctionDefine(
                                        className(),
                                        g.statementsAfterResetProperty(),
                                        g.statementsBeforeResetProperty(),
                                        false));
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(!g.resetFunctionIsInline(), p.resetIsValid(), f(p, g));
    return codes;
}

QString ClassSettings::generateWriteFunctionDefine() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        bool emitSignal = g.writeFunctionEmitSignal()
                && ((typeInheritsInfomation() == inherits_QObject)
                    || (typeInheritsInfomation() == inherits_QWidget)
                    || (typeInheritsInfomation() == inherits_QQuickItem)
                    || (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile));
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos != CODESCHEME_DocComment_Function_InHeaderFileOnly)
            {
                return CODESCHEME_Format_Define(
                            p.writeFunctionDefine(className(),
                                                  g.statementsBeforeWriteProperty(),
                                                  g.statementsMiddleWriteProperty(),
                                                  g.statementsAfterWriteProperty(),
                                                  emitSignal,
                                                  false,
                                                  generatePreventReentrantCode()),
                            p.docCommentWriteFunction(className(),
                                                      g.writeFunctionEmitSignal(),
                                                      g.writeFunctionIsInline(),
                                                      generatePreventReentrantCode()));
            }
        }
        return addNewLineIfNotEmpty(p.writeFunctionDefine(
                                        className(),
                                        g.statementsBeforeWriteProperty(),
                                        g.statementsMiddleWriteProperty(),
                                        g.statementsAfterWriteProperty(),
                                        emitSignal,
                                        false,
                                        generatePreventReentrantCode()));
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(!g.writeFunctionIsInline(), p.needWrite(), f(p, g));
    return codes;
}

QString ClassSettings::generateFunctionsDefine() const
{
    QString s;
    s += sourceFileDefaultConstructor() + "\n";
    if (typeInheritsInfomation() == inherits_None)
    {
        s += sourceFileCopyConstructor() + "\n";
    }
    s += sourceFileDestructor() + "\n";
    if (typeInheritsInfomation() == inherits_None)
    {
        s += sourceFileAssignmentOperator() + "\n";
    }
    s += generateReadFunctionDefine();
    s += generateWriteFunctionDefine();
    s += generateResetFunctionDefine();
    return s;
}

QString ClassSettings::generateInlineReadFunctionDefine() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos != CODESCHEME_DocComment_Function_InSourceFileOnly)
            {
                return CODESCHEME_Format_Define(
                            p.readFunctionDefine(className(),
                                                 g.statementsInReadProperty(),
                                                 true),
                            p.docCommentReadFunction(className(), g.readFunctionIsInline()));
            }
        }
        return addNewLineIfNotEmpty(p.readFunctionDefine(
                                        className(),
                                        g.statementsInReadProperty(),
                                        true));
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(g.readFunctionIsInline(), p.read(), f(p, g));
    return codes;
}

QString ClassSettings::generateInlineResetFunctionDefine() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos != CODESCHEME_DocComment_Function_InSourceFileOnly)
            {
                return CODESCHEME_Format_Define(
                            p.resetFunctionDefine(className(),
                                                  g.statementsAfterResetProperty(),
                                                  g.statementsBeforeResetProperty(),
                                                  true),
                            p.docCommentResetFunction(className(), g.resetFunctionIsInline()));
            }
        }
        return addNewLineIfNotEmpty(p.resetFunctionDefine(
                                        className(),
                                        g.statementsAfterResetProperty(),
                                        g.statementsBeforeResetProperty(),
                                        true));
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(g.resetFunctionIsInline(), p.resetIsValid(), f(p, g));
    return codes;
}

QString ClassSettings::generateInlineWriteFunctionDefine() const
{
    auto f = [this](const Property &p, const PropertiesGroup &g)
    {
        bool emitSignal = g.writeFunctionEmitSignal()
                && ((typeInheritsInfomation() == inherits_QObject)
                    || (typeInheritsInfomation() == inherits_QWidget)
                    || (typeInheritsInfomation() == inherits_QQuickItem)
                    || (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile));
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos != CODESCHEME_DocComment_Function_InSourceFileOnly)
            {
                return CODESCHEME_Format_Define(
                            p.writeFunctionDefine(className(),
                                                  g.statementsBeforeWriteProperty(),
                                                  g.statementsMiddleWriteProperty(),
                                                  g.statementsAfterWriteProperty(),
                                                  emitSignal,
                                                  true,
                                                  generatePreventReentrantCode()),
                            p.docCommentWriteFunction(className(),
                                                      g.writeFunctionEmitSignal(),
                                                      g.writeFunctionIsInline(),
                                                      generatePreventReentrantCode()));
            }
        }
        return addNewLineIfNotEmpty(p.writeFunctionDefine(
                                        className(),
                                        g.statementsBeforeWriteProperty(),
                                        g.statementsMiddleWriteProperty(),
                                        g.statementsAfterWriteProperty(),
                                        emitSignal,
                                        true,
                                        generatePreventReentrantCode()));
    };
    QString codes;
    CLASSSETTINGS_FOREACH_PROPERTIES(g.writeFunctionIsInline(), p.needWrite(), f(p, g));
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
    s = CODESCHEME_DocCommentContent_AssignmentOperator;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentClass() const
{
    QString s;
    s = CODESCHEME_DocCommentContent_Class;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentCopyConstructor() const
{
    QString s;
    s = CODESCHEME_DocCommentContent_CopyConstructor;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentDefaultConstructor() const
{
    QString s;
    if (typeInheritsInfomation() == inherits_None)
    {
        s = CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_None;
    }
    else if (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile)
    {
        s = CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        s = CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_QObject;
    }
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentDestructor() const
{
    QString s;
    if (typeInheritsInfomation() == inherits_None)
    {
        s = CODESCHEME_DocCommentContent_Destructor_Inherits_None;
    }
    else if (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile)
    {
        s = CODESCHEME_DocCommentContent_Destructor_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        s = CODESCHEME_DocCommentContent_Destructor_Inherits_QObject;
    }
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::docCommentFileHeader(const QString &fileName,
                                            const QString &brief,
                                            const QString &detail) const
{
    QString s;
    s = CODESCHEME_DocCommentContent_FileHeader;
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
    s = CODESCHEME_DocCommentContent_FileHeader_HeaderBrief;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::headerFileDocCommentHeaderDetail() const
{
    QString s;
    s = CODESCHEME_DocCommentContent_FileHeader_HeaderDetail;
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
    s = CODESCHEME_DocCommentContent_FileHeader_SourceBrief;
    s = replacePercentToSepecialString(s);
    return s;
}

QString ClassSettings::sourceFileDocCommentHeaderDetail() const
{
    QString s;
    s = CODESCHEME_DocCommentContent_FileHeader_SourceDetail;
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
    if (typeInheritsInfomation() == inherits_None)
    {
        if (inherits().isEmpty())
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
    else if (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile)
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
    s = replaceSpecialStringToPercent(s);
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
    if (typeInheritsInfomation() == inherits_None)
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
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_Detached)
        {
        }
        else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
        {
        }
        else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_Any)
            {
                define += docCommentAssignmentOperator();
            }
            else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InHeaderFileOnly)
            {
            }
            else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InSourceFileOnly)
            {
                define += docCommentAssignmentOperator();
            }
        }
        define += CODESCHEME_Class_Function_AssignmentOperator;
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
    if (typeInheritsInfomation() == inherits_None)
    {
        c = CODESCHEME_File_SourceFileContent_Inherits_None;
    }
    else if (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile)
    {
        c = CODESCHEME_File_SourceFileContent_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        c = CODESCHEME_File_SourceFileContent_Inherits_QObject;
    }
    c = replaceSpecialStringToPercent(c);
    return c;
}

QString ClassSettings::sourceFileCopyConstructor() const
{
    QString define;
    if (typeInheritsInfomation() == inherits_None)
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
            QString codes;
            CLASSSETTINGS_FOREACH_PROPERTIES(
                        true, true,
                        CODESCHEME_Class_Function_CopyConstructor_PreventReentrantMemberInitStatements);
            memberInit.append(codes);
        }
        if (memberInit.startsWith(QString(",")))
        {
            memberInit.replace(0, 1, QString(" :"));
        }
        if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_Detached)
        {
        }
        else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
        {
        }
        else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
        {
            if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_Any)
            {
                define += docCommentCopyConstructor();
            }
            else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InHeaderFileOnly)
            {
            }
            else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InSourceFileOnly)
            {
                define += docCommentCopyConstructor();
            }
        }
        define += CODESCHEME_Class_Function_CopyConstructor;
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
        QString codes;
        CLASSSETTINGS_FOREACH_PROPERTIES(
                    true, true,
                    CODESCHEME_Class_Function_DefaultConstructor_PreventReentrantMemberInitStatements);
        memberInit.append(codes);
    }
    if (typeInheritsInfomation() == inherits_None)
    {
        if (memberInit.startsWith(QString(",")))
        {
            memberInit.replace(0, 1, QString(" :"));
        }
    }
    if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_Detached)
    {
        //std::cout << "ClassSettings::sourceFileDefaultConstructor: CODESCHEME_DocComment_Function_Detached" << std::endl;
    }
    else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
    {
        //std::cout << "ClassSettings::sourceFileDefaultConstructor: CODESCHEME_DocComment_Function_InDeclare" << std::endl;
    }
    else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
    {
        if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_Any)
        {
            define += docCommentDefaultConstructor();
            //std::cout << "ClassSettings::sourceFileDefaultConstructor: CODESCHEME_DocComment_Function_Any" << std::endl;
        }
        else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InHeaderFileOnly)
        {
            //std::cout << "ClassSettings::sourceFileDefaultConstructor: CODESCHEME_DocComment_Function_InHeaderFileOnly" << std::endl;
        }
        else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InSourceFileOnly)
        {
            define += docCommentDefaultConstructor();
            //std::cout << "ClassSettings::sourceFileDefaultConstructor: CODESCHEME_DocComment_Function_InSourceFileOnly" << std::endl;
        }
    }
    if (typeInheritsInfomation() == inherits_None)
    {
        define += CODESCHEME_Class_Function_DefaultConstructor_Inherits_None;
    }
    else if (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile)
    {
        define += CODESCHEME_Class_Function_DefaultConstructor_Inherits_QObject;
    }
    else
    {
        define += CODESCHEME_Class_Function_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile;
    }
    return define;
}

QString ClassSettings::sourceFileDestructor() const
{
    QString define;
    if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_Detached)
    {
    }
    else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDeclare)
    {
    }
    else if (CODESCHEME_DocCommentContent_Function_Attachment == CODESCHEME_DocComment_Function_InDefine)
    {
        if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_Any)
        {
            define += docCommentDefaultConstructor();
        }
        else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InHeaderFileOnly)
        {
        }
        else if (CODESCHEME_DocCommentContent_Function_Pos == CODESCHEME_DocComment_Function_InSourceFileOnly)
        {
            define += docCommentDefaultConstructor();
        }
    }
    if (typeInheritsInfomation() == inherits_None)
    {
        define += CODESCHEME_Class_Function_Destructor_Inherits_None;
    }
    else if (typeInheritsInfomation() == inherits_QWidget_AssociateWithUiFile)
    {
        define += CODESCHEME_Class_Function_Destructor_Inherits_QWidget_AssociateWithUiFile;
    }
    else
    {
        define += CODESCHEME_Class_Function_Destructor_Inherits_QObject;
    }
    return define;
}

QString ClassSettings::sourceFileName() const
{
    QString s;
    s = CODESCHEME_File_SourceFileName;
    return s;
}

