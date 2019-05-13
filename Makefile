##
## EPITECH PROJECT, 2018
## indie studio
## File description:
## Makefile
##

CC		=	g++ -g3

RM		=	rm -f

NAME		=	bomberman

SRCS		=	srcs/main.cpp		\
			srcs/core.cpp		\
			srcs/CEventReceiver.cpp	\
			srcs/CMenu.cpp		\
			srcs/CCharacter.cpp	\
			srcs/CTimer.cpp		\
			srcs/CBox.cpp		\
			srcs/CMap.cpp       \
			srcs/CGame.cpp	\
			srcs/CSound.cpp

OBJS		=	$(SRCS:.cpp=.o)

LDFLAGS		=       -W -Wextra -Werror -lIrrlicht -lGL -lX11 -lXxf86vm -lIrrKlang

CXXFLAGS	+=      -I include/ 


all:            $(NAME)

$(NAME):        $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:         clean
		$(RM) $(NAME)

re:             fclean all

.PHONY:         all clean fclean re
