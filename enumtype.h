#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include <QList>
#include <QString>
#include <QStringList>

class EnumType
{
public:
    EnumType();
    EnumType(const QString &name);
    EnumType(const EnumType &var);
    ~EnumType();

    bool enabled() const;
    int firstValue() const;
    QString name() const;
    QString prefix() const;
    QString suffix() const;
    QStringList vars() const;

    void setEnabled(bool var);
    void setFirstValue(int var);
    void setName(const QString &var);
    void setPrefix(const QString &var);
    void setSuffix(const QString &var);
    void setvars(const QStringList &var);

    QStringList varList() const;
    QString declear() const;
    static QStringList parseEnumDefinesName(const QString &var);

private:
    QString p_name;
    QString p_prefix;
    QString p_suffix;
    QStringList p_vars;
    int p_firstValue;
    bool p_enabled;
};

inline bool EnumType::enabled() const
{
    return p_enabled;
}

inline int EnumType::firstValue() const
{
    return p_firstValue;
}

inline QString EnumType::name() const
{
    return p_name;
}

inline QString EnumType::prefix() const
{
    return p_prefix;
}

inline QString EnumType::suffix() const
{
    return p_suffix;
}

inline QStringList EnumType::vars() const
{
    return p_vars;
}

inline void EnumType::setEnabled(bool var)
{
    p_enabled = var;
}

inline void EnumType::setFirstValue(int var)
{
    p_firstValue = var;
}

inline void EnumType::setName(const QString &var)
{
    p_name = var;
}

inline void EnumType::setPrefix(const QString &var)
{
    p_prefix = var;
}

inline void EnumType::setSuffix(const QString &var)
{
    p_suffix = var;
}

inline void EnumType::setvars(const QStringList &var)
{
    p_vars = var;
}

#endif // ENUMTYPE_H
