# File: Makefile
# Author: Benedict R. Gaster
# Date: 9th June 2017
# Desc: Makefile for all examples in this folder. Note that
#       it is possible automatically add a new challenge using the
#       create_challenge.sh script (found in ../templates/challenges) and
#       for this to work correclty there are placeholders in this file:
#
# Copyright: University of West of England 2017
#
ifeq ($(origin ROOTDIR), undefined)
	ROOTDIR=..
endif
include $(ROOTDIR)/MakefileDefs.inc

DIRS = challenge001 challenge2 sem3 cracker initials2 ceaser dom_test circlesAndRects ${add_challenge}

all: challenge001 challenge2 sem3 cracker initials2 ceaser dom_test circlesAndRects ${add_challenge}

# insert new build rule (do not remove this!!!)
001: force_look
	$(ECHO) looking into 001 : $(MAKE) $(MFLAGS)
	cd 001; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
challenge001: force_look
	$(ECHO) looking into challenge001 : $(MAKE) $(MFLAGS)
	cd challenge001; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
challenge2: force_look
	$(ECHO) looking into challenge2 : $(MAKE) $(MFLAGS)
	cd challenge2; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
sem3: force_look
	$(ECHO) looking into sem3 : $(MAKE) $(MFLAGS)
	cd sem3; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
cracker: force_look
	$(ECHO) looking into cracker : $(MAKE) $(MFLAGS)
	cd cracker; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
initials2: force_look
	$(ECHO) looking into initials2 : $(MAKE) $(MFLAGS)
	cd initials2; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
ceaser: force_look
	$(ECHO) looking into ceaser : $(MAKE) $(MFLAGS)
	cd ceaser; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
dom_test: force_look
	$(ECHO) looking into dom_test : $(MAKE) $(MFLAGS)
	cd dom_test; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
circlesAndRects: force_look
	$(ECHO) looking into circlesAndRects : $(MAKE) $(MFLAGS)
	cd circlesAndRects; $(MAKE) $(MFLAGS)

# insert new build rule (do not remove this!!!)
${add_challenge_rule}

install:
	$(ECHO) installing up in .
	-for d in $(DIRS); do (cd $$d; $(MAKE) install ); done

clean:
	$(ECHO) cleaning up in .
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look:
	true
