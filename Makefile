CXX ?= c++

CFLAGS ?= -O3 -march=native -pipe
CXXFLAGS ?= ${CFLAGS}
override CXXFLAGS += -std=c++17
override CXXFLAGS += -Wall -Wextra -Wpedantic
override CXXFLAGS += -Iinclude
override CXXFLAGS += -Ideps/carp/include -Ideps/tree-sitter/lib/include -Ideps/tree-sitter-typescript/bindings/c

LDFLAGS ?=
override LDFLAGS += ${CXXFLAGS}
override LDFLAGS += -Ldeps/carp -lcarp
override LDFLAGS += -Ldeps/tree-sitter -ltree-sitter
override LDFLAGS += -Ldeps/tree-sitter-typescript/typescript -ltree-sitter-typescript

# set to empty value to disable
FTSC_PROCESS_HEADER_FILES ?= yes
PROCESSED_HEADER_FILES := $(if ${FTSC_PROCESS_HEADER_FILES},$\
														$(subst .hpp,$\
															$(if $(findstring clang,${CXX}),$\
																.hpp.pch,$\
																.hpp.gch),$\
															$(shell find include -name '*.hpp' -type f)))

OBJECT_FILES := $(patsubst src/%.cpp,$\
									build/%.o,$\
									$(shell find src -name '*.cpp' -type f))

FTSC_REQUIREMENTS := deps/carp/libcarp.a $\
										 deps/tree-sitter/libtree-sitter.a $\
										 deps/tree-sitter-typescript/typescript/libtree-sitter-typescript.a $\
										 ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}

define COMPILE
$(CXX) -c $(1) ${CXXFLAGS} -o $(2)

endef
define COMPILE_MAKE
CFLAGS='${CFLAGS}' $(MAKE) -C $(dir $(1)) $(2)

endef
define REMOVE
$(if $(wildcard $(1)),$\
	rm $(1))

endef
define REMOVE_MAKE
$(MAKE) -C $(dir $(1)) clean

endef
define REMOVE_LIST
$(foreach ITEM,$\
	$(1),$\
	$(if $(findstring .a,${ITEM}),$\
		$(call REMOVE_MAKE,${ITEM}),$\
		$(call REMOVE,${ITEM})))
endef

all: ftsc

ftsc: ${FTSC_REQUIREMENTS}
	${CXX} ${OBJECT_FILES} ${LDFLAGS} -o $@
	strip $@

build/%.o: src/%.cpp
	$(call COMPILE,$<,$@)
%.gch: %
	$(call COMPILE,$<,$@)
%.pch: %
	$(call COMPILE,$<,$@)
	
%.a:
	$(call COMPILE_MAKE,$@)
deps/tree-sitter/libtree-sitter.a:
	$(call COMPILE_MAKE,$@,libtree-sitter.a)
deps/tree-sitter-typescript/typescript/libtree-sitter-typescript.a:
	$(call COMPILE_MAKE,$@,libtree-sitter-typescript.a)

clean:
	$(call REMOVE_LIST,${FTSC_REQUIREMENTS})
	$(call REMOVE,ftsc)

.PHONY: all clean install uninstall
