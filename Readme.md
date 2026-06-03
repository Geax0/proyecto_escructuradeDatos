# Sistema de Gestión de Procesos

Simulador de administración de recursos de un Sistema Operativo desarrollado en C++ como parte del curso de Estructura de Datos.

---

## Resumen

Este proyecto simula el comportamiento de un sistema operativo en cuanto a la gestión de procesos, planificación de CPU y administración de memoria. Cada módulo fue implementado con una estructura de datos distinta, sin el uso de la STL, empleando únicamente nodos y punteros nativos con gestión manual de memoria.

---

## Módulos

### Módulo 1 — Gestor de Procesos `(Lista Enlazada Simple)`
Permite registrar, buscar, modificar y eliminar procesos del sistema. Cada proceso almacena su ID, nombre, prioridad y estado.

### Módulo 2 — Planificador de CPU `(Cola de Prioridad)`
Encola los procesos según su nivel de prioridad (1 = más urgente) y los despacha al CPU simulando la ejecución en orden.

### Módulo 3 — Gestor de Memoria `(Pila Dinámica)`
Asigna y libera bloques de memoria RAM simulada siguiendo el principio LIFO. Cada bloque queda asociado al proceso que lo solicitó.

---

## Pasos para ejecutar

1. Descargar o clonar el repositorio
   ```bash
   git clone https://github.com/usuario/SistemaGestionProcesos.git
   ```

2. Abrir DEV C++ 
   ```
   File → open → Proyecto_esctructuradeDatos → CodigoFuenteEscructuradedatos.cpp 
   ``` 

3. Compilar y ejecutar
   ```
   F11
   ```

---

## Tecnologías

| Herramienta | Detalle | 
|---|---|
| Lenguaje | C++ |
| IDE | DEV C++ |
| STL | No utilizada |
| Gestión de memoria | Manual (`new` / `delete`) |

---

## Integrantes

| Nombre | Parte asignada |
|---|---|
| `GEANPIERO ANDRE CUNYAS LANASCA` | parte2 — Planificador CPU |
| `ANDY JEISON VILCHEZ AQUINO` | parte3 — Gestor de Memoria |
| `XIOMARA YAMILE TORRES PATILLA` | parte4 — Menús y Main |
| `FRANK JOSEPH AGUADO GARAY` | parte1 — Estructuras y Gestor de Procesos |

---

> Universidad Continental | Estructura de Datos | 2026
