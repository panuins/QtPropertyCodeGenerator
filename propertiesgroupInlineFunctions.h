/*****************************************************************************
 * propertiesgroupInlineFunctions.h:
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
#ifndef PROPERTIESGROUPINLINEFUNCTIONS_H
#define PROPERTIESGROUPINLINEFUNCTIONS_H
#include <cassert>
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
#include <iostream>
#endif

inline PropertiesGroup::PropertiesGroup() :
    m_d(new PropertiesGroupData())
{
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
    std::cout << "PropertiesGroup: default constructor. id=" << m_d->m_id << std::endl;
#endif
}

inline PropertiesGroup::PropertiesGroup(const QString &name) :
    m_d(new PropertiesGroupData(name))
{
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
    std::cout << "PropertiesGroup:: constructor(const QString &, "
                 "const QString &). id=" << m_d->m_id << std::endl;
#endif
}

inline PropertiesGroup::PropertiesGroup(const PropertiesGroup &p) :
    m_d(p.m_d)
{
    m_d->m_used++;
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
    std::cout << "PropertiesGroup: copy constructor. used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
}

inline PropertiesGroup::PropertiesGroup(const PropertiesGroupData &p) :
    m_d(new PropertiesGroupData(p))
{
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
    std::cout << "PropertiesGroup: copy constructor(PropertiesGroupData). "
                 "used=" << m_d->m_used
              << " id=" << m_d->m_id
              << ". p used=" << p.m_used
              << " p id=" << p.m_id << std::endl;
#endif
}

inline PropertiesGroup::~PropertiesGroup()
{
    m_d->m_used--;
    if (m_d->m_used == 0)
    {
        delete m_d;
    }
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
    std::cout << "PropertiesGroup: destructor. used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
}

inline PropertiesGroup &PropertiesGroup::operator=(const PropertiesGroup &p)
{
    if (p.m_d != m_d)
    {
        p.m_d->m_used++;
        m_d->m_used--;
        if (m_d->m_used == 0)
        {
            delete m_d;
        }
        m_d = p.m_d;
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
        std::cout << "PropertiesGroup::operator=. used=" << m_d->m_used
                  << " id=" << m_d->m_id
                  << ". p used=" << p.m_d->m_used
                  << " p id=" << p.m_d->m_id << std::endl;
#endif
    }
    return *this;
}

inline Property &PropertiesGroup::operator[](int i)
{
    assert((i >= 0) && (i < m_d->m_properties.size()));
    beforeWrite();
    return m_d->m_properties[i];
}

inline const Property &PropertiesGroup::at(int i) const
{
    assert((i >= 0) && (i < m_d->m_properties.size()));
    return m_d->m_properties.at(i);
}

inline bool PropertiesGroup::enabled() const
{
    return m_d->p_enabled;
}

inline QString PropertiesGroup::name() const
{
    return m_d->p_name;
}

inline const QList<Property> &PropertiesGroup::properties() const
{
    return m_d->m_properties;
}

inline bool PropertiesGroup::readFunctionIsInline() const
{
    return m_d->p_readFunctionIsInline;
}

inline bool PropertiesGroup::resetFunctionIsInline() const
{
    return m_d->p_resetFunctionIsInline;
}

inline int PropertiesGroup::size() const
{
    return m_d->m_properties.size();
}

inline QString PropertiesGroup::statementsAfterWriteProperty() const
{
    return m_d->p_statementsAfterWriteProperty;
}

inline QString PropertiesGroup::statementsMiddleWriteProperty() const
{
    return m_d->p_statementsMiddleWriteProperty;
}

inline QString PropertiesGroup::statementsStartWriteProperty() const
{
    return m_d->p_statementsStartWriteProperty;
}

inline bool PropertiesGroup::writeFunctionEmitSignal() const
{
    return m_d->p_writeFunctionEmitSignal;
}

inline bool PropertiesGroup::writeFunctionIsInline() const
{
    return m_d->p_writeFunctionIsInline;
}

inline void PropertiesGroup::clear()
{
    beforeWrite();
    m_d->m_properties.clear();
}

inline void PropertiesGroup::insert(int vari, const Property &varp)
{
    assert((vari >= 0) && (vari < m_d->m_properties.size()));
    beforeWrite();
    m_d->m_properties.insert(vari, varp);
}

inline void PropertiesGroup::removeAt(int var)
{
    beforeWrite();
    m_d->m_properties.removeAt(var);
}

inline void PropertiesGroup::setEnabled(bool var)
{
    beforeWrite();
    m_d->p_enabled = var;
}

inline void PropertiesGroup::setName(const QString &var)
{
    beforeWrite();
    m_d->p_name = var;
}

inline void PropertiesGroup::setProperties(const QList<Property> &var)
{
    beforeWrite();
    m_d->m_properties = var;
}

inline void PropertiesGroup::setReadFunctionIsInline(const bool &var)
{
    beforeWrite();
    m_d->p_readFunctionIsInline = var;
}

inline void PropertiesGroup::setResetFunctionIsInline(const bool &var)
{
    beforeWrite();
    m_d->p_resetFunctionIsInline = var;
}

inline void PropertiesGroup::setStatementsAfterWriteProperty(const QString &var)
{
    beforeWrite();
    m_d->p_statementsAfterWriteProperty = var;
}

inline void PropertiesGroup::setStatementsMiddleWriteProperty(const QString &var)
{
    beforeWrite();
    m_d->p_statementsMiddleWriteProperty = var;
}

inline void PropertiesGroup::setStatementsStartWriteProperty(const QString &var)
{
    beforeWrite();
    m_d->p_statementsStartWriteProperty = var;
}

inline void PropertiesGroup::setWriteFunctionEmitSignal(const bool &var)
{
    beforeWrite();
    m_d->p_writeFunctionEmitSignal = var;
}

inline void PropertiesGroup::setWriteFunctionIsInline(const bool &var)
{
    beforeWrite();
    m_d->p_writeFunctionIsInline = var;
}

inline void PropertiesGroup::beforeWrite()
{
    if (m_d->m_used > 1)
    {
        m_d->m_used--;
        m_d = new PropertiesGroupData(*m_d);
#ifdef DEBUG_PROPERTIESGROUPS_COW_DETAIL
        std::cout << "PropertiesGroup::beforeWrite copy. "
                     "used=" << m_d->m_used
                  << " id=" << m_d->m_id << std::endl;
#endif
    }
}

#endif // PROPERTIESGROUPINLINEFUNCTIONS_H
