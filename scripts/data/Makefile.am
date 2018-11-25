desktopdir = $(datadir)/applications
desktop_DATA = startup-monitor.desktop

icondir = $(datadir)/icons/hicolor/scalable/apps
icon = startup-monitor.svg
icon_DATA = $(icon)

$(icon): $(top_srcdir)/doc/startup-logo.svg
	cp $< $@

EXTRA_DIST = $(desktop_DATA)
	
install-icon:
	mkdir -p $(DESTDIR)$(pkgdatadir)/icons/
	$(INSTALL_DATA) $(icon) $(DESTDIR)$(pkgdatadir)/icons/

uninstall-icon:
	rm -f $(DESTDIR)$(pkgdatadir)/icons/$(icon)

install-data-local: install-icon
uninstall-local: uninstall-icon

clean-local:
	rm -f $(icon)
