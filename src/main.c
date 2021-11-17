#include "../arcomm.h"

void inter_shell(int arduino_fd) {
    char *buf;
    size_t buf_size;

    buf_size = MAX_BUFFER;
    printf(":: ARCOMM RUNNING INTERACTIVELY ::\n");
    printf(":: END INPUT WITH EMPTY NEWLINE\n");
    while (TRUE) {
        buf = (char *)calloc(sizeof(char), MAX_BUFFER);
        if (!buf) {
            perror(ERROR);
            exit(-1);
        }
        getline(&buf, &buf_size, stdin);
        if (!strcmp(buf, "\n"))
            break;
        printf("%ld BYTES SENT TO ARDUINO\n", write(arduino_fd, buf, strlen(buf) - 1));
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
        else if (!strcmp(argv[1], "-s") && argc > 2) {
            to_send = argv[2];
            system(STTY_EXEC);
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
        perror(ERROR);
        return (-1);
    }
    if (mode)
        inter_shell(arduino_fd);
    else {
        if (!write(arduino_fd, to_send, strlen(to_send))) {
            perror(ERROR);
            return (-1);
        }
        usleep(DELAY);
        close(arduino_fd);
    }
    return (0);
}
