# =========================
# NOM DU PROGRAMME
# =========================

NAME = game

# =========================
# COMPILATEUR ET OPTIONS
# =========================

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

# =========================
# SOURCES 
# =========================

SRCS = main.c \
       board.c \
       gravity.c \
       player.c \
       rotation.c \
       save.c \
       win.c

OBJS = $(SRCS:.c=.o)

# =========================
# REGLES PRINCIPALES
# =========================

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# =========================
# COMPILATION .c -> .o
# =========================

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# NETTOYAGE
# =========================

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# =========================
# PHONY
# =========================

.PHONY: all clean fclean re
