#include "inventorywindow.h"
#include "ui_inventorywindow.h"

InventoryWindow::InventoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InventoryWindow)
{
    ui->setupUi(this);

    databaseManager = new DatabaseManager(this);

    initWidgets();
    initConnections();

    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    adjustSize();
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(QStringLiteral("Симулятор Инвентаря"));
}

InventoryWindow::~InventoryWindow()
{
    delete ui;
}

void InventoryWindow::initWidgets()
{
    initUserInventory();
    initAppleTreeInventory();
    mainMenuBtn = new QPushButton(QStringLiteral("Главное Меню"), this);

    QGridLayout *layout{ new QGridLayout(centralWidget()) };
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    layout->addWidget(userInventory, 0, 0, 3, 1);
    layout->addWidget(appleTreeInventory, 0, 1, 1, 1);
    layout->addWidget(mainMenuBtn, 1, 1, 1, 1);
}

void InventoryWindow::initConnections() const
{
    connect(mainMenuBtn, &QPushButton::clicked, this, &QMainWindow::close);

}

void InventoryWindow::initUserInventory()
{
    auto optInventory{ databaseManager->getInventory(0) };
    if (!optInventory.has_value()) {
        qDebug() << "Error: no data to initialize the User inventory";
        return;
    }
    userInventory = new InventoryTable(optInventory.value(), this);
    initInventorySlots(userInventory);
}

void InventoryWindow::initAppleTreeInventory()
{
    auto optInventory{ databaseManager->getInventory(1) };
    if (!optInventory.has_value()) {
        qDebug() << "Error: no data to initialize the Apple Tree inventory";
        return;
    }
    appleTreeInventory = new InventoryTable(optInventory.value(), this);
    initInventorySlots(appleTreeInventory);
}

void InventoryWindow::initInventorySlots(InventoryTable *inventoryTable)
{
    qDebug() << "initInventorySlots";
    auto rowsNum{ inventoryTable->rowCount() };
    auto collumnsNum{ inventoryTable->columnCount() };
    auto slotsNum{ rowsNum * collumnsNum };
    auto tableId{ inventoryTable->id() };


    for (int i{}; i < rowsNum; ++i) {
        for (int j{}; j < collumnsNum; ++j) {
//            qDebug()
//                    << "rowsNum =" << rowsNum << "; collumnsNum =" << collumnsNum
//                    << "; slotsNum =" << slotsNum << "; tableId =" << tableId;
            auto optSlot{ databaseManager->getInventorySlot(tableId, --slotsNum) };
            qDebug() << optSlot->inventoryId() << optSlot->num();
            if (optSlot->itemQuantity()) {
                auto optItem{ databaseManager->getItem(optSlot->itemId()) };
                QTableWidgetItem *tableItem{ new QTableWidgetItem(QIcon(optItem->image_path()), optItem->item_name()) };
                userInventory->setItem(i, j, tableItem);
            }
        }
    }
    qDebug() << "~initInventorySlots";
}
