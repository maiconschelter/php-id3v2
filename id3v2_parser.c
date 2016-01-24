#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "php_id3v2.h"

zend_class_entry *php_id3v2_ce;
static zend_object_handlers id3v2_handlers;

static PHP_METHOD(ID3v2, __construct)
{
	id3v2_object *objval = (id3v2_object*) Z_OBJ_HT_P(getThis());
	char *file;
	int file_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &file, &file_len) == FAILURE)
	{
		return;
	}
	objval->file_name = estrndup(file, file_len);
}

static PHP_METHOD(ID3v2, setFilePath)
{
	id3v2_object *objval = (id3v2_object*) Z_OBJ_HT_P(getThis());
	char *file;
	int file_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &file, &file_len)  == FAILURE)
	{
		return;
	}
	if(objval->file_name) efree(objval->file_name);
	objval->file_name = estrndup(file, file_len);
}

static PHP_METHOD(ID3v2, getFilePath)
{
	id3v2_object *objval = (id3v2_object*) Z_OBJ_HT_P(getThis());
	if(objval->file_name)
	{
		RETURN_STRING(objval->file_name, 1);
	}
	else
	{
		RETURN_FALSE;
	}
}

static zend_function_entry id3v2_methods[] = {
	PHP_ME(ID3v2, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(ID3v2, setFilePath, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(ID3v2, getFilePath, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

static void id3v2_destroy(id3v2_object *objval)
{
	if(objval->file_name) efree(objval->file_name);
	zend_object_std_dtor(&(objval->tag));
	efree(objval);
}

static zend_object_value id3v2_object_create(zend_class_entry *ce)
{
	id3v2_object *objval;
	zend_object_value retval;

	objval = ecalloc(1, sizeof(id3v2_object));
	objval->tag.ce = ce;
	ALLOC_HASHTABLE(objval->tag.properties);
	zend_hash_init(objval->tag.properties, 0, NULL, ZVAL_PTR_DTOR, 0);

	retval.handle = zend_objects_store_put(objval, NULL, NULL, NULL);
	retval.handlers = &id3v2_handlers;

	return retval;
}

int id3v2_init(INIT_FUNC_ARGS)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "ID3v2", id3v2_methods);
	php_id3v2_ce = zend_register_internal_class(&ce);
	php_id3v2_ce->create_object = id3v2_object_create;

	memcpy(&id3v2_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	zend_declare_class_constant_long(php_id3v2_ce, "BLUES", strlen("BLUES"), 0);

	return SUCCESS;
}