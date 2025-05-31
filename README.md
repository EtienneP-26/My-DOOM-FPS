# PROJECT : My-DOOM

## Details:

- First year project
- Five weeks project

## Contributors:
### Devellopers:

- Lucas Verdoucq
- Tom Baes 
- Etienne Pouille

### Externs Tools or Sources:

- Canva
- sounds: pixabay.com, youtube.com (all no copyrights)

## Building and Running the Game

### Compilation

To compile the project, you will need to have CSFML libraries installed on your system. Then use one of the following commands:

```
make
```
or for a clean rebuild:
```
make re
```

The Makefile includes several useful commands:
- `make`: Compile the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and the executable
- `make sclean`: Remove save files
- `make sfclean`: Remove save files, object files, and the executable
- `make re`: Rebuild the entire project
- `make run`: Rebuild, run the game, then clean up object files

### Running the Game

After compiling, start the game with:
```
./My-DOOM
```

For help information:
```
./My-DOOM -h
```

## Controls

### Movement
- `Z`: Move forward
- `S`: Move backward
- `Q`: Move left
- `D`: Move right
- `LEFT SHIFT`: Run (increases movement speed)

### Gameplay
- `MOUSE`: Look around
- `LEFT CLICK`: Shoot
- `F`: Toggle flashlight
- `ESC`: Quit the game

### Save System
- `F5`: Quick save
- `F9`: Quick load

The game automatically handles collision detection, allowing you to navigate through the 3D environment while avoiding walls and obstacles.
