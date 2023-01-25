#include "inventorytable.h"

InventoryTable::InventoryTable(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
    horizontalHeader()->hide();
    verticalHeader()->hide();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i{}; i < rows; ++i) {
        setRowHeight(i, inventoryCellSize);
    }
    for (int i{}; i < columns; ++i) {
        setColumnWidth(i, inventoryCellSize);
    }
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    adjustSize();
}

InventoryTable::~InventoryTable()
{

}
