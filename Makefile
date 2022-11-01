# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 16:16:41 by deelliot          #+#    #+#              #
#    Updated: 2022/11/01 19:53:19 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# FLAGS += -fsanitize=address -Wconversion -Ofast -flto

# Directories
SRCS_DIR = srcs
OBJS_DIR = objs
INCS = -I includes/ -I libft/includes/ -I minilibx/
HDRS = includes/RTv1.h \
	includes/colour_and_light.h \
	includes/matrices.h \
	includes/objects.h \
	includes/tuple.h \
	includes/world.h
LIBFT_DIR = libft
MINILIBX_DIR = minilibx

# Source and object files
FILES = \
	main \
	initialise \
	image \
	error_handling \
	tuple_operations \
	matrix_maths \
	matrix_inversion \
	handle_input \
	intersect \
	matrix_transformations \
	plot \
	normals \
	transform_tuple \
	reflections \
	sphere \
	world \
	view_transform \
	shading \
	camera \
	ray \
	render \
	colour \
	computations \
	sphere_scene

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

# Paths
LIBFT_A = $(LIBFT_DIR)/libft.a
MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
LIBS = $(LIBFT_A) $(MINILIBX_A)

# Libraries
LINKS = \
	-lm \
	-L $(LIBFT_DIR) -lft \
	-L $(MINILIBX_DIR) -lmlx \
	-framework OpenGL -framework Appkit

# iMac minilibx:
# LINKS = -L /usr/local/lib -lmlx -I /usr/local/include -framework \
# 	OpenGL -framework AppKit

#Rules
all: $(NAME)

valgrind_debian: CC := docker run --rm --workdir $(HOME) --entrypoint $(CC) -v $(shell pwd):$(HOME) mooreryan/valgrind
valgrind_debian: PREREQUISITES = .prerequisites_debian
valgrind_debian: fclean libft_debian all

libft_debian:
	make -C $(LIBFT_DIR) valgrind_debian

$(NAME): $(PREREQUISITES) $(LIBS) $(OBJS) Makefile
	touch $(PREREQUISITES)
	$(CC) $(FLAGS) $(INCS) $(LINKS) $(OBJS) -o $(NAME)
	@echo "Usage: ./RTV1 + option"
	@echo "options: >> ??"

$(OBJS): $(OBJS_DIR)%.o:$(SRCS_DIR)%.c $(HDRS) Makefile
	$(CC) $(FLAGS) $(INCS) -o $@ -c $<

PREREQUISITES = .prerequisites
.prerequisites: $(OBJS_DIR)
	/bin/rm -f .prerequisites_debian

.prerequisites_debian: $(OBJS_DIR)
	/bin/rm -f .prerequisites

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
$(LIBFT_A):
	make -C $(LIBFT_DIR)
$(MINILIBX_A):
	make -C $(MINILIBX_DIR)

clean:
	/bin/rm -Rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)
	@echo " Objects removed"

fclean: clean
	/bin/rm -f $(NAME) .prerequisites
	make -C $(LIBFT_DIR) fclean
	@echo " $(NAME) removed "

re: fclean all

.PHONY: all clean fclean re valgrind_debian libft_debian
