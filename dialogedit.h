/*****************************************************************************
 * dialogedit.h:
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
#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include "classsettings.h"
#include <QDialog>
#include <QList>
#include <QStringList>

namespace Ui {
class DialogEdit;
}

class DialogEdit : public QDialog
{
    Q_OBJECT

public:
    enum EditMode
    {
        NewProperty,
        EditExist,
    };

    explicit DialogEdit(QWidget *parent = 0);
    ~DialogEdit();

    /*void changeGroupIndex(int index);
    void changePropertyIndex(int index);*/
    void editExist(const Property &p);
    void editNew(const Property &p);

    /*int currentGroupIndex() const;
    int currentPropertyIndex() const;
    Property currentProperty() const;
    void setClassSettings(ClassSettings *l);*/
    Property currentProperty() const;
    EditMode currentMode() const;
    void setMode(EditMode m);

signals:

protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    void edit(const Property &p);

    void on_checkBoxPropertyConstant_toggled(bool checked);
    void on_checkBoxPropertyDesignable_toggled(bool checked);
    void on_checkBoxPropertyEnabled_toggled(bool checked);
    void on_checkBoxPropertyFinal_toggled(bool checked);
    void on_checkBoxPropertyMember_toggled(bool checked);
    void on_checkBoxPropertyNotify_toggled(bool checked);
    void on_checkBoxPropertyRead_toggled(bool checked);
    void on_checkBoxPropertyReset_toggled(bool checked);
    void on_checkBoxPropertyScriptable_toggled(bool checked);
    void on_checkBoxPropertyStored_toggled(bool checked);
    void on_checkBoxPropertyUser_toggled(bool checked);
    void on_checkBoxPropertyWrite_toggled(bool checked);
    void on_comboBoxPropertyType_currentIndexChanged(const QString &arg1);
    void on_lineEditPropertyDefaultValue_textChanged(const QString &arg1);
    void on_lineEditPropertyDocName_textChanged(const QString &arg1);
    void on_lineEditPropertyDocBrief_textChanged(const QString &arg1);
    void on_lineEditPropertyDocDetail_textChanged(const QString &arg1);
    void on_lineEditPropertyName_textChanged(const QString &arg1);
    void on_lineEditPropertyTypeStringName_textChanged(const QString &arg1);
    void on_pushButtonCloseProperty_clicked();
    void on_pushButtonSaveProperty_clicked();
    void on_spinBoxPropertyRevision_valueChanged(int arg1);
    void updateUi();

private:
    Property m_current;
    QStringList m_qtTypeList;
    QStringList m_boolAliasList;
    QStringList m_doubleAliasList;
    QStringList m_intAliasList;
    QStringList m_uintAliasList;
    QStringList m_longLongAliasList;
    QStringList m_ulongLongAliasList;
    Ui::DialogEdit *ui;
    EditMode m_mode;
    /*ClassSettings *m_list;
    //PropertiesGroup *m_list;
    int m_groupIndex;
    int m_propertyIndex;*/
};

/*inline int DialogEdit::changeGroupIndex() const
{
    return m_groupIndex;
}

inline int DialogEdit::changePropertyIndex() const
{
    return m_propertyIndex;
}*/

inline Property DialogEdit::currentProperty() const
{
    return m_current;
}

/*inline void DialogEdit::setClassSettings(ClassSettings *l)
{
    m_list = l;
}*/

inline DialogEdit::EditMode DialogEdit::currentMode() const
{
    return m_mode;
}

inline void DialogEdit::setMode(DialogEdit::EditMode m)
{
    m_mode = m;
}

#endif // DIALOGEDIT_H
