include				$(MK)cpp.mk
include				$(MK)cleaners.mk

CLASS_FOLDERS		= $(CLASS_NAMES:%=%/)
CLASS_FILES			= $(join $(CLASS_FOLDERS), $(CLASS_NAMES:%=%.a))

CPPFLAGS			+= $(CLASS_FOLDERS:%=-I%)

.DEFAULT_GOAL		:= all
$(NAME)				: $(CLASS_FILES)

$(CLASS_FILES):%	:
	$(MAKE) -C $(dir $@)

.PHONY				: $(CLASS_FOLDERS)
$(CLASS_FOLDERS)	:;$(MAKE) -C $@

.PHONY				: all
all					: $(CLASS_FOLDERS) $(NAME)

.PHONY				: re
re					: fclean all

.PHONY				: clean
clean				: clean_classes

.PHONY				: fclean
fclean				: fclean_classes remove_name
