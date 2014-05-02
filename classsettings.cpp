/*#include "classsettings.h"

ClassSettings::ClassSettings() :
    p_className(),
    p_inherits(),
    p_typeInderitsInfomation(inherits_None),
    p_readFunctionIsInline(true),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
}

ClassSettings::ClassSettings(const QString &name, const QString &inheritsClass) :
    p_className(name),
    p_inherits(inheritsClass),
    p_typeInderitsInfomation(inherits_None),
    p_readFunctionIsInline(true),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
}

ClassSettings::ClassSettings(const ClassSettings &v) :
    m_properties(v.m_properties),
    p_className(v.p_className),
    p_inherits(v.p_inherits),
    p_typeInderitsInfomation(v.p_typeInderitsInfomation),
    p_readFunctionIsInline(v.p_readFunctionIsInline),
    p_writeFunctionEmitSignal(v.p_writeFunctionEmitSignal),
    p_writeFunctionIsInline(v.p_writeFunctionIsInline)
{
}

ClassSettings::~ClassSettings()
{
}

ClassSettings &ClassSettings::operator=(const ClassSettings &v)
{
    m_properties = v.m_properties;
    p_className = v.p_className;
    p_inherits = v.p_inherits;
    p_typeInderitsInfomation = v.p_typeInderitsInfomation;
    p_readFunctionIsInline = v.p_readFunctionIsInline;
    p_writeFunctionEmitSignal = v.p_writeFunctionEmitSignal;
    p_writeFunctionIsInline = v.p_writeFunctionIsInline;
    return *this;
}

QString ClassSettings::generateQPropertyDeclear() const
{
    QString qProperty("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            qProperty.append(QString("    ")
                             + p.qPropertyString());
        }
    }
}

QString ClassSettings::generateReadDeclear() const
{
    QString readDeclear("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            readDeclear.append(QString("    ")
                               + p.readDeclear());
        }
    }
}

QString ClassSettings::generateWriteDeclear() const
{
    QString writeDeclear("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            writeDeclear.append(QString("    ")
                                + p.writeDeclear());
        }
    }
}

QString ClassSettings::generateSignalDeclear() const
{
    QString signalDeclear("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            signalDeclear.append(QString("    ")
                                 + p.signalDeclear());
        }
    }
}

QString ClassSettings::generateMemberVariableDeclear() const
{
    QString memberVars("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            memberVars.append(QString("    ")
                              + p.memberVariableDeclear());
        }
    }
}

QString ClassSettings::generateReadFunctionDefine() const
{
    QString readFunctions("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            readFunctions.append(p.readFunctionDefine(p_className,
                                                      p_readFunctionIsInline)
                                 + "\n");
        }
    }
}

QString ClassSettings::generateWriteFunctionDefine() const
{
    QString writeFunctions("");
    foreach (Property p, m_properties)
    {
        if (p.enabled())
        {
            writeFunctions.append(p.writeFunctionDefine(
                                      p_className,
                                      p_statementsStartWriteProperty,
                                      p_statementsMiddleWriteProperty,
                                      p_statementsAfterWriteProperty,
                                      p_writeFunctionEmitSignal,
                                      p_writeFunctionIsInline)
                                  + "\n");
        }
    }
}*/
