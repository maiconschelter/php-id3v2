#include "php_id3v2.h"

static PHP_MINIT_FUNCTION(id3v2)
{
	return id3v2_init(INIT_FUNC_ARGS_PASSTHRU);
}

zend_module_entry id3v2_module_entry = {
	STANDARD_MODULE_HEADER,
	"id3v2",
	NULL,
	PHP_MINIT(id3v2),
	NULL,
	NULL,
	NULL,
	NULL,
	"1.0.0",
	STANDARD_MODULE_PROPERTIES,
};

#ifdef COMPILE_DL_ID3V2
ZEND_GET_MODULE(id3v2)
#endif