#ifndef CLASSSETTINGS_H
#define CLASSSETTINGS_H
#include "propertiesgroup.h"
#include <QString>

class ClassSettings
{
public:
    enum TypeInheritsInformation
    {
        inherits_None = 0,
        inherits_QObject,
        inherits_QWidget,
        inherits_QQuickItem,
    };

    ClassSettings();
    ClassSettings(const QString &name, const QString &inheritsClass);
    ClassSettings(const ClassSettings &v);
    ~ClassSettings();
    ClassSettings &operator=(const ClassSettings &v);

    QString className() const;
    QString inherits() const;
    TypeInheritsInformation typeInderitsInfomation() const;
    QList<Property> properties() const;

    void setClassName(const QString &var);
    void setInherits(const QString &var);
    void setTypeInderitsInfomation(const TypeInheritsInformation &var);
    void setProperties(const QList<Property> &var);

    /*QString generateQPropertyDeclear() const;
    QString generateReadDeclear() const;
    QString generateWriteDeclear() const;
    QString generateSignalDeclear() const;
    QString generateMemberVariableDeclear() const;

    QString generateReadFunctionDefine() const;
    QString generateWriteFunctionDefine() const;*/

private:
    QList<Property> m_properties;
    QString p_className;
    QString p_inherits;
    TypeInheritsInformation p_typeInderitsInfomation;
};

inline QString ClassSettings::className() const
{
    return p_className;
}

inline QString ClassSettings::inherits() const
{
    return p_inherits;
}

inline QList<Property> ClassSettings::properties() const
{
    return m_properties;
}

inline ClassSettings::TypeInheritsInformation
ClassSettings::typeInderitsInfomation() const
{
    return p_typeInderitsInfomation;
}

inline void ClassSettings::setClassName(const QString &var)
{
    p_className = var;
}

inline void ClassSettings::setInherits(const QString &var)
{
    p_inherits = var;
}

inline void ClassSettings::setProperties(const QList<Property> &var)
{
    m_properties = var;
}

inline void ClassSettings::setTypeInderitsInfomation(
        const ClassSettings::TypeInheritsInformation &var)
{
    p_typeInderitsInfomation = var;
}

#endif // CLASSSETTINGS_H
