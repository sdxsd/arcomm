#include "../arcomm.h"

void inter_shell(int arduino_fd) {
    int c;
    int input;
    size_t iter;
    char *buf;

    iter = 0;
    input = TRUE;
    printf(":: ARCOMM RUNNING INTERACTIVELY ::\n");
    printf(":: MAX BUFFER = %d ::\n", MAX_BUFFER);
    printf(":: END INPUT WITH EOF\n");
    while (input) {
        buf = (char *)calloc(sizeof(char), MAX_BUFFER);
        while (*buf)
            *buf++ = '\0';
        if (!buf) {
            printf("ERROR: BUFFER ALLOCATION FAILED\n");
            exit(-1);
        }
        while ((c = getchar()) && iter < MAX_BUFFER) {
            if (c == EOF)
                input = FALSE;
            buf[iter] = c;
            iter++;
        }
        buf[iter++] = 0;
        printf("\n%ld BYTES SENT TO ARDUINO\n", write(arduino_fd, buf, strlen(buf)));
        free(buf);
    }
    return;
}

int main(int argc, char *argv[]) {
    int  mode = 0;
    int  arduino_fd;
    char *to_send;

    if (argc > 2) {
        if (!strcmp(argv[1], "-i"))
            mode = 1;
        else if (!strcmp(argv[1], "-s"))
            to_send = argv[2];
        else {
            printf("%s\n", USAGE);
            return (0);
        }
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
