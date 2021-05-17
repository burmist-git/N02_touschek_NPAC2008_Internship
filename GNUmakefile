# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:42 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------
#-lHist -lGraf -lGraf3d -lGpad \
#
#-lMatrix -lPhysics

name := exampleN02
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin


CPPFLAGS += -D_REENTRANT -I$(ROOTSYS)/include

EXTRALIBS += -L$(ROOTSYS)/lib -lTree -lRIO -lNet -lMathCore -lCore -lCint

#EXTRALIBS += `root-config --libs`

include $(G4INSTALL)/config/binmake.gmk
