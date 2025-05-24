QT += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InventoryManager
TEMPLATE = app

SOURCES += main.cpp \
           inventorymanager.cpp

HEADERS += inventorymanager.h