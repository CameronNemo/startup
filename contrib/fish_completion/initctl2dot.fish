# global options
complete -x -c initctl2dot -s f -l infile -d 'File to read initctl(8) output from instead of (initctl show-config -e)'
complete -f -c initctl2dot -s h -l help -d 'Display usage statement'
complete -x -c initctl2dot -s r -l restrict-to-jobs -d 'Comma-separated list of jobs to consider instead of all jobs'
complete -x -c initctl2dot -s w -l outfile -d 'File to write output to'
complete -x -c initctl2dot -l color-emits -d 'Color for "emits" lines'
complete -x -c initctl2dot -l color-start-on -d 'Color for "start on" lines'
complete -x -c initctl2dot -l color-stop-on -d 'Color for "stop on" lines'
complete -x -c initctl2dot -l color-event -d 'Color for event boxes'
complete -x -c initctl2dot -l color-text -d 'Color for text in summary'
complete -x -c initctl2dot -l color-bg -d 'Color for background of the diagram'
complete -x -c initctl2dot -l color-event-text -d 'Color for text for event boxes'
complete -x -c initctl2dot -l color-job-text -d 'Color for text in job boxes'
complete -x -c initctl2dot -l color-job -d 'Color for job boxes'
complete -f -c initctl2dot -l system -d 'Connect to the system session'
complete -f -c initctl2dot -l user -d 'Connect to the user session'
