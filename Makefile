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
NAME_BONUS			=	pipex

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

LDLIBS				=	$(LIBPUSHSWAP) $(LIBFT)
LDLIBS_BONUS		=	$(LIBCHECKER) $(LIBFT)

CC					=	gcc

CFLAGS				=	-g $(INCLUDES) #$(SANITIZE)
CFLAGS_BONUS		=	-g $(INCLUDES_BONUS) #$(SANITIZE) 
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

MAIN_FILES	=

SRCS_FILES	= 	

SRCS 		=	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS 		=	$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DIRS		=	$(OBJ_DIR)  $(addprefix $(OBJ_DIR)/, $() $() $() $())

OBJ_MAIN	=	$(addprefix $(OBJ_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_FILES:.c=.o)))

# Source Bonus


SRCSBONUS_FILES		=	

SRCSBONUS 			=	$(addprefix $(SRCBNS_DIR)/, $(SRCSBONUS_FILES))
OBJSBONUS 			=	$(addprefix $(OBJBNS_DIR)/, $(SRCSBONUS_FILES:.c=.o))
DIRSBONUS			=	$(OBJBNS_DIR) $(addprefix $(OBJBNS_DIR)/, $(OPRTS_DIR) $(UTILS_DIR) $(MAIN_DIR))

OBJBONUS_MAIN		=	$(addprefix $(OBJBNS_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_BONUS_FILES:.c=.o)))

# Rules

all:				$(NAME)

bonus:				$(NAME_BONUS)

clean:
	make fclean -C $(LIBFT_DIR)
	$(RM) -r $(LIBS_DIR)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(OBJBNS_DIR)

fclean:				clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re:					fclean all


# Mandatory

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(DIRS) $(LIBS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(LIBPIPEX) $(LIBFT) $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) $(LDFLAGS) -o $@	

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBPUSHSWAP): 	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(DIRS):
	$(MKDIR) $@

$(LIBS_DIR):
	$(MKDIR) $@


# Bonus

$(OBJBNS_DIR)/%.o:		$(SRCBNS_DIR)/%.c | $(DIRSBONUS) $(LIBS_DIR) 
	$(CC) $(CFLAGS_BONUS) -c $< -o $@

$(NAME_BONUS):			$(LIBPIPEX_BONUS) $(LIBFT) $(OBJBONUS_MAIN)
	@rm -rf $(NAME)
	$(CC) $(OBJBONUS_MAIN) $(LDFLAGS_BONUS) -o $@	

$(LIBCHECKER): 	$(OBJSBONUS)
	$(AR) $(ARFLAGS) $@ $(OBJSBONUS)

$(DIRSBONUS):
	$(MKDIR) $@

.SILENT:			clean fclean
.PHONY:				all clean fclean re bonus