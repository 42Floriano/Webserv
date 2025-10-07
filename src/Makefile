include include.mk
MK	:= ../mk/

CPPFLAGS	:= $(CPPFLAGS:-I../%=-I%)
NAME		:= webserv

CLASS_NAMES	:=		\
	WebservDos			\
	HttpClient		\
	ResponseHandler	\
	CGIHandler		\
	CGIReader		\
	Client			\
	Request			\
	Response		\
	HttpMessage		\
	HttpHeaders		\
	PollSock		\
	PollSet			\
	Socket			\
	PollCallback	\
	Console			\
	Address			\
	Config			\
	QueryString		\
	Url				\
	Process			\
	PollEvents		\

include $(MK)pretty.mk
include $(MK)cpp-program.mk

.PHONY: fclean_local
fclean_local:
	$(RM) log;

fclean: fclean_local

.PHONY:docs
docs:
	doxygen
