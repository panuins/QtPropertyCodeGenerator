#include "propertiesgroup.h"

PropertiesGroup::PropertiesGroup() :
    p_className(),
    p_inherits(),
    p_typeInderitsInfomation(inherits_None),
    p_readFunctionIsInline(true),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
}

PropertiesGroup::PropertiesGroup(const QString &name,
                                 const QString &inheritsClass) :
    p_className(name),
    p_inherits(inheritsClass),
    p_typeInderitsInfomation(inherits_None),
    p_readFunctionIsInline(true),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
}

PropertiesGroup::PropertiesGroup(const PropertiesGroup &v) :
    m_properties(v.m_properties),
    p_className(v.p_className),
    p_inherits(v.p_inherits),
    p_statementsAfterWriteProperty(v.p_statementsAfterWriteProperty),
    p_statementsMiddleWriteProperty(v.p_statementsMiddleWriteProperty),
    p_statementsStartWriteProperty(v.p_statementsStartWriteProperty),
    p_typeInderitsInfomation(v.p_typeInderitsInfomation),
    p_readFunctionIsInline(v.p_readFunctionIsInline),
    p_writeFunctionEmitSignal(v.p_writeFunctionEmitSignal),
    p_writeFunctionIsInline(v.p_writeFunctionIsInline)
{
}

PropertiesGroup::~PropertiesGroup()
{
}

PropertiesGroup &PropertiesGroup::operator=(const PropertiesGroup &v)
{
    m_properties = v.m_properties;
    p_className = v.p_className;
    p_inherits = v.p_inherits;
    p_statementsAfterWriteProperty = v.p_statementsAfterWriteProperty;
    p_statementsMiddleWriteProperty = v.p_statementsMiddleWriteProperty;
    p_statementsStartWriteProperty = v.p_statementsStartWriteProperty;
    p_typeInderitsInfomation = v.p_typeInderitsInfomation;
    p_readFunctionIsInline = v.p_readFunctionIsInline;
    p_writeFunctionEmitSignal = v.p_writeFunctionEmitSignal;
    p_writeFunctionIsInline = v.p_writeFunctionIsInline;
    return *this;
}

int PropertiesGroup::find(const QString &name) const
{
    int i = 0;
    for (; i < m_properties.size(); i++)
    {
        if (m_properties.at(i).name() == name)
        {
            return i;
        }
    }
    return -1;
}

QStringList PropertiesGroup::propertiesName() const
{
    QStringList list;
    foreach (Property p, m_properties)
    {
        list.append(p.name());
    }
    return list;
}

void PropertiesGroup::sort()
{
    int i = 0, j = 0;
    QStringList list = this->propertiesName();
    QList<Property> listP;
    list.sort();
    list.removeDuplicates();
    for (; i < list.size(); i++)
    {
        bool found = false;
        for (j = 0; (j < m_properties.size()) && (!found); j++)
        {
            if (m_properties.at(j).name() == list.at(i))
            {
                listP.append(m_properties.at(j));
                found = true;
            }
        }
        /*if (!found)
        {
            std::cout << "PropertiesGroup::sortProperties: Can not find property "
                      << list.at(i).toStdString() << std::endl;
        }*/
    }
    m_properties = listP;
}

QString PropertiesGroup::generateQPropertyDeclear() const
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
    return qProperty;
}

QString PropertiesGroup::generateReadDeclear() const
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
    return readDeclear;
}

QString PropertiesGroup::generateWriteDeclear() const
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
    return writeDeclear;
}

QString PropertiesGroup::generateSignalDeclear() const
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
    return signalDeclear;
}

QString PropertiesGroup::generateMemberVariableDeclear() const
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
    return memberVars;
}

QString PropertiesGroup::generateReadFunctionDefine() const
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
    return readFunctions;
}

QString PropertiesGroup::generateWriteFunctionDefine() const
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
    return writeFunctions;
}
