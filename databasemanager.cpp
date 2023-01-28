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
        qDebug() << "Error: " << mQuery.lastError();
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
                    "FOREIGN KEY(inventory_id) REFERENCES inventory(id)"
                    "FOREIGN KEY(item_id) REFERENCES item(id)"
                    ");"
                    )
                );
    if (!mQuery.isActive()) {
        qDebug() << "Error: " << mQuery.lastError();
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
        qDebug() << "Error: " << mQuery.lastError();
    } else {
        qDebug() << "Table item created";
    }
}

void DatabaseManager::initInventories()
{
    if (!insertInventory(Inventory(0, 3, 3, QStringLiteral("User")))) {
        qDebug() << "Error: " << mQuery.lastError();
    } else {
        qDebug() << "User inventory initialized";
    }

    if (!insertInventory(Inventory(1, 1, 1, QStringLiteral("Apple tree")))) {
        qDebug() << "Error: " << mQuery.lastError();
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
               qDebug() << "Error: " << mQuery.lastError();
           } else {
               qDebug() << "Inventory slot #" << i << '.' << j << "initialized";
           }
        }
    }
}

void DatabaseManager::initItems()
{
    if (!insertItem(Item(0, "Apple", "images/apple.png"))) {
        qDebug() << "Error: " << mQuery.lastError();
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
    mQuery.bindValue(QStringLiteral(":item_name"), item.item_name());
    mQuery.bindValue(QStringLiteral(":image_path"), item.image_path());
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

std::optional<Inventory> DatabaseManager::getInventory(int id)
{
    if (!selectInventory(id)) {
        qDebug() << "Error: " << mQuery.lastError();
        return std::nullopt;
    }
    mQuery.next();
    return Inventory(
                mQuery.value(mQuery.record().indexOf("id")).toInt(),
                mQuery.value(mQuery.record().indexOf("rows_num")).toInt(),
                mQuery.value(mQuery.record().indexOf("columns_num")).toInt(),
                mQuery.value(mQuery.record().indexOf("inventory_name")).toString()
                );
}

std::optional<InventorySlot> DatabaseManager::getInventorySlot(int inventory_id, int num)
{
    if (!selectInventorySlot(inventory_id, num)) {
        qDebug() << "Error: " << mQuery.lastError();
        return std::nullopt;
    }
    mQuery.next();
    return InventorySlot(
                mQuery.value(mQuery.record().indexOf("inventory_id")).toInt(),
                mQuery.value(mQuery.record().indexOf("num")).toInt(),
                mQuery.value(mQuery.record().indexOf("item_id")).toInt(),
                mQuery.value(mQuery.record().indexOf("item_quantity")).toInt()
                );
}

std::optional<Item> DatabaseManager::getItem(int id)
{
    if (!selectItem(id)) {
        qDebug() << "Error: " << mQuery.lastError();
        return std::nullopt;
    }
    mQuery.next();
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

