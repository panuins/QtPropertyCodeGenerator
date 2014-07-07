/*****************************************************************************
 * widget.cpp:
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
#include "paraments.h"
#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QModelIndex>
#include <QSettings>
#include <QTextCodec>
#include <QVariant>
#include <iostream>

inline QString boolToStr(bool b)
{
    return b ? QString("true") : QString("false");
}

Widget::PropertyItem::PropertyItem() :
    name(NULL),
    type(NULL),
    //typeStringName(NULL),
    docName(NULL),
    docDetail(NULL),
    defaultValue(NULL),
    enabled(NULL),
    member(NULL),
    read(NULL),
    write(NULL),
    reset(NULL),
    notify(NULL),
    revision(NULL),
    designable(NULL),
    scriptable(NULL),
    stored(NULL),
    user(NULL),
    constant(NULL),
    final(NULL)
{
}

Widget::PropertyItem::PropertyItem(const Property &p) :
    name(new QTableWidgetItem(p.name())),
    type(new QTableWidgetItem(p.realTypeName())),
    //typeStringName(new QTableWidgetItem(p.typeStringName())),
    docName(new QTableWidgetItem(p.docName())),
    docDetail(new QTableWidgetItem(p.docDetail())),
    defaultValue(new QTableWidgetItem(p.defaultValue().toString())),
    enabled(new QTableWidgetItem(boolToStr(p.enabled()))),
    member(new QTableWidgetItem(boolToStr(p.member()))),
    read(new QTableWidgetItem(boolToStr(p.read()))),
    write(new QTableWidgetItem(boolToStr(p.write()))),
    reset(new QTableWidgetItem(boolToStr(p.reset()))),
    notify(new QTableWidgetItem(boolToStr(p.notify()))),
    revision(new QTableWidgetItem(QString::number(p.revision()))),
    designable(new QTableWidgetItem(boolToStr(p.designable()))),
    scriptable(new QTableWidgetItem(boolToStr(p.scriptable()))),
    stored(new QTableWidgetItem(boolToStr(p.stored()))),
    user(new QTableWidgetItem(boolToStr(p.user()))),
    constant(new QTableWidgetItem(boolToStr(p.constant()))),
    final(new QTableWidgetItem(boolToStr(p.final())))
{
}

Widget::PropertyItem::~PropertyItem()
{
#define deleteIfNotNULL(VAR) \
    if (VAR != NULL) \
    { \
        delete VAR; \
    }
    /*deleteIfNotNULL(name);
    deleteIfNotNULL(docName);
    deleteIfNotNULL(docDetail);
    deleteIfNotNULL(type);
    deleteIfNotNULL(typeStringName);
    deleteIfNotNULL(revision);
    deleteIfNotNULL(member);
    deleteIfNotNULL(read);
    deleteIfNotNULL(write);
    deleteIfNotNULL(reset);
    deleteIfNotNULL(notify);
    deleteIfNotNULL(designable);
    deleteIfNotNULL(scriptable);
    deleteIfNotNULL(stored);
    deleteIfNotNULL(user);
    deleteIfNotNULL(constant);
    deleteIfNotNULL(final);*/
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_currentFile(QString("")),
    ui(new Ui::Widget),
    m_groupIndex(0),
    m_changed(false)
{
    ui->setupUi(this);
    m_dialogEdit = new DialogEdit(this);
    m_dialogSet = new DialogSet(this);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    m_classSettings.clear();
    {
        PropertiesGroup g;
        {
            Property p("height", QVariant::typeToName(QVariant::Double), "qreal");
            p.setDocName(QString("height"));
            p.setDocDetail(QString("will replot"));
            p.setDefaultValue(QString("0.0"));
            g.append(p);
        }
        {
            Property p("width", QVariant::typeToName(QVariant::Double), "qreal");
            p.setDocName(QString("width"));
            p.setDocDetail(QString("will replot"));
            p.setDefaultValue(QString("0.0"));
            g.append(p);
        }
        {
            Property p("pro", QVariant::typeToName(QVariant::Double), "qreal");
            p.setDocName(QString("pro"));
            p.setDocDetail(QString("read only property test"));
            p.setDefaultValue(QString("0.0"));
            p.setWrite(false);
            g.append(p);
        }
        {
            Property p("pwo", QVariant::typeToName(QVariant::Double), "qreal");
            p.setDocName(QString("pwo"));
            p.setDocDetail(QString("write only property test"));
            p.setDefaultValue(QString("0.0"));
            p.setRead(false);
            g.append(p);
        }
        {
            Property p("nn", QVariant::typeToName(QVariant::Double), "qreal");
            p.setDocName(QString("nn"));
            p.setDocDetail(QString("not notify property test"));
            p.setDefaultValue(QString("0.0"));
            p.setNotify(false);
            g.append(p);
        }
        g.setName("size");
        g.setReadFunctionIsInline(true);
        g.setWriteFunctionIsInline(false);
        g.setWriteFunctionEmitSignal(true);
        g.setStatementsStartWriteProperty("        StartWrite;\n");
        g.setStatementsMiddleWriteProperty("        MiddleWrite;\n");
        g.setStatementsAfterWriteProperty("        AfterWrite;\n");
        m_classSettings.append(g);
    }
    {
        PropertiesGroup g;
        {
            Property p("backColor", QVariant::typeToName(QVariant::Color));
            p.setDocName(QString("back color"));
            p.setDocDetail(QString("will replot"));
            p.setDefaultValue(QString("Qt::grey"));
            g.append(p);
        }
        {
            Property p("bordercolor", QVariant::typeToName(QVariant::Color));
            p.setDocName(QString("border color"));
            p.setDocDetail(QString("will replot"));
            p.setDefaultValue(QString("Qt::black"));
            g.append(p);
        }
        g.setName("style");
        g.setReadFunctionIsInline(true);
        g.setWriteFunctionIsInline(false);
        g.setWriteFunctionEmitSignal(true);
        g.setStatementsStartWriteProperty("        StartWrite;\n");
        g.setStatementsMiddleWriteProperty("        MiddleWrite;\n");
        g.setStatementsAfterWriteProperty("        AfterWrite;\n");
        m_classSettings.append(g);
    }
    m_classSettings.setClassName("testClass");
    m_classSettings.setDocName("test class");
    m_classSettings.setInherits("QObject");
    m_classSettings.setTypeInderitsInfomation(ClassSettings::inherits_QObject);
    updateUi();
    connect(m_dialogEdit, SIGNAL(accepted()),
            this, SLOT(on_dialogEdit_accept()));
    connect(m_dialogEdit, SIGNAL(rejected()),
            this, SLOT(on_dialogEdit_rejected()));
    connect(m_dialogSet, SIGNAL(accepted()),
            this, SLOT(on_dialogSet_accept()));
    connect(m_dialogSet, SIGNAL(rejected()),
            this, SLOT(on_dialogSet_rejected()));
    loadSettings();
}

