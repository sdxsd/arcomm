# arcomm [Arduino Communicator]
Simple tool for sending data to an Arduino over the serial port. 

## Installation
***DEFAULT MODE COMPATIBLE ONLY WITH GNU + LINUX SYSTEMS***

The installation is relatively simple:
```
git clone https://github.com/sdxsd/arcomm
cd arcomm
make install
```

## Use
arcomm has two modes of use:

Interactive:
```
    arcomm -i
```

Default:
```
    arcomm -s [content you wish to send]
```

In interactive mode, data is sent each time the return key is pressed, then the amount of bytes sent is displayed. The program closes upon receiving a blank newline.

In default mode, the paramer passed after -s is sent to the Arduino
