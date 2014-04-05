#include <glib.h>

int main(int argc, char const *argv[])
{
	GError *channel_error = NULL;
	GIOChannel *channel = g_io_channel_new_file("great.txt",
		"r",
		&channel_error);

	g_print("GIOChannel Status: %d\n", channel_error);

	gsize buff_size = 100000;
	gchar* book = malloc(buff_size * sizeof(gchar));
	gsize read = NULL;
	GError *book_error = NULL;
	g_io_channel_read_chars(channel, book, buff_size, &read, &book_error);
	g_print("%s\n", book);

	g_print("GIOChannel Read Status: %d\n", book_error);
}