Widget::~Widget()
{
    saveSettings();
    delete ui;
}

//取消，返回false，表示不再继续，其它，返回true，表示当前磁盘上的文件为最新的。
bool Widget::saveChanged()
{
    if (m_changed)
    {
        int ret = QMessageBox::question(
                    this,
                    tr("Save changed?"),
                    tr("Save changed?"),
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if ((ret == QMessageBox::Yes))
        {
            on_pushButtonSaveProject_clicked();
            return !m_changed;
        }
        else if ((ret == QMessageBox::No))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Widget::closeEvent(QCloseEvent *event)
{
    if (saveChanged())
    {
        QWidget::closeEvent(event);
    }
    else
    {
        event->ignore();
    }
}

void Widget::on_comboBoxSelectPropertiesGroups_currentIndexChanged(const QString &arg1)
{
    m_groupIndex = m_classSettings.findGroup(arg1);
    updatePropertiesTable();
    //m_propertyIndex = -1;
}

void Widget::on_dialogEdit_accept()
{
    switch (m_dialogEdit->currentMode())
    {
    case DialogEdit::EditExist:
    {
        int propertyIndex = ui->tableWidgetProperties->currentRow();
        m_classSettings[m_groupIndex][propertyIndex] = m_dialogEdit->currentProperty();
        //m_classSettings[m_groupIndex].sort();
        m_changed = true;
        updatePropertiesTable();
        generateCode();
        break;
    }
    case DialogEdit::NewProperty:
        m_classSettings[m_groupIndex].append(m_dialogEdit->currentProperty());
        //m_classSettings[m_groupIndex].sort();
        m_changed = true;
        updatePropertiesTable();
        generateCode();
        break;
    default:
        break;
    }
    m_classSettings.updateTypeOrder();
}

void Widget::on_dialogEdit_rejected()
{
    //updateUi();
}

void Widget::on_dialogSet_accept()
{
    updateUi();
}

void Widget::on_dialogSet_rejected()
{
    updateUi();
}

void Widget::on_pushButtonAddProperty_clicked()
{
    m_dialogEdit->editNew(m_dialogEdit->currentProperty());
}

void Widget::on_pushButtonEditProperty_clicked()
{
    if (!ui->tableWidgetProperties->selectedItems().isEmpty())
    {
        int propertyIndex = ui->tableWidgetProperties->currentRow();
        m_dialogEdit->editExist(m_classSettings.at(m_groupIndex).at(propertyIndex));
    }
}

void Widget::on_pushButtonExportClass_clicked()
{
    QDir dir(m_currentFile);
    QString dirName = QFileDialog::getExistingDirectory(
                this,
                tr("Select Directory"),
                dir.path(),
                QFileDialog::ShowDirsOnly);
    if (!dirName.isEmpty())
    {
        QDir exportDir(dirName);
        QString headerFileName = m_classSettings.headerFileName();
        QString sourceFileName = m_classSettings.sourceFileName();
        if (exportDir.exists(headerFileName))
        {
            int ret = QMessageBox::question(
                        this,
                        tr("Header file exist"),
                        tr("Header file %1 exist, all modify of this will be lose. "
                           "Are you sure?")
                        .arg(headerFileName),
                        QMessageBox::Yes | QMessageBox::No);
            if (ret != QMessageBox::Yes)
            {
                return;
            }
        }
        if (exportDir.exists(sourceFileName))
        {
            int ret = QMessageBox::question(
                        this,
                        tr("Source file exist"),
                        tr("Source file %1 exist, all modify of this will be lose. "
                           "Are you sure?")
                        .arg(sourceFileName),
                        QMessageBox::Yes | QMessageBox::No);
            if (ret != QMessageBox::Yes)
            {
                return;
            }
        }
        {
            QFile f(exportDir.filePath(headerFileName));
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(m_classSettings.headerFileContent().toUtf8());
            }
        }
        {
            QFile f(exportDir.filePath(sourceFileName));
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(m_classSettings.sourceFileContent().toUtf8());
            }
        }
    }
}

void Widget::on_pushButtonNewProject_clicked()
{
    if (saveChanged())
    {
        m_currentFile.clear();
        m_classSettings = ClassSettings();
        updateUi();
    }
}

void Widget::on_pushButtonOpenProject_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                m_startPath,
                tr("Ini File (*.ini)"));
    if (QFile::exists(fileName))
    {
        loadProperties(fileName);
        m_currentFile = fileName;
    }
}

