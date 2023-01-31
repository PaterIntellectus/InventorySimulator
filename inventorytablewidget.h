#ifndef INVENTORYTABLEWIDGET_H
#define INVENTORYTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>

#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>

#include "inventory.h"

static const int inventoryCellSize = 100;

class InventoryTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    InventoryTableWidget(const Inventory &inventory, QWidget *parent = nullptr);
    ~InventoryTableWidget();

    int id() const { return mId; }
    QString name() const { return mName; }

    virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event) override { return false; }

protected:
//    virtual void dropEvent(QDropEvent *event) override;
//    virtual void dragEnterEvent(QDragEnterEvent *event) override;
//    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
//    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void deleteItem(const QPoint &pos);

private:
    int mId;
    QString mName;
    bool mIsSource;

    void configureAppearance();
};

#endif // INVENTORYTABLEWIDGET_H
