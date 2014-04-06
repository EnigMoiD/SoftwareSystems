#include <glib.h>
#include <stdlib.h>
#include <string.h>

GTree *make_histogram(char** words);
gboolean print_entry(gpointer key, gpointer value, gpointer user_data);

int main(int argc, char const *argv[])
{
	GError *channel_error = NULL;
	GIOChannel *channel = g_io_channel_new_file("great.txt", "r", &channel_error);

	g_print("GIOChannel Status: %d\n", (gint)channel_error);

	gchar* book = NULL;
	gsize length = 0;
	GError *book_error = NULL;
	g_io_channel_read_to_end(channel, &book, &length, &book_error);
	g_print("GIOChannel Read Status: %d\n", (gint)book_error);

	g_print("Begin tokenizing.\n");
	char **words = g_str_tokenize_and_fold(book, "en", NULL);

	GTree *histogram = make_histogram(words);

	g_print("Frequency of words in \"Inventions of the Great War\"\n");
	g_tree_foreach(histogram, print_entry, NULL);

	g_print("Number of Nodes: %d\n", g_tree_nnodes(histogram));
}

gboolean print_entry(gpointer key, gpointer value, gpointer data) {
	g_print("%s: %d\n", key, (gint)value);

	return 0;
}

// Takes an array of words
// Returns a Tree with words as keys and wods frequency as values
GTree *make_histogram(char** words) {
	GTree *table = g_tree_new(strcmp);

	for (int i = 0; words[i] != 0; ++i)
	{
		gpointer value = g_tree_lookup(table, words[i]);
		if (value != NULL)
			g_tree_insert(table, words[i], value + 1);
		else
			g_tree_insert(table, words[i], 1);
	}
	return table;
}