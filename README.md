# CG Track Environment

## **THIS IS A WORK IN PROGRESS ENVIRONMENT**

Base enviroment to use on for CG/OpenGL classes.

## Build

The environment is based on CMake, it should work fine building anywhere but as we're using [vscode](https://code.visualstudio.com/) this build is based on it.

### vscode extensions

- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

### Submodules

Project dependencies are being loaded as submodules to ease updates.
If you face any issue due to any dependency, you probably must as below...

#### [GLEW](https://github.com/nigels-com/glew)

At `external/glew` run:

```bash
make extensions
```

#### [Assimp](https://github.com/assimp/assimp)

At `external/assimp` run:

```bash
cmake CMakeLists.txt
make -j4
```

#### [GLFW](https://github.com/glfw/glfw) and [GLM](https://github.com/g-truc/glm)

You shouldn't face any issue due to GLFW and GLM, but if some information is missing the original repositoty is linked on the title of each dependency.

### CMake

[[Reference video](https://www.youtube.com/watch?v=wP4cwAtU-g8)]

Having instaled CMake extensions, press `F1` to show all commands and select `CMake: Configure` to prepare your environment (for MacOS select `Clang`). You'll probably receive warnings or errors, try to fix them before build any program.

Having sucessfully configured the environment, you're able to build your work.

### Debug

Create a `launch.json` for `C++(GDB/LLDB)` and set `program` to the desired compiled program.
