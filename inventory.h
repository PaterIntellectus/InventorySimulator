#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>

class Inventory
{
public:
    Inventory(int id, int rows_num, int columns_num, const QString &inventory_name, bool is_source);

    int id() const { return mId; }
    const QString &inventoryName() const { return mInventoryName; }
    int rowsNum() const { return mRowsNum; }
    int columnsNum() const { return mColumnsNum; }
    bool isSource() const { return mIsSource; }

    int countSlots() const { return rowsNum() * columnsNum(); };

private:
    int mId;
    int mRowsNum;
    int mColumnsNum;
    QString mInventoryName;
    bool mIsSource;
};

#endif // INVENTORY_H
