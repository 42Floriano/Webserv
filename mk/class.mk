# Include this in the Makefile of each class
# 
# It configures the compilation of
# the `.o` files from `.cpp` files
#
# The default target is $(NAME).a
#
# The var NAME must be equal to the name of the class.

include $(MK)ar.mk
include $(MK)cpp.mk

# `make` == `make all`
.DEFAULT_GOAL		?= all

# target files MUST be added to the SOURCES var
SOURCES				+= $(CPPSOURCES:%=%.cpp)
OBJECTS				:= $(SOURCES:%.cpp=%.o)
ARCHIVE				:= $(NAME).a

.PHONY: all
all: $(ARCHIVE)

.PHONY: clean
clean:
	$(RM) *.o

.PHONY: fclean
fclean: clean
	$(RM) $(ARCHIVE)

.PHONY: re
re: fclean all

$(ARCHIVE): $(ARCHIVE)($(OBJECTS))
