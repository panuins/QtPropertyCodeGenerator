#ifndef PROPERTIESGROUPDATA_H
#define PROPERTIESGROUPDATA_H

#include "enumtype.h"
#include "property.h"
#include <QList>
#include <QStringList>
#define DEBUG_PROPERTIESGROUPS_COW

class PropertiesGroupData
{
public:
    PropertiesGroupData();
    PropertiesGroupData(const QString &name, const QString &inheritsClass);
    PropertiesGroupData(const PropertiesGroupData &v);
    ~PropertiesGroupData();
    //PropertiesGroupData &operator=(const PropertiesGroupData &v);

    QList<Property> m_properties;
    QList<EnumType> m_enums;
    QStringList p_typeOrder;
    QString p_className;
    QString p_inherits;
    QString p_statementsAfterWriteProperty;
    QString p_statementsMiddleWriteProperty;
    QString p_statementsStartWriteProperty;
    int p_typeInderitsInfomation;
    int m_used;
#ifdef DEBUG_PROPERTIESGROUPS_COW
    int m_id;
#endif
    bool p_readFunctionIsInline;
    bool p_writeFunctionEmitSignal;
    bool p_writeFunctionIsInline;
};

#endif // PROPERTIESGROUPDATA_H
