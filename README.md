# GeoMesh

![language](https://img.shields.io/badge/language-C%2FC%2B%2B-green)
![OS](https://img.shields.io/badge/OS-linux%2C%20windows-green)

## About the Project

GeoMesh is a C++ and OpenGL-based renderer for digital elevation models (DEM). It visualizes terrain in 3D space and provides multiple rendering modes for exploration.

This project is under active development and will gain new features such as directional lighting and higher-detail tessellation in the future.

## Project Showcase

### Grayscale Rendering (Fill and Wireframe)

<p align="center">
  <img src="media/terrainGrayscale.gif" width="400">
  <img src="media/terrainGrayscale2.gif" width="400">
</p>

### Biome Rendering (Fill and Wireframe)

<p align="center">
  <img src="media/terrainBiome.gif" width="400">
  <img src="media/terrainBiome2.gif" width="400">
</p>

## Building Project

### Configure

This project uses CMake to generate the build files. To configure the project, use the following command:

```bash
cmake -S . -B build
```

### Build

After configuring the project, you can build it using the following command:

```bash
cmake --build build
```

## Running Project

After building the project, simply run the GeoMesh executable found in the `/build` directory, or execute from the terminal:

```bash
./build/GeoMesh
```

## Controls

### Camera Movement

- **W/A/S/D** - Move forward/backward/left/right
- **Q, E** - Move up/down
- **Mouse Wheel** - Zoom in/out

### Rendering Modes

- **Space Bar** - Wireframe mode
- **F** - Force fill mode
- **G** - Grayscale rendering
- **B** - Biome rendering
