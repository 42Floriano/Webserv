include ../include.mk

NAME	:= HttpMessage

SOURCES	:= 					\
	constructors.cpp		\
	getchunk.cpp			\
	decode.cpp				\
	decode_once.cpp			\
	encode.cpp				\
	encode_once.cpp			\
	getline.cpp				\
	decode_first_line.cpp	\
	decode_headers.cpp		\
	decode_trailers.cpp		\
	decode_chunk_size.cpp	\

include $(MK)class.mk

test-getline: HttpMessage.a ../Console/Console.a
