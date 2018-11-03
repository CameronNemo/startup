## Process this file with automake to produce Makefile.in

AM_CFLAGS = \
	$(NIH_CFLAGS) \
	$(NIH_DBUS_CFLAGS) \
	$(DBUS_CFLAGS)

AM_CPPFLAGS = \
	-DLOCALEDIR="\"$(localedir)\"" \
	-DSBINDIR="\"$(sbindir)\"" \
	-I$(top_builddir) -I$(top_srcdir) -iquote$(builddir) -iquote$(srcdir) \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/test -iquote $(top_srcdir)/test

EXTRA_DIST = util.supp

dist_man_MANS = \
	man/initctl.8

if ENABLE_SYSVCOMPAT
dist_man_MANS += \
	man/reboot.8 \
	man/shutdown.8 \
	man/runlevel.8 \
	man/telinit.8 \
	man/runlevel.7
else
EXTRA_DIST += \
	man/reboot.8 \
	man/shutdown.8 \
	man/runlevel.8 \
	man/telinit.8 \
	man/runlevel.7
endif

bin_PROGRAMS = initctl

if ENABLE_SYSVCOMPAT
sbin_PROGRAMS = \
	reboot \
	runlevel \
	shutdown \
	telinit
else
EXTRA_DIST += \
	reboot.c \
	shutdown.c \
	runlevel.c \
	telinit.c \
	utmp.c \
	sysv.c
endif

initctl_SOURCES = \
	initctl.c initctl.h \
	$(top_srcdir)/init/xdg.c $(top_srcdir)/init/xdg.h
nodist_initctl_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS) \
	$(com_ubuntu_Upstart_Instance_OUTPUTS)
initctl_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)

if ENABLE_SYSVCOMPAT
reboot_SOURCES = \
	reboot.c \
	utmp.c utmp.h
reboot_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS)

runlevel_SOURCES = \
	runlevel.c \
	utmp.c utmp.h
runlevel_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS)

shutdown_SOURCES = \
	shutdown.c \
	utmp.c utmp.h \
	sysv.c sysv.h
nodist_shutdown_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS)
shutdown_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)

telinit_SOURCES = \
	telinit.c \
	utmp.c utmp.h \
	sysv.c sysv.h
nodist_telinit_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Instance_OUTPUTS)
telinit_LDADD = \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)
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


com_ubuntu_Upstart_Instance_OUTPUTS = \
	com.ubuntu.Upstart.Instance.c \
	com.ubuntu.Upstart.Instance.h

com_ubuntu_Upstart_Instance_XML = \
	../dbus/com.ubuntu.Upstart.Instance.xml

$(com_ubuntu_Upstart_Instance_OUTPUTS): $(com_ubuntu_Upstart_Instance_XML)
	$(AM_V_GEN)$(NIH_DBUS_TOOL) \
		--package=$(PACKAGE) \
		--mode=proxy --prefix=job \
		--default-interface=com.ubuntu.Upstart0_6.Instance \
		--output=$@ $<


# These have to be built sources because we can't compile object files
# without the header file existing first
BUILT_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS) \
	$(com_ubuntu_Upstart_Instance_OUTPUTS)

CLEANFILES = \
	$(com_ubuntu_Upstart_OUTPUTS) \
	$(com_ubuntu_Upstart_Job_OUTPUTS) \
	$(com_ubuntu_Upstart_Instance_OUTPUTS)


install-data-hook:
	src=`echo initctl | sed '$(transform)'`.8; \
	for symlink in start stop restart reload status; do \
	  inst=`echo $$symlink | sed '$(transform)'`.8; \
          echo " ln -sf '$$src' '$(DESTDIR)$(man8dir)/$$inst'"; \
	  ln -sf "$$src" "$(DESTDIR)$(man8dir)/$$inst"; \
	done

if ENABLE_SYSVCOMPAT
	src=`echo reboot | sed '$(transform)'`.8; \
	for symlink in halt poweroff; do \
	  inst=`echo $$symlink | sed '$(transform)'`.8; \
          echo " ln -sf '$$src' '$(DESTDIR)$(man8dir)/$$inst'"; \
	  ln -sf "$$src" "$(DESTDIR)$(man8dir)/$$inst"; \
	done
endif

