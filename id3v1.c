#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gostmain(int argc, char **argv)
{
	char id3[128];
	char *fileName = "/home/maicon/Documents/Projects/PHPExt/PHPId3/VivaRevol.mp3";
	FILE *file = fopen(fileName, "rb");
	if(!file){
		printf("Não foi possível encontrar o arquivo: %s.\n", fileName);
		exit(EXIT_FAILURE);
	}
	if(fseek(file, -128, SEEK_END) == 0 && fread(id3, 128, 1, file) != 1){
		printf("Não ler o arquivo: %s.\n", fileName);
		exit(EXIT_FAILURE);
	}
	if(strncmp(id3, "ID3", 3) < 0){
		printf("Sem identificação para o arquivo: %s.\n", fileName);
		exit(EXIT_FAILURE);
	}
	int result = get_tag_version(id3);
	unsigned char *text = id3 + 3;
	char title[31];
	char artist[31];
	char album[31];
	char year[5];
	char comment[31];
	char genre[31];
	memcpy(title, text, 30);
	title[30] = '\0';
	text += 30;
	printf("Título: %s.\n", title);
	memcpy(artist, text, 30);
	artist[30] = '\0';
	text += 30;
	printf("Artista: %s.\n", artist);
	memcpy(album, text, 30);
	album[30] = '\0';
	text += 30;
	printf("Album: %s.\n", album);
	memcpy(year, text, 4);
	year[4] = '\0';
	text += 4;
	printf("Album: %s.\n", year);
	memcpy(comment, text, 30);
	comment[30] = '\0';
	text += 30;
	printf("Comentarios: %s.\n", comment);
	fclose(file);
	return EXIT_SUCCESS;
}