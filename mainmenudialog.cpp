#include "mainmenudialog.h"
#include "ui_mainmenudialog.h"

MainMenuDialog::MainMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenuDialog)
{
    ui->setupUi(this);

    initWidgets();
    initConnections();

    setFixedSize(200, 50);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    setWindowIcon(QIcon(APPLEIMAGE));
    setWindowTitle(QStringLiteral("Симулятор Инвентаря"));
}

MainMenuDialog::~MainMenuDialog()
{
    delete ui;
}

void MainMenuDialog::initWidgets()
{
    inventoryWindow = new InventoryWindow(this);
    newGameBtn = new QPushButton(QStringLiteral("Начать игру"), this);
    exitBtn = new QPushButton(QStringLiteral("Выход"), this);

    QHBoxLayout *layout{ new QHBoxLayout(this) };
    layout->addWidget(newGameBtn);
    layout->addWidget(exitBtn);
}

void MainMenuDialog::initConnections()
{
    connect(exitBtn, &QPushButton::clicked, this, &QDialog::close);

    connect(newGameBtn, &QPushButton::clicked, inventoryWindow, &QMainWindow::show);
    connect(newGameBtn, &QPushButton::clicked, this, &QDialog::hide);
}
