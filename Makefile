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

GREEN 				= 	\033[0;32m
LIGHT_GRAY 			= 	\033[90m
BLUE 				= 	\033[0;34m
NC 					= 	\033[0m
YELLOW				=	\033[93m

SMILEY				=	\xF0\x9F\x98\x81
CHECK				=	\xE2\x9C\x85

MANDATORY_PART 		=	"\n ******************************************************\n				\
						*                                                    *\n					\
						*                                                    *\n					\
						*                   $(YELLOW)MANDATORY PART$(NC)                   *\n		\
						*                                                    *\n					\
						*                                                    *\n					\
						******************************************************\n\n"
BONUS_PART 			=	"\n ******************************************************\n				\
						*                                                    *\n					\
						*                                                    *\n					\
						*                     $(YELLOW)BONUS PART$(NC)                     *\n		\
						*                                                    *\n					\
						*                                                    *\n					\
						******************************************************\n\n"					\

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

CFLAGS				=	-g -Wall -Werror -Wextra $(INCLUDES) #$(SANITIZE)
CFLAGS_BONUS		=	-g -Wall -Werror -Wextra $(INCLUDES_BONUS) #$(SANITIZE) 
LDFLAGS				=	$(LDLIBS) #$(SANITIZE)
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

UTILS_FILES	=	free.c			\
				childs.c		\
				errors.c		\
				math_utils.c	\
				exec_comand.c	\


SRCS_FILES	= 	$(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) \
				$(addprefix $(UTILS_DIR)/, $(UTILS_FILES)) \

SRCS 		=	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS 		=	$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DIRS		=	$(OBJ_DIR)  $(addprefix $(OBJ_DIR)/, $(MAIN_DIR) $(UTILS_DIR))

OBJ_MAIN	=	$(addprefix $(OBJ_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_FILES:.c=.o)))

# Source Bonus

MAIN_BONUS_FILES	=	pipex_bonus.c			\

UTILS_BONUS_FILES	=	free_bonus.c			\
						childs_bonus.c			\
						errors_bonus.c			\
						here_doc_bonus.c		\
						math_utils_bonus.c		\
						exec_comand_bonus.c		\

SRCSBONUS_FILES		=	$(addprefix $(MAIN_DIR)/, $(MAIN_BONUS_FILES)) \
						$(addprefix $(UTILS_DIR)/, $(UTILS_BONUS_FILES)) \

SRCSBONUS 			=	$(addprefix $(SRCBNS_DIR)/, $(SRCSBONUS_FILES))
OBJSBONUS 			=	$(addprefix $(OBJBNS_DIR)/, $(SRCSBONUS_FILES:.c=.o))
DIRSBONUS			=	$(OBJBNS_DIR) $(addprefix $(OBJBNS_DIR)/, $(UTILS_DIR) $(MAIN_DIR))

OBJBONUS_MAIN		=	$(addprefix $(OBJBNS_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_BONUS_FILES:.c=.o)))

# Rules

all:			 	$(NAME)

bonus:				$(BONUS)

clean:
	make -s clean -C $(LIBFT_DIR)
	$(RM) -r $(LIBS_DIR)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(OBJBNS_DIR)
	@echo "---- $(YELLOW)Object files deleted. $(CHECK)$(NC) ----"

fclean:				clean
	make -s fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS)
	@echo "---- $(YELLOW)Binary files deleted. $(CHECK)$(NC) ----"

re:					fclean all


# Mandatory

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(DIRS) $(LIBS_DIR)
	@printf "\r\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$<$(NC)"
	@sleep 0.5
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ_MAIN) $(LDFLAGS) 
	@$(CC) $(OBJ_MAIN) $(LDFLAGS) -o $@
	@sleep 1
	@echo "\n$(GREEN)The program is ready.$(SMILEY) $(CHECK)$(NC)"	

$(LIBFT):
	@(cd $(LIBFT_DIR) && make -s all)

$(LIBPIPEX): 		$(OBJS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRS):
	@echo $(MANDATORY_PART)
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libPipex$(NC)"
	@$(MKDIR) $(DIRS)

$(LIBS_DIR):
	@$(MKDIR) $@


# Bonus

$(OBJBNS_DIR)/%.o:		$(SRCBNS_DIR)/%.c | $(DIRSBONUS) $(LIBS_DIR)
	@printf "\r\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$<$(NC)"
	@sleep 0.5
	@$(CC) $(CFLAGS_BONUS) -c $< -o $@				

$(LIBPIPEX_BONUS): 		$(OBJSBONUS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRSBONUS):
	@echo $(BONUS_PART)
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libPipexBonus$(NC)"
	@$(MKDIR) $(DIRSBONUS)

$(BONUS):				$(LDFLAGS_BONUS) $(OBJBONUS_MAIN)
	@$(CC) $(OBJBONUS_MAIN) $(LDFLAGS_BONUS) -o $@
	@touch $@
	@echo "\n$(GREEN)The program is ready.$(SMILEY) $(CHECK)$(NC)"		

.SILENT:			clean fclean
.PHONY:				all clean fclean re bonus 