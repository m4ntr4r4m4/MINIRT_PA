#GNU Make 3.81

################################################################################

SHELL :=			bash
CC :=				gcc
CFLAGS :=			-g	-O2  -Wall -Wextra -Werror -fsanitize=address,undefined

# Platform-specific MiniLibX flags.
# macOS uses the system MiniLibX (OpenGL/AppKit frameworks); Linux uses the
# bundled minilibx-linux (X11). On Linux, if libX11/libXext live outside the
# default linker path (e.g. a conda env), point the linker at them with:
#   make LIBRARY_PATH=/path/to/lib
UNAME :=			$(shell uname)
INC :=
ifeq ($(UNAME), Darwin)
LDFLAGS :=			-lmlx -framework OpenGL -framework AppKit
else
MLX_DIR :=			./minilibx-linux
INC :=				-I$(MLX_DIR)
CFLAGS +=			$(INC)
LDFLAGS :=			-L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

################################################################################

NAME :=				miniRT

DEP_PATH :=			./DEP
DEP_PATH_MAKE :=	DEP/
OBJ_PATH :=			./OBJ

EXCLUDE_DIRS :=		$(DEP_PATH) $(OBJ_PATH) ./.git ./minilibx-linux
EXCLUDE_FILES :=	./tags

LIBFT_PATH :=		..
LIBFT :=			libft.a

HDR :=				$(shell find . \
						$(foreach PATH, $(EXCLUDE_DIRS), -path "$(PATH)" -prune -o)\
						$(foreach FILE, $(EXCLUDE_FILES), -path "$(FILE)" -prune -o)\
						-type f -and -name "*.h" -print)
HDR :=				$(HDR:./%=%)
SRC :=				$(shell find . \
						$(foreach PATH, $(EXCLUDE_DIRS), -path "$(PATH)" -prune -o)\
						$(foreach FILE, $(EXCLUDE_FILES), -path "$(FILE)" -prune -o)\
						-type f -and -name "*.c" -print)
SRC :=				$(SRC:./%=%)
OBJ :=				$(addprefix $(OBJ_PATH)/,$(SRC:%.c=%.o))
DEP :=				$(addprefix $(DEP_PATH)/,$(SRC:.c=.d))
SUB_DIR :=			$(sort $(dir $(SRC)))
SUB_DIR :=			$(SUB_DIR:.%=%)
SUB_DIR :=			$(SUB_DIR:/%=%)
NEW_DIRS :=			$(addprefix $(OBJ_PATH)/,$(SUB_DIR))
NEW_DIRS +=			$(addprefix $(DEP_PATH)/,$(SUB_DIR))
NEW_DIRS +=			$(OBJ_PATH) $(DEP_PATH) $(LIBFT_OBJ_PATH)

CURRENT_DIR :=		$(shell pwd)
MANPATH_APPEND :=	$(CURRENT_DIR)/manpages
CURRENT_MANPAHT :=	$(shell man --path)

-include $(DEP)

################################################################################

.DEFAULT_GOAL :=	all

$(NEW_DIRS):
	@mkdir -p $@

$(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEP_PATH)/%.d: %.c | $(NEW_DIRS)
	@rm -f $(DEP_PATH)/$@; \
		$(CC) $(INC) -M $< > $@.tmp; \
		sed 's,$(notdir $*).o[ :]*,$(OBJ_PATH)/$(subst $(DEP_PATH_MAKE),,$(basename $@).o) $@ : ,g' \
	   	< $@.tmp > $@; \
		rm -f $@.tmp

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

.PHONY: clean fclean all push update_manpath tags

all: $(NAME)

clean:
	@rm $(DEP) $(OBJ) &> /dev/null || true
	@rmdir -p $(NEW_DIRS) $(DEP_PATH) $(OBJ_PATH) &> /dev/null || true

fclean: clean
	@rm $(NAME) &> /dev/null || true

re: fclean
	@make all

pull:
	@git pull

push: fclean
	@git add .
	@git commit
	@git push

update_manpath:
	@printf "execute:\n"
	@printf "export MANPATH='$(CURRENT_MANPAHT):$(MANPATH_APPEND)'\n"
	@printf "to update the manpath and become able to read the manuals\n"

tags:
	@ctags --extras-all=* --fields-all=* --c-kinds=* --c++-kinds=* $(SRC) $(HDR)
