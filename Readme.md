# Simple shell

to install readline, feel free to edit it to use `fgets` or `scanf` refer to this [link](https://stackoverflow.com/questions/17294809/reading-a-line-using-scanf-not-good) for reference on both. 

```bash
sudo apt-get install libreadline6 libreadline6-dev
```

to compile the code
```bash
mkdir build
mkdir build/bin
gcc shell.c -lreadline -o ./build/shell
gcc ./lib/echo.c -o ./build/bin/echo
```

to run the command

```bash
cd build
./shell
```

You need to change into the build directory for the path to take actual effect