# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 11:50:00 by raitmous          #+#    #+#              #
#    Updated: 2023/12/06 19:28:38 by raitmous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.cpp PmergeMe.cpp
OBJS	= ${SRCS:.cpp=.o}
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM		= rm -rf
NAME	= PmergeMe
CXX = c++

all	: ${NAME}

${NAME} : 
	${CXX} ${CXXFLAGS} ${SRCS} -o ${NAME}

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

a : all clean