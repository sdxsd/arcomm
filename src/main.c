#include "../arcomm.h"

void inter_shell(int arduino_fd) {
    char *buf;
    size_t buf_size;
    int input;
    size_t iter;

    iter = 0;
    buf_size = MAX_BUFFER;
    input = TRUE;
    printf(":: ARCOMM RUNNING INTERACTIVELY ::\n");
    printf(":: MAX BUFFER = %d ::\n", MAX_BUFFER);
    printf(":: END INPUT WITH EMPTY NEWLINE\n");
    while (input) {
        buf = (char *)calloc(sizeof(char), MAX_BUFFER);
        if (!buf) {
            printf("ERROR: BUFFER ALLOCATION FAILED\n");
            exit(-1);
        }
        getline(&buf, &buf_size, stdin);
        if (!strcmp(buf, "\n"))
            input = FALSE;
        printf("\n%ld BYTES SENT TO ARDUINO\n", write(arduino_fd, buf, buf_size));
        free(buf);
    }
    return;
}

int main(int argc, char *argv[]) {
    int  mode = 0;
    int  arduino_fd;
    char *to_send;

    if (argc > 1) {
        if (!strcmp(argv[1], "-i"))
            mode = 1;
        else if (!strcmp(argv[1], "-s") && argc > 2)
        {
            to_send = argv[2];
            system("stty -F /dev/ttyACM0 -hupcl");
        }
        else {
            printf("%s\n", USAGE);
            return (0);
        }
    }
    else {
        printf("%s\n", USAGE);
        return (0);
    }
    arduino_fd = open(ARDUINO_DEVICE, O_WRONLY);
    if (arduino_fd == -1) {
        printf("ERROR: FAILED OPENING ARDUINO DEVICE\n");
        return (-1);
    }
    if (mode)
        inter_shell(arduino_fd);
    else {
        write(arduino_fd, to_send, strlen(to_send));
        usleep(DELAY);
        close(arduino_fd);
    }
    return (0);
}
