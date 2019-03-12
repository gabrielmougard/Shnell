# Shnell - A Shell Snips challenge

This shell implementation is meant to be translated or ported on ARM Cortex class MCU. The task is to write a C program using stdin/stdout to implement a shell with the commands specified in the __CLI main features__ and in __CLI bonus features__ part.

## Operating system

Currently, the program is only compatible with Linux systems. (tested on Ubuntu 18.04)

## Dependencies

(By default, all of these dependencies are installed by default but if you encounter a problem during the building process, refer to this)

 * xterm
 * stdio.h
 * stdlib.h
 * unistd.h
 * sys/types.h
 * sys/stat.h
 * dirent.h

## CLI main features

* __version__ : display the version of the program.
* __help__ : display all commands available for this shell.
* __led on__ `<led_id>` : activate the led with the specified ID.
* __led off__ `<led_id>` : desactivate the led with the specified ID.
* __led off__ `<led_id>` : desactivate the led with the specified ID.
* __led start-blink__ `<led_id>` `<delay>` :  Blink led `<led_id>` with a `<delay>` in ms between on and off, while keeping the shell working.
* __led stop-blink__ `<led_id>` :  Stop the blinking led `<led_id>`.
* __led status__ :  Show the current state of each led.

*(N.B : we emulate the led state change by writting a message to stdout or stderr)*

## CLI bonus features

* __cd__ : the infamous UNIX command to change the current directory is also available.
* __ls__ : you can also list the content of your current directory.
* __pwd__ : print the current working directory.

## How to install

Type the following command in the project directory (in root priviledge) :
`make` and `make install`.
Then you can type `shnell` in a terminal to launch the program.

## Portability to MCU

Coming soon.

## Process story

I began the development of the application Thurday the 7th of March just after receiving the mail for the challenge.
First, I searched on the Internet on how to implement a basic shell in C since I had never done anything like this before...
I found some interesting ressources and I heavily relied on them (at first) to build the upper part of "Shnell" (the reading, parsing and executing processes of the shell).
Then, I decided to implement my own abstract data types for some tasks (e.g : the Node structure, to have a LinkedList containing the written command and not a simple buffer
because of the fixed size of this one). I end up coding the simplest features first (the `version` command, the `pwd` command, etc...) and finally, once I had done the `led status`, `led on`, and `led off` commands, things were just starting to get fun...
I just can't figure out how to do the 'blinking' process without stopping the main program. I got stuck into this particular problem for a couple of days, but I decided to go for some inefficient solutions since I was running out of ideas...
I decided to use child processes (with `fork()`) in an other terminal to simulate the LED. Actually, for each blinking LED, there is one associated terminal with a fancy blinking icon and the PID ! Then I add to do a Makefile in order to build the project. Currently, I'm still debugging the codebase. I hope I will solve the main issues.

Cheers !
