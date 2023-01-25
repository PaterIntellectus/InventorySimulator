#include "databasemanager.h"

DataBaseManager::DataBaseManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("mydatabase.db");


}
