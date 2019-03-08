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


