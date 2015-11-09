Note: still a __work in progress__, so do not expect much.

ASCII Roguelike
===============

Following what I did in the [Tic Tac Toe][tictactoe], the [third game challenge][challenge] is a roguelike.

This time I created a [PlantUML][plantuml] file to describe all the classes in the game, and tried to make things as clean as possible.

TODOs
=====

- [ ] every `.level` should have a `.data` to describe the player's data (at a minimum, initial position, attack and health) and enemies (same thing, with one enemy per line untill the end of the file);
- [ ] validation for `*.data` files;
- [ ] load all valid maps and ask the player which one to run;
- [ ] create more maps.

Instructions
============

To compile and run this program, you need [CMake][cmake] and a C++ compiler that supports C++14 (yes, I moved the requisites up a bit for this one, even though I'm not sure if I actually use anything from the C++14 standard... I know I did before cleaning all test code...).

Oh, this time you'll also need [Boost][boost] (specifically, `system` and `filesystem`). See `sys::lstfiles` in `system/system.cpp`.

If you are not familiar with CMake, the instructions are simple: make a build directory inside the project tree and, from inside of it, call CMake poiting to the folder above. It will generate the necessary files to build the program in your machine; in a \*nix system:

```
mkdir build; cd build; cmake ..; make
```

will create the `main` executable inside the `build` directory.

In a Windows machine, apparently CMake generates Visual Studio files. Check the documentation.

[cmake]: https://cmake.org/
[tictactoe]: https://github.com/fickledogfish/tic_tac_toe
[challenge]: https://www.youtube.com/watch?list=PLSPw4ASQYyynKPY0I-QFHK0iJTjnvNUys&feature=player_detailpage&v=tVWckBaB5xo
[plantuml]: http://plantuml.com/
[boost]: http://www.boost.org/
