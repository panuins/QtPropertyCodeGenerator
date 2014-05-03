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
    typeStringName(NULL),
    docName(NULL),
    docDetail(NULL),
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
    final(NULL),
    enabled(NULL),
    defaultValue(NULL)
{
}

Widget::PropertyItem::PropertyItem(const Property &p) :
    name(new QTableWidgetItem(p.name())),
    type(new QTableWidgetItem(p.type())),
    typeStringName(new QTableWidgetItem(p.typeStringName())),
    docName(new QTableWidgetItem(p.docName())),
    docDetail(new QTableWidgetItem(p.docDetail())),
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
    final(new QTableWidgetItem(boolToStr(p.final()))),
    enabled(new QTableWidgetItem(boolToStr(p.enabled()))),
    defaultValue(new QTableWidgetItem(p.defaultValue().toString()))
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
    m_changed(false)
{
    ui->setupUi(this);
    m_dialogEdit = new DialogEdit(&m_propertiesGroup, this);
    m_dialogSet = new DialogSet(this);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    Property p1("backColor", QVariant::typeToName(QVariant::Color));
    p1.setDocName(QString("背景色"));
    p1.setDocDetail(QString("会重新绘图"));
    p1.setDefaultValue(QString("Qt::black"));
    Property p2("width", QVariant::typeToName(QVariant::Double), "qreal");
    p2.setDocName(QString("宽度"));
    p2.setDocDetail(QString("会重新绘图"));
    p2.setDefaultValue(QString("0.0"));
    m_propertiesGroup.append(p1);
    m_propertiesGroup.append(p2);
    m_propertiesGroup.setClassName("testClass");
    m_propertiesGroup.setInherits("QObject");
    m_propertiesGroup.setTypeInderitsInfomation(PropertiesGroup::inherits_QObject);
    m_propertiesGroup.setReadFunctionIsInline(true);
    m_propertiesGroup.setWriteFunctionIsInline(false);
    m_propertiesGroup.setWriteFunctionEmitSignal(true);
    m_propertiesGroup.setStatementsStartWriteProperty("    StartWrite;\n");
    m_propertiesGroup.setStatementsMiddleWriteProperty("    MiddleWrite;\n");
    m_propertiesGroup.setStatementsAfterWriteProperty("    AfterWrite;\n");
    updateUi();
    connect(m_dialogEdit, SIGNAL(accepted()),
            this, SLOT(on_dialogEdit_accept()));
    connect(m_dialogEdit, SIGNAL(rejected()),
            this, SLOT(on_dialogEdit_rejected()));
    connect(m_dialogSet, SIGNAL(accepted()),
            this, SLOT(on_dialogSet_accept()));
    connect(m_dialogSet, SIGNAL(rejected()),
            this, SLOT(on_dialogSet_rejected()));
}

Widget::~Widget()
{
    delete ui;
}

