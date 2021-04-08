# RTV1 (basic ray tracing engine)
basic engine for rendering multiple objects using ray tracing algorithm
RTv1 is a simple ray tracing program. The project was developed as a part of 42 school program. It parses a 3D scene from a file and applies ray tracing algorithm to render the given scene.
Note: this project was made for MacOS.

<img width="1080" alt="test rt screenshot" src="https://user-images.githubusercontent.com/63746115/114026024-ac081480-986d-11eb-9980-48fd28658f43.png">

Installation

Clone or download this repository and run make in command line while in the root of the repository. This will build executable called RTv1. Makefile compiles SDL2 library from source files. so building process might take some time.

Usage

./RTv1 [filename]
filename must contain path to a valid scene.
If the scene is not valid, RTv1 will write corresponding error on standard output.
you will find example of the file named test 

![image](https://user-images.githubusercontent.com/63746115/114026314-01dcbc80-986e-11eb-9731-138fff348538.png)
![image](https://user-images.githubusercontent.com/63746115/114026351-0b662480-986e-11eb-933e-bf477805aff1.png)

