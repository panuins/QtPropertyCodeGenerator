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
    p_typeInheritsInfomation(inherits_None),
    p_generatePreventReentrantCode(true),
    p_sortAllProperties(true)
{
    m_propertiesGroups.append(PropertiesGroup(QString("primary")));
}

ClassSettings::ClassSettings(const QString &name, const QString &inheritsClass) :
    p_className(name),
    p_inherits(inheritsClass),
    p_typeInheritsInfomation(inherits_None),
    p_generatePreventReentrantCode(true),
    p_sortAllProperties(true)
{
    m_propertiesGroups.append(PropertiesGroup(QString("primary")));
}

ClassSettings::ClassSettings(const ClassSettings &v) :
    m_propertiesGroups(v.m_propertiesGroups),
    m_enums(v.m_enums),
    p_typeOrder(v.p_typeOrder),
    p_className(v.p_className),
    p_docBrief(v.p_docBrief),
    p_docDetail(v.p_docDetail),
    p_docName(v.p_docName),
    p_inherits(v.p_inherits),
    p_typeInheritsInfomation(v.p_typeInheritsInfomation),
    p_generatePreventReentrantCode(v.p_generatePreventReentrantCode),
    p_sortAllProperties(v.p_sortAllProperties)
{
}

ClassSettings::~ClassSettings()
{
}

ClassSettings &ClassSettings::operator=(const ClassSettings &v)
{
    m_propertiesGroups = v.m_propertiesGroups;
    m_enums = v.m_enums;
    p_typeOrder = v.p_typeOrder;
    p_className = v.p_className;
    p_docBrief = v.p_docBrief;
    p_docDetail = v.p_docDetail;
    p_docName = v.p_docName;
    p_inherits = v.p_inherits;
    p_typeInheritsInfomation = v.p_typeInheritsInfomation;
    p_generatePreventReentrantCode = v.p_generatePreventReentrantCode;
    p_sortAllProperties = v.p_sortAllProperties;
    return *this;
}

/*ClassSettings::const_Iterator ClassSettings::begin() const
{
    if (this->sortAllProperties())
    {
        QStringList names = propertiesName();
        ClassSettings::const_Iterator i;
        i.m_classSettings = this;
        QList<QPair<QList<Property>::const_iterator, QList<PropertiesGroup>::const_iterator> > data;
        foreach (QString name, names)
        {
            QList<Property>::const_iterator i
        }
    }
}*/

QStringList ClassSettings::existType() const
{
    QStringList list;
    foreach (PropertiesGroup g, m_propertiesGroups)
    {
        foreach (Property p, g.properties())
        {
            list.append(p.realTypeName());
        }
    }
    list.sort();
    list.removeDuplicates();
    return list;
}

int ClassSettings::findGroup(const QString &name) const
{
    int i = 0;
    for (; i < m_propertiesGroups.size(); i++)
    {
        if (m_propertiesGroups.at(i).name() == name)
        {
            return i;
        }
    }
    return -1;
}

int ClassSettings::findGroupByPropertyName(const QString &name) const
{
    int i = 0;
    for (; i < m_propertiesGroups.size(); i++)
    {
        QList<Property> l = m_propertiesGroups.at(i).properties();
        foreach (Property p, l)
        {
            if (p.name() == name)
            {
                return i;
            }
        }
    }
    return -1;
}


//如果返回值的name属性为空，则表示没找到。
Property ClassSettings::findProperty(const QString &name) const
{
    foreach (PropertiesGroup g, m_propertiesGroups)
    {
        foreach (Property p, g.properties())
        {
            if (p.name() == name)
            {
                return p;
            }
        }
    }
    return Property();
}

QString ClassSettings::parentClass() const
{
    QString strParent("");
    switch (typeInheritsInfomation())
    {
    case inherits_QObject:
        strParent = "QObject";
        break;
    case inherits_QWidget:
    case inherits_QWidget_AssociateWithUiFile:
        strParent = "QWidget";
        break;
    case inherits_QQuickItem:
        strParent = "QQuickItem";
        break;
    default:
        break;
    }
    return strParent;
}

QList<Property> ClassSettings::propertiesIsType(const QString &var) const
{
    QList<Property> listP;
    foreach (PropertiesGroup g, m_propertiesGroups)
    {
        foreach (Property p, g.properties())
        {
            if (p.realTypeName() == var)
            {
                listP.append(p);
            }
        }
    }
    return listP;
}

QStringList ClassSettings::propertiesGroupsName() const
{
    QStringList list;
    foreach (PropertiesGroup g, m_propertiesGroups)
    {
        list.append(g.name());
    }
    list.sort();
    return list;
}

QStringList ClassSettings::propertiesName() const
{
    QStringList list;
    foreach (PropertiesGroup g, m_propertiesGroups)
    {
        foreach (Property p, g.properties())
        {
            list.append(p.name());
        }
    }
    list.removeDuplicates();
    list.sort();
    return list;
}

void ClassSettings::sort()
{
    {
        int i = 0, j = 0;
        QStringList list = this->propertiesGroupsName();
        QList<PropertiesGroup> listP;
        list.sort();
        list.removeDuplicates();
        for (; i < list.size(); i++)
        {
            bool found = false;
            for (j = 0; (j < m_propertiesGroups.size()) && (!found); j++)
            {
                if (m_propertiesGroups.at(j).name() == list.at(i))
                {
                    m_propertiesGroups[j].sort();
                    listP.append(m_propertiesGroups.at(j));
                    found = true;
                }
            }
            /*if (!found)
            {
                std::cout << "ClassSettings::sort: Can not find property "
                          << list.at(i).toStdString() << std::endl;
            }*/
        }
        m_propertiesGroups = listP;
    }
    /*{
        int i = 0, j = 0;
        QStringList list = this->enumsName();
        QList<EnumType> listE;
        list.sort();
        list.removeDuplicates();
        for (; i < list.size(); i++)
        {
            bool found = false;
            for (j = 0; (j < m_enums.size()) && (!found); j++)
            {
                if (m_enums.at(j).name() == list.at(i))
                {
                    listE.append(m_enums.at(j));
                    found = true;
                }
            }
            if (!found)
            {
                std::cout << "ClassSettings::sort: Can not find enum type "
                          << list.at(i).toStdString() << std::endl;
            }
        }
        m_enums = listE;
    }*/
}

void ClassSettings::updateTypeOrder()
{
    foreach (PropertiesGroup g, m_propertiesGroups)
    {
        foreach (Property p, g.properties())
        {
            if (!p_typeOrder.contains(p.realTypeName()))
            {
                p_typeOrder.append(p.realTypeName());
            }
        }
    }
}
