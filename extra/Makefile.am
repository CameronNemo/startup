## Process this file with automake to produce Makefile.in

# Required to allow conditional appends below
EXTRA_DIST =

AM_CFLAGS = \
	$(NIH_CFLAGS) \
	$(NIH_DBUS_CFLAGS) \
	$(DBUS_CFLAGS)

AM_CPPFLAGS = \
	-DLOCALEDIR="\"$(localedir)\"" \
	-DSBINDIR="\"$(sbindir)\"" \
	-I$(top_builddir) -I$(top_srcdir) -iquote$(builddir) -iquote$(srcdir) \
	-I$(top_srcdir)/intl

initdir = $(datadir)/startup
sessionsdir = $(datadir)/xdg/startup
bridgedir = $(startupbridgedir)

dist_sessions_DATA = \
	conf-session/bridge-event.conf \
	conf-session/bridge-file.conf \
	conf-session/re-exec.conf \
	conf-session/bridge-dbus-session.conf \
	conf-session/bridge-dbus-system.conf

bridge_PROGRAMS = \
	event \
	file \
	dbus

dist_init_DATA = \
	conf/bridge-file.conf \
	conf/bridge-dbus.conf

dist_man_MANS = \
	man/startup-event-bridge.8 \
	man/startup-file-bridge.8 \
	man/startup-dbus-bridge.8 \
	man/file-event.7 \
	man/dbus-event.7

if ENABLE_SOCKET_BRIDGE
bridge_PROGRAMS += \
	socket

dist_sessions_DATA += \
	conf-session/bridge-socket.conf

dist_init_DATA += \
	conf/bridge-socket.conf

dist_man_MANS += \
	man/startup-socket-bridge.8 \
	man/socket-event.7

socket_SOURCES = \
	socket.c
nodist_socket_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)
socket_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)
else
EXTRA_DIST += \
	socket.c \
	conf-session/bridge-socket.conf \
	conf/bridge-socket.conf \
	man/startup-socket-bridge.8 \
	man/socket-event.7
endif

event_SOURCES = \
	event.c
nodist_event_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)
event_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)

file_SOURCES = \
	file.c
nodist_file_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)
file_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)

dbus_SOURCES = \
	dbus.c
nodist_dbus_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)
dbus_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)

if ENABLE_LOCAL_BRIDGE
bridge_PROGRAMS += \
	local

dist_man_MANS += \
	man/startup-local-bridge.8

local_SOURCES = \
	local.c
nodist_local_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)
local_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)
else
EXTRA_DIST += \
	local.c \
	man/startup-local-bridge.8
endif

if ENABLE_DCONF_BRIDGE
dist_sessions_DATA += \
	conf-session/bridge-dconf.conf

dist_man_MANS += \
	man/startup-dconf-bridge.8 \
	man/dconf-event.7

bridge_PROGRAMS += \
	dconf

dconf_SOURCES = \
	dconf.c
nodist_dconf_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS)
dconf_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS) \
	$(GIO_LIBS) \
	$(DCONF_LIBS)
dconf_CFLAGS = \
	$(NIH_CFLAGS) \
	$(NIH_DBUS_CFLAGS) \
	$(DBUS_CFLAGS) \
	$(DCONF_CFLAGS)
else
EXTRA_DIST += \
	dconf.c \
	conf-session/dconf.conf \
	man/startup-dconf-bridge.8 \
	man/dconf-event.7
endif

if ENABLE_UDEV_BRIDGE
dist_sessions_DATA += \
	conf-session/bridge-udev.conf

dist_init_DATA += \
	conf/bridge-udev.conf

dist_man_MANS += \
	man/startup-udev-bridge.8

bridge_PROGRAMS += \
	udev

udev_SOURCES = \
	udev.c
nodist_udev_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS)
udev_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS) \
	$(UDEV_LIBS)
udev_CFLAGS = \
	$(NIH_CFLAGS) \
	$(NIH_DBUS_CFLAGS) \
	$(DBUS_CFLAGS) \
	$(UDEV_CFLAGS)
else
EXTRA_DIST += \
	udev.c \
	man/startup-udev-bridge.8 \
	conf-session/bridge-udev.conf \
	conf/bridge-udev.conf
endif

com_ubuntu_Upstart_OUTPUTS = \
	com.ubuntu.Upstart.c \
	com.ubuntu.Upstart.h

com_ubuntu_Upstart_XML = \
	../dbus/com.ubuntu.Upstart.xml

$(com_ubuntu_Upstart_OUTPUTS): $(com_ubuntu_Upstart_XML)
	$(AM_V_GEN)$(NIH_DBUS_TOOL) \
		--package=$(PACKAGE) \
		--mode=proxy --prefix=upstart \
		--default-interface=com.ubuntu.Upstart0_6 \
		--output=$@ $<


com_ubuntu_Upstart_Job_OUTPUTS = \
	com.ubuntu.Upstart.Job.c \
	com.ubuntu.Upstart.Job.h

com_ubuntu_Upstart_Job_XML = \
	../dbus/com.ubuntu.Upstart.Job.xml

$(com_ubuntu_Upstart_Job_OUTPUTS): $(com_ubuntu_Upstart_Job_XML)
	$(AM_V_GEN)$(NIH_DBUS_TOOL) \
		--package=$(PACKAGE) \
		--mode=proxy --prefix=job_class \
		--default-interface=com.ubuntu.Upstart0_6.Job \
		--output=$@ $<


# These have to be built sources because we can't compile object files
# without the header file existing first
BUILT_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)

CLEANFILES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS)


clean-local:
	rm -f *.gcno *.gcda

maintainer-clean-local:
	rm -f *.gcov