void Widget::on_pushButtonSaveProject_clicked()
{
    if (QFile::exists(m_currentFile))
    {
        saveProperties(m_currentFile);
    }
    else
    {
        on_pushButtonSaveProjectAs_clicked();
    }
}

void Widget::on_pushButtonSaveProjectAs_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                m_startPath + QDir::separator() + m_classSettings.className(),
                tr("Ini File (*.ini)"));
    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith(".ini"))
        {
            fileName.append(".ini");
        }
        saveProperties(fileName);
        m_currentFile = fileName;
    }
}

void Widget::on_pushButtonSetProject_clicked()
{
    m_dialogSet->editExist(&m_classSettings);
}

void Widget::on_pushButtonRemoveProperty_clicked()
{
    if (!ui->tableWidgetProperties->selectedItems().isEmpty())
    {
        int propertyIndex = ui->tableWidgetProperties->currentRow();
        m_classSettings[m_groupIndex].removeAt(propertyIndex);
        m_changed = true;
        updatePropertiesTable();
        generateCode();
    }
}

void Widget::on_tableWidgetProperties_doubleClicked(const QModelIndex &index)
{
    int propertyIndex = index.row();
    m_dialogEdit->editExist(m_classSettings[m_groupIndex][propertyIndex]);
}

void Widget::generateCode()
{
    QString strHeaderFileContent = m_classSettings.headerFileContent();
    QString strSourceFileContent = m_classSettings.sourceFileContent();
    ui->textBrowserCppDeclares->setText(strHeaderFileContent);
    ui->textBrowserFunctions->setText(strSourceFileContent);
}

