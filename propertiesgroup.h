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
        inherits_QWidget_associateWidthUiFile,
    };

    PropertiesGroup();
    PropertiesGroup(const QString &name, const QString &inheritsClass);
    PropertiesGroup(const PropertiesGroup &v);
    PropertiesGroup(const PropertiesGroupData &v);
    ~PropertiesGroup();
    PropertiesGroup &operator=(const PropertiesGroup &v);
    Property &operator[](int i);

    Property at(int var) const;
    QString className() const;
    QList<EnumType> enums() const;
    QStringList enumsName() const;
    QStringList existType() const;
    int find(const QString &name) const;
    QString inherits() const;
    QString parentClass() const;
    QList<Property> properties() const;
    QList<Property> propertiesIsType(const QString &var) const;
    QStringList propertiesName() const;
    bool readFunctionIsInline() const;
    int size() const;
    QString statementsAfterWriteProperty() const;
    QString statementsMiddleWriteProperty() const;
    QString statementsStartWriteProperty() const;
    TypeInheritsInformation typeInderitsInfomation() const;
    QStringList typeOrder() const;
    bool writeFunctionEmitSignal() const;
    bool writeFunctionIsInline() const;

    void append(const Property &var);
    void append(const QList<Property> &var);
    void clear();
    void insert(int vari, const Property &varp);
    void removeAt(int var);
    void setClassName(const QString &var);
    void setEnums(const QList<EnumType> &var);
    void setInherits(const QString &var);
    void setProperties(const QList<Property> &var);
    void setReadFunctionIsInline(const bool &var);
    void setStatementsAfterWriteProperty(const QString &var);
    void setStatementsMiddleWriteProperty(const QString &var);
    void setStatementsStartWriteProperty(const QString &var);
    void setTypeInderitsInfomation(const TypeInheritsInformation &var);
    void setTypeOrder(const QStringList &var);
    void setWriteFunctionEmitSignal(const bool &var);
    void setWriteFunctionIsInline(const bool &var);
    void sort();

    QString generateEnumsDeclear() const;
    QString generateQPropertyDeclear() const;
    QString generateReadDeclear() const;
    QString generateWriteDeclear() const;
    QString generateSignalDeclear() const;
    QString generateMemberVariableDeclear() const;

    QString generateReadFunctionDefine() const;
    QString generateWriteFunctionDefine() const;

    QString argumentNameOfThisClass() const;
    QString headerFileContent() const;
    QString headerFileIncludeStatements() const;
    QString headerFileMarco() const;
    QString headerFileName() const;
    QString qOjbectBasedParentArgumentName() const;
    QString sourceFileAssignmentOperator() const;
    QString sourceFileContent() const;
    QString sourceFileCopyConstructor() const;
    QString sourceFileDefaultConstructor() const;
    QString sourceFileDestructor() const;
    QString sourceFileName() const;

private:
    void beforeWrite();

    PropertiesGroupData *m_d;
};
#include "propertiesgroupInlineFunctions.h"
#endif // PROPERTIESGROUP_H
