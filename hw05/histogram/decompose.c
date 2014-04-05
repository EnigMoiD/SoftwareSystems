#include <glib.h>

int main(int argc, char const *argv[])
{
	GError *channel_error = NULL;
	GIOChannel *channel = g_io_channel_new_file("great.txt",
		"r",
		&channel_error);

	g_print("GIOChannel Status: %d\n", channel_error);

	gchar* book = NULL;
	gsize length = NULL;
	GError *book_error = NULL;
	g_io_channel_read_to_end(channel, &book, &length, &book_error);

	g_print("GIOChannel Read Status: %d\n", book_error);
}