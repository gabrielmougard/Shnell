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

Type the following command in the project directory :
`chmod +x install.sh` and `sudo ./install.sh`. Then the build process will begin...
For instance, To execute the demo you can go in `shnell/bin` and type `./shnell`. 

## Portability to MCU

All the libraries (`stdio.h`,`stdlib.h`,`string.h`,`stdio.h`,`signal.h`,`sys/types.h`,`sys/wait.h`,`unistd.h`) are portable on an RaspberryPi ARM processor ( see [this link](https://packages.debian.org/fr/sid/armhf/libc6-dev/filelist)). 
So it already portable to MCU.

## Process story

I began the development of the application Thurday the 7th of March just after receiving the mail for the challenge.
First, I searched on the Internet on how to implement a basic shell in C since I had never done anything like this before...
I found some interesting ressources and I heavily relied on them (at first) to build the upper part of "Shnell" (the reading, parsing and executing processes of the shell).
Then, I decided to implement my own abstract data types for some tasks (e.g : the Node structure, to have a LinkedList containing the written command and not a simple buffer
because of the fixed size of this one). I end up coding the simplest features first (the `version` command, the `pwd` command, etc...) and finally, once I had done the `led status`, `led on`, and `led off` commands, things were just starting to get fun...
I just can't figure out how to do the 'blinking' process without stopping the main program. I got stuck into this particular problem for a couple of days, but I decided to go for some inefficient solutions since I was running out of ideas...
I decided to use child processes (with `fork()`) in an other terminal to simulate the LED. Actually, for each blinking LED, there is one associated terminal with a fancy blinking icon and the PID ! Then I add to do a Makefile in order to build the project. Currently, I'm still debugging the codebase. I hope I will solve the main issues.

Wednesday the 13th of March 2019, the shell is around 85% functionnal. I'm still debugging the `led blink-start` and `led blink-stop` commands since I had a lot of segmentation faults.
I am facing problems (seg fault) that I'm unable to solve for instance.. It seems that when I do `led on <some_id>` it works once and then if I want to do it again, here appear a seg fault.
The blinking process work but since I had seg faults A cannot integrate this functionnality on the global project...
To have a glimpse of the child process, you can go in `blinkingProc/bin` and type `./blink <LED_ID> <PID> <DELAY>` (the DELAY is in ms)... 

Thursday the 14th of March 2019 : Finally ! I get rid of the problem ! Instead of using a file storage system for the structure (ledId,PID,state), I decided to implement an internal storage using Node in a LinkedList. However, when I type `led status`, the two first lines are very strange but when adding leds with `led on <LED_ID>` or `led off <LED_ID>` , it works. Now I have to get rid of small bugs and I will be good to go.

Thursday the 14th of March 2019 : I don't understand why the blinking child process is not starting when calling `led start-blink <LED_ID> <DELAY>` (DELAY in ms).
The list of errors can be found [here](https://linux.die.net/man/2/fork). Of course, if `led start-blink` is unsuccessful, it is the same for `led stop-blink`.

However, all the other features are working (even the bonus ones)

Cheers !
