#ifndef WIDGET_H
#define WIDGET_H

#include "propertiesgroup.h"
#include "dialogedit.h"
#include "dialogset.h"
#include <QCloseEvent>
#include <QList>
#include <QSharedPointer>
#include <QSqlDatabase>
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
        QTableWidgetItem *typeStringName;
        QTableWidgetItem *docName;
        QTableWidgetItem *docDetail;
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
        QTableWidgetItem *enabled;
        QTableWidgetItem *defaultValue;
    };

    void loadProperties(const QString &fileName);
    void saveProperties(const QString &fileName);
    /*QStringList propertiesName() const;
    int findPropertyByName(const QString &name) const;
    void sortProperties();*/

    PropertiesGroup m_propertiesGroup;
    QVector<QSharedPointer<PropertyItem> > m_propertyItems;
    QString m_currentFile;
    Ui::Widget *ui;
    DialogEdit *m_dialogEdit;
    DialogSet *m_dialogSet;
    bool m_changed;
    //QSqlDatabase db;
};

#endif // WIDGET_H
