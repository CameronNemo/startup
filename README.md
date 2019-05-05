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
 * GNU Autoconf 2.61
 * GNU Automake 1.10
 * GNU Libtool 2.2.4
 * GNU Gettext 0.16.1
 * GCC 4.1
 * pkg-config 0.22
 * GNU C Library (glibc) 2.4, or musl libc
 * D-Bus 1.2.16
 * libnih 1.0.4 or 1.0.3 with
 [one patch](https://github.com/keybuk/libnih/commit/4143fac798530fd02ac7c98955b06ab58bbb7242.patch)

These should all be available from Debian, Ubuntu, or Void Linux.

## building

A typical build, suitable for session init usage:

```
$ autoreconf -fi
$ mkdir build
$ cd build
$ ../configure --prefix=/usr --sysconfdir=/etc --disable-sysvcompat
$ make
```

## installing

To install `startup`, use the
[checkinstall](https://www.linux.com/learn/easy-package-creation-checkinstall)
tool to ensure that no file conflicts are present:

```
# checkinstall
```
