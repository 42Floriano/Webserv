srcdir ?= .

FORMAT_STYLE		:= astyle -r
FORMAT_STYLE_OPTION += --style=allman
FORMAT_STYLE_OPTION += --indent=spaces=8
FORMAT_STYLE_OPTION += --align-pointer=name
FORMAT_STYLE_OPTION += --align-reference=type
FORMAT_STYLE_OPTION += --max-code-length=80
FORMAT_STYLE_OPTION += --pad-comma
FORMAT_STYLE_OPTION += --pad-include

FORMAT_STYLE_TARGETS		+= "$(srcdir)/*.cpp"
FORMAT_STYLE_TARGETS		+= "$(srcdir)/*.hpp"
FORMAT_STYLE_TARGETS		+= "$(srcdir)/*.tpp"

.PHONY: pretty
pretty:
	$(FORMAT_STYLE) $(FORMAT_STYLE_OPTION) $(FORMAT_STYLE_TARGETS)
	for file in $$(find -name '*.orig'); do rm $$file; done
