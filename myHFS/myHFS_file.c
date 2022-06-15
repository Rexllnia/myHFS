#include "myHFS_file.h"



void get_dir(char *List)
{
    //struct dirent *ptr;
		FILINFO ptr;
    DIR dir;
		
    //dir = opendir("./FILE");
		f_opendir (&dir,"FILE");
		f_readdir (&dir, &ptr);
		sprintf(List, "");
    while (ptr.fname[0]!=0)
    {
				
//        sprintf(List, "%s%s\n", List, ptr.fname);
				sprintf(List, "%s<br><a href=\" %s\">%s %d</a></br>\n", List, ptr.fname, ptr.fname,ptr.fsize);
				f_readdir (&dir, &ptr);
				
    }
    f_closedir(&dir);
}
//int GetFILEsize(char *path)
//{
//    int size = 0;
//    FIL *fp;
////    fp = fopen(path, "rb");
//		while(f_open(fp,"FILE/add1.txt",FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK);
////    fseek(fp, 0, SEEK_END);
//	f_lseek(fp, );
//    size = ftell(fp);
//    rewind(fp);

//    fclose(fp);
//    return size;
//}