//取消，返回false，表示不再继续，其它，返回true，表示当前磁盘上的文件为最新的。
bool Widget::saveChanged()
{
    if (m_changed)
    {
        int ret = QMessageBox::question(this,
                                        tr("Save changed?"),
                                        tr("Save changed?"),
                                        QMessageBox::Yes
                                        | QMessageBox::No
                                        | QMessageBox::Cancel);
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

void Widget::on_dialogEdit_accept()
{
    switch (m_dialogEdit->currentMode())
    {
    case DialogEdit::EditExist:
    {
        int index = m_dialogEdit->currentIndex();
        m_propertiesGroup[index] = m_dialogEdit->currentProperty();
        m_changed = true;
        updateUi();
        break;
    }
    case DialogEdit::NewProperty:
        m_propertiesGroup.append(m_dialogEdit->currentProperty());
        m_changed = true;
        updateUi();
        break;
    default:
        break;
    }
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
    m_dialogEdit->editNew();
}

void Widget::on_pushButtonEditProperty_clicked()
{
    if (!ui->tableWidgetProperties->selectedItems().isEmpty())
    {
        int propertyIndex = ui->tableWidgetProperties->currentRow();
        m_dialogEdit->editExist(propertyIndex);
    }
}

void Widget::on_pushButtonExportClass_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this,
                                                        tr("Select Directory"),
                                                        ".",
                                                        QFileDialog::ShowDirsOnly);
    if (!dirName.isEmpty())
    {
        QDir exportDir(dirName);
        QString headerFileName = m_propertiesGroup.headerFileName();
        QString sourceFileName = m_propertiesGroup.sourceFileName();
        if (exportDir.exists(headerFileName))
        {
            int ret = QMessageBox::question(this,
                                            tr("Header file exist"),
                                            tr("Header file %1 exist, "
                                               "all modify of this will be lose. "
                                               "Are you sure?")
                                            .arg(headerFileName),
                                            QMessageBox::Yes
                                            | QMessageBox::No);
            if (ret != QMessageBox::Yes)
            {
                return;
            }
        }
        if (exportDir.exists(sourceFileName))
        {
            int ret = QMessageBox::question(this,
                                            tr("Source file exist"),
                                            tr("Source file %1 exist, "
                                               "all modify of this will be lose. "
                                               "Are you sure?")
                                            .arg(sourceFileName),
                                            QMessageBox::Yes
                                            | QMessageBox::No);
            if (ret != QMessageBox::Yes)
            {
                return;
            }
        }
        {
            QFile f(exportDir.filePath(headerFileName));
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(m_propertiesGroup.headerFileContent().toUtf8());
            }
        }
        {
            QFile f(exportDir.filePath(sourceFileName));
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(m_propertiesGroup.sourceFileContent().toUtf8());
            }
        }
    }
}

void Widget::on_pushButtonNewProject_clicked()
{
    if (saveChanged())
    {
        m_currentFile.clear();
        m_propertiesGroup.clear();
        updateUi();
    }
}

void Widget::on_pushButtonOpenProject_clicked()
{
    //QFileDialog dialog;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    ".",
                                                    tr("Ini File (*.ini)"));
    if (QFile::exists(fileName))
    {
        loadProperties(fileName);
        m_currentFile = fileName;
        /*db.close();
        db.setDatabaseName(fileName);
        db.open();*/
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
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    ".",
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
    m_dialogSet->editExist(&m_propertiesGroup);
}

void Widget::on_pushButtonRemoveProperty_clicked()
{
    if (!ui->tableWidgetProperties->selectedItems().isEmpty())
    {
        int propertyIndex = ui->tableWidgetProperties->currentRow();
        m_propertiesGroup.removeAt(propertyIndex);
        m_changed = true;
        updateUi();
    }
}

void Widget::on_tableWidgetProperties_doubleClicked(const QModelIndex &index)
{
    int propertyIndex = index.row();
    m_dialogEdit->editExist(propertyIndex);
}

void Widget::generateCode()
{
    /*QString qProperty("");
    QString readDeclear("");
    QString writeDeclear("");
    QString signalDeclear("");
    QString memberVars("");
    QString readFunctions("");
    QString writeFunctions("");
    foreach (Property p, m_propertiesGroup.properties())
    {
        if (p.enabled())
        {
            qProperty.append(QString("    ")
                             + p.qPropertyString());
            readDeclear.append(QString("    ")
                               + p.readDeclear());
            writeDeclear.append(QString("    ")
                                + p.writeDeclear());
            signalDeclear.append(QString("    ")
                                 + p.signalDeclear());
            memberVars.append(QString("    ")
                              + p.memberVariableDeclear());
            readFunctions.append(p.readFunctionDefine(m_className,
                                                      m_readFunctionIsInline)
                                 + "\n");
            writeFunctions.append(p.writeFunctionDefine(
                                      m_className,
                                      m_statementsStartWriteProperty,
                                      m_statementsMiddleWriteProperty,
                                      m_statementsAfterWriteProperty,
                                      m_writeFunctionEmitSignal,
                                      m_writeFunctionIsInline)
                                  + "\n");
        }
    }*/
    //ui->textBrowserBatchSet->setText(qProperty);
    /*QString strCppDeclares = QString("%1\n"
                                     "public: \n%2\n"
                                     "public slots: \n%3\n"
                                     "signals: \n%4\n"
                                     "private: \n%5")
            .arg(m_propertiesGroup.generateQPropertyDeclear())
            .arg(m_propertiesGroup.generateReadDeclear())
            .arg(m_propertiesGroup.generateWriteDeclear())
            .arg(m_propertiesGroup.generateSignalDeclear())
            .arg(m_propertiesGroup.generateMemberVariableDeclear());
    ui->textBrowserCppDeclares->setText(strCppDeclares);
    ui->textBrowserFunctions->setText(
                m_propertiesGroup.generateReadFunctionDefine() + "\n"
                + m_propertiesGroup.generateWriteFunctionDefine());*/
    QString strHeaderFileContent = m_propertiesGroup.headerFileContent();
    QString strSourceFileContent = m_propertiesGroup.sourceFileContent();
    ui->textBrowserCppDeclares->setText(strHeaderFileContent);
    ui->textBrowserFunctions->setText(strSourceFileContent);
}

