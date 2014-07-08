/*****************************************************************************
 * property.h:
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
#ifndef PROPERTY_H
#define PROPERTY_H
#include "propertydata.h"
#include "sharedFunctions.h"
//#define DEBUG_PROPERTYS_COW_DETAIL

class Property
{
public:
    Property();
    Property(const QString &name,
             const QString &type,
             const QString &typeStringName = QString());
    Property(const Property &p);
    Property(const PropertyData &p);
    ~Property();
    Property &operator=(const Property &p);
    bool operator==(const Property &p) const;
    bool operator!=(const Property &p) const;

    bool constant() const;
    QVariant defaultValue() const;
    bool designable() const;
    QString docBrief() const;
    QString docDetail() const;
    QString docName() const;
    bool enabled() const;
    bool final() const;
    bool member() const;
    QString name() const;
    bool needWrite() const;
    bool notify() const;
    QString realTypeName() const;
    bool read() const;
    bool reset() const;
    bool resetIsValid() const;
    int revision() const;
    bool scriptable() const;
    bool stored() const;
    const QString &type() const;
    QString typeStringName() const;
    QString typePrefix() const;
    bool user() const;
    bool write() const;

    void setConstant(bool b);
    void setDefaultValue(const QVariant &var);
    void setDesignable(bool b);
    void setDocBrief(const QString &var);
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
    void setUseParentSettings(bool b);
    void setUser(bool b);
    void setWrite(bool b);

    QString readFunctionName() const;
    QString resetFunctionName() const;
    QString writeFunctionArgumentName() const;
    QString writeFunctionName() const;
    QString signalName() const;
    QString memberVariableName() const;
    QString preventReentrantVarName() const;

    QString docComment(const QString &className) const;
    QString docCommentBrief() const;
    QString docCommentDetail() const;
    QString docCommentMemberVariable() const;
    QString docCommentPreventReentrantMemberVariable() const;
    QString docCommentReadFunction(const QString &className = QString(""),
                                   bool isInline = true) const;
    QString docCommentResetFunction(const QString &className = QString(""),
                                    bool isInline = true) const;
    QString docCommentWriteFunction(const QString &className,
                                    bool emitSignal = true,
                                    bool isInline = false,
                                    bool preventReentrant = true) const;

    QString qPropertyString() const;
    QString readDeclear() const;
    QString resetDeclear() const;
    QString writeDeclear() const;
    QString signalDeclear() const;
    QString memberVariableDeclear() const;
    QString preventReentrantVarDeclear() const;

    /*QString preventReentrantVarInitialStatement() const;
    QString initialToDefaultValueStatement() const;
    QString initialToSpecifyValueStatement(const QString &str) const;*/

    QString readFunctionDefine(const QString &className,
                               bool isInline = true) const;
    QString resetFunctionDefine(const QString &className,
                                bool isInline = true) const;
    QString writeFunctionDefine(const QString &className,
                                const QString &strBeforSetValue = QString(""),
                                const QString &strBetweenSetValueAndEmit = QString(""),
                                const QString &strAfterEmit = QString(""),
                                bool emitSignal = true,
                                bool isInline = false,
                                bool preventReentrant = true) const;

    static Property invalid();

private:
    void beforeWrite();

    PropertyData *m_d;
};
#include "propertyInlineFunctions.h"
#endif // PROPERTY_H
