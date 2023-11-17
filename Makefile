NAME = cub3D

SRC = $(CUBE_SRC) $(SRC_GNL)

CUBE = array_utils.c images.c map_parsing.c draw.c player.c checkers.c t_tex_utils.c tc_utils.c fetch_header_data.c main.c
CUBE_SRC = $(addprefix srcs/, $(CUBE))

LIBFT_A = libft.a
LIBF_DIR = libft/
LIBFT  = $(addprefix $(LIBF_DIR), $(LIBFT_A))

GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix gnl/, $(GNL))

OBJ = *.o
CC = gcc -g
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LINKS = -framework OpenGL -framework AppKit -lmlx

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Making libft..." $(NONE)
	@make -C $(LIBF_DIR)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(LINKS) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@$(CC) $(FLAGS) -c $(SRC)

norm:
	@echo $(GRAY) ""
	@norminette $(SRC) *.h */*.h
	@echo $(NONE) ""

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ)
	@make -C $(LIBF_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@make -C $(LIBF_DIR) fclean

re: fclean all