void Widget::updateGroupList()
{
    m_classSettings.sort();
    QString current = ui->comboBoxSelectPropertiesGroups->currentText();
    ui->comboBoxSelectPropertiesGroups->blockSignals(true);
    ui->comboBoxSelectPropertiesGroups->clear();
    foreach (QString name, m_classSettings.propertiesGroupsName())
    {
        ui->comboBoxSelectPropertiesGroups->addItem(name);
    }
    ui->comboBoxSelectPropertiesGroups->blockSignals(false);
    int i = ui->comboBoxSelectPropertiesGroups->findText(current);
    if (i >= 0)
    {
        ui->comboBoxSelectPropertiesGroups->setCurrentIndex(i);
    }
    else if (ui->comboBoxSelectPropertiesGroups->count() > 0)
    {
        ui->comboBoxSelectPropertiesGroups->setCurrentIndex(0);
    }
}

void Widget::updatePropertiesTable()
{
    while (ui->tableWidgetProperties->rowCount() != 0)
    {
        ui->tableWidgetProperties->removeRow(0);
    }
    m_propertyItems.clear();
    m_classSettings.sort();
    m_classSettings.updateTypeOrder();
    foreach (Property p, m_classSettings.at(m_groupIndex).properties())
    {
        QSharedPointer<PropertyItem> item(new PropertyItem(p));
        m_propertyItems.append(item);
        int i = ui->tableWidgetProperties->rowCount();
        ui->tableWidgetProperties->insertRow(i);
        int j = 0;
        ui->tableWidgetProperties->setItem(i, j, item->name);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->type);
        j++;
        /*ui->tableWidgetProperties->setItem(i, j, item->typeStringName);
        j++;*/
        ui->tableWidgetProperties->setItem(i, j, item->docName);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->docDetail);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->defaultValue);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->enabled);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->member);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->read);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->write);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->reset);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->notify);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->revision);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->designable);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->scriptable);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->stored);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->user);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->constant);
        j++;
        ui->tableWidgetProperties->setItem(i, j, item->final);
    }
}

void Widget::updateUi()
{
    updateGroupList();
    updatePropertiesTable();
    generateCode();
}

void Widget::loadProperties(const QString &fileName)
{
    /*QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    m_classSettings.setClassName(settings.value("className").toString());
    m_classSettings.setDocName(settings.value("docName").toString());
    m_classSettings.setDocDetail(settings.value("docDetail").toString());
    m_classSettings.setInherits(settings.value("Inherits").toString());
    m_classSettings.setTypeInderitsInfomation(
                (PropertiesGroup::TypeInheritsInformation)
                settings.value("TypeInformation").toInt());
    m_classSettings.setTypeOrder(settings.value("typeOrder").toStringList());
    settings.beginGroup("FunctionsPolicy");
    m_classSettings.setReadFunctionIsInline(
                settings.value("ReadFunctionIsInline").toBool());
    m_classSettings.setWriteFunctionIsInline(
                settings.value("WriteFunctionIsInline").toBool());
    m_classSettings.setWriteFunctionEmitSignal(
                settings.value("WriteFunctionEmitSignal").toBool());
    m_classSettings.setStatementsStartWriteProperty(
                settings.value("WriteFunctionStart").toString());
    m_classSettings.setStatementsMiddleWriteProperty(
                settings.value("WriteFunctionMiddle").toString());
    m_classSettings.setStatementsAfterWriteProperty(
                settings.value("WriteFunctionLast").toString());
    settings.endGroup();
    int size = settings.beginReadArray("properties");
    int i = 0;
    m_classSettings.clear();
    for (; i < size; i++)
    {
        settings.setArrayIndex(i);
        //QString s = settings.value("property").toString();
        Property p;// = Property::fromString(s);
        p.setName(settings.value("name").toString());
        p.setType(settings.value("type").toString());
        p.setTypeStringName(settings.value("typeStringName").toString());
        p.setDocName(settings.value("docName").toString());
        p.setDocDetail(settings.value("docDetail").toString());
        p.setMember(settings.value("member").toBool());
        p.setRead(settings.value("read").toBool());
        p.setWrite(settings.value("write").toBool());
        p.setReset(settings.value("reset").toBool());
        p.setNotify(settings.value("notify").toBool());
        p.setRevision(settings.value("revision").toInt());
        p.setDesignable(settings.value("designable").toBool());
        p.setScriptable(settings.value("scriptable").toBool());
        p.setStored(settings.value("stored").toBool());
        p.setConstant(settings.value("constant").toBool());
        p.setFinal(settings.value("final").toBool());
        p.setEnabled(settings.value("enabled").toBool());
        p.setDefaultValue(settings.value("defaultValue"));
        m_classSettings.append(p);
    }
    settings.endArray();
    updateUi();
    m_changed = false;*/
}

