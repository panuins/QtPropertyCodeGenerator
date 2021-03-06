/*****************************************************************************
 * classsettings.h:
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
#ifndef CLASSSETTINGS_H
#define CLASSSETTINGS_H
#include "propertiesgroup.h"
#include "publicType.h"
#include <QPair>
#include <QString>
#include <QStringList>

class ClassSettings
{
public:
    enum TypeInheritsInformation
    {
        inherits_None = 0,
        inherits_QObject,
        inherits_QWidget,
        inherits_QQuickItem,
        inherits_QWidget_AssociateWithUiFile,
        inherits_QWindow,
        inherits_None_COW,
    };

    /*class const_Iterator
    {
    public:
        const_Iterator();
        const_Iterator(const const_Iterator &other);
        //const_Iterator(const iterator &other);
        bool operator!=(const const_Iterator &other) const;
        const Property &operator*() const;
        const_Iterator operator+(int i) const;
        const_Iterator &operator++();
        const_Iterator operator++(int);
        const_Iterator &operator+=(int i);
        const_Iterator operator-(int i) const;
        int operator-(const_Iterator other) const;
        const_Iterator &operator--();
        const_Iterator operator--(int);
        const_Iterator &operator-=(int i);
        const Property *operator->() const;
        bool operator<(const const_Iterator &other) const;
        bool operator<=(const const_Iterator &other) const;
        bool operator==(const const_Iterator &other) const;
        bool operator>(const const_Iterator &other) const;
        bool operator>=(const const_Iterator &other) const;
        const Property &operator[](int i) const;

    private:
        //QMap<QList<Property>::const_iterator, QList<PropertiesGroup>::const_iterator> m_i;
        QList<QPair<QList<Property>::const_iterator, QList<PropertiesGroup>::const_iterator> > m_data;
        //QStringList m_nameList;
        //QList<QList<Property>::const_iterator> m_pi;
        //QList<QList<PropertiesGroup>::const_iterator> m_pgi;
        QList<QPair<QList<Property>::const_iterator, QList<PropertiesGroup>::const_iterator> >::const_iterator m_i;
        ClassSettings *m_classSettings;

        friend const_Iterator ClassSettings::begin() const;
    };*/

    ClassSettings();
    ClassSettings(const QString &name, const QString &inheritsClass);
    ClassSettings(const ClassSettings &v);
    ~ClassSettings();
    ClassSettings &operator=(const ClassSettings &v);
    PropertiesGroup &operator[](int i);

    const PropertiesGroup &at(int i) const;
    //const_Iterator begin() const;
    QString className() const;
    QString docBrief() const;
    QString docDetail() const;
    QString docName() const;
    QString inherits() const;
    QStringList existType() const;
    int findGroup(const QString &name) const;
    int findGroupByPropertyName(const QString &name) const;
    Property findProperty(const QString &name) const;
    bool generatePreventReentrantCode() const;
    QString parentClass() const;
    const QList<PropertiesGroup> &propertiesGroups() const;
    QList<Property> propertiesIsType(const QString &var) const;
    QStringList propertiesGroupsName() const;
    QStringList propertiesName() const;
    QString replacedDocBrief() const;
    QString replacedDocDetail() const;
    QString replacedDocName() const;
    bool signalIsValid() const;
    int size() const;
    bool sortAllProperties() const;
    TypeInheritsInformation typeInheritsInfomation() const;
    QStringList typeOrder() const;

    void append(const PropertiesGroup &var);
    void append(const QList<PropertiesGroup> &var);
    void clear();
    void removeAt(int i);
    void setClassName(const QString &var);
    void setDocBrief(const QString &var);
    void setDocDetail(const QString &var);
    void setDocName(const QString &var);
    void setGeneratePreventReentrantCode(const bool &var);
    void setInherits(const QString &var);
    void setPropertiesGroups(const QList<PropertiesGroup> &var);
    void setSortAllProperties(bool var);
    void setTypeInheritsInfomation(const TypeInheritsInformation &var);
    void setTypeOrder(const QStringList &var);
    void sort();
    void updateTypeOrder();

    QString generateCode(QString (*f)(Property, PropertiesGroup),
                         bool conditionGroup,
                         bool conditionProperty) const;

    QString generateEnumsDeclear() const;
    QString generateQPropertyDeclear() const;
    QString generateReadDeclear() const;
    QString generateResetDeclear() const;
    QString generateWriteDeclear() const;
    QString generateSignalDeclear() const;
    QString generateMemberVariableDeclear() const;
    QString generateDetachedDocCommentFunctions() const;
    QString generateDetachedDocCommentMemberVariable() const;
    QString generateDetachedDocCommentProperties() const;

    QString generateReadFunctionDefine() const;
    QString generateResetFunctionDefine() const;
    QString generateWriteFunctionDefine() const;
    QString generateFunctionsDefine() const;
    QString generateInlineReadFunctionDefine() const;
    QString generateInlineResetFunctionDefine() const;
    QString generateInlineWriteFunctionDefine() const;
    QString generateInlineFunctionsDefine() const;

    QString docCommentAssignmentOperator() const;
    QString docCommentClass() const;
    QString docCommentCopyConstructor() const;
    QString docCommentDefaultConstructor() const;
    QString docCommentDestructor() const;
    QString docCommentFileHeader(const QString &fileName,
                                 const QString &brief = QString(""),
                                 const QString &detail = QString("")) const;
    QString headerFileDocCommentHeader() const;
    QString headerFileDocCommentHeaderBrief() const;
    QString headerFileDocCommentHeaderDetail() const;
    QString sourceFileDocCommentHeader() const;
    QString sourceFileDocCommentHeaderBrief() const;
    QString sourceFileDocCommentHeaderDetail() const;

    QString argumentNameOfThisClass() const;
    QString classDefine() const;
    QString qojbectBasedParentArgumentName() const;

    QString includeLocalHeaderFileStatement(const QString &fileName) const;
    QString includeSystemHeaderFileStatement(const QString &fileName) const;

    QString headerFileContent() const;
    QString headerFileIncludeStatements() const;
    QString headerFileMarco() const;
    QString headerFileName() const;
    QString sourceFileAssignmentOperator() const;
    QString sourceFileContent() const;
    QString sourceFileCopyConstructor() const;
    QString sourceFileDefaultConstructor() const;
    QString sourceFileDestructor() const;
    QString sourceFileName() const;

    QDomElement toXMLNode(QDomDocument *doc) const;
    static ClassSettings fromXMLNode(const QDomElement &element);

private:
    QList<PropertiesGroup> m_propertiesGroups;
    QList<EnumType> m_enums;
    QStringList p_typeOrder;
    QString p_className;
    QString p_docBrief;
    QString p_docDetail;
    QString p_docName;
    QString p_inherits;
    //DocCommentPolicy p_docCommentPolicy;
    TypeInheritsInformation p_typeInheritsInfomation;
    bool p_generatePreventReentrantCode;
    bool p_sortAllProperties;
};

#include "classsettingsInlineFunctions.h"

#endif // CLASSSETTINGS_H
