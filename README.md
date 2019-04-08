# startup

startup is an events bus and process management daemon which handles
starting of jobs on boot and other conditions, stopping them during
shutdown, and supervising them while the system is running.

Feature highlights:

 * robust task and service framework supporting a variety of process
   lifetimes;
 * extensible events bus that facilitates integration and communication
   throughout a system;
 * flexible service supervision and failure alerting mechanisms; and
 * simple command line and dbus interfaces to administrate services as
   well as startup itself.

## dependencies

The minimum build requirements are:

 * Linux 2.6.24
 * GCC 4.1
 * GNU C Library (glibc) 2.4
 * libnih 1.0.2
 * pkg-config 0.22
 * libnih-dbus 1.0.2
 * nih-dbus-tool 1.0.4 or 1.0.3 with 4143fac798530fd02ac7c98955b06ab58bbb7242
 * D-Bus 1.2.16

These should all be available or accessible from the current release
of any modern Linux distribution.

For detailed compilation and installation instructions see the INSTALL
file.  If you've checked startup out from revision control and want to
contribute, see the HACKING file.
