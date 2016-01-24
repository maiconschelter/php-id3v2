#ifndef PHP_ID3V2_H
#define PHP_ID3V2_H 1

#define PHP_ID3V2_VERSION "1.0.0"
#define PHP_ID3V2_EXTNAME "ID3v2"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry id3v2_module_entry;
#define phpext_id3v2_ptr &id3v2_module_entry

#define ID3v2_HEADER_SIZE 10
#define ID3v2_HEADER_NAME "ID3"

typedef struct _id3v2_object
{
	zend_object tag;

	char *file_name;

	char *artist;
	char *artist_participant;
	char *album;
	char *title;
	char *legend;
	char *composer;
	char *conductor;
	char *publisher;
	char *comments;
	char *copyright_message;
	char *lyrics;
	char *key;

	int *year;
	int *track_number;
	int *style;
	int *beats_per_minute;
} id3v2_object;

int id3v2_init(INIT_FUNC_ARGS);

#endif