
  

## YK Game Engine

  

hi


## Features
1. 2d/3d rendering
2. entity-component-system
3. rigid body physics
4. collision detection and resolution
5. math module
  

  

## Quickstart

```

git clone https://github.com/oh-facts/YK-Game-Engine.git --recursive

```

#
**Supported platforms:** Win32, Docker (headless build)
  

``setup.py``: compiles the engine based on preferences

  

binaries will be built in ``out/``


## Screenshots

![image](https://github.com/oh-facts/YK-Game-Engine/assets/125090383/6adfae3d-95fe-465f-84bf-0b921deec7c0)

![image](https://github.com/oh-facts/YK-Game-Engine/assets/125090383/e9e4411e-b3c7-4506-92df-da516292914e)

[2023-09-23 22-29-14.webm](https://github.com/oh-facts/YK-Game-Engine/assets/125090383/917af386-ddbb-4e59-8758-1581ac449bcd)


  

## Requirements

  

1. cmake cli

2. ninja build system *

3. clang *
4. VS Build tools *

\* These are optional. setup.py uses them to compile the engine, but you can run your own cmake command and pick your own compiler/build system.
  

## Third Party APIs

  

- **[GLFW](https://github.com/glfw/glfw)**: windowing / input handling

  

- **[glad](https://github.com/Dav1dde/glad)**: OpenGL functions loader

  

- **[stb_image](https://github.com/nothings/stb)**: image loader
