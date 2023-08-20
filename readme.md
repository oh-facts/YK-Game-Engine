
  

## YK Game Engine

  

hi

  

  

## Quickstart

```

git clone https://github.com/oh-facts/YK-Game-Engine.git --recursive

```

#
**Supported platforms:** Win32, Docker (headless build)
  

``setup.py``: compiles the engine based on preferences

  

binaries will be built in ``out/``

  
  

## Requirements

  

1. cmake cli

2. ninja build system

3. clang 
4. VS Build tools


Since I don't have a linux and mac, I can't check if it runs there. However, if I did, it wouldn't be tough to get it to work since I tested enough with ubuntu for the docker build. No platform dependent library and all libraries and source code is compiled from scratch.
  

## Third Party APIs

  

- **[GLFW](https://github.com/glfw/glfw)**: windowing / input handling

  

- **[glad](https://github.com/Dav1dde/glad)**: OpenGL functions loader

  

- **[stb_image](https://github.com/nothings/stb)**: image loader