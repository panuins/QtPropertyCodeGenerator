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
#include <QInputDialog>
#include <QMessageBox>
#include <QModelIndex>

DialogSet::DialogSet(QWidget *parent) :
    QDialog(parent),
    //m_current(NULL),
    ui(new Ui::DialogSet)
{
    ui->setupUi(this);
    /*ui->comboBoxClassTypeInformation->addItem("inherits_None");
    ui->comboBoxClassTypeInformation->addItem("inherits_QObject");
    ui->comboBoxClassTypeInformation->addItem("inherits_QWidget");
    ui->comboBoxClassTypeInformation->addItem("inherits_QQuickItem");*/
    ui->labelPropertiesGroupName->hide();
    ui->lineEditPropertiesGroupName->hide();
}

DialogSet::~DialogSet()
{
    delete ui;
}

void DialogSet::editExist(const ClassSettings &l)
{
    setClassSettings(l);
    updateUi();
    QDialog::open();
}

void DialogSet::on_checkBoxClassGeneratePreventReentrantCode_toggled(bool checked)
{
    m_current.setGeneratePreventReentrantCode(checked);
}

void DialogSet::on_checkBoxClassSortAllProperties_toggled(bool checked)
{
    m_current.setSortAllProperties(checked);
}

void DialogSet::on_comboBoxClassTypeInformation_currentIndexChanged(int index)
{
    m_current.setTypeInheritsInfomation(
                (ClassSettings::TypeInheritsInformation)index);
}

void DialogSet::on_lineEditClassName_textChanged(const QString &arg1)
{
    m_current.setClassName(arg1);
}

void DialogSet::on_lineEditClassDocBrief_textChanged(const QString &arg1)
{
    m_current.setDocBrief(arg1);
}

void DialogSet::on_lineEditClassDocDetail_textChanged(const QString &arg1)
{
    m_current.setDocDetail(arg1);
}

void DialogSet::on_lineEditClassDocName_textChanged(const QString &arg1)
{
    m_current.setDocName(arg1);
}

void DialogSet::on_lineEditClassInherits_textChanged(const QString &arg1)
{
    m_current.setInherits(arg1);
}

/*void DialogSet::on_checkBoxPropertiesGroupConstant_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setConstant(checked);
}

void DialogSet::on_checkBoxPropertiesGroupDesignable_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setDesignable(checked);
}

void DialogSet::on_checkBoxPropertiesGroupFinal_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setFinal(checked);
}*/

void DialogSet::on_checkBoxxPropertiesGroupEnabled_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setEnabled(checked);
}

void DialogSet::on_checkBoxPropertiesGroupReadFunctionIsInline_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setReadFunctionIsInline(checked);
}

/*void DialogSet::on_checkBoxPropertiesGroupScriptable_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setScriptable(checked);
}

void DialogSet::on_checkBoxPropertiesGroupStored_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setStored(checked);
}

void DialogSet::on_checkBoxPropertiesGroupUser_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setUser(checked);
}*/

void DialogSet::on_checkBoxPropertiesGroupWriteFunctionIsInline_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setWriteFunctionIsInline(checked);
}

void DialogSet::on_checkBoxPropertiesGroupWriteFunctionEmitSignal_toggled(bool checked)
{
    m_current[propertiesGroupComboboxAt()].setWriteFunctionEmitSignal(checked);
}

void DialogSet::on_plainTextEditPropertiesGroupReadFunction_textChanged()
{
    m_current[propertiesGroupComboboxAt()].setStatementsInReadProperty(
                ui->plainTextEditPropertiesGroupReadFunction->toPlainText());
}

void DialogSet::on_plainTextEditPropertiesGroupResetFunctionLast_textChanged()
{
    m_current[propertiesGroupComboboxAt()].setStatementsAfterResetProperty(
                ui->plainTextEditPropertiesGroupResetFunctionLast->toPlainText());
}

void DialogSet::on_plainTextEditPropertiesGroupResetFunctionStart_textChanged()
{
    m_current[propertiesGroupComboboxAt()].setStatementsBeforeResetProperty(
                ui->plainTextEditPropertiesGroupResetFunctionStart->toPlainText());
}

void DialogSet::on_plainTextEditPropertiesGroupWriteFunctionStart_textChanged()
{
    m_current[propertiesGroupComboboxAt()].setStatementsBeforeWriteProperty(
                ui->plainTextEditPropertiesGroupWriteFunctionStart->toPlainText());
}

