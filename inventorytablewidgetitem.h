#ifndef INVENTORYTABLEWIDGETITEM_H
#define INVENTORYTABLEWIDGETITEM_H

#include <QTableWidgetItem>
//#include <QObject>
//#include <QWidget>

#include "inventoryslot.h"
#include "item.h"
#include "config.h"

class InventoryTableWidgetItem : public QTableWidgetItem
{
//    Q_OBJECT
public:
    InventoryTableWidgetItem(const InventorySlot &inventorySlot, const Item &item);

    int mItemId;
};

#endif // INVENTORYTABLEWIDGETITEM_H
