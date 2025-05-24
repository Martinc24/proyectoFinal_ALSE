#include <QApplication>
#include "inventorymanager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    InventoryManager window;
    window.setWindowTitle("Gestor de Inventario");
    window.resize(800, 600);
    window.show();
    return app.exec();
}