void Widget::loadSettings()
{
    /*QSettings settings(QCoreApplication::applicationDirPath() + QDir::separator()
                       + QString("settings.ini"),
                       QSettings::IniFormat);
    m_startPath = settings.value("StartPath", START_DIR).toString();*/
}

void Widget::saveProperties(const QString &fileName)
{
    /*QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("className", m_classSettings.className());
    settings.setValue("docName", m_classSettings.docName());
    settings.setValue("docDetail", m_classSettings.docDetail());
    settings.setValue("Inherits", m_classSettings.inherits());
    settings.setValue("TypeInformation",
                      (int)m_classSettings.typeInderitsInfomation());
    settings.setValue("typeOrder", m_classSettings.typeOrder());
    settings.beginGroup("FunctionsPolicy");
    settings.setValue("ReadFunctionIsInline",
                      m_classSettings.readFunctionIsInline());
    settings.setValue("WriteFunctionIsInline",
                      m_classSettings.writeFunctionIsInline());
    settings.setValue("WriteFunctionEmitSignal",
                      m_classSettings.writeFunctionEmitSignal());
    settings.setValue("WriteFunctionStart",
                      m_classSettings.statementsStartWriteProperty());
    settings.setValue("WriteFunctionMiddle",
                      m_classSettings.statementsMiddleWriteProperty());
    settings.setValue("WriteFunctionLast",
                      m_classSettings.statementsAfterWriteProperty());
    settings.endGroup();
    settings.beginWriteArray("properties");
    int i = 0;
    for (; i < m_classSettings.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("name", m_classSettings.at(i).name());
        settings.setValue("type", m_classSettings.at(i).type());
        settings.setValue("typeStringName",
                          m_classSettings.at(i).typeStringName());
        settings.setValue("docName", m_classSettings.at(i).docName());
        settings.setValue("docDetail", m_classSettings.at(i).docDetail());
        settings.setValue("member", m_classSettings.at(i).member());
        settings.setValue("read", m_classSettings.at(i).read());
        settings.setValue("write", m_classSettings.at(i).write());
        settings.setValue("reset", m_classSettings.at(i).reset());
        settings.setValue("notify", m_classSettings.at(i).notify());
        settings.setValue("revision", m_classSettings.at(i).revision());
        settings.setValue("designable", m_classSettings.at(i).designable());
        settings.setValue("scriptable", m_classSettings.at(i).scriptable());
        settings.setValue("stored", m_classSettings.at(i).stored());
        settings.setValue("user", m_classSettings.at(i).user());
        settings.setValue("constant", m_classSettings.at(i).constant());
        settings.setValue("final", m_classSettings.at(i).final());
        settings.setValue("enabled", m_classSettings.at(i).enabled());
        settings.setValue("defaultValue", m_classSettings.at(i).defaultValue());
    }
    settings.endArray();
    m_changed = false;*/
}

void Widget::saveSettings()
{
    /*QSettings settings(QCoreApplication::applicationDirPath() + QDir::separator()
                       + QString("settings.ini"),
                       QSettings::IniFormat);*/
}
