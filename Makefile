# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Makefile                                           :+:      :+:    :+:    #
#    Author:   Peru Riezu <riezumunozperu@gmail.com>                           #
#    github:   https://github.com/priezu-m                                     #
#    Licence:  GPLv3                                                           #
#    Created:  2023/09/27 18:57:07                                             #
#    Updated: 2024/01/29 15:29:09 by priezu-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#GNU Make 3.81

################################################################################

SHELL :=			bash
CC :=				gcc
CFLAGS :=			-g	-O2  -Wall -Wextra -Werror
LDFLAGS :=			-lmlx -framework OpenGL -framework Appkit

################################################################################

NAME :=				miniRT

DEP_PATH :=			./DEP
DEP_PATH_MAKE :=	DEP/
OBJ_PATH :=			./OBJ

EXCLUDE_DIRS :=		$(DEP_PATH) $(OBJ_PATH) ./.git
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
		$(CC) -M $< > $@.tmp; \
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
