I first was just testing around with creating a window and setting the size and painting the background.
This project then became a bit of a playground for me to test different features within SDL2
I followed quite a few examples and pursued learning more indepth using chatgpt (I never pasted, only typed what it suggested so that i would gain a better understanding of what was happening)
lastly i made 2 rectangles: one as the player, and one as the obstacle. and created a collision using SDL's HAS_Intersection method to replace my multiple if statements with one singular method.


WHAT I LEARNED ABOUT GAME ENGINES:
- SDL2 is a very useful lib for creating objects
- object movement is a lot more manuipulatable if you break it into 4 sections (speed, acceleration, friction/deceleration, and time)
- never use just a speed variable, it will make someone who runs the game at 150fps experience time 3x faster than someone with 50fps. instead use a deltaTime variable (in the code)
- renderer objects in SDL are loaded first with colour and then used to paint whatever object you want.
- colliders create obstructions by keeping a log of the previous position before movement is applied in order to 'push' an object back to it's previous position if it collides with an object.

WHAT I LEARNED ABOUT C++:
- I broke down the terminal command "g++ main.cpp -o app -lSLD2" and learned that it meant "[COMPILER] [FILE TO COMPILE] [CALL IT] [FILENAME] [COMPILE WITH THIS LIBRARY]
- I learned that if you want to make a larger project, you use CMake to be like maven's pom.xml in java.
- I learned to use a struct for the player instead of a full class to keep the variables inside public by default (where a class is private)

WHAT QUESTIONS I WILL ANSWER WITH FUTURE PROJECTS:
- how can I make scenes with this (main menu, game over, level 2, general UI elements)
- how can I use a sprite instead of just a rectangle
- do I use individual objects to create different entities or do I use inheritance to create an Entity parent object and tons of children objects like (floor, player, bullets, item, wall, etc)
- is gravity just time-based downward speed or is it more complicated (probably is with acceleration upwards when jump and downwards when fall)
- how do I upload a game to somewhere like steam
- can I render in 3D with SDL or will I need more Libraries
- how can I optimize my games overall


 That's all for now folks but I'll see you in the next project!