void Widget::updateUi()
{
    while (ui->tableWidgetProperties->rowCount() != 0)
    {
        ui->tableWidgetProperties->removeRow(0);
    }
    m_propertyItems.clear();
    //sortProperties();
    m_propertiesGroup.sort();
    foreach (Property p, m_propertiesGroup.properties())
    {
        QSharedPointer<PropertyItem> item(new PropertyItem(p));
        m_propertyItems.append(item);
        int i = ui->tableWidgetProperties->rowCount();
        ui->tableWidgetProperties->insertRow(i);
        ui->tableWidgetProperties->setItem(i, 0, item->name);
        ui->tableWidgetProperties->setItem(i, 1, item->type);
        ui->tableWidgetProperties->setItem(i, 2, item->typeStringName);
        ui->tableWidgetProperties->setItem(i, 3, item->docName);
        ui->tableWidgetProperties->setItem(i, 4, item->docDetail);
        ui->tableWidgetProperties->setItem(i, 5, item->member);
        ui->tableWidgetProperties->setItem(i, 6, item->read);
        ui->tableWidgetProperties->setItem(i, 7, item->write);
        ui->tableWidgetProperties->setItem(i, 8, item->reset);
        ui->tableWidgetProperties->setItem(i, 9, item->notify);
        ui->tableWidgetProperties->setItem(i, 10, item->revision);
        ui->tableWidgetProperties->setItem(i, 11, item->designable);
        ui->tableWidgetProperties->setItem(i, 12, item->scriptable);
        ui->tableWidgetProperties->setItem(i, 13, item->stored);
        ui->tableWidgetProperties->setItem(i, 14, item->user);
        ui->tableWidgetProperties->setItem(i, 15, item->constant);
        ui->tableWidgetProperties->setItem(i, 16, item->final);
        ui->tableWidgetProperties->setItem(i, 17, item->enabled);
        ui->tableWidgetProperties->setItem(i, 18, item->defaultValue);
    }
    generateCode();
}

void Widget::loadProperties(const QString &fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    m_propertiesGroup.setClassName(settings.value("className").toString());
    m_propertiesGroup.setInherits(settings.value("Inherits").toString());
    m_propertiesGroup.setTypeInderitsInfomation(
                (PropertiesGroup::TypeInheritsInformation)
                settings.value("TypeInformation").toInt());
    settings.beginGroup("FunctionsPolicy");
    m_propertiesGroup.setReadFunctionIsInline(
                settings.value("ReadFunctionIsInline").toBool());
    m_propertiesGroup.setWriteFunctionIsInline(
                settings.value("WriteFunctionIsInline").toBool());
    m_propertiesGroup.setWriteFunctionEmitSignal(
                settings.value("WriteFunctionEmitSignal").toBool());
    m_propertiesGroup.setStatementsStartWriteProperty(
                settings.value("WriteFunctionStart").toString());
    m_propertiesGroup.setStatementsMiddleWriteProperty(
                settings.value("WriteFunctionMiddle").toString());
    m_propertiesGroup.setStatementsAfterWriteProperty(
                settings.value("WriteFunctionLast").toString());
    settings.endGroup();
    int size = settings.beginReadArray("properties");
    int i = 0;
    m_propertiesGroup.clear();
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
        m_propertiesGroup.append(p);
    }
    settings.endArray();
    updateUi();
    m_changed = false;
}

