# aocpp

__Argentum Online en C++__

La idea es desarrollar un cliente/servidor de [Argentum Online](https://es.wikipedia.org/wiki/Argentum_Online) en C++ que replique la funcionalidad del juego original.

Se toma como referencia la versión __0.13.0__ y el proyecto [AO Libre](https://github.com/ao-libre). 

Es probable que se refactorice la parte de network; lo que rompería la compatibilidad entre esta versión y la original en VB6.

La idea no es desarrollar un juego completo, sino una base que cada quien pueda modear a gusto (como sucede con AO VB6).

Estaría bueno usar algún lenguaje de scripting tipo Python o Lua.

### Descargar y probar

1. Clonar el repositorio o descargar como ZIP.
2. Copiar en la carpeta `recursos` los recursos de AO 0.13.0.
3. El proyecto utiliza la librería SDL, ver [la wiki](https://wiki.libsdl.org/Installation) por instrucciones de instalación. En Debian:  `sudo apt install libsdl2-2.0-0 libsdl2-dev`.
4. Compilar usando cmake.

__Nota:__ Lo más fácil es importar el proyecto en algún IDE como CLion y tocar "play".

### Contribuir

Nuevos contribuidores son bienvenidos.

Sepan que, a la fecha, el proyecto está __muy verde__ y su futuro es incierto.