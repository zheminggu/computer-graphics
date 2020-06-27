# Read Me
## How to use
This project is build with glfw3.3 FreeImage and openGL.

To load model successfully, the direction of model file should not contain any space, you can also input Data/Models/better-balls.d.txt or Data/Models/cow.d.txt to load exist models

input E to start preview mode

input D to stop preview mode

input R to start light mode

input F to stop light mode

input W to move forward camera

input S to move backward camera

input A to stop move camera

input 1 to change into constant shading model

input 2 to change into gouraud shading model

input 3 to change into phong shading model

right click mouse to drag model 

## Project result
![image of balls](Result/balls.gif)
![image of cows](Result/cows.gif)


## Project structure 
### Math dir: 
Math: define constant variables of math, contain some math methods

Matrix4: define a 4*4 matrix, implement some functional operation, such as Mat4*Mat4

Vector3: define a 3 dimensional vector, use to store point, manipulate points

Vector4: defines a 4 dimensional vector, use to calculate transformation


### Utils dir:
Draw: openCV method to draw lines, points in the future it will support draw colors.

File: use to open model, and save prefabs(not achieve yet)


Camera: the Camera in the world, calculate Mat_view and Mat_pers, defines FOV, aspect upvector, and Clipping Plane

ClippingPlane: clipping plane of camera

Debug: use to log information

EdgeTable: edge table structure 

Light: light of the world

Model: Model to load, contains vertex and surface information

ModelEdge: edges in edge table

RenderModel: Model use to render, generate from original model to calculate transformation

Surface: model surface information

Texture: containing texture of a model

### Important class
World: world of this system

World::Prerun(): This is the pipeline of render process. It dealing with Back-face culling, Init vertices vector for models, make world to view transformation and view to 
projection transformation, regulate model after transformation, then translate all the model surfaces into edge table,in the end, create image buffer with z buffer algorithm. 

World::Run(): Render lines and colors with image buffer to screen.



ComputerGraphics: main entrance of the program, use glfw to create window, and then run the world 