#ifndef CLASSSETTINGS_H
#define CLASSSETTINGS_H
/*#include <QString>

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
    QList<Property> properties() const;
    bool readFunctionIsInline() const;
    TypeInheritsInformation typeInderitsInfomation() const;
    bool writeFunctionEmitSignal() const;
    bool writeFunctionIsInline() const;

    void setClassName(const QString &var);
    void setInherits(const QString &var);
    void setProperties(const QList<Property> &var);
    void setReadFunctionIsInline(const bool &var);
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
    TypeInheritsInformation p_typeInderitsInfomation;
    bool p_readFunctionIsInline;
    bool p_writeFunctionEmitSignal;
    bool p_writeFunctionIsInline;
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

inline bool ClassSettings::readFunctionIsInline() const
{
    return p_readFunctionIsInline;
}

inline ClassSettings::TypeInheritsInformation ClassSettings::typeInderitsInfomation() const
{
    return p_typeInderitsInfomation;
}

inline bool ClassSettings::writeFunctionEmitSignal() const
{
    return p_writeFunctionEmitSignal;
}

inline bool ClassSettings::writeFunctionIsInline() const
{
    return p_writeFunctionIsInline;
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

inline void ClassSettings::setReadFunctionIsInline(const bool &var)
{
    p_readFunctionIsInline = var;
}

inline void ClassSettings::setTypeInderitsInfomation(
        const ClassSettings::TypeInheritsInformation &var)
{
    p_typeInderitsInfomation = var;
}

inline void ClassSettings::setWriteFunctionEmitSignal(const bool &var)
{
    p_writeFunctionEmitSignal = var;
}

inline void ClassSettings::setWriteFunctionIsInline(const bool &var)
{
    p_writeFunctionIsInline = var;
}*/
#endif // CLASSSETTINGS_H
