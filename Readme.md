# Simple shell

## dependencies

to install readline, feel free to edit it to use `fgets` or `scanf` refer to this [link](https://stackoverflow.com/questions/17294809/reading-a-line-using-scanf-not-good) for reference on both. 

```bash
sudo apt-get install libreadline6 libreadline6-dev
```

## Features

1. external commands
    1. ls
    2. echo
    3. hello (deprecated, before being released 🤣🤣)
2. internal commands
    1. hello (yes again, this is the one that will actually run)
    2. cd 
    3. env 
    4. set 

## Make from source

to compile the code

```bash
mkdir build
mkdir build/bin
make shell
make commands
```

## Run

```bash
./build/shell
```

## Notes

This code is developed to simulate how I expect an actual shell works. any resmeblance between this and reality is mere coincidence. 