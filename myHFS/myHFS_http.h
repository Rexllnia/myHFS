#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void Create_header(char *buf, int code, char *info, char *filetype);
void sned_header(char *buf,char *filename, int length);
char *get_mime_type(char *name);
void get_GET_request(char buffer);