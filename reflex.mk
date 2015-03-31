# ------------------------------------------------------------------------------
# reflex
# ------------------------------------------------------------------------------

REFLEX_PATH := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
REFLEX_PATH := $(subst $(_ABS_PATH),$(_REL_PATH),$(REFLEX_PATH))

CPPFLAGS += -I$(REFLEX_PATH)/include
LDFLAGS  += -L$(REFLEX_PATH)/lib
LDLIBS   += -Wl,-Bstatic -lReflex -Wl,-Bdynamic

