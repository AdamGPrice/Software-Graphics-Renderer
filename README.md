# Win32-3DGraphicsEngine

A 3D Software renderer demo built in c++ without the use of modern graphics libraries. Just using the Windows32 GDI functions to maniplute the windows pixels in the rasterisation stage.

## Use / View
1. Clone or download the repository into a directory and open the visual studio solution in the src folder and build the project.
2. Run the project exe in the folder or with visual studio.
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