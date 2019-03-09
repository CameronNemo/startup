desktopdir = $(datadir)/applications
desktop_DATA = startup-monitor.desktop

icondir = $(datadir)/icons/hicolor/scalable/apps
icon = startup-monitor.svg
icon_DATA = $(icon)

$(icon): $(top_srcdir)/doc/startup-logo.svg
	cp $< $@

EXTRA_DIST = $(desktop_DATA)

clean-local:
	rm -f $(icon)
