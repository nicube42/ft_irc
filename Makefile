NAME		=	ft_irc

SRC			=	srcs/main.cpp \
				srcs/server/Server.cpp \
				srcs/users/Users.cpp \
				srcs/channels/Channels.cpp \
				srcs/commands/parseCommands.cpp \
				srcs/commands/join.cpp \
				srcs/commands/nick.cpp \
				srcs/commands/oper.cpp \
				srcs/commands/kick.cpp \

HEADERS		=	includes/*.hpp

OBJ			=	$(SRC:srcs/%.cpp=objs/%.o)

CC			=	g++
RM			=	rm -f

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address

OBJDIR		=	objs/

all:			dirs $(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CPPFLAGS) -I includes $(OBJ) -o $(NAME)

objs/%.o:		srcs/%.cpp $(HEADERS)
				$(CC) $(CPPFLAGS) -I includes -c $< -o $@

dirs:
				mkdir -p $(OBJDIR)
				mkdir -p objs/server/
				mkdir -p objs/users/
				mkdir -p objs/channels/
				mkdir -p objs/commands/

clean:
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re dirs
