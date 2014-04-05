#include <glib.h>
#include <stdlib.h>

GHashTable *make_histogram(char** words);
void print_entry(gpointer key, gpointer value, gpointer user_data);

int main(int argc, char const *argv[])
{
	GError *channel_error = NULL;
	GIOChannel *channel = g_io_channel_new_file("great.txt", "r", &channel_error);

	g_print("GIOChannel Status: %d\n", channel_error);

	gchar* book = NULL;
	gsize length = NULL;
	GError *book_error = NULL;
	g_io_channel_read_to_end(channel, &book, &length, &book_error);
	g_print("GIOChannel Read Status: %d\n", book_error);

	g_print("Begin tokenizing.\n");
	char **words = g_str_tokenize_and_fold(book, "en", NULL);

	GHashTable *histogram = make_histogram(words);

	g_print("Frequency of words in \"Inventions of the Great War\"\n");
	g_hash_table_foreach(histogram, print_entry, NULL);
}

void print_entry(gpointer key, gpointer value, gpointer user_data) {
	g_print("%s: %d\n", key, value);
}

// Takes an array of words
// Returns a hashtable with words as keys and wods frequency as values
GHashTable *make_histogram(char** words) {
	GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

	for (int i = 0; words[i] != 0; ++i)
	{
		gpointer value = g_hash_table_lookup(table, words[i]);
		if (value != NULL)
			g_hash_table_insert(table, words[i], value + 1);
		else
			g_hash_table_insert(table, words[i], 1);
	}
	return table;
}