# Inicializacion del proyecto

## 1. Clonado de proyecto

Se clona el proyecto mediante ``` git clone https://github.com/4ndresito3/proyectoFinalIG.git ```

## 2. Ajustes de proyecto para compilacion correcta

Configuracion Windows

```bash Windows
cd <ruta_proyecto>/build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

Configuracion Linux

```bash linux
cd <ruta_proyecto>
mkdir -p build
cd build
cmake ..
make [-j($nproc)]
```

## 3. En el CMakeLists.txt

Meter como PROJECT_NAME proyecto_final para que sea ignorado para el github.

# Obtencion de modelos y texturas

Para los modelos cogerlos de [CGTrader](https://www.cgtrader.com/)

Para las texturas cogerlas de [CGBookCase](https://www.cgbookcase.com/)
