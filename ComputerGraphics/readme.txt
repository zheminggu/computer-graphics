Read Me
This project is build with glfw3.3 and opencv.
To load model successfully, the direction of model file should not contain any space

Project structure 
Math dir: 
Math: define constant variables of math
Matrix4: define a 4*4 matrix, implement some functional operation, such as Mat4*Mat4
Vector3: define a 3 dimensional vector, use to store point, manipulate points
Vector4: defines a 4 dimensional vector, use to calculate transformation

Utils dir:
Draw: openCV method to draw lines, points in the future it will support draw colors.
File: use to open model, and save prefabs(not achieve yet)

Camera: the Camera in the world, calculate Mat_view and Mat_pers, defines FOV, aspect upvector, and Clipping Plane
ClippingPlane: clipping plane of camera
Debug: use to log informations
Model: Model to load, contains vertex and surface information
RenderModel: Model use to render, generate from original model to calculate transformation
Surface: model surface information

World: world of this system
World::Prerun(): dealing with Back-face culling, world to view transformation, and view to projection
World::Run(): Draw lines and colors after transformation

ComputerGraphics: main entrance of the program, use glfw to create window, and then run the world 