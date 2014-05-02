#ifndef DIALOGSET_H
#define DIALOGSET_H

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

private slots:
    void on_pushButtonOpenSettingsPolicy_clicked();

    void on_pushButtonSaveSettingsPolicy_clicked();

    void on_pushButtonSaveSettingsPolicyAs_clicked();

    void on_pushButtonNewSettingsPolicy_clicked();

    void on_pushButtonCloseSettingsDialog_clicked();

    void on_lineEditClassName_textChanged(const QString &arg1);

    void on_lineEditClassInherits_textChanged(const QString &arg1);

    void on_comboBoxClassTypeInformation_currentIndexChanged(int index);

    void on_checkBoxClassReadFunctionIsInline_toggled(bool checked);

    void on_checkBoxClassWriteFunctionIsInline_toggled(bool checked);

    void on_checkBoxClassWriteFunctionEmitSignal_toggled(bool checked);

    void on_plainTextEditClassWriteFunctionStart_textChanged();

    void on_plainTextEditClassWriteFunctionMiddle_textChanged();

    void on_plainTextEditClassWriteFunctionLast_textChanged();

private:
    Ui::DialogSet *ui;
};

#endif // DIALOGSET_H
