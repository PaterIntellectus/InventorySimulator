#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "inventorytablewidget.h"
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

    InventoryTableWidget *userInventory{ nullptr };
    InventoryTableWidget *appleTreeInventory{ nullptr };
    QPushButton *mainMenuBtn{ nullptr };

    DatabaseManager *databaseManager{ nullptr };

    void initWidgets();
    void initConnections() const;

    void initUserInventory();
    void initAppleTreeInventory();

    void initInventorySlots(InventoryTableWidget *inventoryTable);

};

#endif // INVENTORYWINDOW_H
