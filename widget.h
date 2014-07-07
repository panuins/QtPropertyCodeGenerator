/*****************************************************************************
 * widget.h:
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
#ifndef WIDGET_H
#define WIDGET_H

#include "classsettings.h"
#include "dialogedit.h"
#include "dialogset.h"
#include <QCloseEvent>
#include <QList>
#include <QSharedPointer>
#include <QString>
#include <QTableWidgetItem>
#include <QVector>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    /*enum TypeInheritsInformation
    {
        inherits_None,
        inherits_QObject,
        inherits_QWidget,
        inherits_QQuickItem,
    };*/

    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool saveChanged();
    bool saveProject();
    bool saveProjectAs();

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_comboBoxSelectPropertiesGroups_currentIndexChanged(const QString &arg1);
    void on_dialogEdit_accept();
    void on_dialogEdit_rejected();
    void on_dialogSet_accept();
    void on_dialogSet_rejected();
    void on_pushButtonAddProperty_clicked();
    void on_pushButtonEditProperty_clicked();
    void on_pushButtonExportClass_clicked();
    void on_pushButtonNewProject_clicked();
    void on_pushButtonOpenProject_clicked();
    void on_pushButtonRemoveProperty_clicked();
    void on_pushButtonSaveProject_clicked();
    void on_pushButtonSaveProjectAs_clicked();
    void on_pushButtonSetProject_clicked();
    void on_tableWidgetProperties_doubleClicked(const QModelIndex &index);

    void generateCode();
    void updateGroupList();
    void updatePropertiesTable();
    void updateUi();

private:
    class PropertyItem
    {
    public:
        PropertyItem();
        PropertyItem(const Property &p);
        ~PropertyItem();

        QTableWidgetItem *name;
        QTableWidgetItem *type;
        //QTableWidgetItem *typeStringName;
        QTableWidgetItem *docName;
        QTableWidgetItem *docDetail;
        QTableWidgetItem *defaultValue;
        QTableWidgetItem *enabled;
        QTableWidgetItem *member;
        QTableWidgetItem *read;
        QTableWidgetItem *write;
        QTableWidgetItem *reset;
        QTableWidgetItem *notify;
        QTableWidgetItem *revision;
        QTableWidgetItem *designable;
        QTableWidgetItem *scriptable;
        QTableWidgetItem *stored;
        QTableWidgetItem *user;
        QTableWidgetItem *constant;
        QTableWidgetItem *final;
    };

    void loadProperties(const QString &fileName);
    void loadSettings();
    void saveProperties(const QString &fileName);
    void saveSettings();
    /*QStringList propertiesName() const;
    int findPropertyByName(const QString &name) const;
    void sortProperties();*/

    //PropertiesGroup m_propertiesGroup;
    ClassSettings m_classSettings;
    QVector<QSharedPointer<PropertyItem> > m_propertyItems;
    QString m_currentFile;
    QString m_startPath;
    Ui::Widget *ui;
    DialogEdit *m_dialogEdit;
    DialogSet *m_dialogSet;
    int m_groupIndex;
    //int m_propertyIndex;
    bool m_changed;
    //QSqlDatabase db;
};

#endif // WIDGET_H
