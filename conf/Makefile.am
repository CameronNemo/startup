## Process this file with automake to produce Makefile.in

initdir = $(sysconfdir)/init
if ENABLE_SYSVCOMPAT
dist_init_DATA = \
	rc-sysinit.conf \
	rc.conf \
	rcS.conf \
	control-alt-delete.conf
else
EXTRA_DIST = \
	rc-sysinit.conf \
	rc.conf \
	rcS.conf \
	control-alt-delete.conf
endif
