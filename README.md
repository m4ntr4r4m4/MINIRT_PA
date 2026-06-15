# miniRT

> A minimalist CPU ray tracer written in C that renders 3D scenes described in plain‑text `.rt` files.

`miniRT` reads a scene description (camera, lights, and geometric primitives), traces a ray through every pixel, and displays the resulting image in a window using the [MiniLibX](https://github.com/42Paris/minilibx-linux) graphics library. It is a [42 School](https://42.fr) project.

---

## Features

- **Primitives**: spheres, infinite planes, and finite cylinders, any number of each.
- **Lighting**: a single point light source with **diffuse** shading plus a global **ambient** term.
- **Shadows**: hard shadows cast by occluding objects between a surface and the light.
- **Configurable camera**: position, orientation, and horizontal field of view.
- **Plain‑text scenes**: human‑readable `.rt` files, with comments and flexible whitespace.
- **Validation**: the scene file is fully parsed and validated before any rendering begins.
- **Man page**: a `minirt(1)` manual documents the full scene‑file language.

---

## Requirements

- A C compiler (`gcc`) and `make`.
- The **classic MiniLibX** graphics library (`-lmlx`).

> **MiniLibX, not MLX42.** This project uses the classic MiniLibX API
> (`mlx_init`, `mlx_new_window`, `mlx_get_data_addr`, `mlx_put_image_to_window`,
> `mlx_hook` with raw X11 event codes, `mlx_loop`). It is **not** compatible with
> [MLX42](https://github.com/codam-coding-college/MLX42), which has a different
> GLFW/OpenGL-based API.

The `Makefile` auto-detects the platform (`uname`):

- **macOS** (the standard 42 environment): links the system MiniLibX with
  `-lmlx -framework OpenGL -framework AppKit`.
- **Linux**: uses the bundled [`minilibx-linux`](https://github.com/42Paris/minilibx-linux)
  and links `-lmlx -lXext -lX11 -lm`. This needs the X11 development headers/libs
  (`libx11-dev`, `libxext-dev` on Debian/Ubuntu).

---

## Building

### macOS

```sh
make          # build the ./miniRT binary
```

### Linux

Install the X11 development packages, build MiniLibX for Linux inside the
project, then build miniRT:

```sh
sudo apt install libx11-dev libxext-dev        # Debian/Ubuntu
git clone https://github.com/42Paris/minilibx-linux
( cd minilibx-linux && ./configure )           # produces libmlx.a / libmlx_Linux.a
make                                            # builds ./miniRT
```

> If your X11 headers/libs are not in the default system paths (e.g. they come
> from a conda env), tell the compiler and linker where to find them with
> `CPATH=<prefix>/include` and `LIBRARY_PATH=<prefix>/lib`. MiniLibX's
> `./configure` only probes standard locations, so its search list may also need
> the include directory added.

### Common targets

```sh
make clean    # remove object and dependency files
make fclean   # also remove the binary
make re       # rebuild from scratch
```

The build compiles every `.c` file under `src/` (including the bundled `libft`),
generating objects under `OBJ/` and dependency files under `DEP/`. A running
window also requires an active display (X11 on Linux); headless environments can
build but not render.

---

## Usage

```sh
./miniRT <scene.rt>
```

The program opens a `960 × 720` window and renders the scene. Several example scenes are provided in [`example_rt_files/`](example_rt_files):

```sh
./miniRT example_rt_files/std.rt
```

### Controls

| Key            | Action                |
|----------------|-----------------------|
| `ESC`          | Close the window and quit |
| Window close button | Quit |

---

## Scene file format (`.rt`)

Each element is declared on its own line. Elements may appear in any order and be separated by blank lines; descriptors within a line may be separated by any number of spaces. Anything after the last expected descriptor on a line is ignored, so trailing comments are allowed.

Floating‑point values must match the regex `(-?[0-9]{0,19}(\.[0-9]{1,18})?)`, e.g. `1.124`, `-0.1234`.

| ID   | Element          | Format                                                        | Notes |
|------|------------------|---------------------------------------------------------------|-------|
| `A`  | Ambient lighting | `A <ratio> <R,G,B>`                                           | At most one. `ratio` ∈ [0,1] |
| `C`  | Camera           | `C <x,y,z> <nx,ny,nz> <fov>`                                  | Exactly one. `fov` ∈ [0,180] |
| `L`  | Light            | `L <x,y,z> <brightness> <R,G,B>`                             | At most one. `brightness` ∈ [0,1] |
| `sp` | Sphere           | `sp <x,y,z> <diameter> <R,G,B>`                              | Any number |
| `pl` | Plane            | `pl <x,y,z> <nx,ny,nz> <R,G,B>`                             | Any number |
| `cy` | Cylinder         | `cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>`         | Any number |

- **Coordinates / vectors** are three comma‑separated floats, e.g. `12.3,-1.2,0.0`.
- **Orientation vectors** (`C` direction, `pl` normal, `cy` axis) are normalized; each component must be within `[-1, 1]`.
- **Colors** are three comma‑separated integers in `[0, 255]` representing R, G, B.

### Example

```
A  0.2                 255,255,255
C  -50.0,0,20.0        1,0,0          70
L  -40,0,30            0.7            255,255,255
pl 15,0,1              0,0,1          255,0,225
sp 0,0,20              20             255,0,0
cy 50.0,0.0,20.6       0,0,1.0        14.2 21.42  10,0,255
```

A full description of the scene language is available in the man page:

```sh
make update_manpath   # prints the command to add ./manpages to your MANPATH
man minirt
```

---

## Project layout

```
src/
├── main.c              # entry point: parse args, load scene, render
├── parameters/         # .rt file parsing and validation
├── render_scene/       # ray tracing, intersections, shading, MLX window/hooks
│   ├── render_scene.c          # window setup, event loop
│   ├── render_scene_in_buffer.c# per-pixel ray generation
│   ├── sphere_func.c / plane_func.c / cylinder_func.c  # intersections & color
│   ├── shadow.c                # shadow rays
│   └── vecMath.c / vecMath2.c  # vector math used by the renderer
├── vector/             # scene-space vector type and helpers
├── color/              # color type and helpers
└── libft/              # bundled subset of the 42 libft

example_rt_files/       # sample scenes
manpages/man1/minirt.1  # man page describing the .rt language
```

---

## How it works

1. **Parsing** (`get_parameters`) counts and validates every element in the `.rt` file, then loads the camera, ambient light, light source, and primitive lists. Any error aborts before rendering.
2. **Rendering** (`render_scene`) initializes MiniLibX, builds an image buffer, and for each pixel generates a primary ray from the camera through the image plane (using the horizontal field of view to size the plane).
3. **Tracing** (`trace_ray`) tests the ray against every plane, sphere, and cylinder, keeps the closest hit, and computes the pixel color from the ambient term plus diffuse contribution, attenuated by a shadow ray toward the light.
4. The finished buffer is pushed to the window and the MLX event loop runs until the user quits.

---

## Authors

- **Abdelghani Hammoud** (`ahammoud`)
- **Peru Riezu Muñoz** (`priezu-m`)
