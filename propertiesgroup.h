#ifndef PROPERTIESGROUP_H
#define PROPERTIESGROUP_H
#include "property.h"
#include <QList>
#include <QStringList>

class PropertiesGroup
{
public:
    enum TypeInheritsInformation
    {
        inherits_None = 0,
        inherits_QObject,
        inherits_QWidget,
        inherits_QQuickItem,
    };

    PropertiesGroup();
    PropertiesGroup(const QString &name, const QString &inheritsClass);
    PropertiesGroup(const PropertiesGroup &v);
    ~PropertiesGroup();
    PropertiesGroup &operator=(const PropertiesGroup &v);
    Property &operator[](int i);

    void append(const Property &var);
    void append(const QList<Property> &var);
    Property at(int var) const;
    void clear();
    int find(const QString &name) const;
    void insert(int vari, const Property &varp);
    void removeAt(int var);
    int size() const;
    QStringList propertiesName() const;
    void sort();

    QString className() const;
    QString inherits() const;
    QList<Property> properties() const;
    bool readFunctionIsInline() const;
    QString statementsAfterWriteProperty() const;
    QString statementsMiddleWriteProperty() const;
    QString statementsStartWriteProperty() const;
    TypeInheritsInformation typeInderitsInfomation() const;
    bool writeFunctionEmitSignal() const;
    bool writeFunctionIsInline() const;

    void setClassName(const QString &var);
    void setInherits(const QString &var);
    void setProperties(const QList<Property> &var);
    void setReadFunctionIsInline(const bool &var);
    void setStatementsAfterWriteProperty(const QString &var);
    void setStatementsMiddleWriteProperty(const QString &var);
    void setStatementsStartWriteProperty(const QString &var);
    void setTypeInderitsInfomation(const TypeInheritsInformation &var);
    void setWriteFunctionEmitSignal(const bool &var);
    void setWriteFunctionIsInline(const bool &var);

    QString generateQPropertyDeclear() const;
    QString generateReadDeclear() const;
    QString generateWriteDeclear() const;
    QString generateSignalDeclear() const;
    QString generateMemberVariableDeclear() const;

    QString generateReadFunctionDefine() const;
    QString generateWriteFunctionDefine() const;

private:
    QList<Property> m_properties;
    QString p_className;
    QString p_inherits;
    QString p_statementsAfterWriteProperty;
    QString p_statementsMiddleWriteProperty;
    QString p_statementsStartWriteProperty;
    TypeInheritsInformation p_typeInderitsInfomation;
    bool p_readFunctionIsInline;
    bool p_writeFunctionEmitSignal;
    bool p_writeFunctionIsInline;
};

inline Property &PropertiesGroup::operator[](int i)
{
    return m_properties[i];
}

inline void PropertiesGroup::append(const Property &var)
{
    m_properties.append(var);
}

inline void PropertiesGroup::append(const QList<Property> &var)
{
    m_properties.append(var);
}

inline Property PropertiesGroup::at(int var) const
{
    return m_properties.at(var);
}

inline void PropertiesGroup::clear()
{
    m_properties.clear();
}

inline void PropertiesGroup::insert(int vari, const Property &varp)
{
    m_properties.insert(vari, varp);
}

inline void PropertiesGroup::removeAt(int var)
{
    m_properties.removeAt(var);
}

inline int PropertiesGroup::size() const
{
    return m_properties.size();
}

inline QString PropertiesGroup::className() const
{
    return p_className;
}

inline QString PropertiesGroup::inherits() const
{
    return p_inherits;
}

inline QList<Property> PropertiesGroup::properties() const
{
    return m_properties;
}

inline bool PropertiesGroup::readFunctionIsInline() const
{
    return p_readFunctionIsInline;
}

inline QString PropertiesGroup::statementsAfterWriteProperty() const
{
    return p_statementsAfterWriteProperty;
}

inline QString PropertiesGroup::statementsMiddleWriteProperty() const
{
    return p_statementsMiddleWriteProperty;
}

inline QString PropertiesGroup::statementsStartWriteProperty() const
{
    return p_statementsStartWriteProperty;
}

inline PropertiesGroup::TypeInheritsInformation
PropertiesGroup::typeInderitsInfomation() const
{
    return p_typeInderitsInfomation;
}

inline bool PropertiesGroup::writeFunctionEmitSignal() const
{
    return p_writeFunctionEmitSignal;
}

inline bool PropertiesGroup::writeFunctionIsInline() const
{
    return p_writeFunctionIsInline;
}

inline void PropertiesGroup::setClassName(const QString &var)
{
    p_className = var;
}

inline void PropertiesGroup::setInherits(const QString &var)
{
    p_inherits = var;
}

inline void PropertiesGroup::setProperties(const QList<Property> &var)
{
    m_properties = var;
}

inline void PropertiesGroup::setReadFunctionIsInline(const bool &var)
{
    p_readFunctionIsInline = var;
}

inline void PropertiesGroup::setStatementsAfterWriteProperty(const QString &var)
{
    p_statementsAfterWriteProperty = var;
}

inline void PropertiesGroup::setStatementsMiddleWriteProperty(const QString &var)
{
    p_statementsMiddleWriteProperty = var;
}

inline void PropertiesGroup::setStatementsStartWriteProperty(const QString &var)
{
    p_statementsStartWriteProperty = var;
}

inline void PropertiesGroup::setTypeInderitsInfomation(
        const PropertiesGroup::TypeInheritsInformation &var)
{
    p_typeInderitsInfomation = var;
}

inline void PropertiesGroup::setWriteFunctionEmitSignal(const bool &var)
{
    p_writeFunctionEmitSignal = var;
}

inline void PropertiesGroup::setWriteFunctionIsInline(const bool &var)
{
    p_writeFunctionIsInline = var;
}
#endif // PROPERTIESGROUP_H
