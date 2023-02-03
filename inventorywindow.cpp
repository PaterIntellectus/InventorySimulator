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


    setWindowIcon(QIcon(APPLEIMAGE));
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
    layout->addWidget(mainMenuBtn, 2, 1, 1, 1);
}

void InventoryWindow::initConnections() const
{
    connect(mainMenuBtn, &QPushButton::clicked, this, &QMainWindow::close);
    connect(mainMenuBtn, &QPushButton::clicked, userInventory, &QTableWidget::clear);
    connect(mainMenuBtn, &QPushButton::clicked, qobject_cast<QWidget*>(parent()), &QWidget::show);
}

void InventoryWindow::initUserInventory()
{
    userInventory = new InventoryTableWidget(USERINVENTORYID, databaseManager, this);
}

void InventoryWindow::initAppleTreeInventory()
{
    appleTreeInventory = new InventoryTableWidget(APPLETREEINVENTORYID, databaseManager, this);
}
