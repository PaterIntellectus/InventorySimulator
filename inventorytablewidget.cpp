#include "inventorytablewidget.h"

InventoryTableWidget::InventoryTableWidget(const Inventory &inventory, QWidget *parent)
    : QTableWidget(inventory.rowsNum(), inventory.columnsNum(), parent ), mId{ inventory.id() }, mName{ inventory.inventoryName() }
{
    configureAppearance();

    setDragEnabled(true);
    setAcceptDrops(true);
}

InventoryTableWidget::~InventoryTableWidget()
{

}

void InventoryTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        auto item{ itemAt(event->pos()) };
        if (!item) {
            return;
        }
        delete item;
    } else {
        QTableWidget::mousePressEvent(event);
    }
}

void InventoryTableWidget::configureAppearance()
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

void InventoryTableWidget::deleteItem(const QPoint &pos)
{
    QTableWidgetItem *item = itemAt(pos);
    if (!item) {
        qDebug() << "Didn't fing the item";
        return;
    }
    qDebug() << "item found";

    item->setData(
                Qt::DecorationRole,
                QPixmap()
                );
}
