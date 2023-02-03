#include "inventorytablewidgetitem.h"

InventoryTableWidgetItem::InventoryTableWidgetItem(const InventorySlot &inventorySlot, const Item &item)
    : QTableWidgetItem(), mItemId{ item.id() }
{
    setIcon(QPixmap(item.imagePath()));
    if (inventorySlot.itemQuantity() > 1) {
        setText(QString::number(inventorySlot.itemQuantity()));
    }
    setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
}
