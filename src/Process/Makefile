vpath %.cpp private
vpath %.cpp public

include ../include.mk

NAME	:= Process
SOURCES	:= \
	spawn.cpp \
	kill.cpp \
	is_done.cpp \
	_check_if_done.cpp \
	constructors.cpp \
	operators.cpp \
	_configure_env.cpp \
	stdin.cpp \
	stdout.cpp \
	stderr.cpp \
	_parse_command.cpp \
	_configure_stdio.cpp \
	_execute.cpp \
	_fork.cpp \
	_resolve_command.cpp \
	_create_channels.cpp \

include $(MK)class.mk

test: Process.a  ../PollCallback/PollCallback.a ../PollSet/PollSet.a ../CallbackDB/CallbackDB.a  ../Console/Console.a
