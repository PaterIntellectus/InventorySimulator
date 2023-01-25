#ifndef MAINMENUDIALOG_H
#define MAINMENUDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "inventorywindow.h"

#include <QHBoxLayout>
#include <QSizePolicy>



namespace Ui {
class MainMenuDialog;
}

class MainMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenuDialog(QWidget *parent = nullptr);
    ~MainMenuDialog();

private:
    Ui::MainMenuDialog *ui;

    InventoryWindow *inventoryWindow{ nullptr };

    QPushButton *newGameBtn{ nullptr };
    QPushButton *exitBtn{ nullptr };

    void initWidgets();
    void initConnections();
};

#endif // MAINMENUDIALOG_H
