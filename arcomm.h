#ifndef ARCOMM_H
# define ARCOMM_H

# ifdef __APPLE__
#  define ARDUINO_DEVICE "/dev/cu.usbmodem101"
#  define STTY_EXEC "stty -f /dev/cu.usbmodem101 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts"
# endif

# ifdef __linux__
#  define ARDUINO_DEVICE "/dev/ttyACM0"
#  define STTY_EXEC "stty -F /dev/ttyACM0 -hupcl"
# endif

# ifndef ARDUINO_DEVICE
#  define ARDUINO_DEVICE NULL
# endif

# define INTERACTIVE 0
# define TRUE 1
# define FALSE 0
# define MAX_BUFFER 255

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

const char *USAGE = "arcomm [-s] [content] / arcomm -i";
const char *ERROR = "FATAL ERROR";

#endif
