# Pacman
Project for Advanced Programming Course by Torben Petré (s0241699) as a 2nd year Bachelor Student in Computer Sciences at the University of Antwerp.

> [!IMPORTANT]
> If errors appear related to Asset file paths it means the you are not correctly running the project from the right working directory. Continue reading.

The project should be built from a folder located in the project root. The working directory must be set to the build directory (so normally you should not provide any arguments to the compiler). This way assets paths should work right away.

When running from the terminal ensure you are inside the build directory and that this build directory is at the root level of the project, just like `main.cpp` or `CMakeLists.txt`.

## Valgrind
Any Valgrind memory leak tests are recommended to be run with the `sfml.supp` file a suppression file parameter. The SFML library uses some external libraries that produce a lot of noise on the final Leak Summary.

## Docs
Docs are generated with Doxygen and use the doxygen.txt config file. Can also be accessed from [https://kipteamm.github.io/Pacman/](https://kipteamm.github.io/Pacman/)
