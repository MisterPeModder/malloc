ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIB_NAME := ft_malloc
NAME := lib$(LIB_NAME)_$(HOSTTYPE).so
LNK_NAME := lib$(LIB_NAME).so

# Basic definitions
SRC_PATH := srcs
OBJ_PATH := .bin
INC_PATH := includes

# Compiler flags
CPPFLAGS := -iquote$(INC_PATH)
CFLAGS :=	-Wall -Wextra -Werror -std=c89 -pedantic -Wmissing-prototypes \
			-Wsign-conversion -g -fPIC

# Commands
CC := gcc
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
PRINT := printf
NORM := norminette

SRCS_NAMES :=		ft_calloc.c			\
					ft_free.c			\
					ft_malloc.c			\
					ft_realloc.c		\
					interface.c			\
					segment.c			\
					show_alloc_mem.c	\
					utils.c				\

LIBFT_SRCS_NAMES :=	ft_memset.c			\
					ft_bzero.c			\
					ft_memcpy.c			\
					ft_memccpy.c		\
					ft_memmove.c		\
					ft_memchr.c			\
					ft_memcmp.c			\
					ft_strdup.c			\
					ft_strlen.c			\
					ft_strcpy.c			\
					ft_strncpy.c		\
					ft_strcat.c			\
					ft_strncat.c		\
					ft_strlcat.c		\
					ft_strchr.c			\
					ft_strrchr.c		\
					ft_strstr.c			\
					ft_strnstr.c		\
					ft_strcmp.c			\
					ft_strncmp.c		\
					ft_atoi.c			\
					ft_isalpha.c		\
					ft_isdigit.c		\
					ft_isalnum.c		\
					ft_isascii.c		\
					ft_isprint.c		\
					ft_isspace.c		\
					ft_putchar.c		\
					ft_putchar_fd.c		\
					ft_putstr.c			\
					ft_toupper.c		\
					ft_tolower.c		\
					ft_memalloc.c		\
					ft_memdel.c			\
					ft_strnew.c			\
					ft_strdel.c			\
					ft_strmap.c			\
					ft_strmapi.c		\
					ft_strequ.c			\
					ft_strnequ.c		\
					ft_strsub.c			\
					ft_strjoin.c		\
					ft_strtrim.c		\
					ft_strsplit.c		\
					ft_itoa.c			\
					ft_strclr.c			\
					ft_striter.c		\
					ft_striteri.c		\
					ft_putstr_fd.c		\
					ft_putendl.c		\
					ft_putendl_fd.c		\
					ft_putnbr.c			\
					ft_putnbr_fd.c		\
					ft_lstnew.c			\
					ft_lstdelone.c		\
					ft_lstdel.c			\
					ft_lstadd.c			\
					ft_lstiter.c		\
					ft_lstmap.c			\
					ft_strupcase.c		\
					ft_strlowcase.c		\
					ft_lstlen.c			\
					ft_lst_pushback.c	\

SRCS_NAMES += $(addprefix libft/, $(LIBFT_SRCS_NAMES))

SRCS := $(addprefix $(SRC_PATH)/,$(SRCS_NAMES))

OBJS := $(addprefix $(OBJ_PATH)/,$(SRCS_NAMES:.c=.o))

INCS :=			ft_malloc.h			\
INCS :=			ft_malloc_impl.h	\
				libft.h				\

DIRS := $(OBJ_PATH) $(OBJ_PATH)/libft

# THE NORM IS REAL
NORM_LOG := norm.log
NORM_FILES := $(SRCS) $(INCS)

# Cosmetic features
DETAILED = 1
RESET := \033[0m
GREY := \033[90m
GREEN := \033[32m
YELLOW := \033[93m
DYELLOW := \033[33m
UNDERLINE := \033[4m

all: $(LNK_NAME)

$(LNK_NAME): $(NAME)
	@ln -ns $(NAME) $(LNK_NAME) 2> /dev/null || true
	@$(PRINT) "$(GREEN)done!$(RESET)\n"

$(NAME): $(DIRS) $(OBJS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(GREEN)done!$(RESET)"
endif
	@$(PRINT) "\n$(GREY)Compiling $(RESET)$(NAME)$(GREY): $(RESET)"
	@$(CC) -shared -o $(NAME) $(OBJS)

$(DIRS):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(RESET)$(notdir $@)"
endif
	@$(CC) -D _GNU_SOURCE $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) -r *.dSYM
	@$(RM) $(OBJS) 2> /dev/null || true
	@$(RMDIR) $(OBJ_PATH) 2> /dev/null || true
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)object files!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) 2> /dev/null || true
	@$(RM) $(LNK_NAME) 2> /dev/null || true
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)$(NAME) library!$(RESET)\n\n"

re: fclean all

norm:
	@$(PRINT) "$(GREY)Checking $(RESET)The Norm$(GREY)...$(RESET)\n"
	@$(PRINT) "Found $(GREEN)$(words $(NORM_FILES))$(RESET) files!\n"
	@$(RM) $(NORM_LOG)
	@$(NORM) $(NORM_FILES) >> $(NORM_LOG)
	@$(PRINT) "Norm Errors: "
	@cat $(NORM_LOG) | grep Error | wc -l | bc
	@$(PRINT) "See $(UNDERLINE)$(NORM_LOG)$(RESET) for details.\n"

.PHONY: all clean fclean re norm
