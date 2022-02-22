# Setup shared variables used in sub makefiles
ROOTDIR=${PWD}
export

include $(ROOTDIR)/MakefileDefs.inc

DIRS	= challenges examples

all:

#######################################
# build applications
#######################################
challenges: force_look
	$(ECHO) looking into challenges : $(MAKE) $(MFLAGS)
	cd challenges; $(MAKE) $(MFLAGS)

#######################################
# build applications
#######################################
examples: force_look
	$(ECHO) looking into examples : $(MAKE) $(MFLAGS)
	cd examples; $(MAKE) $(MFLAGS)

solutions: force_look
	$(ECHO) looking into solutions : $(MAKE) $(MFLAGS)
	cd solutions; $(MAKE) $(MFLAGS)

#######################################
# build assignment
#######################################
assignment: force_look
	$(ECHO) looking into assignment : $(MAKE) $(MFLAGS)
	cd assignment; $(MAKE) $(MFLAGS)

#######################################
# clean everything
#######################################
clean :
	$(ECHO) cleaning up in .
	-$(RM) -f $(EXE) $(OBJS) $(OBJLIBS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look:
	true
