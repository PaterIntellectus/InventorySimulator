#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DataBaseManager : QObject
{
    Q_OBJECT
public:
    DataBaseManager(
            const QString& dbtype = QStringLiteral("QSQLITE"),
            const QString& dbname = QStringLiteral("InventorySimulator.db")
            );


private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
