#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

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

    QTableWidget *inventoryTable{ nullptr };


    void initWidgets();
    void initConnections();
};

#endif // INVENTORYWINDOW_H
