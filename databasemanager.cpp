#include "databasemanager.h"

DatabaseManager::DatabaseManager(QWidget *parent, const QString &dbtype, const QString &dbname)
    : QObject{ parent }
{
    mDatabase = QSqlDatabase::addDatabase(dbtype);
    mDatabase.setDatabaseName(dbname);

    if (!mDatabase.open()) {
        qDebug() << "Error: connection with database failed";
        return;
    }
    qDebug() << "Database: connection established";

    mQuery = QSqlQuery(mDatabase);

    initTables();
    initInventories();
    initItems();
    initInventorySlots();
}

void DatabaseManager::initTables()
{
    // inventory
    mQuery.exec(
                QStringLiteral(
                    "CREATE TABLE inventory("
                    "id INTEGER NOT NULL, "
                    "rows_num INTEGER NOT NULL, "
                    "columns_num INTEGER NOT NULL, "
                    "inventory_name VARCHAR(255) NOT NULL, "

                    "PRIMARY KEY (id)"
                    ");"
                    )
                );
    if (!mQuery.isActive()) {
        showLastError();
    } else {
        qDebug() << "Table inventory created";
    }

    // inventory_slot
    mQuery.exec(
                QStringLiteral(
                    "CREATE TABLE inventory_slot("
                    "inventory_id INTEGER NOT NULL, "
                    "num INTEGER NOT NULL, "
                    "item_id INTEGER, "
                    "item_quantity INTEGER, "

                    "PRIMARY KEY (inventory_id, num), "
                    "FOREIGN KEY (inventory_id) REFERENCES inventory(id)"
                    "FOREIGN KEY (item_id) REFERENCES item(id)"
                    ");"
                    )
                );
    if (!mQuery.isActive()) {
        showLastError();
    } else {
        qDebug() << "Table inventory_slot created";
    }

    // item
    mQuery.exec(
                QStringLiteral(
                    "CREATE TABLE item("
                    "id INTEGER NOT NULL, "
                    "item_name VARCHAR(255) NOT NULL, "
                    "image_path TEXT NOT NULL, "

                    "PRIMARY KEY (id)"
                    ");"
                    )
                );
    if (!mQuery.isActive()) {
        showLastError();
    } else {
        qDebug() << "Table item created";
    }
}

void DatabaseManager::initInventories()
{
    if (!insertInventory(Inventory(0, 3, 3, QStringLiteral("User")))) {
        showLastError();
    } else {
        qDebug() << "User inventory initialized";
    }

    if (!insertInventory(Inventory(1, 1, 1, QStringLiteral("Apple tree")))) {
        showLastError();
    } else {
        qDebug() << "Apple tree inventory initialized";
    }
}

void DatabaseManager::initInventorySlots()
{
    for (int i{}; selectInventory(i) && mQuery.next(); ++i) {
        auto inventory{ getInventory(i) };
        for (int j{}; j < inventory->countSlots(); ++j) {
            if (!insertInventorySlot(InventorySlot(inventory->id(), j))) {
               showLastError();
            } else {
               qDebug() << "Inventory slot #" << i << '.' << j << "initialized";
            }
        }
    }
}

void DatabaseManager::initItems()
{
    if (!insertItem(Item(1, "Apple", "images/apple.png"))) {
        showLastError();
    } else {
        qDebug() << "Apple item initialized";
    }
}

bool DatabaseManager::insertInventory(const Inventory &inventory)
{
    mQuery.prepare(
                QStringLiteral(
                    "INSERT INTO inventory (id, rows_num, columns_num, inventory_name)"
                    "VALUES (:id, :rows_num, :columns_num, :inventory_name)"
                    )
                );
    mQuery.bindValue(QStringLiteral(":id"), inventory.id());
    mQuery.bindValue(QStringLiteral(":rows_num"), inventory.rowsNum());
    mQuery.bindValue(QStringLiteral(":columns_num"), inventory.columnsNum());
    mQuery.bindValue(QStringLiteral(":inventory_name"), inventory.inventoryName());
    return mQuery.exec();
}

bool DatabaseManager::insertInventorySlot(const InventorySlot &inventory_slot)
{
    mQuery.prepare(
                QStringLiteral(
                    "INSERT INTO inventory_slot (inventory_id, num, item_id, item_quantity)"
                    "VALUES (:inventory_id, :num, :item_id, :item_quantity)"
                    )
                );
    mQuery.bindValue(QStringLiteral(":inventory_id"), inventory_slot.inventoryId());
    mQuery.bindValue(QStringLiteral(":num"), inventory_slot.num());
    mQuery.bindValue(QStringLiteral(":item_id"), inventory_slot.itemId());
    mQuery.bindValue(QStringLiteral(":item_quantity"), inventory_slot.itemQuantity());
    return mQuery.exec();
}

bool DatabaseManager::insertItem(const Item &item)
{
    mQuery.prepare(
                QStringLiteral(
                    "INSERT INTO item (id, item_name, image_path)"
                    "VALUES (:id, :item_name, :image_path)"
                    )
                );
    mQuery.bindValue(QStringLiteral(":id"), item.id());
    mQuery.bindValue(QStringLiteral(":item_name"), item.itemName());
    mQuery.bindValue(QStringLiteral(":image_path"), item.imagePath());
    return mQuery.exec();
}

