#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include "propertiesgroup.h"
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

    explicit DialogEdit(PropertiesGroup *list, QWidget *parent = 0);
    ~DialogEdit();

    void changeIndex(int index);
    void editExist(int index);
    void editNew();

    int currentIndex() const;
    Property currentProperty() const;
    void setPropertiesList(PropertiesGroup *l);
    EditMode currentMode() const;
    void setMode(EditMode m);

signals:

protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButtonSaveProperty_clicked();
    void on_pushButtonCloseProperty_clicked();
    void on_lineEditPropertyName_textChanged(const QString &arg1);
    void on_lineEditPropertyDocName_textChanged(const QString &arg1);
    void on_lineEditPropertyDocDetail_textChanged(const QString &arg1);
    void on_comboBoxPropertyType_currentIndexChanged(int index);
    void on_lineEditPropertyTypeStringName_textChanged(const QString &arg1);
    void on_spinBoxPropertyRevision_valueChanged(int arg1);
    void on_lineEditPropertyDefaultValue_textChanged(const QString &arg1);
    void on_checkBoxPropertyMember_toggled(bool checked);
    void on_checkBoxPropertyRead_toggled(bool checked);
    void on_checkBoxPropertyWrite_toggled(bool checked);
    void on_checkBoxPropertyReset_toggled(bool checked);
    void on_checkBoxPropertyNotify_toggled(bool checked);
    void on_checkBoxPropertyDesignable_toggled(bool checked);
    void on_checkBoxPropertyScriptable_toggled(bool checked);
    void on_checkBoxPropertyStored_toggled(bool checked);
    void on_checkBoxPropertyUser_toggled(bool checked);
    void on_checkBoxPropertyConstant_toggled(bool checked);
    void on_checkBoxPropertyFinal_toggled(bool checked);
    void on_checkBoxPropertyEnabled_toggled(bool checked);
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
    PropertiesGroup *m_list;
    EditMode m_mode;
    int m_index;
};

inline int DialogEdit::currentIndex() const
{
    return m_index;
}

inline Property DialogEdit::currentProperty() const
{
    return m_current;//m_list->at(m_index);
}

inline void DialogEdit::setPropertiesList(PropertiesGroup *l)
{
    m_list = l;
}

inline DialogEdit::EditMode DialogEdit::currentMode() const
{
    return m_mode;
}

inline void DialogEdit::setMode(DialogEdit::EditMode m)
{
    m_mode = m;
}

#endif // DIALOGEDIT_H
