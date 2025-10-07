include ../include.mk

NAME	:= PollSet

SOURCES += \
	CallbackDB.cpp	\
	fd.cpp \
	index.cpp \
	registerCallback.cpp \
	removeCallback.cpp \
	onPollSuccess.cpp \
	onPollError.cpp \
	onPollTimeout.cpp \
	orthodox.cpp \
	no_callback_left.cpp \
	poll.cpp \
	print_events.cpp \
	

include $(MK)class.mk

test: PollSet.a ../CallbackDB/CallbackDB.a ../PollCallback/PollCallback.a 
