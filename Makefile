CC	= clang++ -std=c++98 -Wall -Werror -Wextra
RM	= rm -rf

NAME	= containers
NAME_FT 	= ./$(NAME)_FT
NAME_STL	= ./$(NAME)_STL

INCS_DIR	= ./inc/
MAIN_INC	= -I$(INCS_DIR)
INCS		= $(addprefix $(INCS_DIR), \
				utils.hpp \
				map.hpp \
				vector.hpp \
			)

MAIN_SRC	= main.cpp
SRCS_DIR	= ./srcs/
SRCS		= $(addprefix $(SRCS_DIR), \
				ft_print.cpp \
				v_access.cpp \
				v_compare.cpp \
				v_const.cpp \
				v_erase.cpp \
				v_insert.cpp \
				v_it.cpp \
				v_swap.cpp \
				m_bound.cpp \
				m_const.cpp \
				m_access.cpp \
				m_erase.cpp \
				m_find.cpp \
				m_it.cpp \
				m_insert.cpp \
				m_swap.cpp \
				m_compare.cpp \
			)

MAIN		= $(SRCS_DIR)$(MAIN_SRC)

OBJSFT_DIR	= ./objs/objsFT/
OBJSSTL_DIR	= ./objs/objsSTL/
OBJS		= $(SRCS:$(SRCS_DIR)%.cpp=$(OBJSFT_DIR)%.o)
OBJSSTL		= $(SRCS:$(SRCS_DIR)%.cpp=$(OBJSSTL_DIR)%.o)

_CLEAR			= \033[0K\r\c
_OK				= [\033[32mOK\033[0m]
_KO				= [\033[31mOK\033[0m]

$(OBJSFT_DIR)%.o : $(SRCS_DIR)%.cpp
					@mkdir -p $(OBJSFT_DIR) 
					@echo "[..] $(NAME_FT) compiling $*.cpp\r\c"
					@$(CC) $(MAIN_INC) -c $< -o $@
					@echo "$(_CLEAR)"

$(OBJSSTL_DIR)%.o : $(SRCS_DIR)%.cpp
					@mkdir -p $(OBJSSTL_DIR) 
					@echo "[..] $(NAME_STL) compiling $*.cpp\r\c"
					@$(CC) -DUSESTL $(MAIN_INC) -c $< -o $@
					@echo "$(_CLEAR)"

all				: $(NAME_FT) $(NAME_STL)

$(NAME_FT)		: $(OBJS) $(INCS) $(MAIN)
					@$(CC) $(OBJS) $(MAIN_INC) $(MAIN) -o $(NAME_FT)
					@echo "$(_OK) $(NAME)FT compiled"

$(NAME_STL)		: $(OBJSSTL) $(INCS) $(MAIN)
					@$(CC) -DUSESTL $(OBJSSTL) $(MAIN_INC) $(MAIN) -o $(NAME_STL)
					@echo "$(_OK) $(NAME)STL compiled"

clean			:
					@$(RM) "./objs"

fclean			:	clean
					@$(RM) $(NAME_FT) $(NAME_STL)

re				: fclean all

.PHONY			: all clean fclean re
