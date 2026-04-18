*This project has been created as part of the 42 curriculum by marshaky, aramarak*

# cub3D

# Description
This project is a simple ray-caster inspired by Wolfenstein 3D. Its goal is to parse `.cub`
configuration files, render a textured first-person view using MiniLibX, and support basic
player movement and rotation. The project is implemented in C and intended to demonstrate
ray-casting fundamentals and low-level graphics using MiniLibX.

## Instructions

### Build
The project uses the provided `Makefile`. Build with:

```bash
make
```

### Run
Run the binary with a `.cub` map file:

```bash
./cub3d maps/example.cub
```

Notes:
- Ensure X11 development headers/libraries are installed on Linux.
- The project links against a local `libft` and `minilibx` included in `libraries/`.

## Resources

- Ray casting overview: https://lodev.org/cgtutor/raycasting.html
- MiniLibX examples and docs (see `libraries/minilibx-*`)
- C reference and common algorithms

AI usage disclosure:
- AI assistance was used only for small, non-core tasks: README drafting and Makefile formatting
  suggestions. No AI-generated code was copied into the core parsing, rendering, or game logic.

---

## Project goals
- Understand ray-casting principles
- Work with MiniLibX
- Parse `.cub` configuration files
- Render textures and walls
- Handle player movement and rotation

## Technologies
- Language: C
- Graphics library: MiniLibX
- Platform: Linux / macOS

## Project structure
```
cub3D/
├── src/
├── includes/
├── libraries/
├── maps/
├── Makefile
└── README.md
```

## Troubleshooting
- If `make` doesn't rebuild after header changes, ensure object rules depend on headers (see Makefile).
- For Valgrind "still reachable" reports, free application-owned resources on exit; some MLX allocations
  are expected.

## How to contribute
- Open an issue or submit a PR with a focused change and description of the problem solved.