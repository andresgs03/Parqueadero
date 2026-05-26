@echo off
setlocal

echo ======================================
echo Compilando generador de placas
echo ======================================

set ROOT=%~dp0..
set GENERADOR=%ROOT%\generador

cd /d "%GENERADOR%"

cl /EHsc main.cpp GeneradorPlacas.cpp ClienteSocket.cpp ws2_32.lib /Fe:generador.exe

if errorlevel 1 (
    echo.
    echo Error al compilar el generador.
    echo Verifique que esta ejecutando este archivo desde Developer Command Prompt for VS.
    pause
    exit /b 1
)

echo.
echo Generador compilado correctamente.
echo Archivo generado: generador\generador.exe

pause
endlocal
