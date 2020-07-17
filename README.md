# C++ Software Grahpics Renderer

A 3D Software renderer demo built in C++ without the use of modern graphics libraries. Just using the Windows32 GDI functions to maniplute the windows pixels in the rasterisation stage.

<img src="images/showcase.gif" width="800" height="450">

## Setup
1. Clone or download the repository into a directory and open the Visual Studio solution in the src folder and build the project.
2. Launch inside Visual Studio or by running the project executable.
    * If you get a files missing error. Copy the 'MD2Models' folder to the built project directory 'x64/debug' or 'x64/release'.

## Renderer Features

* Wireframe Model View
* Object Transformations
    * Translation
    * Rotation
    * Scaling
* Backface Culling
* Solid Flat Shading
* Lighting Sources
    * Ambient
    * Directional
    * Point
    * Spot
* Diffuse/Specular reflections
    * Phong Lighting Model
* Rasteriser (Triangle Algorithm)
* Object Textures (With Perspective Correction)