NAME		=	ft_irc

SRC			=	srcs/main.cpp \
				srcs/server/Server.cpp

HEADERS		=	includes/server/Server.hpp

OBJ			=	$(SRC:srcs/%.cpp=objs/%.o)

CC			=	g++
RM			=	rm -f

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic

OBJDIR		=	objs/

all:			dirs $(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CPPFLAGS) -I includes $(OBJ) -o $(NAME)

objs/%.o:		srcs/%.cpp $(HEADERS)
				$(CC) $(CPPFLAGS) -I includes -c $< -o $@

dirs:
				mkdir -p $(OBJDIR)
				mkdir -p objs/server/

clean:
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re dirs
