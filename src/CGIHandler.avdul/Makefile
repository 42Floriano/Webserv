vpath	%.cpp	CGIHandler

CPPFLAGS	+= -I.
NAME	:= CGIHandler
SOURCES	:= 				\
	CGIHandler.cpp		\

MK		:= ../mk/
include $(MK)class.mk
.DEFAULT_GOAL = CGIHandler.a

test: CGIHandler.a

CPPFLAGS	+= -I../Address
CPPFLAGS	+= -I../Socket/includes
CPPFLAGS	+= -I../HttpMessage
CPPFLAGS	+= -I../Request
CPPFLAGS	+= -I../Response
CPPFLAGS	+= -I../Response
CPPFLAGS	+= -I../PollSock
CPPFLAGS	+= -I../Console
CPPFLAGS 	+= -I../ServerConfig
CPPFLAGS	+= -I../
