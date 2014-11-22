/*****************************************************************************
 * classsettingsInlineFunctions.h:
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
#ifndef CLASSSETTINGSINLINEFUNCTIONS_H
#define CLASSSETTINGSINLINEFUNCTIONS_H
//#include <cassert>

inline PropertiesGroup &ClassSettings::operator[](int i)
{
    //assert(i >= 0);
    //assert(i < m_propertiesGroups.size());
    return m_propertiesGroups[i];
}

inline const PropertiesGroup &ClassSettings::at(int i) const
{
    //assert(i >= 0);
    //assert(i < m_propertiesGroups.size());
    return m_propertiesGroups.at(i);
}

inline QString ClassSettings::className() const
{
    return p_className;
}

inline QString ClassSettings::docBrief() const
{
    return p_docBrief;
}

inline QString ClassSettings::docDetail() const
{
    return p_docDetail;
}

inline QString ClassSettings::docName() const
{
    return p_docName;
}

inline bool ClassSettings::generatePreventReentrantCode() const
{
    return p_generatePreventReentrantCode;
}

inline QString ClassSettings::inherits() const
{
    return p_inherits;
}

inline const QList<PropertiesGroup> &ClassSettings::propertiesGroups() const
{
    return m_propertiesGroups;
}

inline QString ClassSettings::replacedDocBrief() const
{
    return replacePercentToSepecialString(docBrief());
}

inline QString ClassSettings::replacedDocDetail() const
{
    return replacePercentToSepecialString(docDetail());
}

inline QString ClassSettings::replacedDocName() const
{
    return replacePercentToSepecialString(docName());
}

inline bool ClassSettings::signalIsValid() const
{
    return (p_typeInheritsInfomation == inherits_QObject)
            || (p_typeInheritsInfomation == inherits_QWidget)
            || (p_typeInheritsInfomation == inherits_QQuickItem)
            || (p_typeInheritsInfomation == inherits_QWidget_AssociateWithUiFile)
            || (p_typeInheritsInfomation == inherits_QWindow);
}

inline int ClassSettings::size() const
{
    return m_propertiesGroups.size();
}

inline bool ClassSettings::sortAllProperties() const
{
    return p_sortAllProperties;
}

inline ClassSettings::TypeInheritsInformation
ClassSettings::typeInheritsInfomation() const
{
    return p_typeInheritsInfomation;
}

inline QStringList ClassSettings::typeOrder() const
{
    return p_typeOrder;
}

inline void ClassSettings::append(const PropertiesGroup &var)
{
    m_propertiesGroups.append(var);
}

inline void ClassSettings::append(const QList<PropertiesGroup> &var)
{
    m_propertiesGroups.append(var);
}

inline void ClassSettings::clear()
{
    m_propertiesGroups.clear();
}

inline void ClassSettings::removeAt(int i)
{
    //assert((i >= 0) && (i < m_propertiesGroups.size()));
    m_propertiesGroups.removeAt(i);
}

inline void ClassSettings::setClassName(const QString &var)
{
    p_className = var;
}

inline void ClassSettings::setDocBrief(const QString &var)
{
    p_docBrief = var;
}

inline void ClassSettings::setDocDetail(const QString &var)
{
    p_docDetail = var;
}

inline void ClassSettings::setDocName(const QString &var)
{
    p_docName = var;
}

inline void ClassSettings::setGeneratePreventReentrantCode(const bool &var)
{
    p_generatePreventReentrantCode = var;
}

inline void ClassSettings::setInherits(const QString &var)
{
    p_inherits = var;
}

inline void ClassSettings::setPropertiesGroups(const QList<PropertiesGroup> &var)
{
    m_propertiesGroups = var;
}

inline void ClassSettings::setSortAllProperties(bool var)
{
    p_sortAllProperties = var;
}

inline void ClassSettings::setTypeInheritsInfomation(
        const ClassSettings::TypeInheritsInformation &var)
{
    p_typeInheritsInfomation = var;
}

inline void ClassSettings::setTypeOrder(const QStringList &var)
{
    p_typeOrder = var;
}

#endif // CLASSSETTINGSINLINEFUNCTIONS_H