void Widget::saveProperties(const QString &fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("className", m_propertiesGroup.className());
    settings.setValue("Inherits", m_propertiesGroup.inherits());
    settings.setValue("TypeInformation",
                      (int)m_propertiesGroup.typeInderitsInfomation());
    settings.beginGroup("FunctionsPolicy");
    settings.setValue("ReadFunctionIsInline",
                      m_propertiesGroup.readFunctionIsInline());
    settings.setValue("WriteFunctionIsInline",
                      m_propertiesGroup.writeFunctionIsInline());
    settings.setValue("WriteFunctionEmitSignal",
                      m_propertiesGroup.writeFunctionEmitSignal());
    settings.setValue("WriteFunctionStart",
                      m_propertiesGroup.statementsStartWriteProperty());
    settings.setValue("WriteFunctionMiddle",
                      m_propertiesGroup.statementsMiddleWriteProperty());
    settings.setValue("WriteFunctionLast",
                      m_propertiesGroup.statementsAfterWriteProperty());
    settings.endGroup();
    settings.setValue("typeOrder", m_propertiesGroup.typeOrder());
    settings.beginWriteArray("properties");
    int i = 0;
    for (; i < m_propertiesGroup.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("name", m_propertiesGroup.at(i).name());
        settings.setValue("type", m_propertiesGroup.at(i).type());
        settings.setValue("typeStringName",
                          m_propertiesGroup.at(i).typeStringName());
        settings.setValue("docName", m_propertiesGroup.at(i).docName());
        settings.setValue("docDetail", m_propertiesGroup.at(i).docDetail());
        settings.setValue("member", m_propertiesGroup.at(i).member());
        settings.setValue("read", m_propertiesGroup.at(i).read());
        settings.setValue("write", m_propertiesGroup.at(i).write());
        settings.setValue("reset", m_propertiesGroup.at(i).reset());
        settings.setValue("notify", m_propertiesGroup.at(i).notify());
        settings.setValue("revision", m_propertiesGroup.at(i).revision());
        settings.setValue("designable", m_propertiesGroup.at(i).designable());
        settings.setValue("scriptable", m_propertiesGroup.at(i).scriptable());
        settings.setValue("stored", m_propertiesGroup.at(i).stored());
        settings.setValue("user", m_propertiesGroup.at(i).user());
        settings.setValue("constant", m_propertiesGroup.at(i).constant());
        settings.setValue("final", m_propertiesGroup.at(i).final());
        settings.setValue("enabled", m_propertiesGroup.at(i).enabled());
        settings.setValue("defaultValue", m_propertiesGroup.at(i).defaultValue());
    }
    settings.endArray();
    m_changed = false;
}

/*QStringList Widget::propertiesName() const
{
    QStringList list;
    foreach (Property p, m_properties)
    {
        list.append(p.name());
    }
    return list;
}

int Widget::findPropertyByName(const QString &name) const
{
    int i = 0;
    for (; i < m_properties.size(); i++)
    {
        if (m_properties.at(i).name() == name)
        {
            return i;
        }
    }
    return -1;
}

void Widget::sortProperties()
{
    int i = 0, j = 0;
    bool found = false;
    QStringList list = propertiesName();
    QList<Property> listP;
    list.sort();
    list.removeDuplicates();
    for (; i < list.size(); i++)
    {
        found = false;
        for (j = 0; j < m_properties.size(); j++)
        {
            if (m_properties.at(j).name() == list.at(i))
            {
                listP.append(m_properties.at(j));
                found = true;
            }
        }
        if (!found)
        {
            std::cout << "Widget::sortProperties: Can not find property "
                      << list.at(i).toStdString() << std::endl;
        }
    }
    m_properties = listP;
}*/
