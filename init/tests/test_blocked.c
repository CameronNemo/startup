/* upstart
 *
 * test_blocked.c - test suite for init/blocked.c
 *
 * Copyright © 2008 Canonical Ltd.
 * Author: Scott James Remnant <scott@netsplit.com>.
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

#include <nih/test.h>

#include <nih/dbus.h>

#include "job_class.h"
#include "job.h"
#include "event.h"
#include "blocked.h"



void
test_new (void)
{
	Blocked        *blocked;
	JobClass       *class;
	Job            *job;
	Event          *event;
	NihDBusMessage *message;

	TEST_FUNCTION ("blocked_new");

	/* Check that we can create a new blocked record for a job, with the
	 * details filled in correctly.  The returned structure should not be
	 * in a list.
	 */
	TEST_FEATURE ("with job");
	class = job_class_new (NULL, "test");
	job = job_new (class, "");

	TEST_ALLOC_FAIL {
		blocked = blocked_new (NULL, BLOCKED_JOB, job);

		if (test_alloc_failed) {
			TEST_EQ_P (blocked, NULL);
			continue;
		}

		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_LIST_EMPTY (&blocked->entry);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);

		nih_free (blocked);
	}

	nih_free (class);


	/* Check that we can create a new blocked record for an event, with
	 * the details filled in correctly.  The returned structure should
	 * not be in a list.
	 */
	TEST_FEATURE ("with event");
	event = event_new (NULL, "foo", NULL);

	TEST_ALLOC_FAIL {
		blocked = blocked_new (NULL, BLOCKED_EVENT, event);

		if (test_alloc_failed) {
			TEST_EQ_P (blocked, NULL);
			continue;
		}

		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_LIST_EMPTY (&blocked->entry);
		TEST_EQ (blocked->type, BLOCKED_EVENT);
		TEST_EQ_P (blocked->event, event);

		nih_free (blocked);
	}

	nih_free (event);


	/* Check that we can create a new blocked record for a D-Bus message,
	 * with the details filled in correctly.  The returned structure should
	 * not be in a list.
	 */
	TEST_FEATURE ("with D-Bus message");
	message = nih_new (NULL, NihDBusMessage);
	message->conn = NULL;
	message->message = NULL;

	TEST_ALLOC_FAIL {
		blocked = blocked_new (NULL, BLOCKED_MESSAGE, message);

		if (test_alloc_failed) {
			TEST_EQ_P (blocked, NULL);
			continue;
		}

		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_LIST_EMPTY (&blocked->entry);
		TEST_EQ (blocked->type, BLOCKED_MESSAGE);
		TEST_EQ_P (blocked->message, message);

		nih_free (blocked);
	}

	nih_free (message);
}


int
main (int   argc,
      char *argv[])
{
	test_new ();

	return 0;
}