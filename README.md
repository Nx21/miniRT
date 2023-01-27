# 42 miniRt Project
Welcome to the 42 minirt project! This project is a simple raytracer that is capable of rendering basic geometric shapes in a 3D space. The project is written in C and is intended for educational purposes.

# Requirements
- A C compiler (such as GCC)
- The 42mlx library
- The Makefile

# Compiling and Running

To compile the project, navigate to the project directory in your terminal and run the following command:
```bash
make
```
This will create an executable file called "minirt". To run the program, use the following command:
```bash
./minirt scene_file
```
Where scene_file is the path to a scene file that describes the objects, lights, and camera for the scene you want to render. An example scene file is provided in the "scenes" directory.

# Scene File Format
The scene file is a simple text file that describes the objects, lights, and camera for the scene you want to render.
Each object, light, and camera is defined by a single line in the file, with the following format:

```txt
[object/light/camera] [properties]
```

For example, to define a blue sphere with a radius of 12.6 and a position of (0.0, 0.0, 20.6), you would use the following line :

```txt
sp 0.0,0.0,20.6 12.6 0,0,255
```

Please refer to the example scene file for more information on the specific properties and format for each object, light, and camera.

# Limitations

This project is a basic implementation of a raytracer and as such has several limitations. Some of the most notable limitations include:

Only basic geometric shapes are supported (spheres and planes)
Shadows and reflections are not currently supported
The number of objects and lights that can be rendered is limited

# Conclusion

This project is intended as an educational tool to help understand the basic concepts of a raytracer. It is not intended for production use.
If you have any questions or encounter any issues while using this project, please contact us.
