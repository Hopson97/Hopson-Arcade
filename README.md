# hopson-arcade

This is a collection of small aracde-y games, created using C++17 and SFML

## Games

List of all the games in the "arcade".

### Space Invaders

[Source](https://github.com/Hopson97/Hopson-Arcade/tree/master/Source/SpaceInvaders)

[Video](https://www.youtube.com/watch?v=MkpxwsybNPo)

This is based on the 1978 arcade game created by Tomohiro Nishikad.

This was the first game added to this project.

![Space Invaders](https://i.imgur.com/b7KAzXo.png)


## Building and Running

### Libraries

SFML is required.

These can be installed from your project manager. For example, on Debian/ Ubuntu:

```sh
sudo apt install libsfml-dev
```

If this is not possible (eg windows), you can install these manually from their respective websites:

https://www.sfml-dev.org/download.php

### Linux

To build, at the root of the project:

```sh
sh scripts/build.sh
```

To run, at the root of the project:

```sh
sh scripts/run.sh
```

To build and run in release mode, simply add the `release` suffix:

```sh
sh scripts/build.sh release
sh scripts/run.sh release
```

You can also create a deployable build (that can be sent) by doing:

```sh
sh scripts/deploy.sh
```
