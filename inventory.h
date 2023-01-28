#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>

class Inventory
{
public:
    Inventory(int id, int rows_num, int columns_num, const QString &inventory_name);

    int id() const { return mId; }
    QString inventoryName() const { return mInventoryName; }
    int rowsNum() const { return mRowsNum; }
    int columnsNum() const { return mColumnsNum; }

    int countSlots() const { return rowsNum() * columnsNum(); };

private:
    int mId;
    int mRowsNum;
    int mColumnsNum;
    QString mInventoryName;
};

#endif // INVENTORY_H
