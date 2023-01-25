#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "inventorytable.h"
#include "databasemanager.h"

#include <QHBoxLayout>
#include <QGridLayout>

#include <QtSql>

namespace Ui {
class InventoryWindow;
}

class InventoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InventoryWindow(QWidget *parent = nullptr);
    ~InventoryWindow();

private:
    Ui::InventoryWindow *ui;

    InventoryTable *myInventory{ nullptr };
    InventoryTable *storageInventory{ nullptr };
    QPushButton *mainMenuBtn{ nullptr };

    DataBaseManager *databaseManager{ nullptr };

    void initWidgets();
    void initConnections();
};

#endif // INVENTORYWINDOW_H
