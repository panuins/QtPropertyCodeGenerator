#include "propertiesgroupdata.h"
#ifdef DEBUG_PROPERTIESGROUPS_COW
#include <iostream>
static int id = -1;
#endif

PropertiesGroupData::PropertiesGroupData() :
    p_className(),
    p_inherits(),
    p_typeInderitsInfomation(0),
    m_used(1),
    p_readFunctionIsInline(true),
    p_writeFunctionEmitSignal(true),
    p_writeFunctionIsInline(false)
{
#ifdef DEBUG_PROPERTIESGROUPS_COW
    id++;
    m_id = id;
    std::cout << "PropertiesGroupData created. id=" << id << std::endl;
#endif
}

PropertiesGroupData::PropertiesGroupData(const QString &name,
                                         const QString &inheritsClass) :
    p_className(name),
    p_inherits(inheritsClass),
    p_typeInderitsInfomation(0),
    m_used(1),
    p_readFunctionIsInline(true),
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
    p_className(v.p_className),
    p_inherits(v.p_inherits),
    p_statementsAfterWriteProperty(v.p_statementsAfterWriteProperty),
    p_statementsMiddleWriteProperty(v.p_statementsMiddleWriteProperty),
    p_statementsStartWriteProperty(v.p_statementsStartWriteProperty),
    p_typeInderitsInfomation(v.p_typeInderitsInfomation),
    m_used(1),
    p_readFunctionIsInline(v.p_readFunctionIsInline),
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
