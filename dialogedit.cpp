/*****************************************************************************
 * dialogedit.cpp:
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
#include "dialogedit.h"
#include "ui_dialogedit.h"
#include "sharedFunctions.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include <QVariant>
#include <iostream>

DialogEdit::DialogEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEdit)
    //m_list(list),
    //m_index(-1)
{
    ui->setupUi(this);
    ui->comboBoxPropertyType->blockSignals(true);
    ui->comboBoxPropertyType->clear();
#define AddQvariantType(PropertyType) \
    { \
        QString strName = QString(QVariant::typeToName(PropertyType)); \
        ui->comboBoxPropertyType->addItem(strName); \
        m_qtTypeList.append(strName); \
    }
    /*if (strName.startsWith(QChar('Q'), Qt::CaseInsensitive)) \
    { \
        m_qtTypeList.append(strName); \
    } \*/
    //std::cout << QString(QVariant::typeToName(PropertyType)).toStdString() << std::endl;
    //AddQvariantType(QVariant::Invalid);

    AddQvariantType(QVariant::Bool);
    AddQvariantType(QVariant::Double);
    AddQvariantType(QVariant::Int);
    AddQvariantType(QVariant::UInt);
    AddQvariantType(QVariant::LongLong);
    AddQvariantType(QVariant::ULongLong);

    AddQvariantType(QVariant::UserType);
    AddQvariantType(QVariant::Char);
    AddQvariantType(QVariant::String);
    AddQvariantType(QVariant::ByteArray);
    AddQvariantType(QVariant::List);
    AddQvariantType(QVariant::StringList);
    AddQvariantType(QVariant::Url);

    AddQvariantType(QVariant::Color);
    AddQvariantType(QVariant::Font);
    AddQvariantType(QVariant::Date);
    AddQvariantType(QVariant::DateTime);
    AddQvariantType(QVariant::Time);

    AddQvariantType(QVariant::Point);
    AddQvariantType(QVariant::PointF);
    AddQvariantType(QVariant::Size);
    AddQvariantType(QVariant::SizeF);
    AddQvariantType(QVariant::Rect);
    AddQvariantType(QVariant::RectF);
    AddQvariantType(QVariant::Line);
    AddQvariantType(QVariant::LineF);
    AddQvariantType(QVariant::Brush);
    AddQvariantType(QVariant::Pen);

    AddQvariantType(QVariant::BitArray);
    AddQvariantType(QVariant::Bitmap);
    AddQvariantType(QVariant::Cursor);
    AddQvariantType(QVariant::EasingCurve);
    AddQvariantType(QVariant::Hash);
    AddQvariantType(QVariant::Icon);
    AddQvariantType(QVariant::Image);
    AddQvariantType(QVariant::KeySequence);
    AddQvariantType(QVariant::Locale);
    AddQvariantType(QVariant::Map);
    AddQvariantType(QVariant::Matrix);
    AddQvariantType(QVariant::Transform);
    AddQvariantType(QVariant::Matrix4x4);
    AddQvariantType(QVariant::Palette);
    AddQvariantType(QVariant::Pixmap);
    AddQvariantType(QVariant::Polygon);
#if QT_VERSION >= 0x050000
    AddQvariantType(QVariant::PolygonF);
#endif
    AddQvariantType(QVariant::Quaternion);
    AddQvariantType(QVariant::RegExp);
    AddQvariantType(QVariant::Region);
    AddQvariantType(QVariant::SizePolicy);
    AddQvariantType(QVariant::TextFormat);
    AddQvariantType(QVariant::TextLength);
    AddQvariantType(QVariant::Vector2D);
    AddQvariantType(QVariant::Vector3D);
    AddQvariantType(QVariant::Vector4D);
#if QT_VERSION >= 0x050000
    AddQvariantType(QVariant::Uuid);
    AddQvariantType(QVariant::ModelIndex);
    AddQvariantType(QVariant::RegularExpression);
