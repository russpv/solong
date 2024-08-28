NAME = solong
OUTPUT = executable

SOURCES = main.c parse_args.c init_app.c render_map.c events.c utils.c frees.c 
BONUS_SOURCES = $(SOURCES)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)
OBJECTS = $(SOURCES:.c=.o)

# Colors
YELLOW = \033[33m
GREEN = \033[32m
RESET = \033[0m
BOLD = \033[1m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L$(LIB_DIR) -lft
LDFLAGS_SO = -L$(LIB_DIR) -lft -Wl,-rpath,$(LIB_DIR)

LIB_CPDIR = .
LIB_DIR = libft
LIB_NAME = libft.a
LIB_NAME_SO = libft.so
LIB_PATH = $(LIB_DIR)/$(LIB_NAME)
LIB_PATH_SO = $(LIB_DIR)/$(LIB_NAME_SO)

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL framework AppKit
endif


# Targets
all: $(MLX_LIB) $(NAME)

$(NAME): $(LIB_PATH) $(OBJECTS)
	@echo "Creating $(NAME) $(OUTPUT)..."
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(MLX_FLAGS)
	chmod +x $@
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: $(words $(OBJECTS) ) object file(s)$(RESET)"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

bonus: .bonus_made

.bonus_made: $(NAME)

#	@echo "Creating $(NAME) $(OUTPUT)..."
#	$(CC) $^ -o $@ $(CFLAGS)
#	chmod +x $@
#	-@touch .bonus_made
#	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
#	@echo "$(YELLOW)Created: $(words $(OBJECTS) $(BONUS_OBJECTS)) object file(s)$(RESET)"
#	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDES) #Initial compilation of .c files

# make lib
$(LIB_PATH):
	@$(MAKE) -C $(LIB_DIR)
	@echo "Copying $(LIB_NAME) to ../"
	@cp $(LIB_PATH) .

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS) 
	@$(MAKE) -C $(LIB_DIR) clean
	rm -f $(LIB_NAME) # don't delete so!
	-@rm -f .bonus_made
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW) Deleted: $(words $(OBJECTS) $(BONUS_OBJECTS)) object file(s)$(RESET)"

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_PATH)
	rm -f $(LIB_NAME)
	rm -f $(LIB_NAME_SO)
	@echo "$(GREEN)SUCCESS$(RESET)"
	@echo "$(YELLOW) Deleted $(words $(NAME)) object files(s)$(RESET)"
	@echo "$(YELLOW) Deleted: $(NAME)"

re: fclean all

so:

	$(CC) -fPIC $(CFLAGS) -c $(SOURCES) $(BONUS_SOURCES)
	$(CC) -nostartfiles -shared -o pipex.so $(OBJECTS) $(BONUS_OBJECTS)

.PHONY: all bonus clean fclean re so
