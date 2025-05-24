# proyectoFinal_ALSE
🗂️ Descripción del Proyecto: Sistema de Gestión de Inventario
Este proyecto es una aplicación de escritorio desarrollada con Qt en C++, que permite gestionar de manera sencilla y eficiente un inventario de componentes u objetos. Utiliza una base de datos local SQLite para almacenar la información de cada artículo registrado.

🔧 Características principales:
Ingreso de artículos con los siguientes datos:

Nombre

Tipo

Cantidad

Ubicación

Fecha de adquisición (generada automáticamente)

Visualización de componentes en una tabla interactiva (QTableView).

Búsqueda y filtrado en tiempo real por nombre.

Alerta visual de bajo stock (opcional de implementar).

Exportación de inventario a archivos CSV.

Interfaz intuitiva y responsiva, diseñada con widgets de Qt y organizada con QVBoxLayout.

🛠️ Tecnologías utilizadas:
Lenguaje: C++

Framework: Qt 5/6

Base de datos: SQLite (persistente, embebida)

Modelo de datos: QSqlTableModel

Interfaz gráfica: QMainWindow, QTableView, QLineEdit, QPushButton

📁 Casos de uso:
Control de inventario para laboratorios, talleres, almacenes, escuelas, etc.

Seguimiento del stock de componentes electrónicos o materiales físicos.

Generación de reportes CSV para respaldos o auditorías.
