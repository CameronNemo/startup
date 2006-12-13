/* libnih
 *
 * test_signal.c - test suite for nih/signal.c
 *
 * Copyright © 2006 Scott James Remnant <scott@netsplit.com>.
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

#include <signal.h>

#include <nih/macros.h>
#include <nih/list.h>
#include <nih/signal.h>


static void
my_sig_handler (int signum) {
}

void
test_set_handler (void)
{
	struct sigaction act;
	int              ret, i;

	/* Check that we can install a signal handler, and that the action
	 * for that signal points to our handler, has the right flags and
	 * an empty signal mask.
	 */
	TEST_FUNCTION ("nih_signal_set_handler");
	ret = nih_signal_set_handler (SIGUSR1, my_sig_handler);

	TEST_EQ (ret, 0);

	sigaction (SIGUSR1, NULL, &act);
	TEST_EQ_P (act.sa_handler, my_sig_handler);
	TEST_TRUE (act.sa_flags & SA_RESTART);
	TEST_FALSE (act.sa_flags & SA_RESETHAND);

	for (i = 1; i < 32; i++)
		TEST_FALSE (sigismember (&act.sa_mask, i));
}

void
test_set_default (void)
{
	struct sigaction act;
	int              ret, i;

	/* Check that we can reset a signal to the default handling, which
	 * should update the action properly.
	 */
	TEST_FUNCTION ("nih_signal_set_default");
	ret = nih_signal_set_default (SIGUSR1);

	TEST_EQ (ret, 0);

	sigaction (SIGUSR1, NULL, &act);
	TEST_EQ_P (act.sa_handler, SIG_DFL);
	TEST_FALSE (act.sa_flags & SA_RESTART);
	TEST_FALSE (act.sa_flags & SA_NOCLDSTOP);

	for (i = 1; i < 32; i++)
		TEST_FALSE (sigismember (&act.sa_mask, i));
}

void
test_set_ignore (void)
{
	struct sigaction act;
	int              ret, i;

	/* Check that we can set a signal to be ignored, which should update
	 * the action properly.
	 */
	TEST_FUNCTION ("nih_signal_set_ignore");
	ret = nih_signal_set_ignore (SIGUSR1);

	TEST_EQ (ret, 0);

	sigaction (SIGUSR1, NULL, &act);
	TEST_EQ_P (act.sa_handler, SIG_IGN);
	TEST_FALSE (act.sa_flags & SA_RESTART);
	TEST_FALSE (act.sa_flags & SA_NOCLDSTOP);

	for (i = 1; i < 32; i++)
		TEST_FALSE (sigismember (&act.sa_mask, i));
}

void
test_reset (void)
{
	struct sigaction act;
	int              i;

	/* Check that we can reset all signals back to their defaults. */
	TEST_FUNCTION ("nih_signal_reset");
	nih_signal_set_ignore (SIGTERM);
	nih_signal_reset ();

	sigaction (SIGTERM, NULL, &act);
	TEST_EQ_P (act.sa_handler, SIG_DFL);
	TEST_FALSE (act.sa_flags & SA_RESTART);
	TEST_FALSE (act.sa_flags & SA_NOCLDSTOP);

	for (i = 1; i < 32; i++)
		TEST_FALSE (sigismember (&act.sa_mask, i));
}


static int handler_called = 0;
static void *last_data;
static NihSignal *last_signal;

static void
my_handler (void *data, NihSignal *signal)
{
	handler_called++;
	last_data = data;
	last_signal = signal;
}

void
test_add_handler (void)
{
	NihSignal *signal;

	/* Check that we can add a signal handling callback function, and
	 * that the structure returned is properly populated and placed in
	 * the callbacks list.
	 */
	TEST_FUNCTION ("nih_signal_add_handler");
	signal = nih_signal_add_handler (NULL, SIGUSR1, my_handler, &signal);

	TEST_ALLOC_SIZE (signal, sizeof (NihSignal));
	TEST_LIST_NOT_EMPTY (&signal->entry);
	TEST_EQ (signal->signum, SIGUSR1);
	TEST_EQ_P (signal->handler, my_handler);
	TEST_EQ_P (signal->data, &signal);

	nih_list_free (&signal->entry);
}

void
test_poll (void)
{
	NihSignal *signal1, *signal2;

	TEST_FUNCTION ("nih_signal_poll");
	signal1 = nih_signal_add_handler (NULL, SIGUSR1, my_handler, &signal1);
	signal2 = nih_signal_add_handler (NULL, SIGUSR2, my_handler, &signal2);

	/* Check that we can poll for a signal being caught, which should
	 * result in only the callback for that signal being run.
	 */
	TEST_FEATURE ("with one signal");
	handler_called = 0;
	last_data = NULL;
	last_signal = NULL;

	nih_signal_handler (SIGUSR1);
	nih_signal_poll ();

	TEST_EQ (handler_called, 1);
	TEST_EQ_P (last_signal, signal1);
	TEST_EQ_P (last_data, &signal1);


	/* Check that we can poll for only the other signal. */
	TEST_FEATURE ("with different signal");
	handler_called = 0;
	last_data = NULL;
	last_signal = NULL;

	nih_signal_handler (SIGUSR2);
	nih_signal_poll ();

	TEST_EQ (handler_called, 1);
	TEST_EQ_P (last_signal, signal2);
	TEST_EQ_P (last_data, &signal2);


	/* Check that we can poll for both signals. */
	TEST_FEATURE ("with multiple signals");
	handler_called = 0;

	nih_signal_handler (SIGUSR1);
	nih_signal_handler (SIGUSR2);
	nih_signal_poll ();

	TEST_EQ (handler_called, 2);


	/* Check what happens if a signal we have no callbacks for is
	 * caught.  This should run neither callback.
	 */
	TEST_FEATURE ("with unknown signal");
	handler_called = 0;

	nih_signal_handler (SIGINT);
	nih_signal_poll ();

	TEST_EQ (handler_called, 0);
}


int
main (int   argc,
      char *argv[])
{
	test_set_handler ();
	test_set_default ();
	test_set_ignore ();
	test_reset ();
	test_add_handler ();
	test_poll ();

	return 0;
}
