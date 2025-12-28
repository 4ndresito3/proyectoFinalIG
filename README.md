# Inicializacion del proyecto
## 1. Clonado de proyecto
Se clona el proyecto mediante ``` git clone https://github.com/4ndresito3/proyectoFinalIG.git ```

## 2. Ajustes de proyecto para compilacion correcta
```bash Windows
cd <ruta_proyecto>/build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

```bash linux
cd <ruta_proyecto>
mkdir -p build
cd build
cmake ..
make [-j($nproc)]
```
