/* libnih
 *
 * test_logging.c - test suite for nih/logging.c
 *
 * Copyright © 2007 Scott James Remnant <scott@netsplit.com>.
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

#include <stdio.h>
#include <string.h>

#include <nih/macros.h>
#include <nih/alloc.h>
#include <nih/string.h>
#include <nih/logging.h>
#include <nih/main.h>


static NihLogLevel last_priority = NIH_LOG_UNKNOWN;
static char *last_message = NULL;

static int
my_logger (NihLogLevel  priority,
	   const char  *message)
{
	last_priority = priority;
	last_message = strdup (message);

	if (! strcmp (message, "this should error"))
		return -1;

	return 0;
}

void
test_set_logger (void)
{
	/* Check that we can change the logger function, and that the
	 * function is called for the logging macros that follow.
	 */
	TEST_FUNCTION ("nih_log_set_logger");
	nih_log_set_priority (NIH_LOG_MESSAGE);
	nih_log_set_logger (my_logger);

	last_priority = NIH_LOG_UNKNOWN;

	nih_fatal ("some message");

	TEST_EQ (last_priority, NIH_LOG_FATAL);

	free (last_message);

	nih_log_set_logger (nih_logger_printf);
}

void
test_set_priority (void)
{
	/* Check that we reduce the minimum priority and end up getting
	 * log messages we wouldn't have previously received.
	 */
	TEST_FUNCTION ("nih_log_set_priority");
	nih_log_set_logger (my_logger);
	nih_log_set_priority (NIH_LOG_DEBUG);

	last_priority = NIH_LOG_UNKNOWN;

	nih_debug ("some message");

	TEST_EQ (last_priority, NIH_LOG_DEBUG);

	free (last_message);

	nih_log_set_logger (nih_logger_printf);
	nih_log_set_priority (NIH_LOG_MESSAGE);
}

void
test_log_message (void)
{
	int ret;

	TEST_FUNCTION ("nih_log_message");
	nih_log_set_logger (my_logger);

	/* Check that a message with high enough priority makes it through
	 * to the logger.
	 */
	TEST_FEATURE ("with message of high enough priority");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_log_message (NIH_LOG_FATAL,
				       "message with %s %d formatting",
				       "some", 20);

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_FATAL);
		TEST_EQ_STR (last_message, "message with some 20 formatting");

		free (last_message);
	}


	/* Check that a message with insufficient priority does not make it
	 * through to the logger.
	 */
	TEST_FEATURE ("with message of insufficient priority");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_log_message (NIH_LOG_DEBUG, "not high enough");

		TEST_GT (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_UNKNOWN);
		TEST_EQ_P (last_message, NULL);
	}


	/* Check that an error code returned from the logger is returned
	 * by the function.
	 */
	TEST_FEATURE ("with error code returned from logger");
	ret = nih_log_message (NIH_LOG_FATAL, "this should error");

	TEST_LT (ret, 0);

	free (last_message);


	/* Check that the nih_debug macro wraps the call properly and
	 * includes the function in which the message occurred.
	 */
	TEST_FUNCTION ("nih_debug");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		nih_log_set_priority (NIH_LOG_DEBUG);

		ret = nih_debug ("%s debugging message", "a");

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_DEBUG);
		TEST_EQ_STR (last_message,
			     "test_log_message: a debugging message");

		free (last_message);
	}


	/* Check that the nih_info macro wraps the call properly. */
	TEST_FUNCTION ("nih_info");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_info ("%d formatted %s", 47, "message");

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_INFO);
		TEST_EQ_STR (last_message, "47 formatted message");

		free (last_message);
	}


	/* Check that the nih_warn macro wraps the call properly. */
	TEST_FUNCTION ("nih_warn");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_warn ("%d formatted %s", -2, "text");

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_WARN);
		TEST_EQ_STR (last_message, "-2 formatted text");

		free (last_message);
	}


	/* Check that the nih_message macro wraps the call properly.
	 */
	TEST_FUNCTION ("nih_message");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_message ("%d formatted %s", -24, "string");

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_MESSAGE);
		TEST_EQ_STR (last_message, "-24 formatted string");

		free (last_message);
	}


	/* Check that the nih_error macro wraps the call properly. */
	TEST_FUNCTION ("nih_error");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_error ("formatted %d %s", 42, "text");

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_ERROR);
		TEST_EQ_STR (last_message, "formatted 42 text");

		free (last_message);
	}


	/* Check that the nih_fatal macro wraps the call properly. */
	TEST_FUNCTION ("nih_fatal");
	TEST_ALLOC_FAIL {
		last_priority = NIH_LOG_UNKNOWN;
		last_message = NULL;

		ret = nih_fatal ("%s message %d", "formatted", 999);

		TEST_EQ (ret, 0);
		TEST_EQ (last_priority, NIH_LOG_FATAL);
		TEST_EQ_STR (last_message, "formatted message 999");

		free (last_message);
	}


	nih_log_set_priority (NIH_LOG_MESSAGE);
	nih_log_set_logger (nih_logger_printf);
}

