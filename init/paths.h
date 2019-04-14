/* upstart
 *
 * Copyright © 2010-2011 Canonical Ltd.
 * Author: Scott James Remnant <scott@netsplit.com>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef INIT_PATHS_H
#define INIT_PATHS_H

/**
 * PATH:
 *
 * This is the default PATH set by the init process itself.
 **/
#ifndef PATH
#define PATH "/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/sbin:/sbin:/bin"
#endif


/**
 * CONSOLE:
 *
 * This is the console device we give to processes that want one.
 **/
#ifndef CONSOLE
#define CONSOLE "/dev/console"
#endif

/**
 * DEV_NULL:
 *
 * This is the console device we give to processes that do not want any
 * console.
 **/
#ifndef DEV_NULL
#define DEV_NULL "/dev/null"
#endif


/**
 * CONFDIR_ENV:
 *
 * If this environment variable is set, read configuration files
 * from the location specified, rather than CONFDIR.
 *
 * Value is expected to be the full path to an alternative job
 * configuration directory.
 **/
#ifndef CONFDIR_ENV
#define CONFDIR_ENV "UPSTART_CONFDIR"
#endif

/**
 * STATE_FILE_ENV:
 *
 * If set, write STATE_FILE on any re-exec.
 **/
#ifndef STATE_FILE_ENV
#define STATE_FILE_ENV "UPSTART_WRITE_STATEFILE"
#endif

/**
 * LOGDIR_ENV:
 *
 * Environment variable that if set specifies an alternative directory
 * to JOB_LOGDIR to write log files to.
 *
 **/
#ifndef LOGDIR_ENV
#define LOGDIR_ENV "UPSTART_LOGDIR"
#endif

/**
 * SESSION_ENV:
 *
 * Environment variable that is set when running as a Session Init.
 **/
#ifndef SESSION_ENV
#define SESSION_ENV "UPSTART_SESSION"
#endif


/**
 * INIT_CONFFILE_LEGACY:
 *
 * Legacy init daemon configuration file.
 **/
#ifndef INIT_CONFFILE_LEGACY
#define INIT_CONFFILE_LEGACY "/etc/init.conf"
#endif

/**
 * INIT_CONFDIR_LEGACY:
 *
 * Legacy top-level directory of the system configuration files.
 **/
#ifndef INIT_CONFDIR_LEGACY
#define INIT_CONFDIR_LEGACY "/etc/init"
#endif

/**
 * INIT_DATADIR:
 *
 * Directory for configuration data shipped by system integrators.
 **/
#ifndef INIT_DATADIR
#define INIT_DATADIR "/usr/share/startup"
#endif

/**
 * INIT_CONFDIR:
 *
 * Directory for system administrator configuration files.
 **/
#ifndef INIT_CONFDIR
#define INIT_CONFDIR "/etc/startup"
#endif

/**
 * JOB_LOGDIR:
 *
 * Directory that jobs which specify CONSOLE_LOG will have their output
 * logged to.
 *
 **/
#ifndef JOB_LOGDIR
#define JOB_LOGDIR "/var/log/startup"
#endif


/**
 * INIT_XDG_DATADIR_LEGACY:
 *
 * Legacy path for system-wide user session jobs.
 **/
#ifndef INIT_XDG_DATADIR_LEGACY
#define INIT_XDG_DATADIR_LEGACY "/usr/share/upstart/sessions"
#endif

/**
 * INIT_XDG_DATADIR:
 *
 * Directory for user session config data shipped by system integrators.
 **/
#ifndef INIT_XDG_DATADIR
#define INIT_XDG_DATADIR "/usr/share/xdg/startup"
#endif


/**
 * INIT_HOME_CONFDIR_LEGACY:
 *
 * Configurations in this folder will be picked up when running as a
 * user session for compatibility purposes only.
 **/
#ifndef INIT_HOME_CONFDIR_LEGACY
#define INIT_HOME_CONFDIR_LEGACY ".init"
#endif

/**
 * INIT_XDG_SUBDIR_LEGACY:
 *
 * Like INIT_XDG_SUBDIR, but lower priority.
 * Used for configurations, but not logs.
 **/
#ifndef INIT_XDG_SUBDIR_LEGACY
#define INIT_XDG_SUBDIR_LEGACY "upstart"
#endif

/**
 * INIT_XDG_SUBDIR:
 *
 * This is the name of the sub folder we will use when constructing
 * config source dirs and logging dirs with XDG compliant folders.
 **/
#ifndef INIT_XDG_SUBDIR
#define INIT_XDG_SUBDIR "startup"
#endif

/**
 * INIT_XDG_SESSION_SUBDIR:
 *
 * Directory below XDG_RUNTIME_DIR/INIT_XDG_SUBDIR used to
 * store session details.
 **/
#ifndef INIT_XDG_SESSION_SUBDIR
#define INIT_XDG_SESSION_SUBDIR "sessions"
#endif


/**
 * SHELL:
 *
 * This is the shell binary used whenever we need special processing for
 * a command or when we need to run a script.
 **/
#ifndef SHELL
#define SHELL "/bin/sh"
#endif

/**
 * SBINDIR:
 *
 * Directory containing system binaries.
 **/
#ifndef SBINDIR
#define SBINDIR "/sbin"
#endif

/**
 * TELINIT:
 *
 * This is the telinit binary used when init is executed as an ordinary
 * process.
 **/
#ifndef TELINIT
#define TELINIT SBINDIR "/telinit"
#endif

/**
 * CONF_EXT_STD:
 *
 * File extension for standard configuration files.
 **/
#define CONF_EXT_STD ".conf"

/**
 * CONF_EXT_OVERRIDE:
 *
 * File extension for override files.
 *
 * Note that override files are not stored in the ConfSource 'files' hash:
 * all JobClass information from override files is added to the JobClass for
 * the corresponding (CONF_EXT_STD) object.
 **/
#define CONF_EXT_OVERRIDE ".override"

/**
 * SESSION_EXT:
 *
 * File extension for session files.
 **/
#ifndef SESSION_EXT
#define SESSION_EXT ".session"
#endif

/**
 * Determine if specified path extension representes a standard
 * configuration file.
 *
 * @period: pointer to last period in path to check.
 *
 * Returns 1 if specified path extension matches that for a
 * standard configuration file, else return 0.
 **/
#define IS_CONF_EXT_STD(period) \
	(!strcmp (period, CONF_EXT_STD))

/**
 * Determine if specified path extension representes an
 * override file.
 *
 * @period: pointer to last period in path to check.
 *
 * Returns 1 if specified path extension matches that for
 * an override file, else return 0.
 **/
#define IS_CONF_EXT_OVERRIDE(period) \
	(!strcmp (period, CONF_EXT_OVERRIDE))

/**
 * Determine if specified filename has a valid configuration
 * file name extension.
 *
 * @period: pointer to last period in filename.
 *
 * Returns: TRUE if extension beyond @period is one of the
 * recognized types, else FALSE.
 **/
#define IS_CONF_EXT(period) \
	(IS_CONF_EXT_STD(period) || \
	 IS_CONF_EXT_OVERRIDE(period))

#endif /* INIT_PATHS_H */
