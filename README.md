# M-N-K Tic-Tac-Toe in C89
Console-based tic-tac-toe client featuring editable board size and win condition parameters, as well as logging of game history.
Written in C89 spec for a university assignment.

Showcases use of C langauge features such as structs, conditional compliation and make, and features a custom linked-list implementation.

## Instructions for Use
Implemented for use in a Linux environment.

Run the following commands to compile:
```bash
> cd src
> make
```

Then run the following command to run the game:
```bash
> ./tictactoe ../res/settings.txt
```
## Custom Game Parameters
The `settings.txt` file in `res/` can be edited to customise board size and win conditions in the format below (without comments):

```c
m=5 // Board width.
n=5 // Board height.
k=4 // Tiles in a row needed to win.