# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 10:07:45 by marvin            #+#    #+#              #
#    Updated: 2023/04/10 10:07:45 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variable

NAME				=	pipex
BONUS				=	.bonus

LIBS_DIR			=	libs
LIBPIPEX			=	$(LIBS_DIR)/libPipex.a
LIBPIPEX_BONUS		=	$(LIBS_DIR)/libPipexBonus.a

LIBFT_DIR			=	./libft
LIBFT				=	$(LIBFT_DIR)/libft.a

OBJ_DIR				=	build
OBJBNS_DIR			=	buildbonus
SRC_DIR				=	src
SRCBNS_DIR			= 	srcbonus

INC_DIR				=	inc
INCBONUS_DIR		=	incbonus

MAIN_DIR			=	main
UTILS_DIR			=	utils

LDLIBS				=	$(LIBPIPEX) $(LIBFT)
LDLIBS_BONUS		=	$(LIBPIPEX_BONUS) $(LIBFT)

CC					=	gcc

CFLAGS				=	-g -Wall -Werror -Wextra $(INCLUDES) $(SANITIZE)
CFLAGS_BONUS		=	-g -Wall -Werror -Wextra $(INCLUDES_BONUS) #$(SANITIZE) 
LDFLAGS				=	$(LDLIBS) $(SANITIZE)
LDFLAGS_BONUS		=	$(LDLIBS_BONUS) #$(SANITIZE)
INCLUDES			=	-I$(INC_DIR) -I$(addsuffix $(INC_DIR), $(LIBFT_DIR)/)
INCLUDES_BONUS		=	-I$(INCBONUS_DIR) -I$(addsuffix $(INC_DIR), $(LIBFT_DIR)/)

SANITIZE			=	-fsanitize=address

MKDIR				=	mkdir -p
RM					=	rm -f
AR					= 	ar

ARFLAGS 			= 	rsc

# Source

MAIN_FILES	=	pipex.c

UTILS_FILES	=	childs.c		\
				exec_comand.c	\
				free.c			\
				math_utils.c	\
				errors.c		\


SRCS_FILES	= 	$(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) \
				$(addprefix $(UTILS_DIR)/, $(UTILS_FILES)) \

SRCS 		=	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS 		=	$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DIRS		=	$(OBJ_DIR)  $(addprefix $(OBJ_DIR)/, $(MAIN_DIR) $(UTILS_DIR))

OBJ_MAIN	=	$(addprefix $(OBJ_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_FILES:.c=.o)))

# Source Bonus

MAIN_BONUS_FILES	=	pipex_bonus.c			\

UTILS_BONUS_FILES	=	childs_bonus.c			\
						errors_bonus.c			\
						exec_comand_bonus.c		\
						free_bonus.c			\
						math_utils_bonus.c		\
						here_doc_bonus.c		\

SRCSBONUS_FILES		=	$(addprefix $(MAIN_DIR)/, $(MAIN_BONUS_FILES)) \
						$(addprefix $(UTILS_DIR)/, $(UTILS_BONUS_FILES)) \

SRCSBONUS 			=	$(addprefix $(SRCBNS_DIR)/, $(SRCSBONUS_FILES))
OBJSBONUS 			=	$(addprefix $(OBJBNS_DIR)/, $(SRCSBONUS_FILES:.c=.o))
DIRSBONUS			=	$(OBJBNS_DIR) $(addprefix $(OBJBNS_DIR)/, $(UTILS_DIR) $(MAIN_DIR))

OBJBONUS_MAIN		=	$(addprefix $(OBJBNS_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_BONUS_FILES:.c=.o)))

# Rules

all:				$(NAME)

bonus:				$(BONUS)

clean:
	make fclean -C $(LIBFT_DIR)
	$(RM) -r $(LIBS_DIR)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(OBJBNS_DIR)

fclean:				clean
	$(RM) $(NAME)
	$(RM) $(BONUS)

re:					fclean all

print-%:
	@echo '$*=$($*)'


# Mandatory

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(DIRS) $(LIBS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ_MAIN) $(LIBPIPEX) $(LIBFT)
	$(CC) $? $(LDFLAGS) -o $@	

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBPIPEX): 		$(OBJS)
	$(AR) $(ARFLAGS) $@ $?

$(DIRS):
	$(MKDIR) $@

$(LIBS_DIR):
	$(MKDIR) $@


# Bonus

$(OBJBNS_DIR)/%.o:		$(SRCBNS_DIR)/%.c | $(DIRSBONUS) $(LIBS_DIR) 
	$(CC) $(CFLAGS_BONUS) -c $< -o $@				

$(LIBPIPEX_BONUS): 		$(OBJSBONUS)
	$(AR) $(ARFLAGS) $@ $?

$(DIRSBONUS):
	$(MKDIR) $@

$(BONUS):				$(OBJBONUS_MAIN) $(LIBPIPEX_BONUS) $(LIBFT) 
	$(CC) $? $(LDFLAGS_BONUS) -o $(NAME)
	@touch $@	

.SILENT:			clean fclean
.PHONY:				all clean fclean re bonus