# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 21:01:22 by sdel-gra          #+#    #+#              #
#    Updated: 2024/01/17 14:11:54 by sdel-gra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# \ = is used to Splitting Long Lines 3.1.1

# ;\ = indicates a multiline command and keeps the instance of the terminal for 
# the next command

# % = the same as * 'wildcard'
# $@ = means what is before the : in the target
# $^ = means what is after the : in the target
# $< = the first prerequisite (usually a source file)
# -I.  = adds include directory of header files.
# -f = force the removal even if the files have been already deleted. 

# -c = Compile or assemble the source files, but do not link.
# The linking stage simply is not done. The ultimate output is
# in the form of an object file for each source file.
# By default, the object file name for a source file is made by replacing
# the suffix .c, .i, .s, etc., with .o. Unrecognized input files,
# not requiring compilation or assembly, are ignored.

# .PHONY : clean
# phony prevent make from getting confused by an actual file called `clean' 
# and causes it to continue in spite of errors from rm
# A rule such as this should not be placed at the beginning of the makefile, because we do not want it to run by default!
# Thus, in the example makefile, we want the rule for edit, which recompiles the editor, to remain the default goal.
# Since clean is not a dependency of edit, this rule will not run at all if we give the command `make' with no arguments. 
# In order to make the rule run, we have to type `make clean'


NAME = philo_bonus
INCLUDE = include

#			FLAGS			#

CFLAGS = -Wall -Werror -Wextra -g -I include

#			DEFINITIONS		#

CC	= cc -g 
INC	= -I.
AR	= ar
RM	= rm -rf

#			PATH & SOURCES	#

SRC		=	main_bonus\
			handler_bonus\
			time_bonus\
			utils_bonus\
			free_bonus\
			setup_bonus

SRC_PATH = src/
SRCFC	= $(addprefix $(SRC_PATH),$(addsuffix .c, $(SRC)))
SRCO	= $(SRCFC:.c=.o)
OBJS	= $(SRCFC:.c=.o)

#			COLORS			#

DEF_COLOR = \033[0;39m
G = \033[0;92m
R = \033[0;91m
C = \033[0;96m

#			RULES			#

%.o : $(SRCS_DIR)%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I includes

all: 	${NAME}
	

$(NAME):	$(OBJS)
		@echo "$(C)compiling $(NAME) $(DEF_COLOR)"
		@$(CC) $(CFLAG) $(OBJS) -o $(NAME) -lpthread
		@echo "$(G)$(NAME) compiled$(DEF_COLOR)"

clean: 
	@${RM} ${OBJS}

fclean:	clean
		$(RM) $(NAME)
		@echo "$(G)$(NAME) full cleaned!$(DEF_COLOR)"

re: fclean all