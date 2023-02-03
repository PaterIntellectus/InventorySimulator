#include "inventorytablewidget.h"


//InventoryTableWidget::InventoryTableWidget(const Inventory &inventory, QWidget *parent)
//    : QTableWidget(inventory.rowsNum(), inventory.columnsNum(), parent ),
//      mId{ inventory.id() }, mName{ inventory.inventoryName() }, mIsSource{ inventory.isSource() }
//{
//    configureAppearance();

//    setDragEnabled(true);
//    setAcceptDrops(true);
//}

InventoryTableWidget::InventoryTableWidget(int inventory_id, DatabaseManager *dbmanager, QWidget *parent)
    : QTableWidget(parent)
{
    auto optInventory{ dbmanager->getInventory(inventory_id) };
    if (!optInventory) {
        qDebug() <<
                    "Can't initialize the inventory with id:" << inventory_id << "\n"
                    "there is no such table in database";
        return;
    }
    mId = optInventory->id();
    mName = optInventory->inventoryName();
    mIsSource = optInventory->isSource();

    setRowCount(optInventory->rowsNum());
    setColumnCount(optInventory->columnsNum());

    initSlots(optInventory.value(), dbmanager);
    initMediaPlayer();

    configureAppearance();
    setDragEnabled(true);
    if (!optInventory->isSource()) {
        setAcceptDrops(true);
    }
}

InventoryTableWidget::~InventoryTableWidget()
{

}

void InventoryTableWidget::dropEvent(QDropEvent *event)
{
    auto sourceTable{ qobject_cast<InventoryTableWidget*>(event->source()) };
    auto draggedItem{ sourceTable->currentItem() };
    if (!draggedItem) { return; }

    auto row{ event->position().y() / INVENTORYCELLSIZE };
    auto column{ event->position().x() / INVENTORYCELLSIZE };

    auto dropItem{ itemAt(event->position().toPoint()) };
    if (!dropItem) {
        setItem(row, column, draggedItem->clone());
    }

    if (sourceTable->isSource()) {
        item(row, column)->setText(QString::number(item(row, column)->text().toInt() + 1));
    }
    else if (dropItem && draggedItem != dropItem) {
        item(row, column)->setText(QString::number(item(row, column)->text().toInt() + draggedItem->text().toInt()));
    }
    else {
        item(row, column)->setText(QString::number(draggedItem->text().toInt()));
    }

    if (!sourceTable->isSource() && draggedItem != dropItem) {
        deleteStack(draggedItem);
    }
    event->accept();
}

void InventoryTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (!isSource() && event->button() == Qt::RightButton) {
        useItem(event->pos());
    } else {
        QTableWidget::mousePressEvent(event);
    }
}

void InventoryTableWidget::useItem(const QPoint &pos)
{
    auto item{ itemAt(pos) };
    deleteItem(item);

    // playing item.use_sound_effect:
    // in the future the sound playing when item used
    // can depend on the item itself
    // for now it's just playing only one sound
    if (item) {
        player->setSource(QUrl::fromLocalFile(SOUNDSFOLDER + "biting_apple.mp3"));
        player->stop();
        player->play();
    }
}

void InventoryTableWidget::deleteItem(QTableWidgetItem *item)
{
    if (!item || isSource()) { return; }
    if (item->text().toInt() > 1) {
        item->setText(QString::number(item->text().toInt() - 1));
    } else {
        delete item;
    }
}

void InventoryTableWidget::deleteStack(QTableWidgetItem *item)
{
    if (!item || isSource()) { return; }
    delete item;
}

void InventoryTableWidget::initSlots(const Inventory &inventory, DatabaseManager *dbmanager)
{
    int slotNum{};

    for (int i{}; i < rowCount(); ++i) {
        for (int j{}; j < columnCount(); ++j) {
            auto optSlot{ dbmanager->getInventorySlot(inventory.id(), slotNum++) };
            if (optSlot->itemQuantity()) {
                auto *tableItem{ new InventoryTableWidgetItem(optSlot.value(), dbmanager->getItem(optSlot->itemId()).value()) };
                setItem(i, j, tableItem);
            }
        }
    }
}

void InventoryTableWidget::initMediaPlayer()
{
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
}

void InventoryTableWidget::configureAppearance()
{
    // removing headers and scroll bars
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // setting size of cells and icons
    for (int i{}; i < rowCount(); ++i) {
        setRowHeight(i, INVENTORYCELLSIZE);
    }
    for (int i{}; i < columnCount(); ++i) {
        setColumnWidth(i, INVENTORYCELLSIZE);
    }
    setIconSize(QSize(INVENTORYCELLSIZE, INVENTORYCELLSIZE));

    // removing the ability fo the text to elide
    // it makes the text visible even if the icon occupies the whole space of the cell
    setTextElideMode(Qt::ElideNone);

    // some size adjustments of the table
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    adjustSize();
}
