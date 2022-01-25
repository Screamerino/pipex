LIB_DIR				=	libft/
LIB					=	libft.a
LIBFT				=	${addprefix ${LIB_DIR}, ${LIB}}
NAME        		=   pipex
SRC_FILES   		=   pipex.c				parser.c
SRC_FILES_BONUS		=	pipex_bonus.c		parser_bonus.c	run_child_bonus.c\
						pipex_utils.c
SRC_DIR				=	src/
INC_FILES			=	pipex.h
INC_FILES_BONUS		=	pipex_bonus.h
INC_DIR				=	inc/
CC          		=   gcc
CFLAGS      		=   -Wall -Wextra -Werror -I ${LIB_DIR} -I ${INC_DIR}
SRC_LIBFT_FILES		=	ft_isalpha.c		ft_isdigit.c	ft_isalnum.c\
						ft_atoi.c			ft_bzero.c		ft_calloc.c\
						ft_isascii.c		ft_isprint.c	ft_memchr.c\
						ft_memcmp.c			ft_memmove.c	ft_memset.c\
						ft_strchr.c			ft_strdup.c		ft_strlcat.c\
						ft_strlcpy.c		ft_strlen.c		ft_strncmp.c\
						ft_strnstr.c		ft_strrchr.c	ft_tolower.c\
						ft_toupper.c		ft_memcpy.c		ft_strtrim.c\
						ft_strjoin.c		ft_substr.c		ft_split.c\
						ft_itoa.c			ft_strmapi.c	ft_striteri.c\
						ft_putchar_fd.c		ft_putstr_fd.c	ft_putendl_fd.c\
						ft_putnbr_fd.c		ft_freearr.c	get_next_line.c\
						get_next_line_utils.c
INC_LIBFT_FILES		=	libft.h				get_next_line.h
INC_LIBFT			=	${addprefix ${LIB_DIR}, ${INC_LIBFT_FILES}}
SRC_LIBFT			=	${addprefix ${LIB_DIR}, ${SRC_LIBFT_FILES}}
SRC					=	${addprefix ${SRC_DIR}, ${SRC_FILES}}
SRC_BONUS			=	${addprefix ${SRC_DIR}, ${SRC_FILES_BONUS}}
INC					=	${addprefix ${INC_DIR}, ${INC_FILES}}
INC_BONUS			=	${addprefix ${INC_DIR}, ${INC_FILES_BONUS}}
OBJ					=	${SRC:%.c=%.o}
OBJ_BONUS			=	${SRC_BONUS:%.c=%.o}
.PHONY	:   all re clean fclean bonus libft

all :   ${NAME}

${LIBFT}	:	${SRC_LIBFT} ${INC_LIBFT}
	cd ${LIB_DIR} && ${MAKE}

%.o :   %.c ${LIBFT}
	${CC} ${CFLAGS} -c $< -o $@

${NAME} :  ${OBJ} ${INC}
	${CC} ${CFLAGS} -L ${LIB_DIR} -lft -o ${NAME} ${OBJ}

bonus	:	${LIBFT}
	@make OBJ="${OBJ_BONUS}" INC=${INC_BONUS} all

clean   :
	rm -rf ${OBJ} ${OBJ_BONUS}

fclean  :   clean
	rm -rf ${NAME}
	@cd ${LIB_DIR} && ${MAKE} fclean

re		:	fclean all
