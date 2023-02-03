#ifndef CONFIGS_H
#define CONFIGS_H

#include <QString>

static const int USERINVENTORYID{ 0 };
static const int APPLETREEINVENTORYID{ 1 };

static const int INVENTORYCELLSIZE{ 100 };

static const QString SOUNDSFOLDER{ "./sounds/" };
static const QString IMAGESFOLDER{ "./images/"};

static const QString APPLEIMAGE{ IMAGESFOLDER + "apple.png"};

static const QString DBTYPE{ "QSQLITE" };
static const QString DBNAME{ "InventorySimulator.db" };





//auto dropItem{ itemAt(event->position().toPoint()) };
//if (!dropItem) {
//    setItem(row, column, draggedItem->clone());
////        dropItem = itemAt(event->position().toPoint());
//}
//qDebug() << "before quantity:" << item(row, column)->text();

//if (sourceTable->isSource()) {
//    item(row, column)->setText(QString::number(item(row, column)->text().toInt() + 1));
//}
//else if (dropItem && draggedItem != dropItem) {
//    item(row, column)->setText(QString::number(item(row, column)->text().toInt() + draggedItem->text().toInt()));
//}
//else {
//    item(row, column)->setText(QString::number(draggedItem->text().toInt()));
//}
//qDebug() << "after quantity:" << item(row, column)->text();

#endif // CONFIGS_H