void DialogSet::on_plainTextEditPropertiesGroupWriteFunctionMiddle_textChanged()
{
    m_current[propertiesGroupComboboxAt()].setStatementsMiddleWriteProperty(
                ui->plainTextEditPropertiesGroupWriteFunctionMiddle->toPlainText());
}

void DialogSet::on_plainTextEditPropertiesGroupWriteFunctionLast_textChanged()
{
    m_current[propertiesGroupComboboxAt()].setStatementsAfterWriteProperty(
                ui->plainTextEditPropertiesGroupWriteFunctionLast->toPlainText());
}

void DialogSet::on_plainTextEditTypeOrder_textChanged()
{
    QStringList typeOrder = ui->plainTextEditTypeOrder->toPlainText().split("\n");
    typeOrder.removeAll(QString(""));
    m_current.setTypeOrder(typeOrder);
}

void DialogSet::on_pushButtonPropertiesGroupAdd_clicked()
{
    //m_current.append(PropertiesGroup(QString("new")));
    QInputDialog dialog;
    dialog.setTextValue(QString("newGroup"));
    int ret = dialog.exec();
    if (ret == QDialog::Accepted)
    {
        QString newName = dialog.textValue();
        if (!nameIsCIndentifier(newName))
        {
            QMessageBox::critical(this,
                                  tr("Invalid name"),
                                  tr("Error: new name must be a valid C/C++ indentifier."));
            return;
        }
        if (m_current.findGroup(newName) >= 0)
        {
            QMessageBox::critical(this,
                                  tr("Invalid name"),
                                  tr("Error: new name %1 already exist.")
                                  .arg(newName));
            return;
        }
        m_current.append(PropertiesGroup(newName));
        updateUi();
    }
}

void DialogSet::on_pushButtonPropertiesGroupChangeName_clicked()
{
    QInputDialog dialog;
    dialog.setTextValue(m_current.at(propertiesGroupComboboxAt()).name());
    int ret = dialog.exec();
    if (ret == QDialog::Accepted)
    {
        QString newName = dialog.textValue();
        if (!nameIsCIndentifier(newName))
        {
            QMessageBox::critical(this,
                                  tr("Invalid name"),
                                  tr("Error: new name must be a valid C/C++ indentifier."));
            return;
        }
        if (m_current.findGroup(newName) >= 0)
        {
            QMessageBox::critical(this,
                                  tr("Invalid name"),
                                  tr("Error: new name %1 already exist.")
                                  .arg(newName));
            return;
        }
        m_current[propertiesGroupComboboxAt()].setName(newName);
        updateUi();
    }
}

void DialogSet::on_pushButtonPropertiesGroupRemove_clicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(
                this,
                tr("Delete group?"),
                tr("Are you sure delete group %1, and its all properties?")
                .arg(ui->comboBoxPropertiesGroups->currentText()));
    if (button == QMessageBox::Yes)
    {
        int i = m_current.findGroup(ui->comboBoxPropertiesGroups->currentText());
        m_current.removeAt(i);
    }
    if (m_current.propertiesGroups().isEmpty())
    {
        m_current.append(PropertiesGroup());
    }
    updateUi();
}

void DialogSet::on_comboBoxPropertiesGroups_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    //ui->lineEditPropertiesGroupName->setText(arg1);
    int index = propertiesGroupComboboxAt();
    ui->checkBoxPropertiesGroupReadFunctionIsInline->setChecked(
                m_current.at(index).readFunctionIsInline());
    ui->checkBoxPropertiesGroupWriteFunctionIsInline->setChecked(
                m_current.at(index).writeFunctionIsInline());
    ui->checkBoxPropertiesGroupWriteFunctionEmitSignal->setChecked(
                m_current.at(index).writeFunctionEmitSignal());
    ui->checkBoxxPropertiesGroupEnabled->setChecked(
                m_current.at(index).enabled());
    /*ui->spinBoxPropertiesGroupRevision->setValue(
                m_current.at(index).revision());
    ui->checkBoxPropertiesGroupDesignable->setChecked(
                m_current.at(index).designable());
    ui->checkBoxPropertiesGroupScriptable->setChecked(
                m_current.at(index).scriptable());
    ui->checkBoxPropertiesGroupStored->setChecked(
                m_current.at(index).stored());
    ui->checkBoxPropertiesGroupUser->setChecked(
                m_current.at(index).user());
    ui->checkBoxPropertiesGroupConstant->setChecked(
                m_current.at(index).constant());
    ui->checkBoxPropertiesGroupFinal->setChecked(
                m_current.at(index).final());*/
    ui->plainTextEditPropertiesGroupReadFunction->setPlainText(
                m_current.at(index).statementsInReadProperty());
    ui->plainTextEditPropertiesGroupResetFunctionStart->setPlainText(
                m_current.at(index).statementsBeforeResetProperty());
    ui->plainTextEditPropertiesGroupResetFunctionLast->setPlainText(
                m_current.at(index).statementsAfterResetProperty());
    ui->plainTextEditPropertiesGroupWriteFunctionStart->setPlainText(
                m_current.at(index).statementsBeforeWriteProperty());
    ui->plainTextEditPropertiesGroupWriteFunctionMiddle->setPlainText(
                m_current.at(index).statementsMiddleWriteProperty());
    ui->plainTextEditPropertiesGroupWriteFunctionLast->setPlainText(
                m_current.at(index).statementsAfterWriteProperty());
}