#endif
    ui->comboBoxPropertyType->blockSignals(false);
    ui->comboBoxPropertyType->setCurrentIndex(0);
    /*Qt::WindowFlags flags(this->windowFlags());
    flags &= ~Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);*/
    {
        QRegExp exp(QString("[0-9a-zA-Z_]*"));
        QRegExpValidator *vName =
                new QRegExpValidator(exp, ui->lineEditPropertyName);
        ui->lineEditPropertyName->setValidator(vName);
    }
    {
        QRegExp exp(QString("[a-zA-Z_][0-9a-zA-Z_ *<>:]*"));
        QRegExpValidator *vType =
                new QRegExpValidator(exp, ui->lineEditPropertyTypeStringName);
        ui->lineEditPropertyTypeStringName->setValidator(vType);
    }
    m_boolAliasList.append("Bool");
    m_boolAliasList.append("BOOL");

    m_doubleAliasList.append("qreal");
    m_doubleAliasList.append("float");

    m_intAliasList.append("char");
    m_intAliasList.append("CHAR");
    m_intAliasList.append("qint8");
    m_intAliasList.append("signed char");

    m_intAliasList.append("short");
    m_intAliasList.append("SHORT");
    m_intAliasList.append("qint16");
    m_intAliasList.append("signed short");

    m_intAliasList.append("int");
    m_intAliasList.append("INT");
    m_intAliasList.append("qint32");
    m_intAliasList.append("signed int");
    m_intAliasList.append("signed");

    m_uintAliasList.append("uchar");
    m_uintAliasList.append("UCHAR");
    m_uintAliasList.append("quint8");
    m_uintAliasList.append("unsigned char");

    m_uintAliasList.append("ushort");
    m_uintAliasList.append("USHORT");
    m_uintAliasList.append("quint16");
    m_uintAliasList.append("unsigned short");

    m_uintAliasList.append("uint");
    m_uintAliasList.append("UINT");
    m_uintAliasList.append("uqint32");
    m_uintAliasList.append("unsigned int");
    m_uintAliasList.append("unsigned");

    if (sizeof(long) == sizeof(int))
    {
        m_intAliasList.append("long");
        m_intAliasList.append("signed long");
        m_intAliasList.append("LONG");

        m_uintAliasList.append("ulong");
        m_uintAliasList.append("unsigned long");
        m_uintAliasList.append("uLONG");
    }
    else if (sizeof(long) > sizeof(int))
    {
        m_longLongAliasList.append("long");
        m_longLongAliasList.append("signed long");
        m_longLongAliasList.append("LONG");

        m_ulongLongAliasList.append("ulong");
        m_ulongLongAliasList.append("unsigned long");
        m_ulongLongAliasList.append("uLONG");
    }

    m_longLongAliasList.append("long long");
    m_longLongAliasList.append("long long int");
    m_longLongAliasList.append("qint64");
    m_longLongAliasList.append("__int64");
    m_longLongAliasList.append("qlonglong");

    m_ulongLongAliasList.append("unsigned long long");
    m_ulongLongAliasList.append("unsigned long long int");
    m_ulongLongAliasList.append("quint64");
    m_ulongLongAliasList.append("unsigned __int64");
    m_ulongLongAliasList.append("qulonglong");
}

DialogEdit::~DialogEdit()
{
    delete ui;
}

/*void DialogEdit::changeGroupIndex(int index)
{
    m_groupIndex = index;
    m_propertyIndex = -1;
}

void DialogEdit::changePropertyIndex(int index)
{
    m_propertyIndex = index;
    if ((index >= 0) && (index < m_list->size()))
    {
        m_current = m_list->at(index);
    }
    updateUi();
}*/

void DialogEdit::editExist(const Property &p)
{
    this->setMode(EditExist);
    edit(p);
    QDialog::open();
}

void DialogEdit::editNew(const Property &p)
{
    this->setMode(NewProperty);
    edit(p);
    QDialog::open();
}

void DialogEdit::edit(const Property &p)
{
    m_current = p;
    updateUi();
}

/*void DialogEdit::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
}*/

void DialogEdit::on_checkBoxPropertyConstant_toggled(bool checked)
{
    m_current.setConstant(checked);
}

void DialogEdit::on_checkBoxPropertyDesignable_toggled(bool checked)
{
    m_current.setDesignable(checked);
}

void DialogEdit::on_checkBoxPropertyEnabled_toggled(bool checked)
{
    m_current.setEnabled(checked);
}

void DialogEdit::on_checkBoxPropertyFinal_toggled(bool checked)
{
    m_current.setFinal(checked);
}

void DialogEdit::on_checkBoxPropertyMember_toggled(bool checked)
{
    m_current.setMember(checked);
}

void DialogEdit::on_checkBoxPropertyNotify_toggled(bool checked)
{
    m_current.setNotify(checked);
}

void DialogEdit::on_checkBoxPropertyRead_toggled(bool checked)
{
    m_current.setRead(checked);
}

void DialogEdit::on_checkBoxPropertyReset_toggled(bool checked)
{
    m_current.setReset(checked);
}

void DialogEdit::on_checkBoxPropertyScriptable_toggled(bool checked)
{
    m_current.setScriptable(checked);
}

void DialogEdit::on_checkBoxPropertyStored_toggled(bool checked)
{
    m_current.setStored(checked);
}

void DialogEdit::on_checkBoxPropertyUser_toggled(bool checked)
{
    m_current.setUser(checked);
}

void DialogEdit::on_checkBoxPropertyWrite_toggled(bool checked)
{
    m_current.setWrite(checked);
}

