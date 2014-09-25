/*****************************************************************************
 * propertyInlineFunctions.h:
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
#ifndef PROPERTYINLINEFUNCTIONS_H
#define PROPERTYINLINEFUNCTIONS_H
#include "paraments.h"
#ifdef DEBUG_PROPERTYS_COW_DETAIL
#include <iostream>
#endif

inline Property::Property() :
    m_d(new PropertyData())
{
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: default constructor. id=" << m_d->m_id << std::endl;
#endif
}

inline Property::Property(const QString &name,
                          const QString &type,
                          const QString &typeStringName) :
    m_d(new PropertyData(name, type, typeStringName))
{
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property:: constructor(const QString &, "
                 "const QString &, "
                 "const QString &). id=" << m_d->m_id << std::endl;
#endif
}

inline Property::Property(const Property &p) :
    m_d(p.m_d)
{
    m_d->m_used++;
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: copy constructor. used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
}

inline Property::Property(const PropertyData &p) :
    m_d(new PropertyData(p))
{
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: copy constructor(PropertyData). "
                 "used=" << m_d->m_used
              << " id=" << m_d->m_id
              << ". p used=" << p.m_used
              << " p id=" << p.m_id << std::endl;
#endif
}

inline Property::~Property()
{
    m_d->m_used--;
    if (m_d->m_used == 0)
    {
        delete m_d;
    }
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: destructor. used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
}

inline Property &Property::operator=(const Property &p)
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
#ifdef DEBUG_PROPERTYS_COW_DETAIL
        std::cout << "Property::operator=. used=" << m_d->m_used
                  << " id=" << m_d->m_id
                  << ". p used=" << p.m_d->m_used
                  << " p id=" << p.m_d->m_id << std::endl;
#endif
    }
    return *this;
}

inline bool Property::constant() const
{
    return m_d->p_constant;
}

inline QVariant Property::defaultValue() const
{
    return m_d->p_defaultValue;
}

inline bool Property::designable() const
{
    return m_d->p_designable;
}

inline QString Property::docBrief() const
{
    return m_d->p_docBrief;
}

inline QString Property::docDetail() const
{
    return m_d->p_docDetail;
}

inline QString Property::docName() const
{
    return m_d->p_docName;
}

inline bool Property::enabled() const
{
    return m_d->p_enabled;
}

inline bool Property::final() const
{
    return m_d->p_final;
}

inline bool Property::member() const
{
    return m_d->p_member;
}

inline QString Property::name() const
{
    return m_d->p_name;
}

inline bool Property::needWrite() const
{
    return write() || resetIsValid();
}

inline bool Property::notify() const
{
    return m_d->p_notify;
}

inline bool Property::read() const
{
    return m_d->p_read;
}

inline QString Property::realTypeName() const
{
    if (m_d->p_typeStringName.isEmpty())
    {
        return m_d->p_type;
    }
    else
    {
        return m_d->p_typeStringName;
    }
}

inline QString Property::replacedDocBrief() const
{
    return replacePercentToSepecialString(docBrief());
}

inline QString Property::replacedDocDetail() const
{
    return replacePercentToSepecialString(docDetail());
}

inline QString Property::replacedDocName() const
{
    return replacePercentToSepecialString(docName());
}

inline bool Property::reset() const
{
    return m_d->p_reset;
}

inline bool Property::resetIsValid() const
{
    bool canReset = (m_d->p_defaultValue.canConvert(QMetaType::QString)
                     && !m_d->p_defaultValue.toString().isEmpty());
    return reset() && canReset;
}

inline int Property::revision() const
{
    return m_d->p_revision;
}

inline bool Property::scriptable() const
{
    return m_d->p_scriptable;
}

inline bool Property::stored() const
{
    return m_d->p_stored;
}

inline const QString &Property::type() const
{
    return m_d->p_type;
}

inline QString Property::typeStringName() const
{
    return m_d->p_typeStringName;
}

inline bool Property::user() const
{
    return m_d->p_user;
}

inline bool Property::write() const
{
    return m_d->p_write;
}

inline void Property::setConstant(bool b)
{
    beforeWrite();
    m_d->p_constant = b;
}

inline void Property::setDesignable(bool b)
{
    beforeWrite();
    m_d->p_designable = b;
}

inline void Property::setDefaultValue(const QVariant &var)
{
    beforeWrite();
    m_d->p_defaultValue = var;
}

inline void Property::setDocBrief(const QString &var)
{
    beforeWrite();
    m_d->p_docBrief = var;
}

inline void Property::setDocDetail(const QString &name)
{
    beforeWrite();
    m_d->p_docDetail = name;
}

inline void Property::setDocName(const QString &name)
{
    beforeWrite();
    m_d->p_docName = name;
}

inline void Property::setEnabled(bool var)
{
    beforeWrite();
    m_d->p_enabled = var;
}

inline void Property::setFinal(bool b)
{
    beforeWrite();
    m_d->p_final = b;
}

inline void Property::setName(const QString &name)
{
    beforeWrite();
    m_d->p_name = name;
}

inline void Property::setMember(bool var)
{
    beforeWrite();
    m_d->p_member = var;
}

inline void Property::setNotify(bool var)
{
    beforeWrite();
    m_d->p_notify = var;
}

inline void Property::setRead(bool var)
{
    beforeWrite();
    m_d->p_read = var;
}

inline void Property::setReset(bool var)
{
    beforeWrite();
    m_d->p_reset = var;
}

inline void Property::setRevision(int n)
{
    beforeWrite();
    m_d->p_revision = n;
}

inline void Property::setScriptable(bool b)
{
    beforeWrite();
    m_d->p_scriptable = b;
}

inline void Property::setStored(bool b)
{
    beforeWrite();
    m_d->p_stored = b;
}

inline void Property::setType(const QString & type)
{
    beforeWrite();
    m_d->p_type = type;
}

inline void Property::setTypeStringName(const QString &name)
{
    beforeWrite();
    m_d->p_typeStringName = name;
}

inline void Property::setUser(bool b)
{
    beforeWrite();
    m_d->p_user = b;
}

inline void Property::setWrite(bool var)
{
    beforeWrite();
    m_d->p_write = var;
}

inline void Property::beforeWrite()
{
    if (m_d->m_used > 1)
    {
        m_d->m_used--;
        m_d = new PropertyData(*m_d);
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property::beforeWrite copy. "
                 "used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
    }
}

#endif // PROPERTYINLINEFUNCTIONS_H
