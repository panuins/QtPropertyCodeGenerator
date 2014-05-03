/*****************************************************************************
 * classsettings.cpp:
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

ClassSettings::ClassSettings() :
    p_className(),
    p_inherits(),
    p_typeInderitsInfomation(inherits_None)
{
}

ClassSettings::ClassSettings(const QString &name, const QString &inheritsClass) :
    p_className(name),
    p_inherits(inheritsClass),
    p_typeInderitsInfomation(inherits_None)
{
}

ClassSettings::ClassSettings(const ClassSettings &v) :
    m_properties(v.m_properties),
    p_className(v.p_className),
    p_inherits(v.p_inherits),
    p_typeInderitsInfomation(v.p_typeInderitsInfomation)
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
    return *this;
}

/*QString ClassSettings::generateQPropertyDeclear() const
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
