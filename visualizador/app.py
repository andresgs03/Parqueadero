import io
import time

import pandas as pd
import streamlit as st

try:
    import parqueadero
    LIBRERIA_CARGADA = True
except Exception as e:
    parqueadero = None
    LIBRERIA_CARGADA = False
    ERROR_IMPORTACION = str(e)


st.set_page_config(
    page_title="Visualizador Parqueadero",
    page_icon="P",
    layout="wide"
)

st.title("Sistema de Parqueadero")
st.caption("Visualizador en Python + Streamlit conectado a una librería dinámica C++ mediante SWIG")

PUERTO = 8080

if not LIBRERIA_CARGADA:

    st.error("No se pudo importar la librería dinámica generada con SWIG.")
    st.code(ERROR_IMPORTACION)
    st.info("Verifica que los archivos parqueadero.py y _parqueadero.pyd estén dentro de la carpeta visualizador.")
    st.stop()


if "servidor_iniciado" not in st.session_state:

    resultado = parqueadero.iniciarServidor(PUERTO)

    st.session_state.servidor_iniciado = True
    st.session_state.resultado_servidor = resultado


if st.session_state.resultado_servidor:

    st.success(f"Servidor socket iniciado en el puerto {PUERTO}.")

else:

    st.error(f"No se pudo iniciar el servidor en el puerto {PUERTO}.")
    st.stop()


eventos_recibidos = 0

for i in range(10):

    mensaje = parqueadero.recibirEvento()

    if mensaje != "":

        eventos_recibidos += 1


col1, col2, col3, col4 = st.columns(4)

with col1:
    st.metric("Total celdas", parqueadero.getCapacidad())

with col2:
    st.metric("Celdas libres", parqueadero.getLibres())

with col3:
    st.metric("Celdas ocupadas", parqueadero.getOcupadas())

with col4:
    st.metric("Eventos nuevos", eventos_recibidos)


st.subheader("Último evento")
st.info(parqueadero.getUltimoEvento())


celdas_csv = parqueadero.obtenerCeldasCSV()
df_celdas = pd.read_csv(io.StringIO(celdas_csv))

st.subheader("Estado visual del parqueadero")

cols_por_fila = 5

for inicio in range(0, len(df_celdas), cols_por_fila):

    fila = df_celdas.iloc[inicio:inicio + cols_por_fila]
    columnas = st.columns(cols_por_fila)

    for indice, (_, celda) in enumerate(fila.iterrows()):

        numero = celda["numero"]
        estado = celda["estado"]

        placa = ""
        hora = ""

        if pd.notna(celda["placa"]):
            placa = str(celda["placa"])

        if pd.notna(celda["hora"]):
            hora = str(celda["hora"])

        with columnas[indice]:

            if estado == "Ocupada":

                st.error(f"Celda {numero}\n\n{placa}\n\n{hora}")

            else:

                st.success(f"Celda {numero}\n\nLibre")


st.subheader("Tabla de celdas")
st.dataframe(df_celdas, use_container_width=True)


historial_csv = parqueadero.obtenerHistorialCSV()
df_historial = pd.read_csv(io.StringIO(historial_csv))

st.subheader("Historial reciente de eventos")
st.dataframe(df_historial.tail(20), use_container_width=True)


col_a, col_b = st.columns(2)

with col_a:

    if st.button("Reiniciar parqueadero"):

        parqueadero.reiniciarParqueadero()
        st.rerun()

with col_b:

    auto = st.checkbox("Actualizar automáticamente", value=True)


if auto:

    time.sleep(1)
    st.rerun()
