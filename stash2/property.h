#ifndef PROPERTY_H
#define PROPERTY_H
#include <QList>
#include <QString>
#include <QVariant>

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

class Property
{
public:
    Property();
    Property(//const QString &className,
             const QString &name,
             const QString & type,
             const QString &typeStringName = QString());
    Property(const Property &p);
    Property &operator=(const Property &p);
    bool operator==(const Property &p) const;
    bool operator!=(const Property &p) const;

    //QString className() const;
    bool constant() const;
    bool designable() const;
    QString docDetail() const;
    QString docName() const;
    bool enabled() const;
    bool final() const;
    bool member() const;
    QString name() const;
    bool notify() const;
    bool read() const;
    QString realTypeName() const;
    bool reset() const;
    int revision() const;
    bool scriptable() const;
    bool stored() const;
    const QString & type() const;
    QString typeStringName() const;
    QString typePrefix() const;
    bool user() const;
    bool write() const;

    QString toString() const;
    //bool writeToSql(QSqlQuery &query);
    QString qPropertyString() const;

    QString readFunctionName() const;
    QString writeFunctionName() const;
    QString signalName() const;
    QString memberVariableName() const;

    QString readDeclear() const;
    QString writeDeclear() const;
    QString signalDeclear() const;
    QString memberVariableDeclear() const;

    QString readFunctionDefine(const QString &className,
                               bool isInline = true) const;
    QString writeFunctionDefine(const QString &className,
                                const QString &strBeforSetValue = QString(""),
                                const QString &strBetweenSetValueAndEmit = QString(""),
                                const QString &strAfterEmit = QString(""),
                                bool emitSignal = true,
                                bool isInline = false) const;

    //void setClassName(const QString &name);
    void setConstant(bool b);
    void setDesignable(bool b);
    void setDocDetail(const QString &name);
    void setDocName(const QString &name);
    void setEnabled(bool b);
    void setFinal(bool b);
    void setMember(bool b);
    void setName(const QString &name);
    void setNotify(bool b);
    void setRead(bool b);
    void setReset(bool b);
    void setRevision(int n);
    void setScriptable(bool b);
    void setStored(bool b);
    void setType(const QString & type);
    void setTypeStringName(const QString &name);
    void setUser(bool b);
    void setWrite(bool b);

    static Property fromString(const QString &str);

private:
    QString writeFunctionArgumentName() const;
    //QString m_className;
    QString m_docDetail;
    QString m_docName;
    QString m_name;
    QString m_type;
    QString m_typeStringName;
    int m_revision;
    bool m_constant;
    bool m_designable;
    bool m_enabled;
    bool m_final;
    bool m_member;
    bool m_notify;
    bool m_read;
    bool m_reset;
    bool m_scriptable;
    bool m_stored;
    bool m_user;
    bool m_write;
};

inline bool Property::constant() const
{
    return m_constant;
}

inline bool Property::designable() const
{
    return m_designable;
}

inline QString Property::docDetail() const
{
    return m_docDetail;
}

inline QString Property::docName() const
{
    return m_docName;
}

inline bool Property::enabled() const
{
    return m_enabled;
}

inline bool Property::final() const
{
    return m_final;
}
inline bool Property::member() const
{
    return m_member;
}

inline QString Property::name() const
{
    return m_name;
}

inline bool Property::notify() const
{
    return m_notify;
}

inline bool Property::read() const
{
    return m_read;
}

inline QString Property::realTypeName() const
{
    if (m_typeStringName.isEmpty())
    {
        return m_type;
    }
    else
    {
        return m_typeStringName;
    }
}

inline bool Property::reset() const
{
    return m_reset;
}

inline int Property::revision() const
{
    return m_revision;
}

inline bool Property::scriptable() const
{
    return m_scriptable;
}

inline bool Property::stored() const
{
    return m_stored;
}

inline const QString & Property::type() const
{
    return m_type;
}

inline QString Property::typeStringName() const
{
    return m_typeStringName;
}

inline bool Property::user() const
{
    return m_user;
}

inline bool Property::write() const
{
    return m_write;
}

inline void Property::setName(const QString &name)
{
    m_name = name;
}

inline void Property::setType(const QString & type)
{
    m_type = type;
}

inline void Property::setTypeStringName(const QString &name)
{
    m_typeStringName = name;
}

inline void Property::setDocName(const QString &name)
{
    m_docName = name;
}

inline void Property::setDocDetail(const QString &name)
{
    m_docDetail = name;
}

inline void Property::setMember(bool b)
{
    m_member = b;
}

inline void Property::setRead(bool b)
{
    m_read = b;
}

inline void Property::setWrite(bool b)
{
    m_write = b;
}

inline void Property::setReset(bool b)
{
    m_reset = b;
}

inline void Property::setNotify(bool b)
{
    m_notify = b;
}

inline void Property::setRevision(int n)
{
    m_revision = n;
}

inline void Property::setDesignable(bool b)
{
    m_designable = b;
}

inline void Property::setScriptable(bool b)
{
    m_scriptable = b;
}

inline void Property::setStored(bool b)
{
    m_stored = b;
}

inline void Property::setUser(bool b)
{
    m_user = b;
}

inline void Property::setConstant(bool b)
{
    m_constant = b;
}

inline void Property::setEnabled(bool b)
{
    m_enabled = b;
}

inline void Property::setFinal(bool b)
{
    m_final = b;
}

#endif // PROPERTY_H
