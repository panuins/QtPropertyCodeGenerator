#include "dialogset.h"
#include "ui_dialogset.h"

DialogSet::DialogSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSet)
{
    ui->setupUi(this);
}

DialogSet::~DialogSet()
{
    delete ui;
}

void DialogSet::on_pushButtonOpenSettingsPolicy_clicked()
{

}

void DialogSet::on_pushButtonSaveSettingsPolicy_clicked()
{

}

void DialogSet::on_pushButtonSaveSettingsPolicyAs_clicked()
{

}

void DialogSet::on_pushButtonNewSettingsPolicy_clicked()
{

}

void DialogSet::on_pushButtonCloseSettingsDialog_clicked()
{

}

void DialogSet::on_lineEditClassName_textChanged(const QString &arg1)
{

}

void DialogSet::on_lineEditClassInherits_textChanged(const QString &arg1)
{

}

void DialogSet::on_comboBoxClassTypeInformation_currentIndexChanged(int index)
{

}

void DialogSet::on_checkBoxClassReadFunctionIsInline_toggled(bool checked)
{

}

void DialogSet::on_checkBoxClassWriteFunctionIsInline_toggled(bool checked)
{

}

void DialogSet::on_checkBoxClassWriteFunctionEmitSignal_toggled(bool checked)
{

}

void DialogSet::on_plainTextEditClassWriteFunctionStart_textChanged()
{

}

void DialogSet::on_plainTextEditClassWriteFunctionMiddle_textChanged()
{

}

void DialogSet::on_plainTextEditClassWriteFunctionLast_textChanged()
{

}
