# Computer Graphics
In this project, I intend to implement a simplistic version of the 3d polygon rendering pipeline using my own lineair algebra library in C. The project depends on SDL2 for the rendering and uses Make as the build tool. Within the pipeline, the following steps are subsequently performed:

**3D modeling transformation -> Viewing transformation -> Perspective transformation**

## Quick start
```
> make
> ./3dprp.exe
```

## How it works
During the 3D modeling transform stage, the points of the vectors of the initial object may be scaled, rotated or translated. The initial object should be defined with homogeneous coordinates (x, y, z, h) to allow for the chaining of multiple transformation matrices into a single transformation matrix. The following matrices are used for these operations. Keep in mind that the order of the transformations matters when working with matrices. 

### Scalar transformation matrix
---
```
    [s_x   0    0   0]
S = [ 0   s_y   0   0]
    [ 0    0   s_z  0]
    [ 0    0    0   1]
```

### Rotation transformation matrices
---
```
      [1    0        0     0]
R_x = [0  cos(a)  -sin(a)  0]
      [0  sin(a)   cos(a)  0]
      [0    0        0     1]
```
```
      [ cos(a)  0  sin(a)  0]
R_y = [   0     1    0     0]
      [-sin(a)  0  cos(a)  0]
      [   0     0    0     1]
```
```
      [cos(a)  -sin(a)  0  0]
R_z = [sin(a)   cos(a)  0  0]
      [  0        0     1  0]
      [  0        0     0  1]
```

### Translation transformation matrix
---

```
    [1  0  0  t_x]
T = [0  1  0  t_y]
    [0  0  1  t_z]
    [0  0  0    1]
```

These matrices are meant to transform the object in the 3D modeling transformation step of the pipeline. The following definitions are meant for the viewing transformations.

### Viewing transformation matrix
---
The unit vectors of the 3d viewing coordinate system are usually denoted as $\vec{u}$, $\vec{v}$, $\vec{w}$. To calculate the appropriate transformation matrix, it is necessary to determine the the position of the observer of the rendering, the direction that the observer is watching from and the direction of the UP-vector. 
- COP = Center of Projection
- VRP = View Reference Point
- VUW = View Up Vector

With these defined, the $\vec{u}$, $\vec{v}$, $\vec{w}$ vectors can be specified in the following way:
- $\vec{w} = VRP - COP$
- $\vec{u} = VUV \times \vec{w}$
- $\vec{v} = \vec{w} \times \vec{u}$

Combined together, the viewing translation matrix and the viewing rotation matrix has the following form, where the translation is defined as negative COP:

```
        [u_x  u_y  u_z  0] [1  0  0  -COP_x]
R * T = [v_x  v_y  v_z  0] [0  1  0  -COP_y]
        [w_x  w_y  w_z  0] [0  0  1  -COP_z]
        [ 0    0    0   1] [0  0  0     1  ]
```
### Perspective transformation matrix
---
The perspective projection matrix transforms the vector space in a way that adds depth to the projected points.

```
        [-d/w   0    0    0]
        [  0  -d/w   0    0]
        [  0    0  -d/w   0]
        [  0    0    0    1]
```

Where d is the distance between the Center of Projection (COP) and the View Reference Point (VRP). 
