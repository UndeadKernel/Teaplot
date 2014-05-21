# The Teaplot Graphics Library

Teaplot is a GUI demonstrating the capabilities of the Teaplot Graphics Library (TGL). The library is developed entirely from scratch. TGL is a software-based computer graphics library in the same style of OpenGL. Performance is not one of the objectives of the library; its main objective is to demonstrate how modern computer graphic algorithms and techniques are implemented.

![ScreenShot](http://www.binarycharly.com/site/wp-content/uploads/2012/10/teaplot.png)

## Teaplot Features:

- GUI application developed in C++ using QT that renders .obj files into a viewport.
- Transformations: Modify where the mesh is rendered in the viewport (interactive controls for the mesh). Controls translation, scale and rotation in the “y” axis of the mesh. It also provides a way to change from an orthographic to a frustum perspective.
- Lines: Rendered using the Bresenham’s algorithm.
- Geometry: Parse meshes saved in the .obj format.
- The viewport window is entirely rendered from scratch. The mesh is first drawn onto an RGB array surface (pixel by pixel) and then displayed as an image. The viewport is able to be resized. The program will reconstruct the mesh for the new window geometry. The projections are not recalculated to fit the new aspect ratio of the window.

![ScreenShot](http://www.binarycharly.com/site/wp-content/uploads/2012/10/monkey.gif)

## TGL Features:

- Pseudo-OpenGL library for the manipulation of graphics, created entirely from scratch.
- Orthographic and Perspective projections.
- 3 types of homogeneous transformations: translation, scale and rotation in the “y” axis.
- Three render primitives have been implemented: points, lines and triangles. Lines are drawn using the Bresenham algorithm.
- TGL works internally using two matrices, one for the ModelView transformations and one for the Perspective transformations. The .obj files are parsed into “Shape” objects that the library is then able to render. This means that the library is capable of rendering multiple meshes at once.
- Triangle rasterization, gourad vertex colouring, backface culling, z-buffering, clipping.
- Triangle rasterization is being performed using a heavily optimized scanline algorithm.
- CCW backface culling.
- Vertex colouring: Each vertex of a model can have a single colour assigned to it.
- Illumination is performed using phong shading.
