# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 20:41:46 by tfregni           #+#    #+#              #
#    Updated: 2023/09/04 17:01:17 by tvasilev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix $(SRCS_DIR)/, main.c parse.c populate_element.c populate_solid.c parse_util.c \
				libx.c render.c sphere.c plane.c vector_calcs.c event_handler.c \
				matrix_calcs.c camera.c shade.c vec3.c ray.c cylinder.c)
UNAME_S		:= $(shell uname -s)
OBJS		= ${patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,${SRCS}}
SRCS_DIR 	= srcs
OBJS_DIR 	= obj
INC_DIR		= includes
CC			= cc
CFLAGS		= -O3 -Wall -Wextra -Werror -g
NAME		= minirt
LINKS		= -lm -Llibft -lft
INC			= -Ilibft -I$(INC_DIR)
RE_LIBFT	= "$(wildcard ./libft/libft.a)"
DSYM		= *.dSYM
RM			= rm -rf
MAKE		= make -s

ifeq (${UNAME_S}, Linux)
MLX_PATH	= mlx-linux
MLX_TAR 	= minilibx-linux.tgz
LINKS 		+= -lbsd -lXext -lX11
INC			+= -Ilinux
endif

ifeq (${UNAME_S}, Darwin)
MLX_PATH	= mlx-mac
MLX_TAR		= minilibx_opengl.tgz
LINKS		+= -framework OpenGL -framework AppKit
INC			+= -Imac
endif

INC 		+= -I${MLX_PATH}
LINKS 		+= -L./${MLX_PATH} -lmlx

mlx		:
	@if [ ! -d "./$(MLX_PATH)" ]; then \
		@echo "Downloading minilibx"; \
		@$(MAKE) getmlxlib; \
	fi
	@echo "Building minilibx"
	@$(MAKE) -C ${MLX_PATH}
	@$(MAKE) ${NAME}

${NAME}	: ${OBJS}
	@$(MAKE) libft
	@printf "Making miniRT... "
	@${CC} ${CFLAGS} ${OBJS} ${LINKS} -o ${NAME}
	@echo "done"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	${CC} ${CFLAGS} ${INC} -c $< -o $@

all		: mlx

# ifneq wasn't working because of missing quotes
# ifneq ("${RE_LIBFT}" yes
# ifneq (${RE_LIBFT} no
# also, make -C ${LIB} calls the all rule that cleans
libft	:
ifneq ("${RE_LIBFT}", "./libft/libft.a")
	@$(MAKE) libft.a --no-print-directory -C libft
endif

clean	:
	@${MAKE} clean -C libft
ifneq ("$(wildcard ${NAME} ${MLX_PATH})", "")
	@printf "Cleaning up minilibx... "
	@${MAKE} clean -C ${MLX_PATH}
	@echo "done"
endif
ifneq ("$(wildcard ${OBJS_DIR} $(DSYM))", "")
	@printf "Cleaning up miniRT objects..."
	@${RM} ${OBJS_DIR} $(DSYM)
	@echo "done"
endif

getmlxlib:
ifeq (${UNAME_S}, Linux)
	@if [ ! -d ${MLX_PATH} ]; then \
			@echo "Downloading miniLibX for Linux..."; \
			wget https://cdn.intra.42.fr/document/document/12154/${MLX_TAR}; \
			mkdir ${MLX_PATH}; \
			tar -xzf minilibx-linux.tgz --strip-components=1 -C ${MLX_PATH}; \
			rm minilibx-linux.tgz; \
	fi
else ifeq (${UNAME_S}, Darwin)
	@if [ ! -d ${MLX_PATH} ]; then \
			@echo "Downloading miniLibX for Mac..."; \
			wget https://cdn.intra.42.fr/document/document/12155/${MLX_TAR}; \
			mkdir ${MLX_PATH}; \
			tar -xzf minilibx_opengl.tgz --strip-components=1 -C ${MLX_PATH}; \
			rm minilibx_opengl.tgz; \
	fi
endif

fclean	: clean
	@$(MAKE) fclean -C libft
ifneq ("$(wildcard ${NAME})", "")
	@printf "Cleaning up miniRT executable..."
	@${RM} ${NAME}
	@echo "done"
endif

re		: fclean all

.PHONY	: all clean fclean re libft getmlxlib mlx
