#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QTableWidget>
#include <QHeaderView>

static const int inventoryCellSize = 100;

class InventoryTable : public QTableWidget
{
    Q_OBJECT
public:
    InventoryTable(int rows, int columns, QWidget *parent);
    ~InventoryTable();

};

#endif // INVENTORYTABLE_H
