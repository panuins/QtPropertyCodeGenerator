/*****************************************************************************
 * dialogset.cpp:
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
#include "dialogset.h"
#include "ui_dialogset.h"
#include <QModelIndex>

DialogSet::DialogSet(QWidget *parent) :
    QDialog(parent),
    m_current(NULL),
    ui(new Ui::DialogSet)
{
    ui->setupUi(this);
    /*ui->comboBoxClassTypeInformation->addItem("inherits_None");
    ui->comboBoxClassTypeInformation->addItem("inherits_QObject");
    ui->comboBoxClassTypeInformation->addItem("inherits_QWidget");
    ui->comboBoxClassTypeInformation->addItem("inherits_QQuickItem");*/
}

DialogSet::~DialogSet()
{
    delete ui;
}

void DialogSet::editExist(PropertiesGroup *l)
{
    setPropertiesGroup(l);
    ui->lineEditClassName->setText(l->className());
    ui->lineEditClassInherits->setText(l->inherits());
    ui->comboBoxClassTypeInformation->setCurrentIndex(
                (int)l->typeInderitsInfomation());
    ui->checkBoxGroupReadFunctionIsInline->setChecked(
                l->readFunctionIsInline());
    ui->checkBoxGroupWriteFunctionEmitSignal->setChecked(
                l->writeFunctionEmitSignal());
    ui->checkBoxGroupWriteFunctionIsInline->setChecked(
                l->writeFunctionIsInline());
    ui->plainTextEditGroupWriteFunctionStart->setPlainText(
                l->statementsStartWriteProperty());
    ui->plainTextEditGroupWriteFunctionMiddle->setPlainText(
                l->statementsMiddleWriteProperty());
    ui->plainTextEditGroupWriteFunctionLast->setPlainText(
                l->statementsAfterWriteProperty());
    /*ui->listWidgetEnumTypeList->addItems(l->enumsName());
    if (ui->listWidgetEnumTypeList->count() >= 1)
    {
        ui->listWidgetEnumTypeList->setCurrentIndex(QModelIndex(0, 0));
        ui->lineEditEnumTypeName->setText(l->enums().at(0).name());
        ui->lineEditEnumPrefix->setText(l->enums().at(0).prefix());
        ui->lineEditEnumSuffix->setText(l->enums().at(0).suffix());
        ui->plainTextEditEnumsVars->setPlainText(l->enums().at(0).varList().join("\n"));
    }*/
    QStringList typeList = m_current->existType();
    QStringList typeOrderUi = ui->plainTextEditTypeOrder->toPlainText().split("\n");
    typeOrderUi.removeAll(QString(""));
    typeList.removeAll(QString(""));
    foreach (QString var, typeList)
    {
        if (!typeOrderUi.contains(var))
        {
            typeOrderUi.append(var);
        }
    }
    ui->plainTextEditTypeOrder->setPlainText(typeOrderUi.join("\n"));
    m_current->setTypeOrder(typeOrderUi);
    QDialog::open();
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
    this->close();
}

void DialogSet::on_lineEditClassName_textChanged(const QString &arg1)
{
    m_current->setClassName(arg1);
}

void DialogSet::on_lineEditClassInherits_textChanged(const QString &arg1)
{
    m_current->setInherits(arg1);
}

void DialogSet::on_comboBoxClassTypeInformation_currentIndexChanged(int index)
{
    m_current->setTypeInderitsInfomation(
                (PropertiesGroup::TypeInheritsInformation)index);
}

void DialogSet::on_checkBoxGroupReadFunctionIsInline_toggled(bool checked)
{
    m_current->setReadFunctionIsInline(checked);
}

void DialogSet::on_checkBoxGroupWriteFunctionIsInline_toggled(bool checked)
{
    m_current->setWriteFunctionIsInline(checked);
}

void DialogSet::on_checkBoxGroupWriteFunctionEmitSignal_toggled(bool checked)
{
    m_current->setWriteFunctionEmitSignal(checked);
}

void DialogSet::on_plainTextEditGroupWriteFunctionStart_textChanged()
{
    m_current->setStatementsStartWriteProperty(
                ui->plainTextEditGroupWriteFunctionStart->toPlainText());
}

void DialogSet::on_plainTextEditGroupWriteFunctionMiddle_textChanged()
{
    m_current->setStatementsMiddleWriteProperty(
                ui->plainTextEditGroupWriteFunctionMiddle->toPlainText());
}

void DialogSet::on_plainTextEditGroupWriteFunctionLast_textChanged()
{
    m_current->setStatementsAfterWriteProperty(
                ui->plainTextEditGroupWriteFunctionLast->toPlainText());
}

void DialogSet::on_pushButtonEnumTypeNameAdd_clicked()
{
    //ui->listWidgetEnumTypeList->addItem("");
    //m_current
}

void DialogSet::on_pushButtonEnumTypeNameRemove_clicked()
{

}

void DialogSet::on_plainTextEditEnumDeclare_textChanged()
{

}

void DialogSet::on_plainTextEditTypeOrder_textChanged()
{
    QStringList typeOrder = ui->plainTextEditTypeOrder->toPlainText().split("\n");
    typeOrder.removeAll(QString(""));
    m_current->setTypeOrder(typeOrder);
}
