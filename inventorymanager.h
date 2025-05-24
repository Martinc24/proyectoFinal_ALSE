#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>

class InventoryManager : public QMainWindow {
    Q_OBJECT

public:
    InventoryManager(QWidget *parent = nullptr);

private slots:
    void filterComponents(const QString &text);
    void addComponent();
    void exportToCSV();

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QLineEdit *searchBox;
    QTableView *tableView;
    QPushButton *addBtn, *exportBtn;

    void setupDatabase();
    void setupUI();
};

#endif // INVENTORYMANAGER_H