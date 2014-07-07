/*****************************************************************************
 * propertiesgroupdata.cpp:
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
#include "propertiesgroupdata.h"
#ifdef DEBUG_PROPERTIESGROUPS_COW
#include <iostream>
static int id = -1;
#endif

PropertiesGroupData::PropertiesGroupData() :
    m_used(1),
    p_enabled(true),
    p_readFunctionIsInline(true),
    p_resetFunctionIsInline(false),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
#ifdef DEBUG_PROPERTIESGROUPS_COW
    id++;
    m_id = id;
    std::cout << "PropertiesGroupData created. id=" << id << std::endl;
#endif
}

PropertiesGroupData::PropertiesGroupData(const QString &name) :
    p_name(name),
    m_used(1),
    p_enabled(true),
    p_readFunctionIsInline(true),
    p_resetFunctionIsInline(false),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
#ifdef DEBUG_PROPERTIESGROUPS_COW
    id++;
    m_id = id;
    std::cout << "PropertiesGroupData created. id=" << m_id << std::endl;
#endif
}

PropertiesGroupData::PropertiesGroupData(const PropertiesGroupData &v) :
    m_properties(v.m_properties),
    p_statementsAfterWriteProperty(v.p_statementsAfterWriteProperty),
    p_statementsMiddleWriteProperty(v.p_statementsMiddleWriteProperty),
    p_statementsStartWriteProperty(v.p_statementsStartWriteProperty),
    m_used(1),
    p_enabled(v.p_enabled),
    p_readFunctionIsInline(v.p_readFunctionIsInline),
    p_resetFunctionIsInline(v.p_resetFunctionIsInline),
    p_writeFunctionEmitSignal(v.p_writeFunctionEmitSignal),
    p_writeFunctionIsInline(v.p_writeFunctionIsInline)
{
#ifdef DEBUG_PROPERTIESGROUPS_COW
    id++;
    m_id = id;
    std::cout << "PropertiesGroupData created. id=" << id << std::endl;
#endif
}

PropertiesGroupData::~PropertiesGroupData()
{
#ifdef DEBUG_PROPERTIESGROUPS_COW
    std::cout << "PropertiesGroupData removed. id=" << m_id << std::endl;
#endif
}

/*PropertiesGroupData &PropertiesGroupData::operator=(const PropertiesGroupData &v)
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
}*/
