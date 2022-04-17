# Директория LibFT
FT_DIR	=	./libft/
FT_LNK	=	-L $(FT_DIR) -l ft

# Директория MLX
MLX_DIR	=	./minilibx/
MLX_LNK	=	-L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit

# Основная директория проекта
SRC_DIR	=	./src/

# Файлы и заголовки
HEAD_LH	=	$(FT_DIR)libft.h
HEAD_LA	=	$(FT_DIR)libft.a
HEAD_MH	=	$(MLX_DIR)mlx.h
HEAD_MA	=	$(MLX_DIR)libmlx.a
HEAD_PH	=	$(SRC_DIR)cub3d.h
SRCS	=	parse.c parse_line.c parse_utils.c \
			keydown.c draw.c draw_column.c \
			main.c
SRCSB	=	parse.c parse_line.c parse_utils.c \
			keydown_bonus.c draw.c draw_column.c \
			main.c

# Параметры сборки и удаления
NAME	=	cub3D
NAMEB	=	cub3D_bonus
OBJS	=	$(addprefix $(SRC_DIR),$(SRCS:.c=.o))
OBJSB	=	$(addprefix $(SRC_DIR),$(SRCSB:.c=.o))
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

# =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*= #

all:		makelib makemlx makeprog

bonus:		makelib makemlx makebonus

makelib:	$(HEAD_LH)
			make -C $(FT_DIR)

makemlx:	$(HEAD_MH)
			make -C $(MLX_DIR)

makeprog:	$(HEAD_LA) $(HEAD_MA) $(HEAD_PH)
			make $(NAME)

makebonus:	$(HEAD_LA) $(HEAD_MA) $(HEAD_PH)
			make $(NAMEB)

$(SRC_DIR)%.o:$(SRC_DIR)%.c $(HEAD_PH)
			$(CC) $(CFLAGS) -I $(FT_DIR) -I $(MLX_DIR) -I $(SRC_DIR) -o $@ -c $< -Ofast

$(NAME):	$(OBJS) $(HEAD_LA) $(HEAD_MA)
			$(CC) $(CFLAGS) $(OBJS) $(FT_LNK) -Ofast $(MLX_LNK) -lm -o $(NAME)

$(NAMEB):	$(OBJSB) $(HEAD_LA) $(HEAD_MA)
			$(CC) $(CFLAGS) $(OBJSB) $(FT_LNK) -Ofast $(MLX_LNK) -lm -o $(NAMEB)

clean:
			${RM} $(OBJS)
			${RM} ./src/keydown_bonus.o
			make -C $(FT_DIR) clean
			make -C $(MLX_DIR) clean

fclean:
			${RM} $(OBJS)
			${RM} ./src/keydown_bonus.o
			make -C $(FT_DIR) fclean
			make -C $(MLX_DIR) clean
			${RM} $(NAME)
			${RM} $(NAMEB)

re:			fclean all

.PHONY:		all clean fclean re bonus
