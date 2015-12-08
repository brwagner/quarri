# Quarri
A remake of the math class classic BlockDude, where you play an adorable forklift named Quarri who needs to solve puzzles consisting of moving and maneuver around blocks in order to bust out of block hell and find her real home

# Supported Platforms
Linux, Mac, Windows (if make installed)

## Running from binary
In the quarri distribution folder you should see:

* main
* runner
* res/

Run main from the command line using ./main. Note: Running main by double clicking will just pop up an empty screen.

Run the tests from the command line using ./runner.

If you need to make a distribution run 'make dist' in source.

## Compiling from source
#####WARNING: make sure the path you clone to doesn't have spaces in any directory name or the Makefile won't work

1. git clone https://github.ccs.neu.edu/QuadPrism/Quarri.git
2. cd Quarri
3. make install
4. make
5. ./main

## Objective
Get to the green block to advance to the next level, until there no levels left!

## Controls
A and D move Quarri left and right. 
Left and right arrows move the camera left and right.
S to pick up/put down a block.

## Movement
When the player hits A or D,
if Quarri is not facing in that direction (left for A, right for D), she turns to face that way but stays in the same place.
if Quarri is already facing that direction, she moves that way.
Quarri moves one space on the grid at a time.
Player must tap the key more than one time in order to move more than once.
Quarri will automatically move up on top of a block if there is a block in her way
but, if the obstacle is two or more blocks high, Quarri cannot move in that direction
Quarri can fall down any number of blocks, no matter how deep the pit. 
No fall damage.

## Pick things up and put things down
When you press S arrow:
If Quarri is not holding a block, Quarri picks up the block directly in front of her, if there is one.
If Quarri is holding a block, she puts it down in the space directly in front of her, if there is space.
Quarri carries the block on top of her head. This makes it so she can't get through shallow rooms.
Quarri cannot pick up bricks. Quarri can only pick up certain movable blocks distinguished by color.
When placing a block, the place where the block goes is the place where Quarri would have gone if she had moved in that direction. 
If there is a pit, she places the block in the bottom of the pit.
Likewise, if Quarri cannot move there, she cannot place a block there.
So, if there is an obstacle of two or more blocks high, Quarri cannot place a block in that direction.
The exception to these rules is that, if there is a one-block-high obstacle in front of Quarri, she cannot place the block there.
Quarri turns around when you move (or attempt to move) in a direction, so that when you place a block it goes in the space towards the last direction you moved in (ie if you just pressed left she will put the block down to her left, never to her right).
Placing a block does not cause Quarri to move.
