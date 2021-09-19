" Vim syntax file
" Language:	Startup job files
" Maintainer:	Cameron Nemo
" Last Change:	2021 Sep 19
" License:	GPL v2
" Version:	0.6
" Remark:	Syntax highlighting for startup(8) job files.
"
" It is inspired by the initng syntax file and includes sh.vim to do the
" highlighting of script blocks.

if version < 600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif

let is_bash = 1
syn include @Shell syntax/sh.vim

syn case match

syn match startupComment /#.*$/ contains=startupTodo
syn keyword startupTodo TODO FIXME contained

syn region startupString start=/"/ end=/"/ skip=/\\"/

syn region startupScript matchgroup=startupStatement start="script" end="end script" contains=@startupShellCluster

syn cluster startupShellCluster contains=@Shell

" one argument
syn keyword startupStatement description author version instance expect
syn keyword startupStatement pid kill normal console env exit export
syn keyword startupStatement umask nice oom chroot chdir exec setuid setgid
syn keyword startupStatement usage

" two arguments
syn keyword startupStatement limit

" one or more arguments (events)
syn keyword startupStatement emits

syn keyword startupStatement on start stop

" flag, no parameter
syn keyword startupStatement respawn service instance manual debug task

" prefix for exec or script
syn keyword startupOption pre-start post-start pre-stop post-stop

" option for kill
syn keyword startupOption timeout signal
" option for oom
syn keyword startupOption score never
" options for console
syn keyword startupOption output owner none log
" options for expect
syn keyword startupOption stop fork daemon readyfd none
" options for limit
syn keyword startupOption unlimited core cpu data fsize memlock msgqueue nice
syn keyword startupOption nofile nproc rss rtprio sigpending stack

" 'options' for start/stop on
syn keyword startupOption and or

" Upstart itself and associated utilities
syn keyword startupEvent started
syn keyword startupEvent starting
syn keyword startupEvent startup
syn keyword startupEvent stopped
syn keyword startupEvent stopping
syn match   startupEvent /session-end/
syn match   startupEvent /control-alt-delete/
syn match   startupEvent /keyboard-request/
syn match   startupEvent /power-status-changed/

" Bridges
syn keyword startupEvent dbus
syn keyword startupEvent file
syn keyword startupEvent socket
syn match   startupEvent /\S*-device-\S*/

hi def link startupComment   Comment
hi def link startupTodo	     Todo
hi def link startupString    String
hi def link startupStatement Statement
hi def link startupOption    Type
hi def link startupEvent     Define

let b:current_syntax = "startup"
