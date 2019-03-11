# Shnell - A Shell Snips challenge

This shell implementation is meant to be translated or ported on ARM Cortex class MCU. The task is to write a C program using stdin/stdout to implement a shell with the following command :

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

With GCC... duh !
(Coming soon)

## Portability to MCU

Coming soon.

## Process story

I began the development of the application Thurday the 7th of March just after receiving the mail for the challenge.
First, I searched on the Internet on how to implement a basic shell in C since I had never done anything like this before...
I found some interesting ressources and I heavily relied on them (at first) to build the upper part of "Shnell" (the reading, parsing and executing processes of the shell).
Then, I decided to implement my own abstract data types for some tasks (e.g : the Node structure, to have a LinkedList containing the written command and not a simple buffer
because of the fixed size of this one). I end up coding the simplest features first (the `version` command, the `pwd` command, etc...) and finally, once I had done the `led status`, `led on`, and `led off` commands, things were just starting to get fun...
I just can't figure out how to do the 'blinking' process without stopping the main program. I got stuck into this particular problem for a couple of days, but I decided to go for some inefficient solutions since I was running out of ideas...
I decided to use child processes (with `fork()`) in an other terminal to simulate the LED. Actually, for each blinking LED, there is one associated terminal with a fancy blinking icon and the PID ! Currently, I'm still debugging the codebase. I hope I will solve the main issues.

Cheers !
