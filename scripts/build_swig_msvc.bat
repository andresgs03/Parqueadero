@echo off
setlocal

echo ======================================
echo Compilando libreria dinamica con SWIG
echo ======================================

set ROOT=%~dp0..
set LIBRERIA=%ROOT%\libreria
set VISUALIZADOR=%ROOT%\visualizador

cd /d "%LIBRERIA%"

echo.
echo Buscando rutas de Python...

for /f "delims=" %%i in ('python -c "import sysconfig; print(sysconfig.get_paths()[\"include\"])"') do set PY_INCLUDE=%%i

for /f "delims=" %%i in ('python -c "import sysconfig, os; print(sysconfig.get_config_var(\"LIBDIR\") or os.path.join(sysconfig.get_config_var(\"installed_base\"), \"libs\"))"') do set PY_LIBDIR=%%i

for /f "delims=" %%i in ('python -c "import sys; print(\"python\" + str(sys.version_info.major) + str(sys.version_info.minor) + \".lib\")"') do set PY_LIBFILE=%%i

echo Include Python: %PY_INCLUDE%
echo Librerias Python: %PY_LIBDIR%
echo Archivo lib Python: %PY_LIBFILE%

echo.
echo Generando wrapper con SWIG...

swig -c++ -python -I"%LIBRERIA%" parqueadero.i

if errorlevel 1 (
    echo.
    echo Error al ejecutar SWIG.
    echo Verifique que SWIG este instalado y agregado al PATH.
    pause
    exit /b 1
)

echo.
echo Compilando modulo _parqueadero.pyd...

cl /EHsc /LD puente.cpp Parqueadero.cpp Celda.cpp ServidorSocket.cpp parqueadero_wrap.cxx /I"%PY_INCLUDE%" /I"%LIBRERIA%" ws2_32.lib /link /LIBPATH:"%PY_LIBDIR%" %PY_LIBFILE% /OUT:_parqueadero.pyd

if errorlevel 1 (
    echo.
    echo Error al compilar la libreria dinamica.
    echo Verifique que esta ejecutando este archivo desde Developer Command Prompt for VS.
    pause
    exit /b 1
)

echo.
echo Copiando archivos generados al visualizador...

copy /Y parqueadero.py "%VISUALIZADOR%\parqueadero.py"
copy /Y _parqueadero.pyd "%VISUALIZADOR%\_parqueadero.pyd"

echo.
echo Libreria compilada correctamente.
echo Archivos copiados a la carpeta visualizador:
echo - parqueadero.py
echo - _parqueadero.pyd

pause
endlocal
