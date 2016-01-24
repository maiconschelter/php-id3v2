dnl $id$
dnl config.m4 for extension id3v2

PHP_ARG_ENABLE(id3v2, whether to enable id3v2 support,
[  --enable-id3v2	Enable id3v2 support])

if test "$PHP_ID3V2" = "yes"; then
	PHP_NEW_EXTENSION(id3v2, php_id3v2.c id3v2_parser.c, $ext_shared)
fi