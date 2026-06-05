# Manual de Usuario
# Sistema de Gestión de Procesos
### Simulador de Administración de Recursos en un Sistema Operativo

**Universidad Continental | Estructura de Datos | 2026**

**Integrantes:**
- Cunyas Lanasca, Geanpiero Andre
- Vilchez Aquino, Andy Jeison
- Torres Patilla, Xiomara Yamile
- Aguado Garay, Frank Joseph

---

## Tabla de Contenidos

1. [Introducción](#1-introducción)
2. [Requisitos del Sistema](#2-requisitos-del-sistema)
3. [Compilación y Ejecución](#3-compilación-y-ejecución)
4. [Descripción General](#4-descripción-general)
5. [Menú Principal](#5-menú-principal)
6. [Módulo 1 — Gestor de Procesos](#6-módulo-1--gestor-de-procesos)
7. [Módulo 2 — Planificador de CPU](#7-módulo-2--planificador-de-cpu)
8. [Módulo 3 — Gestor de Memoria](#8-módulo-3--gestor-de-memoria)
9. [Resumen del Sistema](#9-resumen-del-sistema)
10. [Reglas y Restricciones](#10-reglas-y-restricciones)
11. [Mensajes de Error Comunes](#11-mensajes-de-error-comunes)
12. [Ejemplo de Sesión Completa](#12-ejemplo-de-sesión-completa)

---

## 1. Introducción

El **Sistema de Gestión de Procesos** es un simulador educativo que replica, de forma simplificada, el comportamiento de un sistema operativo al administrar procesos, la cola de ejecución de la CPU y la memoria RAM. El programa está implementado en **C++** y utiliza tres estructuras de datos fundamentales:

| Módulo | Estructura de Datos | Función Principal |
|---|---|---|
| Gestor de Procesos | Lista Enlazada Simple | Registrar, buscar, modificar y eliminar procesos |
| Planificador de CPU | Cola de Prioridad | Ordenar y ejecutar procesos según su prioridad |
| Gestor de Memoria | Pila Dinámica | Asignar y liberar bloques de RAM simulada |

---

## 2. Requisitos del Sistema

- Compilador C++ compatible con el estándar C++11 o superior (g++, clang++, MSVC).
- Sistema operativo: Windows, Linux o macOS.
- Terminal o consola de comandos.

---

## 3. Compilación y Ejecución

**En Linux / macOS:**
```bash
g++ -o simulador main.cpp
./simulador
```

**En Windows (MinGW):**
```bash
g++ -o simulador.exe main.cpp
simulador.exe
```

> **Nota:** El comando `system("cls")` utilizado para limpiar pantalla funciona en Windows. En Linux/macOS puede reemplazarse por `system("clear")` si se desea.

---

## 4. Descripción General

Al iniciar el programa, se presenta el **Menú Principal** con cuatro opciones. La navegación se realiza escribiendo el número de opción y presionando `Enter`. El sistema valida todas las entradas y rechaza caracteres no numéricos o valores fuera de rango, solicitando nuevamente la entrada al usuario.

---

## 5. Menú Principal

```
========================================
   SISTEMA DE GESTION DE PROCESOS
   Simulador de SO | Estructura de Datos
   Universidad Continental  |  2026
========================================
1. Gestor de Procesos  (Lista Enlazada)
2. Planificador de CPU (Cola Prioridad)
3. Gestor de Memoria   (Pila Dinamica)
4. Ver resumen del sistema
0. Salir
========================================
```

| Opción | Descripción |
|---|---|
| `1` | Accede al módulo de gestión de procesos |
| `2` | Accede al planificador de CPU |
| `3` | Accede al gestor de memoria RAM |
| `4` | Muestra el estado completo del sistema |
| `0` | Cierra el simulador y libera toda la memoria |

---

## 6. Módulo 1 — Gestor de Procesos

> Implementado con una **Lista Enlazada Simple**.

```
=== GESTOR DE PROCESOS (Lista Enlazada Simple) ===
1. Registrar nuevo proceso
2. Buscar proceso por ID
3. Modificar prioridad / estado
4. Eliminar proceso
5. Ver todos los procesos
0. Volver al menú principal
```

---

### 6.1 Registrar Nuevo Proceso — Opción `1`

Registra un nuevo proceso en el sistema. **Al mismo tiempo, reserva automáticamente un bloque de memoria RAM** para ese proceso en la pila (Módulo 3).

**Datos solicitados:**

| Campo | Tipo | Descripción |
|---|---|---|
| ID | Entero positivo único | Identificador del proceso |
| Nombre | Texto (sin espacios) | Nombre descriptivo del proceso |
| Prioridad | Entero positivo | Nivel de prioridad (1 = más alta) |
| Tamaño de bloque | Entero positivo (KB) | Memoria RAM a reservar |

**Condiciones para el registro:**
- El ID no debe existir previamente.
- Debe haber suficiente memoria RAM disponible (máximo 4096 KB en total).
- Si la memoria es insuficiente, el registro se cancela.

**Ejemplo de uso:**
```
ID (entero unico): 101
Nombre: Navegador
Prioridad (1=alta): 2
Tamano de bloque de memoria a asignar (KB): 512

[PUSH] Bloque de 512 KB asignado al proceso ID=101. Memoria total en uso: 512 / 4096 KB
Proceso 'Navegador' (ID=101) registrado correctamente.
```

---

### 6.2 Buscar Proceso por ID — Opción `2`

Busca un proceso en la lista y muestra su información completa.

**Ejemplo de uso:**
```
ID a buscar: 101
Encontrado -> ID=101 | Nombre: Navegador | Prioridad: 2 | Estado: Listo
```

Si el ID no existe:
```
No se encontro el proceso con ID=101
```

---

### 6.3 Modificar Prioridad / Estado — Opción `3`

Actualiza la prioridad y el estado de un proceso ya registrado.

**Datos solicitados:**

| Campo | Descripción |
|---|---|
| ID | Identificador del proceso a modificar |
| Nueva prioridad | Nuevo valor numérico de prioridad |
| Nuevo estado | `Listo`, `Espera` o `Ejecutando` |

**Ejemplo de uso:**
```
ID a modificar: 101
Nueva prioridad: 1
Nuevo estado (Listo/Espera/Ejecutando): Ejecutando

Proceso ID=101 actualizado. Prioridad=1 | Estado=Ejecutando
```

---

### 6.4 Eliminar Proceso — Opción `4`

Elimina un proceso de la lista enlazada por su ID.

>  **Importante:** Eliminar un proceso de la lista **no libera automáticamente** su bloque de memoria en la pila ni lo retira de la cola de CPU. Se recomienda hacerlo manualmente desde los módulos correspondientes.

**Ejemplo de uso:**
```
ID a eliminar: 101
Proceso 'Navegador' (ID=101) eliminado.
Nota: Recuerde liberar sus recursos de la RAM (Modulo 3) y CPU (Modulo 2) si es necesario.
```

---

### 6.5 Ver Todos los Procesos — Opción `5`

Muestra una tabla con todos los procesos actualmente registrados.

**Ejemplo de salida:**
```
--------------------------------------------------
ID    | Nombre             | Prioridad | Estado
--------------------------------------------------
101    | Navegador          | 2         | Listo
102    | Antivirus          | 1         | Ejecutando
--------------------------------------------------
Total de procesos: 2
```

---

## 7. Módulo 2 — Planificador de CPU

> Implementado con una **Cola de Prioridad** (menor número = mayor urgencia).

```
=== PLANIFICADOR DE CPU (Cola de Prioridad) ===
1. Encolar proceso para CPU
2. Ejecutar (desencolar) proceso
3. Ver cola de ejecución
0. Volver al menú principal
```

---

### 7.1 Encolar Proceso — Opción `1`

Agrega un proceso (previamente registrado en el Módulo 1) a la cola de ejecución. El proceso se **inserta automáticamente en la posición correcta** según su prioridad: los de menor número van al frente.

**Dato solicitado:** ID del proceso a encolar.

**Ejemplo de uso:**
```
ID del proceso a encolar: 102
Proceso 'Antivirus' encolado con prioridad 1
```

> Si el ID no está registrado en la lista de procesos, la operación se cancela.

---

### 7.2 Ejecutar Proceso — Opción `2`

Saca el proceso del **frente de la cola** (el de mayor prioridad) y simula su ejecución.

**Ejemplo de salida:**
```
[CPU] Ejecutando: 'Antivirus' (ID=102 | Prioridad=1)
Proceso finalizado y removido de la cola.
```

---

### 7.3 Ver Cola de Ejecución — Opción `3`

Muestra todos los procesos en espera, ordenados de mayor a menor prioridad (frente → final).

**Ejemplo de salida:**
```
Orden de ejecucion (frente -> final):
------------------------------------------
ID    | Nombre             | Prioridad
------------------------------------------
102    | Antivirus          | 1
101    | Navegador          | 2
------------------------------------------
Procesos en cola: 2
```

---

## 8. Módulo 3 — Gestor de Memoria

> Implementado con una **Pila Dinámica (Stack)**. Límite máximo: **4096 KB**.

```
=== GESTOR DE MEMORIA (Pila Dinamica) ===
1. Asignar bloque de memoria (push)
2. Liberar bloque de memoria (pop)
3. Ver estado de la memoria
0. Volver al menú principal
```

---

### 8.1 Asignar Bloque de Memoria (Push) — Opción `1`

Reserva un bloque de memoria para un proceso. El bloque se apila en el tope.

**Datos solicitados:**

| Campo | Descripción |
|---|---|
| ID del proceso | Identificador al que se asignará el bloque |
| Tamaño (KB) | Cantidad de memoria a reservar |

**Ejemplo de uso:**
```
ID del proceso: 103
Tamano del bloque (KB): 256

[PUSH] Bloque de 256 KB asignado al proceso ID=103. Memoria total en uso: 768 / 4096 KB
```

>  Si la memoria disponible es insuficiente, la operación se cancela con un mensaje de error.

---

### 8.2 Liberar Bloque de Memoria (Pop) — Opción `2`

Libera el bloque en el **tope de la pila** (el último que fue asignado).

**Ejemplo de salida:**
```
[POP] Liberando bloque de 256 KB (Proceso ID=103)
Bloque liberado. Memoria en uso: 512 KB
```

> La pila sigue el principio **LIFO** (Last In, First Out): siempre se libera el bloque más recientemente asignado.

---

### 8.3 Ver Estado de la Memoria — Opción `3`

Muestra todos los bloques de memoria activos, desde el tope hasta la base.

**Ejemplo de salida:**
```
Estado de la Pila (tope -> base):
------------------------------
ID Proceso  | Tamano (KB)
------------------------------
103         | 256 KB
102         | 128 KB
101         | 512 KB
------------------------------
Bloques activos : 3
Memoria en uso  : 896 KB
```

---

## 9. Resumen del Sistema

La opción `4` del menú principal muestra en una sola pantalla el estado completo del sistema:

- Lista de todos los procesos registrados.
- Cola de ejecución de la CPU.
- Estado actual de la pila de memoria RAM.

Útil para verificar la consistencia del sistema antes de realizar operaciones importantes.

---

## 10. Reglas y Restricciones

| Regla | Detalle |
|---|---|
| IDs únicos | No se pueden registrar dos procesos con el mismo ID |
| Límite de RAM | La memoria simulada tiene un máximo de **4096 KB** |
| Registro con memoria | Al registrar un proceso se reserva memoria obligatoriamente |
| Eliminación manual | Eliminar un proceso de la lista **no** libera su RAM ni su lugar en la cola |
| Orden en cola | La cola de prioridad ordena automáticamente (prioridad 1 = más urgente) |
| Pop de pila | Solo se puede liberar el bloque del tope (LIFO) |
| Entradas válidas | El sistema solo acepta enteros positivos donde corresponde; rechaza letras o negativos |

---

## 11. Mensajes de Error Comunes

| Mensaje | Causa | Solución |
|---|---|---|
| `ERROR: Ya existe un proceso con ID X` | ID duplicado al registrar | Usar un ID diferente |
| `ERROR: Memoria RAM insuficiente` | No hay KB disponibles en la pila | Liberar bloques (Módulo 3, opción 2) |
| `ERROR: No existe un proceso con ID X` | ID no encontrado en la lista | Verificar el ID con la opción 5 del Módulo 1 |
| `La cola de ejecucion esta vacia` | Se intentó ejecutar sin procesos en cola | Encolar un proceso primero (Módulo 2, opción 1) |
| `La pila de memoria esta vacia` | Se intentó hacer pop sin bloques | Asignar memoria primero (Módulo 3, opción 1) |
| `Entrada invalida. Ingrese un numero entero positivo` | Se ingresó texto o un número negativo | Ingresar solo números enteros positivos |

---

## 12. Ejemplo de Sesión Completa

A continuación se muestra un flujo típico de uso del simulador:

**Paso 1 — Registrar dos procesos:**
```
Módulo 1 > Opción 1
  ID: 10 | Nombre: Chrome | Prioridad: 3 | Bloque: 400 KB  → OK
  ID: 20 | Nombre: Sistema | Prioridad: 1 | Bloque: 200 KB → OK
```

**Paso 2 — Encolar ambos procesos en la CPU:**
```
Módulo 2 > Opción 1
  Encolar ID=10 → Cola: [Sistema(1), Chrome(3)]
  Encolar ID=20 → Cola: [Sistema(1), Chrome(3)]
```

**Paso 3 — Ejecutar el proceso de mayor prioridad:**
```
Módulo 2 > Opción 2
  [CPU] Ejecutando: 'Sistema' (ID=20 | Prioridad=1)
```

**Paso 4 — Liberar la memoria del proceso ejecutado:**
```
Módulo 3 > Opción 2
  [POP] Liberando bloque de 200 KB (Proceso ID=20)
```

**Paso 5 — Ver resumen del sistema:**
```
Menú Principal > Opción 4
  → 1 proceso en lista, 1 en cola, 400 KB en uso
```

**Paso 6 — Salir:**
```
Menú Principal > Opción 0
  Cerrando el simulador... (memoria dinámica liberada)
```

---

*Manual generado para el proyecto de Estructura de Datos — Universidad Continental, 2026.*
