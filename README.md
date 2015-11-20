# Quarri
A remake of the math class classic BlockDude, where you play an adorable forklift named Quarri who needs to solve puzzles consisting of moving and maneuver around blocks in order to bust out of block hell and find her real home

## Installing and running
#####WARNING: make sure the path you clone to doesn't have spaces in any directory name or the Makefile won't work

1. git clone https://github.ccs.neu.edu/QuadPrism/Quarri.git
2. cd Quarri
3. make install
4. make
5. ./main

## Objective
Get to the exit

## Controls
Left and right arrows move left and right. (see movement)
Space bar or down arrow to pick up/put down a block (see pick things up and put things down)

## Movement
Quarri moves one space on the grid at a time.
Player must tap the key more than one time in order to move more than once.
Quarri will automatically move up on top of a block if there is a block in her way
but, if the obstacle is two or more blocks high, Quarri cannot move in that direction
Quarri can fall down any number of blocks, no matter how deep the pit. 
No fall damage.

## Pick things up and put things down
When you press space/down arrow:
If Quarri is not holding a block, Quarri picks up the block directly in front of her, if there is one.
If Quarri is holding a block, she puts it down in the space directly in front of her, if there is space.

Quarri carries the block on top of her head. This makes it so she can't get through shallow rooms.
Quarri cannot pick up bricks.
When placing a block, the place where the block goes is the place where Quarri would have gone if she had moved in that direction. 
So, if there is a one-block-high obstacle in front of Quarri, she places it on top of that obstacle.
If there is a pit, she places the block in the bottom of the pit.
Likewise, if Quarri cannot move there, she cannot place a block there.
So, if there is an obstacle of two or more blocks high, Quarri cannot place a block in that direction.
Quarri turns around when you move (or attempt to move) in a direction, so that when you place a block it goes in the space towards the last direction you moved in (ie if you just pressed left she will put the block down to her left, never to her right).
Placing a block does not cause Quarri to move.
