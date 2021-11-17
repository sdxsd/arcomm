#ifndef ARCOMM_H
# define ARCOMM_H
# define VERSION 0.1
# define INTERACTIVE 0
# define TRUE 1
# define FALSE 0
# define DELAY 1024
# define MAX_BUFFER 255
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

const char *USAGE = "arcomm [-s] [content] / arcomm -i";
const char *ARDUINO_DEVICE = "/dev/ttyACM0";
const char *STTY_EXEC = "stty -F /dev/ttyACM0 -hupcl";

#endif
