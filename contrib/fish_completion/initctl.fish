# Global options
complete -f -c initctl -l session -d 'Use existing session D-Bus session (for testing)'
complete -f -c initctl -l system -d 'Use system D-Bus'
complete -x -c initctl -l dest -d 'Name for the Startup daemon in system D-Bus'
complete -f -c initctl -l user -d 'Run in user mode'
complete -f -c initctl -s q -l quiet -d 'Only output errors'
complete -f -c initctl -s v -l verbose -d 'Include informational messages'
complete -f -c initctl -l help -d 'Show help'
complete -f -c initctl -l version -d 'Output version information'

# Job commands
complete -f -c initctl -n __fish_use_subcommand -a start -d 'Start job'
complete -f -c initctl -n __fish_use_subcommand -a stop -d 'Stop job'
complete -f -c initctl -n __fish_use_subcommand -a restart -d 'Restart job'
complete -f -c initctl -n __fish_use_subcommand -a reload -d 'Reload job'
complete -f -c initctl -n __fish_use_subcommand -a status -d 'Query status of job'
complete -f -c initctl -n __fish_use_subcommand -a list -d 'List known jobs'

# Event commands
complete -f -c initctl -n __fish_use_subcommand -a emit -d 'Emit an event'

# Environment commands
complete -f -c initctl -n __fish_use_subcommand -a get-env -d 'Retrieve value of a job environment variable'
complete -f -c initctl -n __fish_use_subcommand -a list-env -d 'Show all job environment variables'
complete -f -c initctl -n __fish_use_subcommand -a reset-env -d 'Revert all job environment variable changes'
complete -f -c initctl -n __fish_use_subcommand -a set-env -d 'Set one or more job environment variables'
complete -f -c initctl -n __fish_use_subcommand -a unset-env -d 'Remove one or more job environment variables'

# Other commands
complete -f -c initctl -n __fish_use_subcommand -a reload-configuration -d 'Reload init daemon configuration'
complete -f -c initctl -n __fish_use_subcommand -a version -d 'Request version of the init daemon'
complete -f -c initctl -n __fish_use_subcommand -a log-priority -d 'Change minimum priority of log messages from init daemon'
complete -f -c initctl -n __fish_use_subcommand -a show-config -d 'Show emits, start on and stop on defaults for a job'
complete -f -c initctl -n __fish_use_subcommand -a check-config -d 'Check for unreachable jobs/event conditions'
complete -f -c initctl -n __fish_use_subcommand -a usage -d 'Show job usage message if available'
complete -f -c initctl -n __fish_use_subcommand -a notify-cgroup-manager-address -d 'Inform daemon of D-Bus address cgroup manager is available on'
complete -f -c initctl -n __fish_use_subcommand -a notify-dbus-address -d 'Inform daemon D-Bus address to connect to'
complete -f -c initctl -n __fish_use_subcommand -a notify-disk-writeable -d 'Inform daemon that disk is now writeable'
complete -f -c initctl -n __fish_use_subcommand -a list-sessions -d 'List all sessions'
complete -f -c initctl -n __fish_use_subcommand -a re-exec -d 'Perform stateful re-exec'
complete -f -c initctl -n __fish_use_subcommand -a help -d 'Display list of commands'

# -n|--no-wait for some of the Job commands
complete -f -c initctl -n "__fish_seen_subcommand_from start stop restart emit" -s n -l no-wait -d 'Do not wait for action to return'

# -r|--retain for some of the Environment commands
complete -f -c initctl -n "__fish_seen_subcommand_from set-env unset-env reset-env" -s r -l retain -d 'Do not modify already set variables'

# Offer all 'stop/waiting' jobs with 'start' subcommand
complete -f -c initctl -n "__fish_seen_subcommand_from start" -a "(__fish_initctl_run list | string match --entire stop/waiting | string split ' ' -f 1)" -d Job

# Offer all 'start/*' jobs with 'stop', 'reload' and 'restart' subcommands
complete -f -c initctl -n "__fish_seen_subcommand_from stop reload restart" -a "(__fish_initctl_run list | string match --entire start/running | string split ' ' -f 1)" -d Job

# Offer all jobs with its status to the 'status' subcommand
complete -f -c initctl -n "__fish_seen_subcommand_from status" -a "(__fish_initctl_list_with_status)"

# Offer all jobs to the 'check-config' subcommand
complete -f -c initctl -n "__fish_seen_subcommand_from check-config" -a "(__fish_initctl_run list | string split ' ' -f 1)" -d Job

# Offer all envs from 'list-env' subcommand to 'get-env' and 'unset-env'
complete -f -c initctl -n "__fish_seen_subcommand_from get-env unset-env" -a "(__fish_initctl_run list-env | string replace -r '=' '\tVariable: ')"

# Possible priority levels for 'log-priority' subcommand
complete -f -c initctl -n "__fish_seen_subcommand_from log-priority" -a "debug info message warn error fatal" -d 'Priority'

# -e|--enumerate option for 'show-config' subcommand
complete -f -c initctl -n "__fish_seen_subcommand_from show-config" -s e -l enumerate -d 'Print per line each "start on" and "stop on" condition for each event or job'

# -i|--ignore-events and -w|--warn for 'check-config' subcommand
complete -x -c initctl -n "__fish_seen_subcommand_from check-config" -s i -l ignore-events -d 'Comma-separated list of events to ignore'
complete -f -c initctl -n "__fish_seen_subcommand_from check-config" -s w -l warn -d 'treat any unknown jobs and events as errors'

# Show all the events from 'emits' in configuration to emit
complete -x -c initctl -n "__fish_seen_subcommand_from emit" -a "(__fish_initctl_get_events)" -d 'Event'

function __fish_initctl_context -d 'Get the current startup context based on the commandline'
	if __fish_seen_argument -l user
		echo -- user
	else if __fish_seen_argument -l session
		echo -- session
	else if __fish_seen_argument -l system
		echo -- system
	else if set -q UPSTART_SESSION
		echo -- user
	else
		echo -- system
	end
end

function __fish_initctl_run -d 'Run initctl with the appropriate context'
	initctl --(__fish_initctl_context) $argv
end

function __fish_initctl_list_with_status -d 'Get Job and status from initctl'
	__fish_initctl_run list \
		| cut -d ' ' -f 1-2 \
		| string replace -r ',$' '' \
		| string replace -r ' ' '\tJob: '
end

function __fish_initctl_extract_events -d 'Extract emitted events from job configuration'
	grep -E '^[[:space:]]*emits ' $argv/*.conf \
	| cut -d : -f 2- \
	| string replace 'emits ' '' \
	| string replace ' ' \n \
	| sort -u
end

function __fish_initctl_get_events -d 'Print all events that jobs in the current context emit'
	switch (__fish_initctl_context)
		case system
			__fish_initctl_extract_events /etc/startup /etc/init /usr/share/startup
		case user session
			set -l dirs
			if set -q XDG_CONFIG_HOME
				set -a dirs $XDG_CONFIG_HOME/startup
				set -a dirs $XDG_CONFIG_HOME/upstart
			else
				set -a dirs $HOME/.config/startup
				set -a dirs $HOME/.config/upstart
			end
			if set -q XDG_CONFIG_DIRS
				for d in (string replace : ' ' $XDG_CONFIG_DIRS)
					set -a dirs $d/startup
					set -a dirs $d/upstart
				end
			else
				set -a dirs /etc/xdg/startup
				set -a dirs /etc/xdg/upstart
			end
			# never implemented XDG_DATA_DIRS in the startup daemon
			set -a dirs /usr/share/xdg/startup
			__fish_initctl_extract_events $dirs
	end
end
