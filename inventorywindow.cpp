#include "inventorywindow.h"
#include "ui_inventorywindow.h"

InventoryWindow::InventoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InventoryWindow)
{
    ui->setupUi(this);

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
    myInventory = new InventoryTable(3, 3, this);
    storageInventory = new InventoryTable(1, 1, this);
    mainMenuBtn = new QPushButton(QStringLiteral("Главное Меню"), this);

    QGridLayout *layout{ new QGridLayout(centralWidget()) };
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    layout->addWidget(myInventory, 0, 0, 3, 1);
    layout->addWidget(storageInventory, 0, 1, 1, 1);
    layout->addWidget(mainMenuBtn, 1, 1, 1, 1);
}

void InventoryWindow::initConnections()
{
    connect(mainMenuBtn, &QPushButton::clicked, this, &QMainWindow::close);

}
