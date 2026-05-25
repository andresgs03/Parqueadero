# Proyecto Parqueadero

Sistema de simulación de parqueadero con comunicación por sockets, librería dinámica en C++ integrada con Python mediante SWIG y visualizador gráfico en Streamlit.

## Arquitectura general

- Un generador en C++ simula el sensor de placas.
- El generador envía placa, fecha, hora y celda por socket.
- Una librería dinámica en C++ recibe los eventos.
- Python usa la librería mediante SWIG.
- Streamlit muestra el estado del parqueadero.

## Formato del mensaje

PLACA;FECHA;HORA;CELDA

Ejemplo:

ABC123;2026-05-25;14:30:15;7
