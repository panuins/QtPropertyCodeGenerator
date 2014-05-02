#ifndef PROPERTY_H
#define PROPERTY_H
#include "propertydata.h"
//#define DEBUG_PROPERTYS_COW_DETAIL

class Property
{
public:
    Property();
    Property(//const QString &className,
             const QString &name,
             const QString &type,
             const QString &typeStringName = QString());
    Property(const Property &p);
    Property(const PropertyData &p);
    ~Property();
    Property &operator=(const Property &p);
    bool operator==(const Property &p) const;
    bool operator!=(const Property &p) const;

    //QString className() const;
    bool constant() const;
    QVariant defaultValue() const;
    bool designable() const;
    QString docDetail() const;
    QString docName() const;
    bool enabled() const;
    bool final() const;
    bool member() const;
    QString name() const;
    bool notify() const;
    QString realTypeName() const;
    bool read() const;
    bool reset() const;
    int revision() const;
    bool scriptable() const;
    bool stored() const;
    const QString & type() const;
    QString typeStringName() const;
    QString typePrefix() const;
    bool user() const;
    bool write() const;

    //void setClassName(const QString &name);
    void setConstant(bool b);
    void setDefaultValue(const QVariant &var);
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

    QString toString() const;
    QString qPropertyString() const;

    QString readFunctionName() const;
    QString writeFunctionName() const;
    QString signalName() const;
    QString memberVariableName() const;

    QString readDeclear() const;
    QString writeDeclear() const;
    QString signalDeclear() const;
    QString memberVariableDeclear() const;

    QString initialToDefaultValueStatement() const;
    QString initialToSpecifyValueStatement(const QString &str) const;

    QString readFunctionDefine(const QString &className,
                               bool isInline = true) const;
    QString writeFunctionDefine(const QString &className,
                                const QString &strBeforSetValue = QString(""),
                                const QString &strBetweenSetValueAndEmit = QString(""),
                                const QString &strAfterEmit = QString(""),
                                bool emitSignal = true,
                                bool isInline = false) const;

    static Property fromString(const QString &str);

private:
    void beforeWrite();
    static QString boolToStr(bool b);
    static bool strTobool(const QString &str);
    static QString replaceFisrtLetterToLower(const QString &str);
    static QString replaceFisrtLetterToUpper(const QString &str);
    QString writeFunctionArgumentName() const;

    PropertyData *m_d;
};
#include "propertyInlineFunctions.h"
#endif // PROPERTY_H
