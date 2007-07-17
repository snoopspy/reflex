# Module.mk for reflex module
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

MODDIR       := reflex
MODDIRS      := $(MODDIR)/src
MODDIRI      := $(MODDIR)/inc

REFLEXDIR    := $(MODDIR)
REFLEXDIRS   := $(REFLEXDIR)/src
REFLEXDIRI   := $(REFLEXDIR)/inc

##### libReflex #####
REFLEXL      := $(MODDIRI)/LinkDef.h
REFLEXDS     := $(MODDIRS)/G__Reflex.cxx
REFLEXDO     := $(REFLEXDS:.cxx=.o)
REFLEXDH     := $(REFLEXDS:.cxx=.h)

REFLEXAH     := $(wildcard $(MODDIRI)/Reflex/*.h)
REFLEXBH     := $(wildcard $(MODDIRI)/Reflex/Builder/*.h)
REFLEXIH     := $(wildcard $(MODDIRI)/Reflex/internal/*.h)
REFLEXH      := $(REFLEXAH) $(REFLEXBH) $(REFLEXIH)
REFLEXAPIH   := $(filter-out $(MODDIRI)/Reflex/Builder/ReflexBuilder.h,\
	        $(filter-out $(MODDIRI)/Reflex/Reflex.h,\
	        $(filter-out $(MODDIRI)/Reflex/SharedLibrary.h,\
	        $(filter-out $(MODDIRI)/Reflex/DictionaryGenerator.h,\
		$(REFLEXAH) $(REFLEXBH)))))
REFLEXS      := $(filter-out $(MODDIRS)/G__%,$(wildcard $(MODDIRS)/*.cxx))
REFLEXO      := $(REFLEXS:.cxx=.o)

REFLEXDEP    := $(REFLEXO:.o=.d) $(REFLEXDO:.o=.d)

REFLEXLIB    := $(LPATH)/libReflex.$(SOEXT)
REFLEXDICTLIB:= $(LPATH)/libReflexDict.$(SOEXT)
REFLEXDICTMAP:= $(REFLEXDICTLIB:.$(SOEXT)=.rootmap)

# used in the main Makefile
ALLHDRS      += $(patsubst $(MODDIRI)/Reflex/%.h,include/Reflex/%.h,$(REFLEXH))
ALLLIBS      += $(REFLEXLIB) $(REFLEXDICTLIB)
ALLMAPS      += $(REFLEXDICTMAP)

# include all dependency files
INCLUDEFILES += $(REFLEXDEP)

# genreflex
RFLX_GRFLXSD := $(REFLEXDIR)/python/genreflex
RFLX_GRFLXDD := lib/python/genreflex

RFLX_GCCXMLPATHPY := $(RFLX_GRFLXDD)/gccxmlpath.py

RFLX_GRFLXS   := $(wildcard $(RFLX_GRFLXSD)/*.py)
RFLX_GRFLXPY  := $(patsubst $(RFLX_GRFLXSD)/%.py,$(RFLX_GRFLXDD)/%.py,$(RFLX_GRFLXS))
RFLX_GRFLXPY  += $(RFLX_GCCXMLPATHPY)
ifneq ($(BUILDPYTHON),no)
RFLX_GRFLXPYC := $(subst .py,.pyc,$(RFLX_GRFLXPY))
endif

RFLX_LIBDIR = $(LIBDIR)

ifeq ($(PLATFORM),win32)
RFLX_GENREFLEX = bin/genreflex.bat
RFLX_GENRFLXRC = bin/genreflex-rootcint.bat
# test suite
RFLX_CPPUNITI   = "$(shell cygpath -w '$(CPPUNIT)/include')"
RFLX_CPPUNITLL  = "$(shell cygpath -w '$(CPPUNIT)/lib/cppunit.lib')"
RFLX_REFLEXLL   = lib/libReflex.lib
else
RFLX_GENREFLEX = bin/genreflex
RFLX_GENRFLXRC = bin/genreflex-rootcint
# test suite
RFLX_CPPUNITI   = $(CPPUNIT)/include
RFLX_CPPUNITLL  = -L$(CPPUNIT)/lib -lcppunit
RFLX_REFLEXLL   = -Llib -lReflex
ifneq ($(PLATFORM),fbsd)
ifneq ($(PLATFORM),obsd)
RFLX_REFLEXLL   += -ldl
endif
endif
endif

ifeq ($(PLATFORM),solaris)
RFLX_REFLEXLL   += -ldemangle
endif

RFLX_GENREFLEX_CMD = python ../../lib/python/genreflex/genreflex.py

RFLX_TESTD      = $(REFLEXDIR)/test
RFLX_TESTLIBD1  = $(RFLX_TESTD)/testDict1
RFLX_TESTLIBD2  = $(RFLX_TESTD)/testDict2
RFLX_TESTLIBS1  = $(RFLX_TESTD)/Reflex_rflx.cpp
RFLX_TESTLIBS2  = $(RFLX_TESTD)/Class2Dict_rflx.cpp
RFLX_TESTLIBS   = $(RFLX_TESTLIBS1) $(RFLX_TESTLIBS2)
RFLX_TESTLIBO   = $(subst .cpp,.o,$(RFLX_TESTLIBS))
RFLX_TESTLIB    = $(subst $(RFLX_TESTD)/,lib/libtest_,$(subst _rflx.o,Rflx.$(SOEXT),$(RFLX_TESTLIBO)))

RFLX_UNITTESTS = $(RFLX_TESTD)/test_Reflex_generate.cxx    \
                 $(RFLX_TESTD)/test_ReflexBuilder_unit.cxx \
                 $(RFLX_TESTD)/test_Reflex_unit.cxx        \
                 $(RFLX_TESTD)/test_Reflex_simple1.cxx     \
                 $(RFLX_TESTD)/test_Reflex_simple2.cxx
RFLX_UNITTESTO = $(subst .cxx,.o,$(RFLX_UNITTESTS))
RFLX_UNITTESTX = $(subst .cxx,,$(RFLX_UNITTESTS))

RFLX_GENMAPS   = $(REFLEXDIRS)/genmap/genmap.cxx
RFLX_GENMAPO   = $(RFLX_GENMAPS:.cxx=.o)
RFLX_GENMAPX   = bin/genmap$(EXEEXT)

ALLEXECS += $(RFLX_GENREFLEX) $(RFLX_GENRFLXRC) $(RFLX_GENMAPX)

##### local rules #####
POSTBIN += $(RFLX_GRFLXPYC) $(RFLX_GRFLXPY)

include/Reflex/%.h: $(REFLEXDIRI)/Reflex/%.h
		@(if [ ! -d "include/Reflex" ]; then          \
		   mkdir -p include/Reflex;                   \
		fi)
		@(if [ ! -d "include/Reflex/Builder" ]; then  \
		   mkdir -p include/Reflex/Builder;           \
		fi)
		@(if [ ! -d "include/Reflex/internal" ]; then \
		   mkdir -p include/Reflex/internal;          \
		fi)
		cp $< $@

.PRECIOUS: $(RFLX_GRFLXPY)

$(RFLX_GCCXMLPATHPY): config/Makefile.config
		@(if [ ! -d "lib/python/genreflex" ]; then \
		  mkdir -p lib/python/genreflex; fi )
		@echo "gccxmlpath = '$(GCCXML)'" > $(RFLX_GCCXMLPATHPY);

$(RFLX_GRFLXDD)/%.py: $(RFLX_GRFLXSD)/%.py $(RFLX_GCCXMLPATHPY)
		@(if [ ! -d "lib/python/genreflex" ]; then \
		  mkdir -p lib/python/genreflex; fi )
		cp $< $@

$(RFLX_GRFLXDD)/%.pyc: $(RFLX_GRFLXDD)/%.py
		@python -c 'import py_compile; py_compile.compile( "$<" )'

$(RFLX_GENMAPO) : $(RFLX_GENMAPS)
	$(CXX) $(OPT) $(CXXFLAGS) -Iinclude -I$(REFLEXDIRS)/genmap -c $< $(CXXOUT)$@

$(RFLX_GENMAPX) : $(RFLX_GENMAPO) $(REFLEXLIB)
	$(LD) $(LDFLAGS) -o $@ $(RFLX_GENMAPO) $(RFLX_REFLEXLL)

$(REFLEXLIB): $(REFLEXO) $(ORDER_) $(MAINLIBS)
		@$(MAKELIB) $(PLATFORM) $(LD) "$(LDFLAGS)"      \
		"$(SOFLAGS)" libReflex.$(SOEXT) $@ "$(REFLEXO)" \
		"$(REFLEXLIBEXTRA)"

$(REFLEXDICTLIB): $(REFLEXDO) $(ORDER_) $(MAINLIBS) $(REFLEXLIB)
		@$(MAKELIB) $(PLATFORM) $(LD) "$(LDFLAGS)"      \
		"$(SOFLAGS)" libReflexDict.$(SOEXT) $@ "$(REFLEXDO)" \
		"$(REFLEXDICTLIBEXTRA)"

$(REFLEXDS): $(REFLEXAPIH) $(REFLEXL) $(ROOTCINTTMPEXE)
		@echo "Generating dictionary $@..."
		$(ROOTCINTTMP) -f $@ -c -p -Ireflex/inc $(REFLEXAPIH) $(REFLEXL)

$(REFLEXDICTMAP): $(RLIBMAP) $(MAKEFILEDEP) $(REFLEXL)
		$(RLIBMAP) -o $(REFLEXDICTMAP) -l $(REFLEXDICTLIB) \
		   -d $(REFLEXDICTLIBDEPM) -c $(REFLEXL)

all-reflex:     $(REFLEXLIB) $(REFLEXDICTLIB) $(REFLEXDICTMAP) $(RFLX_GRFLXPYC) $(RFLX_GRFLXPY)

clean-genreflex:
		@rm -f bin/genreflex*
		@rm -rf lib/python/genreflex

clean-check-reflex:
		@rm -f $(RFLX_TESTLIBS) $(RFLX_TESTLIBO) $(RFLX_UNITTESTO) $(RFLX_UNITTESTX)

clean-reflex: clean-genreflex clean-check-reflex
		@rm -f $(RFLX_GENMAPX)
		@rm -f $(REFLEXO) $(REFLEXDO)

clean::         clean-reflex

distclean-reflex: clean-reflex
		@rm -f $(REFLEXDEP) $(REFLEXLIB) $(REFLEXDICTLIB) $(REFLEXDICTMAP)
		@rm -rf include/Reflex lib/python

distclean::     distclean-reflex

# test suite

check-reflex: $(REFLEXLIB) $(RFLX_TESTLIB) $(RFLX_UNITTESTX)
ifeq ($(PLATFORM),win32)
		@export PATH="`pwd`/bin:$(CPPUNIT)/lib:$(PATH)"; \
		$(RFLX_TESTD)/test_Reflex_generate; \
		$(RFLX_TESTD)/test_Reflex_simple1; \
		$(RFLX_TESTD)/test_Reflex_simple2; \
		$(RFLX_TESTD)/test_Reflex_unit; \
		$(RFLX_TESTD)/test_ReflexBuilder_unit
else
		@export LD_LIBRARY_PATH=`pwd`/lib:$(CPPUNIT)/lib; \
		$(RFLX_TESTD)/test_Reflex_generate; \
		$(RFLX_TESTD)/test_Reflex_simple1; \
		$(RFLX_TESTD)/test_Reflex_simple2; \
		$(RFLX_TESTD)/test_Reflex_unit; \
		$(RFLX_TESTD)/test_ReflexBuilder_unit
endif

lib/libtest_%Rflx.$(SOEXT) : $(RFLX_TESTD)/%_rflx.o
		@$(MAKELIB) $(PLATFORM) $(LD) "$(LDFLAGS)" "$(SOFLAGS)" $(notdir $@) $@ $< $(RFLX_REFLEXLL)

%_rflx.o : %_rflx.cpp
		$(CXX) $(OPT) $(CXXFLAGS) -c $< $(CXXOUT)$@

$(RFLX_TESTLIBS1) : $(REFLEXDIRI)/Reflex/Reflex.h $(RFLX_TESTLIBD1)/selection.xml
		cd $(RFLX_TESTD); $(RFLX_GENREFLEX_CMD) testDict1/Reflex.h -s testDict1/selection.xml -I../../include

$(RFLX_TESTLIBS2) : $(RFLX_TESTLIBD2)/Class2Dict.h $(RFLX_TESTLIBD2)/selection.xml $(wildcard $(RFLX_TESTLIBD2)/*.h)
		cd $(RFLX_TESTD); $(RFLX_GENREFLEX_CMD) testDict2/Class2Dict.h -s testDict2/selection.xml -I../../include --iocomments

$(RFLX_UNITTESTO) : $(RFLX_TESTD)/test_Reflex%.o : $(RFLX_TESTD)/test_Reflex%.cxx
		$(CXX) $(OPT) $(CXXFLAGS) -I$(RFLX_CPPUNITI) -Ireflex -c $< $(CXXOUT)$@

$(RFLX_UNITTESTX) : $(RFLX_TESTD)/test_Reflex% : $(RFLX_TESTD)/test_Reflex%.o
		$(LD) $(LDFLAGS) -o $@ $< $(RFLX_CPPUNITLL) $(RFLX_REFLEXLL)

$(REFLEXO):      PCHCXXFLAGS =
$(RFLX_GENMAPO): PCHCXXFLAGS =
