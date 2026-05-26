# Proyecto Parqueadero

Sistema de simulación de parqueadero con comunicación por sockets entre dos computadores, librería dinámica en C++ integrada con Python mediante SWIG y visualizador gráfico en Streamlit.

## Descripción general

El proyecto simula el funcionamiento básico de un parqueadero inteligente.

Un programa en C++ actúa como generador de placas y representa el sensor o cámara del parqueadero. Este generador detecta una placa, fecha, hora y celda, y envía esa información por socket a otro computador.

En el computador receptor, una librería dinámica en C++ recibe la información mediante socket, actualiza el estado del parqueadero y permite que Python consulte la información mediante SWIG. Finalmente, Streamlit muestra el estado del parqueadero en una interfaz gráfica.

## Arquitectura

```txt
Computador 1
└── Generador C++
    ├── Genera placa, fecha, hora y celda
    ├── Actúa como cliente socket
    └── Envía eventos cada 2 a 5 segundos

            ↓ Socket TCP

Computador 2
└── Visualizador Python + Streamlit
    └── Usa librería dinámica C++ mediante SWIG
        ├── Actúa como servidor socket
        ├── Recibe los eventos
        ├── Actualiza el estado del parqueadero
        └── Entrega datos a Python
```

## Formato del mensaje

Cada evento enviado por el generador tiene el siguiente formato:

```txt
PLACA;FECHA;HORA;CELDA
```

Ejemplo:

```txt
ABC123;2026-05-25;14:30:15;7
```

## Regla principal del parqueadero

- Si una placa llega por primera vez, se interpreta como entrada.
- Si la misma placa vuelve a llegar, se interpreta como salida.
- Al salir, se libera la celda asociada a esa placa.

## Estructura del proyecto

```txt
ProyectoParqueadero/
│
├── generador/
│   ├── ClienteSocket.h
│   ├── ClienteSocket.cpp
│   ├── GeneradorPlacas.h
│   ├── GeneradorPlacas.cpp
│   └── main.cpp
│
├── libreria/
│   ├── Celda.h
│   ├── Celda.cpp
│   ├── Parqueadero.h
│   ├── Parqueadero.cpp
│   ├── ServidorSocket.h
│   ├── ServidorSocket.cpp
│   ├── puente.h
│   ├── puente.cpp
│   └── parqueadero.i
│
├── visualizador/
│   ├── app.py
│   └── requirements.txt
│
├── scripts/
│   ├── build_generador_msvc.bat
│   ├── build_swig_msvc.bat
│   └── run_visualizador.bat
│
├── docs/
│   └── UML.jpg
├── README.md
└── .gitignore
```

## Requisitos

El proyecto está orientado a Windows porque utiliza Winsock.

Se recomienda tener instalado:

- Windows.
- Python 3.11 o 3.12.
- Streamlit.
- Pandas.
- SWIG para Windows.
- Visual Studio Community 2022 o Visual Studio Build Tools 2022.
- Componente de Visual Studio: Desktop development with C++.

## Instalación de dependencias de Python

Desde la raíz del proyecto:

```bat
pip install -r visualizador\requirements.txt
```

## Compilar el generador C++

Abrir Developer Command Prompt for VS 2022 y ejecutar desde la raíz del proyecto:

```bat
scripts\build_generador_msvc.bat
```

Esto genera localmente:

```txt
generador\generador.exe
```

Este archivo no se sube al repositorio porque es un archivo compilado.

## Compilar la librería dinámica con SWIG

Desde Developer Command Prompt for VS 2022 ejecutar:

```bat
scripts\build_swig_msvc.bat
```

Este script genera la interfaz de SWIG y compila la librería dinámica para Python.

Archivos generados localmente:

```txt
visualizador\parqueadero.py
visualizador\_parqueadero.pyd
```

Estos archivos tampoco se suben al repositorio porque son generados automáticamente.

## Ejecutar el visualizador

En el computador receptor:

```bat
scripts\run_visualizador.bat
```

O manualmente:

```bat
cd visualizador
streamlit run app.py
```

El visualizador inicia el servidor socket en el puerto 8080.

## Ejecutar el generador

En el computador emisor:

```bat
generador\generador.exe IP_DEL_COMPUTADOR_RECEPTOR 8080
```

Ejemplo en red local:

```bat
generador\generador.exe 192.168.1.34 8080
```

Para pruebas en el mismo computador:

```bat
generador\generador.exe 127.0.0.1 8080
```

## Orden correcto de ejecución

1. En el computador receptor, compilar la librería dinámica con SWIG.
2. Ejecutar el visualizador con Streamlit.
3. Identificar la IP del computador receptor usando `ipconfig`.
4. En el computador emisor, compilar el generador.
5. Ejecutar el generador indicando la IP del computador receptor.
6. Verificar en Streamlit la entrada y salida de vehículos.

## Archivos generados que no se suben

El repositorio no incluye archivos compilados ni generados automáticamente.

No se suben:

```txt
*.exe
*.obj
*.lib
*.exp
*.pyd
*.dll
parqueadero.py
parqueadero_wrap.cxx
__pycache__/
```

Estos archivos se generan localmente al ejecutar los scripts de compilación.

## Componentes principales

### Generador C++

Simula el sensor del parqueadero.

Funciones principales:

- genera placas aleatorias;
- genera fecha y hora;
- asigna celdas;
- repite placas para simular salidas;
- envía eventos cada 2 a 5 segundos.

### Librería C++

Contiene la lógica principal del parqueadero.

Incluye:

- clase `Celda`;
- clase `Parqueadero`;
- clase `ServidorSocket`;
- funciones puente para Python;
- archivo de interfaz SWIG.

### Visualizador Streamlit

Muestra:

- total de celdas;
- celdas libres;
- celdas ocupadas;
- último evento;
- tabla de celdas;
- historial de eventos;
- estado visual del parqueadero.

## Uso de Git

El proyecto se organizó en ramas para separar las funcionalidades principales:

```txt
main
feature/logica-parqueadero
feature/parqueadero
```

La rama `feature/logica-parqueadero` se usó para crear la clase `Celda`.

La rama `feature/parqueadero` se usó para integrar la lógica completa, sockets, generador, SWIG, visualizador y documentación.

## Nota sobre la comunicación entre computadores

Para que la comunicación funcione entre dos computadores:

- ambos deben estar en la misma red;
- el computador receptor debe tener abierto el visualizador;
- el generador debe apuntar a la IP del computador receptor;
- puede ser necesario permitir el puerto 8080 en el firewall de Windows.