bool DatabaseManager::selectInventory(int id)
{
    mQuery.prepare(
                QStringLiteral(
                    "SELECT * FROM inventory "
                    "WHERE id = :id;"
                    )
                );
    mQuery.bindValue(QStringLiteral(":id"), id);
    return mQuery.exec();
}

bool DatabaseManager::selectInventorySlot(int inventory_id, int num)
{
    mQuery.prepare(
                QStringLiteral(
                    "SELECT * FROM inventory_slot "
                    "WHERE inventory_id = :inventory_id AND num = :num;"
                    )
                );
    mQuery.bindValue(QStringLiteral(":inventory_id"), inventory_id);
    mQuery.bindValue(QStringLiteral(":num"), num);
    return mQuery.exec();
}

bool DatabaseManager::selectItem(int id)
{
    mQuery.prepare(
                QStringLiteral(
                    "SELECT * FROM item "
                    "WHERE id = :id;"
                    )
                );
    mQuery.bindValue(QStringLiteral(":id"), id);
    return mQuery.exec();
}

bool DatabaseManager::updateInventory(const Inventory &inventory)
{
    mQuery.prepare(
                QStringLiteral(
                    "UPDATE inventory "
                    "SET rows_num = :rows_num, columns_num = :columns_num, inventory_name = :inventory_name "
                    "WHERE id = :id;"
                    )
                );
    mQuery.bindValue(QStringLiteral(":id"), inventory.id());
    mQuery.bindValue(QStringLiteral(":rows_num"), inventory.columnsNum());
    mQuery.bindValue(QStringLiteral(":columns_num"), inventory.rowsNum());
    mQuery.bindValue(QStringLiteral(":inventory_name"), inventory.inventoryName());
    return mQuery.exec();
}

bool DatabaseManager::updateInventorySlot(const InventorySlot &slot)
{
    mQuery.prepare(
                QStringLiteral(
                    "UPDATE inventory_slot "
                    "SET item_id = :item_id, item_quantity = :item_quantity "
                    "WHERE inventory_id = :inventory_id AND num = :num;"
                    )
                );
    mQuery.bindValue(QStringLiteral(":inventory_id"), slot.inventoryId());
    mQuery.bindValue(QStringLiteral(":num"), slot.num());
    mQuery.bindValue(QStringLiteral(":item_id"), slot.itemId());
    mQuery.bindValue(QStringLiteral(":item_quantity"), slot.itemQuantity());
    return mQuery.exec();
}

bool DatabaseManager::updateItem(const Item &item)
{
    mQuery.prepare(
                QStringLiteral(
                    "UPDATE item "
                    "SET item_name = :item_name, image_path = :image_path "
                    "WHERE id = :id;"
                    )
                );
    mQuery.bindValue(QStringLiteral(":id"), item.id());
    mQuery.bindValue(QStringLiteral(":item_name"), item.itemName());
    mQuery.bindValue(QStringLiteral(":image_path"), item.imagePath());
    return mQuery.exec();
}

std::optional<Inventory> DatabaseManager::getInventory(int id)
{
    if (!selectInventory(id) || !mQuery.next()) {
        showLastError();
        return std::nullopt;
    }
    return Inventory(
                mQuery.value(mQuery.record().indexOf("id")).toInt(),
                mQuery.value(mQuery.record().indexOf("rows_num")).toInt(),
                mQuery.value(mQuery.record().indexOf("columns_num")).toInt(),
                mQuery.value(mQuery.record().indexOf("inventory_name")).toString()
                );
}

std::optional<InventorySlot> DatabaseManager::getInventorySlot(int inventory_id, int num)
{
    if (!selectInventorySlot(inventory_id, num) || !mQuery.next()) {
        showLastError();
        return std::nullopt;
    }
    return InventorySlot(
                mQuery.value(mQuery.record().indexOf("inventory_id")).toInt(),
                mQuery.value(mQuery.record().indexOf("num")).toInt(),
                mQuery.value(mQuery.record().indexOf("item_id")).toInt(),
                mQuery.value(mQuery.record().indexOf("item_quantity")).toInt()
                );
}

std::optional<Item> DatabaseManager::getItem(int id)
{
    if (!selectItem(id) || !mQuery.next()) {
        showLastError();
        return std::nullopt;
    }
    return Item(
                mQuery.value(mQuery.record().indexOf("id")).toInt(),
                mQuery.value(mQuery.record().indexOf("item_name")).toString(),
                mQuery.value(mQuery.record().indexOf("image_path")).toString()
                );
}

bool DatabaseManager::showSelectedTables()
{
    if (!mQuery.isSelect()) {
        return false;
    }
    while (mQuery.next()) {
        for (int i{}; i < mQuery.record().count(); ++i) {
            qDebug() << mQuery.record().fieldName(i) << ": " << mQuery.value(i).toString();
        }
    }
    return true;
}

void DatabaseManager::showLastError()
{
    qDebug() << "Error: " << mQuery.lastError();
}

