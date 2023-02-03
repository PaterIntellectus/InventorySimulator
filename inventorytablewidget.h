#ifndef INVENTORYTABLEWIDGET_H
#define INVENTORYTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>

#include <QMediaPlayer>
#include <QAudioOutput>

#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>

#include "inventory.h"
#include "inventorytablewidgetitem.h"
#include "databasemanager.h"
#include "config.h"

class InventoryTableWidget : public QTableWidget
{
    Q_OBJECT
public:
//    InventoryTableWidget(const Inventory &inventory, QWidget *parent = nullptr);
    InventoryTableWidget(int inventory_id, DatabaseManager *dbmanager, QWidget *parent = nullptr);
    ~InventoryTableWidget();

    int id() const { return mId; }
    QString name() const { return mName; }
    bool isSource() const { return mIsSource; }

    virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event) override { return false; }

protected:
    virtual void dropEvent(QDropEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void useItem(const QPoint &pos);
    void deleteItem(QTableWidgetItem *item);
    void deleteStack(QTableWidgetItem *item);

private:
    int mId;
    QString mName;
    bool mIsSource;

    QMediaPlayer *player{ nullptr };
    QAudioOutput *audioOutput{ nullptr };

    void initSlots(const Inventory &inventory, DatabaseManager *dbmanager);
    void initMediaPlayer();

    void configureAppearance();
};

#endif // INVENTORYTABLEWIDGET_H
