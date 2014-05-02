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
    PropertyData(//const QString &className,
                 const QString &name,
                 const QString &type,
                 const QString &typeStringName = QString(""));
    PropertyData(const PropertyData &p);
    ~PropertyData();
    //PropertyData &operator=(const PropertyData &p);

    //QString p_className;
    QVariant p_defaultValue;
    QString p_docDetail;
    QString p_docName;
    QString p_name;
    QString p_type;
    QString p_typeStringName;
    int p_revision;
    int m_used;
#ifdef DEBUG
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
