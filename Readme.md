# Simple shell

## dependencies

to install readline, feel free to edit it to use `fgets` or `scanf` refer to this [link](https://stackoverflow.com/questions/17294809/reading-a-line-using-scanf-not-good) for reference on both. 

```bash
sudo apt-get install libreadline6 libreadline6-dev
```

## Features

1. external commands: Can run any external command in `/usr/bin`.

2. internal commands
    1. hello
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
