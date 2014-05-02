#ifndef DIALOGSET_H
#define DIALOGSET_H

#include "propertiesgroup.h"
#include <QDialog>

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

private:
    PropertiesGroup *m_current;
    Ui::DialogSet *ui;
};

inline void DialogSet::setPropertiesGroup(PropertiesGroup *l)
{
    m_current = l;
}

#endif // DIALOGSET_H
