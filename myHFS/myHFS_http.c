#include "myHFS_http.h"

void Create_header(char *buf, int code, char *info, char *filetype)
{
    sprintf(buf, "HTTP/1.1 %d %s\r\nContent-Type:%s\r\n\r\n", code, info, filetype);
}
void sned_header(char *buf,char *filename, int length)
{

	sprintf(buf,"HTTP/1.1 200 OK\r\nContent-Type:application/octet-stream\r\nContent-Length:%d\r\nAccept-Ranges: bytes\r\nContent-Disposition:attachment; filename=%s\r\n\r\n",length,filename);
	


}

char *get_mime_type(char *name)
{
    char *dot;
    dot = strrchr(name, '.');
    if (dot == (char *)0)
        return "text/plain;charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".hml") == 0)
        return "text/html;charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".c") == 0)
        return "text/html;charset=utf-8\r\nContent-Disposition:attachment;\r\n";
}