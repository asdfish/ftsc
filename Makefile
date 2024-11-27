CXX ?= c++

CXXFLAGS ?= -Og -g -march=native -pipe
CFLAGS ?= ${CXXFLAGS}
override CXXFLAGS += -std=c++17
override CXXFLAGS += -Wall -Wextra -Wpedantic
override CXXFLAGS += -Iinclude
override CXXFLAGS += -Ideps/carp -Ideps/tree-sitter/lib/include -Ideps/tree-sitter-typescript/bindings/c

LDFLAGS ?=
override LDFLAGS += ${CXXFLAGS}
override LDFLAGS += -Ldeps/tree-sitter -l:libtree-sitter.a
override LDFLAGS += -Ldeps/tree-sitter-typescript/typescript -l:libtree-sitter-typescript.a

# set to empty value to disable
FTSC_PROCESS_HEADER_FILES ?= yes
PROCESSED_HEADER_FILES := $(if ${FTSC_PROCESS_HEADER_FILES},$\
														$(subst .hpp,$\
															$(if $(findstring clang,${CC}),$\
																.hpp.pch,$\
																.hpp.gch),$\
															$(shell find include -name '*.hpp' -type f)))

OBJECT_FILES := $(patsubst src/%.cpp,$\
									build/%.o,$\
									$(shell find src -name '*.cpp' -type f))

FTSC_REQUIREMENTS := deps/tree-sitter/libtree-sitter.a $\
										 deps/tree-sitter-typescript/typescript/libtree-sitter-typescript.a $\
										 ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}

define COMPILE
${CXX} -c $(1) ${CXXFLAGS} -o $(2)

endef
define REMOVE
$(if $(wildcard $(1)),$\
	rm $(1))

endef
define REMOVE_LIBRARY
$(if $(wildcard $(1)),$\
	$(MAKE) -C $(dir $(1)) clean)

endef
define REMOVE_LIST
$(foreach ITEM,$\
	$(1),$\
	$(if $(findstring .a,${ITEM}),$\
		$(call REMOVE_LIBRARY,${ITEM}),$\
		$(call REMOVE,${ITEM})))
endef

all: ftsc

ftsc: ${FTSC_REQUIREMENTS}
	${CXX} ${OBJECT_FILES} ${LDFLAGS} -o $@

build/%.o: src/%.cpp
	$(call COMPILE,$<,$@)
%.gch: %
	$(call COMPILE,$<,$@)
%.pch: %
	$(call COMPILE,$<,$@)
	
%.a:
	CFLAGS='${CFLAGS}' $(MAKE) -C $(dir $@)
deps/tree-sitter/libtree-sitter.a:
	CFLAGS='${CFLAGS}' $(MAKE) -C $(dir $@) libtree-sitter.a
deps/tree-sitter-typescript/typescript/libtree-sitter-typescript.a:
	CFLAGS='${CFLAGS}' $(MAKE) -C $(dir $@) libtree-sitter-typescript.a

clean:
	$(call REMOVE_LIST,${FTSC_REQUIREMENTS})
	$(call REMOVE,ftsc)

.PHONY: all clean install uninstall
