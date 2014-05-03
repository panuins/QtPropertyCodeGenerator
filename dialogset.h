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

#include "propertiesgroup.h"
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

    void editExist(PropertiesGroup *l);
    void setPropertiesGroup(PropertiesGroup *l);

private slots:
    void on_pushButtonOpenSettingsPolicy_clicked();
    void on_pushButtonSaveSettingsPolicy_clicked();
    void on_pushButtonSaveSettingsPolicyAs_clicked();
    void on_pushButtonNewSettingsPolicy_clicked();
    void on_pushButtonCloseSettingsDialog_clicked();
    void on_lineEditClassName_textChanged(const QString &arg1);
    void on_lineEditClassInherits_textChanged(const QString &arg1);
    void on_comboBoxClassTypeInformation_currentIndexChanged(int index);
    void on_checkBoxGroupReadFunctionIsInline_toggled(bool checked);
    void on_checkBoxGroupWriteFunctionIsInline_toggled(bool checked);
    void on_checkBoxGroupWriteFunctionEmitSignal_toggled(bool checked);
    void on_plainTextEditGroupWriteFunctionStart_textChanged();
    void on_plainTextEditGroupWriteFunctionMiddle_textChanged();
    void on_plainTextEditGroupWriteFunctionLast_textChanged();
    void on_pushButtonEnumTypeNameAdd_clicked();
    void on_pushButtonEnumTypeNameRemove_clicked();
    void on_plainTextEditEnumDeclare_textChanged();

    void on_plainTextEditTypeOrder_textChanged();

private:
    PropertiesGroup *m_current;
    Ui::DialogSet *ui;
};

inline void DialogSet::setPropertiesGroup(PropertiesGroup *l)
{
    m_current = l;
}

#endif // DIALOGSET_H
