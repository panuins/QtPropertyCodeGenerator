/*****************************************************************************
 * propertiesgroup.h:
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
#ifndef PROPERTIESGROUP_H
#define PROPERTIESGROUP_H
#include "propertiesgroupdata.h"
//#define DEBUG_PROPERTIESGROUPS_COW_DETAIL

class PropertiesGroup
{
public:
    PropertiesGroup();
    PropertiesGroup(const QString &name);
    PropertiesGroup(const PropertiesGroup &v);
    PropertiesGroup(const PropertiesGroupData &v);
    ~PropertiesGroup();
    PropertiesGroup &operator=(const PropertiesGroup &v);
    Property &operator[](int i);

    const Property &at(int i) const;
    bool enabled() const;
    int find(const QString &name) const;
    QString name() const;
    const QList<Property> &properties() const;
    QStringList propertiesName() const;
    bool readFunctionIsInline() const;
    QString replacedStatementsAfterResetProperty() const;
    QString replacedStatementsAfterWriteProperty() const;
    QString replacedStatementsBeforeResetProperty() const;
    QString replacedStatementsBeforeWriteProperty() const;
    QString replacedStatementsInReadProperty() const;
    QString replacedStatementsMiddleWriteProperty() const;
    bool resetFunctionIsInline() const;
    int size() const;
    QString statementsAfterResetProperty() const;
    QString statementsAfterWriteProperty() const;
    QString statementsBeforeResetProperty() const;
    QString statementsBeforeWriteProperty() const;
    QString statementsInReadProperty() const;
    QString statementsMiddleWriteProperty() const;
    bool writeFunctionEmitSignal() const;
    bool writeFunctionIsInline() const;

    void append(const Property &var);
    void append(const QList<Property> &var);
    void clear();
    void insert(int vari, const Property &varp);
    void removeAt(int var);
    void setEnabled(bool var);
    void setName(const QString &var);
    void setProperties(const QList<Property> &var);
    void setReadFunctionIsInline(const bool &var);
    void setResetFunctionIsInline(const bool &var);
    void setStatementsAfterResetProperty(const QString &var);
    void setStatementsAfterWriteProperty(const QString &var);
    void setStatementsBeforeResetProperty(const QString &var);
    void setStatementsBeforeWriteProperty(const QString &var);
    void setStatementsInReadProperty(const QString &var);
    void setStatementsMiddleWriteProperty(const QString &var);
    void setWriteFunctionEmitSignal(const bool &var);
    void setWriteFunctionIsInline(const bool &var);
    void sort();

    QDomElement toXMLNode(QDomDocument *doc) const;
    static PropertiesGroup fromXMLNode(const QDomElement &element);

private:
    void beforeWrite();

    PropertiesGroupData *m_d;
};
#include "propertiesgroupInlineFunctions.h"
#endif // PROPERTIESGROUP_H
