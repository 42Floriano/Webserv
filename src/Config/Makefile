include ../include.mk

vpath	%.cpp ConfigParser

NAME	:= Config

PARSING := \
	utils.cpp \
	types.cpp \
	validation.cpp \
	specs.cpp \
	parseDirective.cpp \
	parseContext.cpp


SOURCES	:= 					\
	$(PARSING)				\
	Config.cpp 				\
	normalize_path.cpp		\
	ConfigItem.cpp			\
	ConfigIter.cpp			\
	FieldSpec.cpp			\
	resolve_path.cpp		\
	match_location.cpp		\

include $(MK)class.mk

test-config: Config.a ../Console/Console.a
test-config2: Config.a