void DialogSet::on_lineEditPropertiesGroupName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    //m_current[propertiesGroupComboboxAt()].setName(arg1);
}

/*void DialogSet::on_spinBoxPropertiesGroupRevision_valueChanged(int arg1)
{
    m_current[propertiesGroupComboboxAt()].setRevision(arg1);
}*/

int DialogSet::propertiesGroupComboboxAt() const
{
    QString name = ui->comboBoxPropertiesGroups->currentText();
    int i = m_current.findGroup(name);
    return i;
}

void DialogSet::updateUi()
{
    ui->lineEditClassName->setText(m_current.className());
    ui->lineEditClassDocName->setText(m_current.docName());
    ui->lineEditClassDocBrief->setText(m_current.docBrief());
    ui->lineEditClassDocDetail->setText(m_current.docDetail());
    ui->lineEditClassInherits->setText(m_current.inherits());
    ui->comboBoxClassTypeInformation->setCurrentIndex(
                (int)(m_current.typeInheritsInfomation()));
    ui->checkBoxClassGeneratePreventReentrantCode->setChecked(
                m_current.generatePreventReentrantCode());
    ui->checkBoxClassSortAllProperties->setChecked(
                m_current.sortAllProperties());

    /*ui->listWidgetEnumTypeList->addItems(m_current.enumsName());
    if (ui->listWidgetEnumTypeList->count() >= 1)
    {
        ui->listWidgetEnumTypeList->setCurrentIndex(QModelIndex(0, 0));
        ui->lineEditEnumTypeName->setText(m_current.enums().at(0).name());
        ui->lineEditEnumPrefix->setText(m_current.enums().at(0).prefix());
        ui->lineEditEnumSuffix->setText(m_current.enums().at(0).suffix());
        ui->plainTextEditEnumsVars->setPlainText(m_current.enums().at(0).varList().join("\n"));
    }*/

    m_current.updateTypeOrder();
    QStringList typeOrder = m_current.typeOrder();
    ui->plainTextEditTypeOrder->setPlainText(typeOrder.join("\n"));

    ui->comboBoxPropertiesGroups->blockSignals(true);
    QString currentGroup = ui->comboBoxPropertiesGroups->currentText();
    ui->comboBoxPropertiesGroups->clear();
    foreach (QString name, m_current.propertiesGroupsName())
    {
        ui->comboBoxPropertiesGroups->addItem(name);
    }
    int currentIndex = ui->comboBoxPropertiesGroups->findText(currentGroup);
    if (currentIndex >= 0)
    {
        ui->comboBoxPropertiesGroups->setCurrentIndex(currentIndex);
        /*on_comboBoxPropertiesGroups_currentIndexChanged(
                    ui->comboBoxPropertiesGroups->currentText());*/
    }
    else if (ui->comboBoxPropertiesGroups->count() > 0)
    {
        ui->comboBoxPropertiesGroups->setCurrentIndex(0);
        /*on_comboBoxPropertiesGroups_currentIndexChanged(
                    ui->comboBoxPropertiesGroups->currentText());*/
    }
    ui->comboBoxPropertiesGroups->blockSignals(false);
}

void DialogSet::on_pushButtonSetClose_clicked()
{
    emit rejected();
    this->close();
}

void DialogSet::on_pushButtonSetSave_clicked()
{
    emit accept();
    this->close();
}
