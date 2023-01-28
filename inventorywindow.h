#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "inventorytable.h"
#include "databasemanager.h"
#include "inventory.h"

#include <QHBoxLayout>
#include <QGridLayout>


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

    InventoryTable *userInventory{ nullptr };
    InventoryTable *appleTreeInventory{ nullptr };
    QPushButton *mainMenuBtn{ nullptr };

    DatabaseManager *databaseManager{ nullptr };

    void initWidgets();
    void initConnections() const;

    void initUserInventory();
    void initAppleTreeInventory();

    void initInventorySlots(InventoryTable *inventoryTable);

};

#endif // INVENTORYWINDOW_H
