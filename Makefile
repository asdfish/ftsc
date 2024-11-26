CC ?= cc
CFLAGS ?= -O2 -march=native -pipe
COMMONFLAGS := -std=c99 $\
							 -Wall -Wextra -Wpedantic $\
							 -Iinclude $\
							 -Ideps/carp $\
							 -Ideps/tree-sitter-typescript/typescript
LDFLAGS := ${CFLAGS} ${COMMONFLAGS} $\
					 -Ldeps/tree-sitter-typescript/typescript -l:libtree-sitter-typescript.a

# uncomment/comment to enable/disable
# PROCESS_HEADER_FILES := yes
PROCESSED_HEADER_FILES := $(if ${PROCESS_HEADER_FILES},$\
														$(subst .h,$\
															$(if $(findstring clang,${CC}),$\
																.h.pch,$\
																.h.gch),$\
															$(shell find include -name '*.h' -type f)))

OBJECT_FILES := $(patsubst src/%.c,$\
									build/%.o,$\
									$(shell find src -name '*.c' -type f))

FTSC_REQUIREMENTS := deps/tree-sitter-typescript/typescript/libtree-sitter-typescript.a $\
										 ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}

define COMPILE
${CC} -c $(1) ${CFLAGS} ${COMMONFLAGS} -o $(2)

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
	${CC} ${OBJECT_FILES} ${LDFLAGS} -o $@

build/%.o: src/%.c
	$(call COMPILE,$<,$@)
%.gch: %
	$(call COMPILE,$<,$@)
%.pch: %
	$(call COMPILE,$<,$@)

%.a:
	CFLAGS='${CFLAGS}' $(MAKE) -C $(dir $@)

clean:
	$(call REMOVE_LIST,${FTSC_REQUIREMENTS})
	$(call REMOVE,ftsc)

.PHONY: all clean install uninstall
