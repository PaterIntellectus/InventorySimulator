#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QTableWidget>
#include <QHeaderView>

#include "inventory.h"

static const int inventoryCellSize = 100;

class InventoryTable : public QTableWidget
{
    Q_OBJECT
public:
//    InventoryTable(int id, const QString &inventory_name, int rows, int columns, QWidget *parent);
    InventoryTable(const Inventory &inventory, QWidget *parent = nullptr);
    ~InventoryTable();

    int id() const { return mId; }

private:
    int mId;
    QString mName;

    void configureAppearance();

};

#endif // INVENTORYTABLE_H
