#include "inventorytable.h"

//InventoryTable::InventoryTable(int id, const QString & inventory_name, int rows, int columns, QWidget *parent)
//    : QTableWidget(rows, columns, parent)
//{

//    configureAppearance();
//}

InventoryTable::InventoryTable(const Inventory &inventory, QWidget *parent)
    : QTableWidget(inventory.rowsNum(), inventory.columnsNum(), parent ), mId{ inventory.id() }, mName{ inventory.inventoryName() }
{
    configureAppearance();
}

InventoryTable::~InventoryTable()
{

}

void InventoryTable::configureAppearance()
{
    horizontalHeader()->hide();
    verticalHeader()->hide();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i{}; i < rowCount(); ++i) {
        setRowHeight(i, inventoryCellSize);
    }
    for (int i{}; i < columnCount(); ++i) {
        setColumnWidth(i, inventoryCellSize);
    }
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    adjustSize();
}
