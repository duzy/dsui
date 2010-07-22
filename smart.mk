#
#

$(call sm-new-module, dsui, shared)

ds.ui.dir := $(sm.module.dir)
ds.ui.dir.lib := $(ds.ui.dir)/out/$V/lib

include $(ds.ui.dir)/check-deps.mk

#sm.log.filename := dsui.log
sm.module.out_implib := dsui

sm.module.dirs.include := \
  $(ds.ui.dir)/include \
  $(ds.third.boost.dir)

sm.module.sources := $(wildcard src/*.cpp)

ifeq ($(sm.os.name),linux)
  sm.module.sources += $(wildcard src/x11/*.cpp)
  sm.module.libs += X11
else
ifeq ($(sm.os.name),win32)
  sm.module.sources += $(wildcard src/win32/*.cpp)
endif
endif

$(call sm-build-this)
$(call sm-load-subdirs)
