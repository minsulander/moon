PACKAGE = maudio
TOLUA_FILES = $(shell find . -name '*.tolua' -o -name '*.lua')

tolua_$(PACKAGE).h tolua_$(PACKAGE).cpp: $(TOLUA_FILES)
	tolua -H tolua_$(PACKAGE).h -o tolua_$(PACKAGE).cpp $(PACKAGE).tolua
	
clean:
	rm -f tolua_$(PACKAGE).h tolua_$(PACKAGE).cpp
