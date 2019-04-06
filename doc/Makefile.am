## Process this file with automake to produce Makefile.in

EXTRA_DIST = \
	states.dot \
	states.png

states.png: states.dot
	dot -Tpng -o$@ $<
