include	../include.mk

vpath	%.cpp parsing:parsing-utils:utils

NAME	:= HttpHeaders
SOURCES	:= \
	constructors.cpp \
	parse.cpp print.cpp \
	seal.cpp \
	unseal.cpp \
	is_sealed.cpp \
	get.cpp \
	mutable_get.cpp \
	insert.cpp \
	parse_value.cpp \
	parse_key.cpp \
	content_length.cpp \
	insert.cpp \
	insert_buffered_key_value.cpp \
	normalize_key.cpp \
	trim_string.cpp \
	begin.cpp \
	end.cpp

include	$(MK)class.mk

../Console/Console.a:
	$(MAKE) -C ../Console

test: HttpHeaders.a ../Console/Console.a
