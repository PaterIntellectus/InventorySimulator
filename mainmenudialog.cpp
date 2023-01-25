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
    connect(exitBtn, &QPushButton::clicked, this, &QMainWindow::close);

    connect(newGameBtn, &QPushButton::clicked, inventoryWindow, &QWidget::show);
//    connect(newGameBtn, &QPushButton::clicked, this, &QWidget::hide);
}
