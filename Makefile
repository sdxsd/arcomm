CC = gcc
CFILES = src/main.c
OFLAGS = -o
NAME = arcomm

all: clean $(NAME)

$(NAME):
	$(CC) $(CFILES) $(OFLAGS) $(NAME)

clean:
	@rm -f $(NAME)

install: $(NAME)
	sudo cp $(NAME) /usr/bin/
