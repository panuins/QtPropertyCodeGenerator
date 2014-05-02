#include "propertydata.h"
#ifdef DEBUG_PROPERTYS_COW
#include <iostream>
static int id = -1;
#endif

PropertyData::PropertyData() :
    p_docDetail(""),
    p_docName(""),
    p_name(""),
    p_type(QVariant::typeToName(QVariant::UserType)),
    p_typeStringName(""),
    p_revision(PropertyDefaultRevision),
    m_used(1),
    p_constant(PropertyDefaultConstant),
    p_designable(PropertyDefaultDesignable),
    p_enabled(PropertyDefaultEnabled),
    p_final(PropertyDefaultFinal),
    p_member(PropertyDefaultMember),
    p_notify(PropertyDefaultNotify),
    p_read(PropertyDefaultRead),
    p_reset(PropertyDefaultReset),
    p_scriptable(PropertyDefaultScriptable),
    p_stored(PropertyDefaultStored),
    p_user(PropertyDefaultUser),
    p_write(PropertyDefaultWrite)
{
#ifdef DEBUG_PROPERTYS_COW
    id++;
    m_id = id;
    std::cout << "PropertyData created. id=" << id << std::endl;
#endif
}

PropertyData::PropertyData(//const QString &className,
                           const QString &name,
                           const QString &type,
                           const QString &typeStringName) :
    //p_className(className),
    p_docDetail(""),
    p_docName(""),
    p_name(name),
    p_type(type),
    p_typeStringName(typeStringName),
    p_revision(PropertyDefaultRevision),
    m_used(1),
    p_constant(PropertyDefaultConstant),
    p_designable(PropertyDefaultDesignable),
    p_enabled(PropertyDefaultEnabled),
    p_final(PropertyDefaultFinal),
    p_member(PropertyDefaultMember),
    p_notify(PropertyDefaultNotify),
    p_read(PropertyDefaultRead),
    p_reset(PropertyDefaultReset),
    p_scriptable(PropertyDefaultScriptable),
    p_stored(PropertyDefaultStored),
    p_user(PropertyDefaultUser),
    p_write(PropertyDefaultWrite)
{
#ifdef DEBUG_PROPERTYS_COW
    id++;
    m_id = id;
    std::cout << "PropertyData created. id=" << m_id << std::endl;
#endif
}

PropertyData::PropertyData(const PropertyData &p) :
    p_defaultValue(p.p_defaultValue),
    p_docDetail(p.p_docDetail),
    p_docName(p.p_docName),
    p_name(p.p_name),
    p_type(p.p_type),
    p_typeStringName(p.p_typeStringName),
    p_revision(p.p_revision),
    m_used(1),
    p_constant(p.p_constant),
    p_designable(p.p_designable),
    p_enabled(p.p_enabled),
    p_final(p.p_final),
    p_member(p.p_member),
    p_notify(p.p_notify),
    p_read(p.p_read),
    p_reset(p.p_reset),
    p_scriptable(p.p_scriptable),
    p_stored(p.p_stored),
    p_user(p.p_user),
    p_write(p.p_write)
{
#ifdef DEBUG_PROPERTYS_COW
    id++;
    m_id = id;
    std::cout << "PropertyData created. id=" << id << std::endl;
#endif
}

PropertyData::~PropertyData()
{
#ifdef DEBUG_PROPERTYS_COW
    std::cout << "PropertyData removed. id=" << id << std::endl;
#endif
}

/*PropertyData &PropertyData::operator=(const PropertyData &p)
{
    p_name = p.p_name;
    p_docName = p.p_docName;
    p_docDetail = p.p_docDetail;
    p_type = p.p_type;
    p_typeStringName = p.p_typeStringName;
    p_revision = p.p_revision;
    p_member = p.p_member;
    p_read = p.p_read;
    p_write = p.p_write;
    p_reset = p.p_reset;
    p_notify = p.p_notify;
    p_designable = p.p_designable;
    p_scriptable = p.p_scriptable;
    p_stored = p.p_stored;
    p_user = p.p_user;
    p_constant = p.p_constant;
    p_final = p.p_final;
    p_enabled = p.p_enabled;
    return *this;
}*/