install-exec-hook:
	src=`echo initctl | sed '$(transform);s/$$/$(EXEEXT)/'`; \
	for symlink in start stop restart reload status; do \
	  inst=`echo $$symlink | sed '$(transform);s/$$/$(EXEEXT)/'`; \
          echo " ln -sf '$$src' '$(DESTDIR)$(bindir)/$$inst'"; \
	  ln -sf "$$src" "$(DESTDIR)$(bindir)/$$inst"; \
	done

if ENABLE_SYSVCOMPAT
	src=`echo reboot | sed '$(transform);s/$$/$(EXEEXT)/'`; \
	for symlink in halt poweroff; do \
	  inst=`echo $$symlink | sed '$(transform);s/$$/$(EXEEXT)/'`; \
          echo " ln -sf '$$src' '$(DESTDIR)$(sbindir)/$$inst'"; \
	  ln -sf "$$src" "$(DESTDIR)$(sbindir)/$$inst"; \
	done
endif

uninstall-hook:
if ENABLE_SYSVCOMPAT
	for symlink in start stop restart reload status halt poweroff; do \
else
	for symlink in start stop restart reload status; do
endif
	  file=`echo $$symlink | sed '$(transform)'`.8; \
          echo " rm -f '$(DESTDIR)$(man8dir)/$$file'"; \
	  rm -f "$(DESTDIR)$(man8dir)/$$file"; \
	  file=`echo $$symlink | sed '$(transform);s/$$/$(EXEEXT)/'`; \
          echo " rm -f '$(DESTDIR)$(sbindir)/$$file'"; \
	  rm -f "$(DESTDIR)$(sbindir)/$$file"; \
	done

# Ensure a clean test environment (that will not touch the running users
# one). Tests that need the variables listed below are expected to set
# them to appropriate temporary values as needed.
AM_TESTS_ENVIRONMENT= \
	unset -v \
		XDG_RUNTIME_DIR \
		DBUS_SESSION_BUS_ADDRESS \
		UPSTART_SESSION \
		UPSTART_INSTANCE \
		UPSTART_EVENTS \
		UPSTART_JOB;

if ENABLE_TAP_OUTPUT
LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/tap-driver.sh
else
LOG_DRIVER = $(SHELL) $(top_srcdir)/test-driver
endif

TESTS = \
	test_initctl

if ENABLE_SYSVCOMPAT
TESTS += \
	test_utmp \
	test_sysv \
	test_telinit
endif

check_PROGRAMS = $(TESTS)

test_initctl_SOURCES = \
	tests/test_initctl.c \
	initctl.c \
	$(top_srcdir)/init/xdg.c $(top_srcdir)/init/xdg.h
test_initctl_CFLAGS = $(AM_CFLAGS) -DTEST
test_initctl_LDADD = \
	com.ubuntu.Upstart.o \
	com.ubuntu.Upstart.Job.o com.ubuntu.Upstart.Instance.o \
	$(top_builddir)/test/libtest_util_common.a \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)
if ENABLE_CGROUPS
test_initctl_LDADD += $(CGMANAGER_LIBS)
endif


if ENABLE_SYSVCOMPAT
test_utmp_SOURCES = tests/test_utmp.c
test_utmp_LDADD = \
	utmp.o \
	$(NIH_LIBS)

test_sysv_SOURCES = tests/test_sysv.c
nodist_test_sysv_SOURCES = \
	$(com_ubuntu_Upstart_OUTPUTS)
test_sysv_LDADD = \
	sysv.o utmp.o \
	$(LTLIBINTL) \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)

test_telinit_SOURCES = tests/test_telinit.c telinit.c
test_telinit_CFLAGS = $(AM_CFLAGS) -DTEST
test_telinit_LDADD = \
	sysv.o utmp.o \
	com.ubuntu.Upstart.o \
	com.ubuntu.Upstart.Job.o com.ubuntu.Upstart.Instance.o \
	$(NIH_LIBS) \
	$(NIH_DBUS_LIBS) \
	$(DBUS_LIBS)
endif


.PHONY: tests
tests: $(BUILT_SOURCES) $(check_PROGRAMS) $(top_builddir)/init/startup $(top_builddir)/test/libtest_util_common.a

clean-local:
	rm -f *.gcno *.gcda

maintainer-clean-local:
	rm -f *.gcov
