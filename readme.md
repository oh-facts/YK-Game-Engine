
  

## YK Game Engine

  

hi


## Features
1. 2d/3d rendering
2. entity-component-system
3. rigid body physics (wip)
4. collision detection and resolution
5. math module
  

  

## Quickstart

```

git clone https://github.com/oh-facts/YK-Game-Engine.git --recursive
cd YK-Game-Engine
python setup.py

```

#
**Supported platforms:** win32, linux (tested on ubuntu and arch), probably mac (assuming they haven't killed opengl driver support)
  

``setup.py``: compiles the engine based on preferences.

  

binaries will be built in ``out/``


## Screenshots


https://github.com/oh-facts/YK-Game-Engine/assets/125090383/d3bc8263-2f77-41c3-b22c-bc4f0c82d618

![image](https://github.com/oh-facts/YK-Game-Engine/assets/125090383/e9e4411e-b3c7-4506-92df-da516292914e)

[2023-09-23 22-29-14.webm](https://github.com/oh-facts/YK-Game-Engine/assets/125090383/917af386-ddbb-4e59-8758-1581ac449bcd)


  

## Requirements

  

1. cmake

2. ninja or make

3. clang or gcc or mingw or msvc

4. python *


\* python is optional. You can run cmake commands yourself to compile for your compiler/architecture of choice. setup.py can do it for you otherwise

## Tutorial

### wip

You can check out sandbox for samples. Although it usually has deprecated code because of how often the api changes.
  

## Third Party APIs

  

- **[GLFW](https://github.com/glfw/glfw)**: window / input handling

  

- **[glad](https://github.com/Dav1dde/glad)**: OpenGL spec api

  

- **[stb_image](https://github.com/nothings/stb)**: image loader
