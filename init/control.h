/* upstart
 *
 * Copyright © 2007 Canonical Ltd.
 * Author: Scott James Remnant <scott@ubuntu.com>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef INIT_CONTROL_H
#define INIT_CONTROL_H

#include <nih/macros.h>
#include <nih/io.h>


NIH_BEGIN_EXTERN

/* The control socket */
NihIo *control_io;


NihIo *control_open            (void)
	__attribute__ ((warn_unused_result, malloc));
void   control_close           (void);

void   control_send_job_status (pid_t pid, Job *job);
void   control_send_instance   (pid_t pid, Job *job);

NIH_END_EXTERN

#endif /* INIT_CONTROL_H */
