# **************************************************************************** #
#                                                                              #
#                                                                              #
#    cleaners.mk                                             4 2               #
#                                                         (@)-=-(@)            #
#    By: fwhite42 <FUCK THE NORM>                          (  o  )             #
#                                                        _/'-----'\_           #
#    Created: 2024/07/27 08:38:37 by fwhite42          \\ \\     // //         #
#    Updated: 2025/04/23 01:31:11 by fwhite42           _)/_\---/_\(_          #
#                                                                              #
# **************************************************************************** #

.PHONY	: remove_objects
remove_objects:
	$(RM) $(OBJECTS)

.PHONY	: remove_classes
remove_classes:
	$(RM) $(NAME).a

.PHONY	: remove_d_files
remove_d_files:
	$(RM) $(OBJECTS:%.o=%.d)
	$(RM) *.d

.PHONY	: remove_d_files

.PHONY: remove_name
remove_name:
	$(RM) $(NAME)

.PHONY: clean_classes
clean_classes:
	for class in $(CLASS_NAMES); do $(MAKE) -C $$class clean; done;

.PHONY: fclean_classes
fclean_classes:
	for class in $(CLASS_NAMES); do $(MAKE) -C $$class fclean; done;
