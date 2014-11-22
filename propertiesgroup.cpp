/*****************************************************************************
 * propertiesgroup.cpp:
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
#include "propertiesgroup.h"
#include "property.h"
#include "sharedFunctions.h"
#include <QDateTime>

int PropertiesGroup::find(const QString &name) const
{
    int i = 0;
    for (; i < m_d->m_properties.size(); i++)
    {
        if (m_d->m_properties.at(i).name() == name)
        {
            return i;
        }
    }
    return -1;
}

QStringList PropertiesGroup::propertiesName() const
{
    QStringList list;
    foreach (Property p, m_d->m_properties)
    {
        list.append(p.name());
    }
    return list;
}

void PropertiesGroup::append(const Property &var)
{
    beforeWrite();
    /*if (!m_d->p_typeOrder.contains(var.realTypeName()))
    {
        m_d->p_typeOrder.append(var.realTypeName());
    }*/
    m_d->m_properties.append(var);
}

void PropertiesGroup::append(const QList<Property> &var)
{
    beforeWrite();
    /*foreach (Property p, var)
    {
        if (!m_d->p_typeOrder.contains(p.realTypeName()))
        {
            m_d->p_typeOrder.append(p.realTypeName());
        }
    }*/
    m_d->m_properties.append(var);
}

void PropertiesGroup::sort()
{
    beforeWrite();
    {
        int i = 0, j = 0;
        QStringList list = this->propertiesName();
        QList<Property> listP;
        list.sort();
        list.removeDuplicates();
        for (; i < list.size(); i++)
        {
            bool found = false;
            for (j = 0; (j < m_d->m_properties.size()) && (!found); j++)
            {
                if (m_d->m_properties.at(j).name() == list.at(i))
                {
                    listP.append(m_d->m_properties.at(j));
                    found = true;
                }
            }
            /*if (!found)
            {
                std::cout << "PropertiesGroup::sort: Can not find property "
                          << list.at(i).toStdString() << std::endl;
            }*/
        }
        m_d->m_properties = listP;
    }
}

QDomElement PropertiesGroup::toXMLNode(QDomDocument *doc) const
{
    QDomElement element = doc->createElement("PropertiesGroup");
#define SETATTRIBUTE(NAME) element.setAttribute(#NAME, NAME())
#define SETATTRIBUTE_BOOL(NAME) element.setAttribute(#NAME, (NAME() ? QString("true") : QString("false")))
    SETATTRIBUTE(name);
    SETATTRIBUTE_BOOL(readFunctionIsInline);
    SETATTRIBUTE_BOOL(writeFunctionIsInline);
    SETATTRIBUTE_BOOL(writeFunctionEmitSignal);
    SETATTRIBUTE_BOOL(resetFunctionIsInline);
    SETATTRIBUTE_BOOL(enabled);
    SETATTRIBUTE(statementsInReadProperty);
    SETATTRIBUTE(statementsBeforeResetProperty);
    SETATTRIBUTE(statementsAfterResetProperty);
    SETATTRIBUTE(statementsBeforeWriteProperty);
    SETATTRIBUTE(statementsMiddleWriteProperty);
    SETATTRIBUTE(statementsAfterWriteProperty);
    foreach (Property p, m_d->m_properties)
    {
        element.appendChild(p.toXMLNode(doc));
    }
    return element;
}

PropertiesGroup PropertiesGroup::fromXMLNode(const QDomElement &element)
{
    if (element.tagName() == "PropertiesGroup")
    {
        PropertiesGroup g;
        g.setName(element.attribute("name"));
        g.setReadFunctionIsInline(stringToBool(element.attribute("readFunctionIsInline")));
        g.setWriteFunctionIsInline(stringToBool(element.attribute("writeFunctionIsInline")));
        g.setWriteFunctionEmitSignal(stringToBool(element.attribute("writeFunctionEmitSignal")));
        g.setResetFunctionIsInline(stringToBool(element.attribute("resetFunctionIsInline")));
        g.setEnabled(stringToBool(element.attribute("enabled")));
        g.setStatementsInReadProperty(element.attribute("statementsInReadProperty"));
        g.setStatementsBeforeResetProperty(element.attribute("statementsBeforeResetProperty"));
        g.setStatementsAfterResetProperty(element.attribute("statementsAfterResetProperty"));
        g.setStatementsBeforeWriteProperty(element.attribute("statementsBeforeWriteProperty"));
        g.setStatementsMiddleWriteProperty(element.attribute("statementsMiddleWriteProperty"));
        g.setStatementsAfterWriteProperty(element.attribute("statementsAfterWriteProperty"));
        QDomNodeList list = element.elementsByTagName("Property");
        int i = 0;
        for (; i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            g.append(Property::fromXMLNode(node.toElement()));
        }
        return g;
    }
    else
    {
        return PropertiesGroup();
    }
}
