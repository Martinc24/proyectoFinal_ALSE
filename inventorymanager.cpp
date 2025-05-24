#include "inventorymanager.h"
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QFileDialog>
#include <QTextStream>
#include <QSqlError>


InventoryManager::InventoryManager(QWidget *parent) : QMainWindow(parent) {
    setupDatabase();
    setupUI();
}

void InventoryManager::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("inventory.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        exit(1);
    }
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS components ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT,"
               "type TEXT,"
               "quantity INTEGER,"
               "location TEXT,"
               "purchase_date TEXT)");
}

void InventoryManager::setupUI() {
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    model = new QSqlTableModel(this, db);
    model->setTable("components");
    model->select();

    tableView = new QTableView;
    tableView->setModel(model);

    addBtn = new QPushButton("Agregar Artículo");
    exportBtn = new QPushButton("Exportar CSV");
    searchBox = new QLineEdit;
    searchBox->setPlaceholderText("Buscar por nombre...");

    layout->addWidget(searchBox);
    layout->addWidget(addBtn);
    layout->addWidget(exportBtn);
    layout->addWidget(tableView);
    central->setLayout(layout);
    setCentralWidget(central);

    connect(searchBox, &QLineEdit::textChanged, this, &InventoryManager::filterComponents);
    connect(addBtn, &QPushButton::clicked, this, &InventoryManager::addComponent);
    connect(exportBtn, &QPushButton::clicked, this, &InventoryManager::exportToCSV);
}

void InventoryManager::filterComponents(const QString &text) {
    model->setFilter(QString("name LIKE '%%1%'").arg(text));
    model->select();
}

void InventoryManager::addComponent() {
    QSqlQuery query;
    QString name = "Ejemplo";
    QString type = "Resistor";
    int quantity = 10;
    QString location = "Cajón 1";
    QString purchaseDate = QDate::currentDate().toString("yyyy-MM-dd");

    query.prepare("INSERT INTO components (name, type, quantity, location, purchase_date) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(quantity);
    query.addBindValue(location);
    query.addBindValue(purchaseDate);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Insert Error", query.lastError().text());
    } else {
        model->select();
    }
}

void InventoryManager::exportToCSV() {
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar como CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream out(&file);
    for (int col = 0; col < model->columnCount(); ++col) {
        out << model->headerData(col, Qt::Horizontal).toString();
        if (col < model->columnCount() - 1) out << ",";
    }
    out << "\n";

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            out << model->data(model->index(row, col)).toString();
            if (col < model->columnCount() - 1) out << ",";
        }
        out << "\n";
    }
    file.close();
}