void
test_logger_printf (void)
{
	FILE *output;
	int   ret = 0;

	TEST_FUNCTION ("nih_logger_printf");
	output = tmpfile ();
	program_name = "test";
	nih_log_set_priority (NIH_LOG_DEBUG);


	/* Check that a low priority message is output to stdout and formatted
	 * correctly, without the program name prefixed to the front.
	 */
	TEST_FEATURE ("with low priority message");
	TEST_DIVERT_STDOUT (output) {
		ret = nih_log_message (NIH_LOG_DEBUG,
				       "message with %s %d formatting",
				       "some", 20);
	}
	rewind (output);

	TEST_EQ (ret, 0);
	TEST_FILE_EQ (output, "message with some 20 formatting\n");
	TEST_FILE_END (output);

	TEST_FILE_RESET (output);


	/* Check that ordinary messages are output on stdout and formatted
	 * correctly, without the program name prefixed on the front.
	 */
	TEST_FEATURE ("with ordinary message");
	TEST_DIVERT_STDOUT (output) {
		ret = nih_log_message (NIH_LOG_MESSAGE,
				       "message with %s %d formatting",
				       "some", 20);
	}
	rewind (output);

	TEST_EQ (ret, 0);
	TEST_FILE_EQ (output, "message with some 20 formatting\n");
	TEST_FILE_END (output);

	TEST_FILE_RESET (output);


	/* Check that warning messages are output on stderr and formatted
	 * correctly, with the program name prefixed on the front.
	 */
	TEST_FEATURE ("with ordinary message");
	TEST_DIVERT_STDERR (output) {
		ret = nih_log_message (NIH_LOG_WARN,
				       "message with %s %d formatting",
				       "some", 20);
	}
	rewind (output);

	TEST_EQ (ret, 0);
	TEST_FILE_EQ (output, "test: message with some 20 formatting\n");
	TEST_FILE_END (output);

	TEST_FILE_RESET (output);


	/* Check that a high priority message is output to stderr and formatted
	 * correctly, with the program name prefixed on the front.
	 */
	TEST_FEATURE ("with high priority message");
	TEST_DIVERT_STDERR (output) {
		ret = nih_log_message (NIH_LOG_FATAL,
				       "%s message %d formatted",
				       "error", -1);
	}
	rewind (output);

	TEST_EQ (ret, 0);
	TEST_FILE_EQ (output, "test: error message -1 formatted\n");
	TEST_FILE_END (output);

	TEST_FILE_RESET (output);


	/* Check that a message with a GNU-style filename prefix is correctly
	 * formatted, with no space between the program name and the message.
	 */
	TEST_FEATURE ("with prefixed message");
	TEST_DIVERT_STDERR (output) {
		ret = nih_log_message (NIH_LOG_FATAL,
				       "%s:%d: some error or other",
				       "example.txt", 303);
	}
	rewind (output);

	TEST_EQ (ret, 0);
	TEST_FILE_EQ (output, "test:example.txt:303: some error or other\n");
	TEST_FILE_END (output);

	TEST_FILE_RESET (output);


	/* Check that an error code is returned if the output stream is
	 * closed.
	 */
	TEST_FEATURE ("with closed stream");
	TEST_DIVERT_STDERR (output) {
		close (STDERR_FILENO);

		ret = nih_log_message (NIH_LOG_FATAL, "an error message");
	}

	TEST_LT (ret, 0);


	fclose (output);
	nih_log_set_priority (NIH_LOG_MESSAGE);
}


int
main (int   argc,
      char *argv[])
{
	test_set_logger ();
	test_set_priority ();
	test_log_message ();
	test_logger_printf ();

	return 0;
}
