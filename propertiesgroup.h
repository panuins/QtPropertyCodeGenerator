#ifndef PROPERTIESGROUP_H
#define PROPERTIESGROUP_H
#include "propertiesgroupdata.h"
#define DEBUG_PROPERTIESGROUPS_COW_DETAIL

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
    PropertiesGroup(const PropertiesGroupData &v);
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

    //QString baseClass() const;
    QString parentClass() const;
    QString headerFileName() const;
    QString headerFileMarco() const;
    QString headerFileContent() const;
    QString sourceFileName() const;
    QString sourceFileDefaultInitial() const;
    QString sourceFileCopyInitial() const;
    QString sourceFileContent() const;

private:
    void beforeWrite();

    PropertiesGroupData *m_d;
};
#include "propertiesgroupInlineFunctions.h"
#endif // PROPERTIESGROUP_H
