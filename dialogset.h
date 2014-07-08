/*****************************************************************************
 * dialogset.h:
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
#ifndef DIALOGSET_H
#define DIALOGSET_H

#include "classsettings.h"
//#include "propertiesgroup.h"
#include <QDialog>
#include <QStringList>

namespace Ui {
class DialogSet;
}

class DialogSet : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSet(QWidget *parent = 0);
    ~DialogSet();

    ClassSettings classSettings() const;
    void editExist(const ClassSettings &l);
    void setClassSettings(const ClassSettings &l);

private slots:
    void on_checkBoxClassGeneratePreventReentrantCode_toggled(bool checked);
    void on_checkBoxClassSortAllProperties_toggled(bool checked);
    void on_comboBoxClassTypeInformation_currentIndexChanged(int index);
    void on_lineEditClassName_textChanged(const QString &arg1);
    void on_lineEditClassDocBrief_textChanged(const QString &arg1);
    void on_lineEditClassDocDetail_textChanged(const QString &arg1);
    void on_lineEditClassDocName_textChanged(const QString &arg1);
    void on_lineEditClassInherits_textChanged(const QString &arg1);

    /*void on_checkBoxPropertiesGroupConstant_toggled(bool checked);
    void on_checkBoxPropertiesGroupDesignable_toggled(bool checked);
    void on_checkBoxPropertiesGroupFinal_toggled(bool checked);*/
    void on_checkBoxPropertiesGroupReadFunctionIsInline_toggled(bool checked);
    /*void on_checkBoxPropertiesGroupScriptable_toggled(bool checked);
    void on_checkBoxPropertiesGroupStored_toggled(bool checked);
    void on_checkBoxPropertiesGroupUser_toggled(bool checked);*/
    void on_checkBoxPropertiesGroupWriteFunctionIsInline_toggled(bool checked);
    void on_checkBoxPropertiesGroupWriteFunctionEmitSignal_toggled(bool checked);
    void on_comboBoxPropertiesGroups_currentIndexChanged(const QString &arg1);
    void on_lineEditPropertiesGroupName_textChanged(const QString &arg1);
    void on_plainTextEditPropertiesGroupWriteFunctionStart_textChanged();
    void on_plainTextEditPropertiesGroupWriteFunctionMiddle_textChanged();
    void on_plainTextEditPropertiesGroupWriteFunctionLast_textChanged();
    void on_pushButtonPropertiesGroupAdd_clicked();
    void on_pushButtonPropertiesGroupChangeName_clicked();
    void on_pushButtonPropertiesGroupRemove_clicked();
    //void on_spinBoxPropertiesGroupRevision_valueChanged(int arg1);

    void on_plainTextEditTypeOrder_textChanged();

    void on_pushButtonSetSave_clicked();
    void on_pushButtonSetClose_clicked();

private:
    int propertiesGroupComboboxAt() const;
    void updateUi();

    ClassSettings m_current;
    Ui::DialogSet *ui;
};

inline ClassSettings DialogSet::classSettings() const
{
    return m_current;
}

inline void DialogSet::setClassSettings(const ClassSettings &l)
{
    m_current = l;
}

#endif // DIALOGSET_H
