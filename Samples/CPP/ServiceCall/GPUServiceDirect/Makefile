#
# Makefile for GPUServiceDirect
#
DEPTH = $(shell find_depth)

COMPONENT_DEPTH = $(if $(GONE_TO_BUILD_DIR),../)../..

include $(DEPTH)/make/swdefs

ifneq (,$(DRIVER_OS_WNOW64A))
SUBDIRS += wNow64a
endif

ifneq (,$(DRIVER_OS_WNXT64A))
SUBDIRS += wNxt64a
endif

LOG_DIRS += $(SUBDIRS)

include $(DEPTH)/make/swrules