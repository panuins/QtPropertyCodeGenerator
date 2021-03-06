/*****************************************************************************
 * propertydata.h:
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
#ifndef PROPERTYDATA_H
#define PROPERTYDATA_H

#include <QList>
#include <QString>
#include <QVariant>
#define DEBUG_PROPERTYS_COW

#define PropertyDefaultMember false
#define PropertyDefaultRead true
#define PropertyDefaultWrite true
#define PropertyDefaultReset false
#define PropertyDefaultNotify true
#define PropertyDefaultRevision 0
#define PropertyDefaultDesignable true
#define PropertyDefaultScriptable true
#define PropertyDefaultStored true
#define PropertyDefaultUser false
#define PropertyDefaultConstant false
#define PropertyDefaultFinal false
#define PropertyDefaultEnabled true

class PropertyData
{
public:
    PropertyData();
    PropertyData(const QString &name,
                 const QString &type,
                 const QString &typeStringName = QString(""));
    PropertyData(const PropertyData &p);
    ~PropertyData();

    QVariant p_defaultValue;
    QString p_docBrief;
    QString p_docDetail;
    QString p_docName;
    QString p_name;
    QString p_type;
    QString p_typeStringName;
    int p_revision;
    int m_used;
#ifdef DEBUG_PROPERTYS_COW
    int m_id;
#endif
    bool p_constant;
    bool p_designable;
    bool p_enabled;
    bool p_final;
    bool p_member;
    bool p_notify;
    bool p_read;
    bool p_reset;
    bool p_scriptable;
    bool p_stored;
    bool p_user;
    bool p_write;
};

#endif // PROPERTYDATA_H
