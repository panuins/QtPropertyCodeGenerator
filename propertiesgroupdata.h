/*****************************************************************************
 * propertiesgroupdata.h:
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
#ifndef PROPERTIESGROUPDATA_H
#define PROPERTIESGROUPDATA_H

#include "enumtype.h"
#include "property.h"
#include <QList>
#include <QStringList>
#define DEBUG_PROPERTIESGROUPS_COW

#define PropertyGroupDefaultRevision 0
#define PropertyGroupDefaultDesignable true
#define PropertyGroupDefaultScriptable true
#define PropertyGroupDefaultStored true
#define PropertyGroupDefaultUser false
#define PropertyGroupDefaultConstant false
#define PropertyGroupDefaultFinal false

class PropertiesGroupData
{
public:
    PropertiesGroupData();
    PropertiesGroupData(const QString &name);
    PropertiesGroupData(const PropertiesGroupData &v);
    ~PropertiesGroupData();

    QList<Property> m_properties;
    QString p_name;
    QString p_statementsInReadProperty;
    QString p_statementsAfterResetProperty;
    QString p_statementsBeforeResetProperty;
    QString p_statementsAfterWriteProperty;
    QString p_statementsBeforeWriteProperty;
    QString p_statementsMiddleWriteProperty;
    int m_used;
#ifdef DEBUG_PROPERTIESGROUPS_COW
    int m_id;
#endif
    bool p_enabled;
    bool p_readFunctionIsInline;
    bool p_resetFunctionIsInline;
    bool p_writeFunctionEmitSignal;
    bool p_writeFunctionIsInline;
};

#endif // PROPERTIESGROUPDATA_H
