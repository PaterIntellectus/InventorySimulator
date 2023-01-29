#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H

#include <QVariant>
#include <QMetaType>

class InventorySlot
{
public:
    InventorySlot(int inventory_id, int num, int item_id = 0, int item_quantity = 0);

    int inventoryId() const { return mInventoryId; }
    int num() const { return mNum; }
    int itemId() const { return mItemId; }
    int itemQuantity() const { return mItemQuantity; }

private:
    int mInventoryId;
    int mNum;
    int mItemId;
    int mItemQuantity;
};

#endif // INVENTORYSLOT_H