void DialogEdit::on_comboBoxPropertyType_currentIndexChanged(const QString &arg1)
{
    m_current.setType(arg1);
    if (m_mode == NewProperty)
    {
        std::string stdstr = m_current.type().toStdString();
        QVariant::Type typeId = QVariant::nameToType(stdstr.c_str());
        switch (typeId)
        {
        case QVariant::Bool:
            ui->lineEditPropertyDefaultValue->setText("true");
            break;
        case QVariant::Double:
            ui->lineEditPropertyDefaultValue->setText("0.0");
            break;
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::LongLong:
        case QVariant::ULongLong:
            ui->lineEditPropertyDefaultValue->setText("0");
            break;
        default:
            break;
        }
    }
}

void DialogEdit::on_lineEditPropertyDefaultValue_textChanged(const QString &arg1)
{
    m_current.setDefaultValue(arg1);
}

void DialogEdit::on_lineEditPropertyDocBrief_textChanged(const QString &arg1)
{
    m_current.setDocBrief(arg1);
}

void DialogEdit::on_lineEditPropertyDocDetail_textChanged(const QString &arg1)
{
    m_current.setDocDetail(arg1);
}

void DialogEdit::on_lineEditPropertyDocName_textChanged(const QString &arg1)
{
    m_current.setDocName(arg1);
}

void DialogEdit::on_lineEditPropertyName_textChanged(const QString &arg1)
{
    m_current.setName(arg1);
}

void DialogEdit::on_lineEditPropertyTypeStringName_textChanged(
        const QString &arg1)
{
    m_current.setTypeStringName(arg1);
    if (m_qtTypeList.contains(arg1))
    {
        m_current.setType(arg1);
        int typeIndex = ui->comboBoxPropertyType->findText(arg1);
        ui->comboBoxPropertyType->setCurrentIndex(typeIndex);
    }
    else
    {
        int typeId;
        if (m_boolAliasList.contains(arg1))
        {
            typeId = QVariant::Bool;
        }
        else if (m_doubleAliasList.contains(arg1))
        {
            typeId = QVariant::Double;
        }
        else if (m_intAliasList.contains(arg1))
        {
            typeId = QVariant::Int;
        }
        else if (m_uintAliasList.contains(arg1))
        {
            typeId = QVariant::UInt;
        }
        else if (m_longLongAliasList.contains(arg1))
        {
            typeId = QVariant::LongLong;
        }
        else if (m_ulongLongAliasList.contains(arg1))
        {
            typeId = QVariant::ULongLong;
        }
        else
        {
            return;
        }
        QString name(QVariant::typeToName(typeId));
        int typeIndex = ui->comboBoxPropertyType->findText(name);
        ui->comboBoxPropertyType->setCurrentIndex(typeIndex);
    }
}

void DialogEdit::on_pushButtonCloseProperty_clicked()
{
    emit rejected();
    this->close();
}

void DialogEdit::on_pushButtonSaveProperty_clicked()
{
    if (m_current.name().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Invalid name."),
                              tr("Error: Must input a name."));
        return;
    }
    emit accept();
    this->close();
}

void DialogEdit::on_spinBoxPropertyRevision_valueChanged(int arg1)
{
    m_current.setRevision(arg1);
}

void DialogEdit::updateUi()
{
    ui->lineEditPropertyName->setText(m_current.name());
    ui->lineEditPropertyDocName->setText(m_current.docName());
    ui->lineEditPropertyDocBrief->setText(m_current.docBrief());
    ui->lineEditPropertyDocDetail->setText(m_current.docDetail());
    QString typeId = m_current.type();
    int typeIndex = ui->comboBoxPropertyType->findText(typeId);
    ui->comboBoxPropertyType->setCurrentIndex(typeIndex);
    ui->lineEditPropertyTypeStringName->setText(m_current.typeStringName());
    ui->spinBoxPropertyRevision->setValue(m_current.revision());
    ui->checkBoxPropertyMember->setChecked(m_current.member());
    ui->checkBoxPropertyRead->setChecked(m_current.read());
    ui->checkBoxPropertyWrite->setChecked(m_current.write());
    ui->checkBoxPropertyReset->setChecked(m_current.reset());
    ui->checkBoxPropertyNotify->setChecked(m_current.notify());
    ui->checkBoxPropertyDesignable->setChecked(m_current.designable());
    ui->checkBoxPropertyScriptable->setChecked(m_current.scriptable());
    ui->checkBoxPropertyStored->setChecked(m_current.stored());
    ui->checkBoxPropertyUser->setChecked(m_current.user());
    ui->checkBoxPropertyConstant->setChecked(m_current.constant());
    ui->checkBoxPropertyFinal->setChecked(m_current.final());
    ui->checkBoxPropertyEnabled->setChecked(m_current.enabled());
    ui->lineEditPropertyDefaultValue->setText(m_current.defaultValue().toString());
}
