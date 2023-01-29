#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>

#include <QDebug>

#include <QtSql>

#include "databaseconfig.h"
#include "inventory.h"
#include "inventoryslot.h"
#include "item.h"

#include <optional>

class DatabaseManager : QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(
            QWidget *parent = nullptr,
            const QString &dbtype = DBTYPE,
            const QString &dbname = DBNAME
            );

    std::optional<Inventory> getInventory(int id);
    std::optional<InventorySlot> getInventorySlot(int inventory_id, int num);
    std::optional<Item> getItem(int id);

private:
    QSqlDatabase mDatabase;
    QSqlQuery mQuery;

    void initTables();
    void initInventories();
    void initInventorySlots();
    void initItems();

    bool insertInventory(const Inventory &inventory);
    bool insertInventorySlot(const InventorySlot &slot);
    bool insertItem(const Item& item);

    bool selectInventory(int id);
    bool selectInventorySlot(int inventory_id, int num);
    bool selectItem(int id);

    bool updateInventory(const Inventory &inventory);
    bool updateInventorySlot(const InventorySlot &slot);
    bool updateItem(const Item& item);

    bool showSelectedTables();
    void showLastError();
};

#endif // DATABASEMANAGER_H
