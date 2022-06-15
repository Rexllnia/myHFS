#include "myHFS_html.h"

//void InitHTMLFILE(char *path)
//{
//	  UINT Br,Bw;
//		FILINFO ptr;
//    DIR dir;
//    FIL fp;
//    char buf[1024];
//    char *p1, *p2, *p3;
//    char href_dir_buf[11520];
// 
//		f_opendir (&dir,"FILE");
//		f_readdir (&dir, &ptr);
//		sprintf(href_dir_buf, "");
//    while (ptr.fname[0]!=0)
//    {
//				
//        sprintf(href_dir_buf, "%s%s\n", href_dir_buf, ptr.fname);
//				f_readdir (&dir, &ptr);
//				
//    }
//    f_closedir(&dir);
//    // ptr = readdir(dir);
////    f_readdir (&dir, &ptr);
////    sprintf(href_dir_buf, "<br>文件目录</br>\n");
////    while (ptr.fname[0]!=0)
////    {
////        if(strcmp(ptr.fname,".")>0&&strcmp(ptr.fname,"..")>0)
////        {
////            sprintf(href_dir_buf, "%s<br><a href=\" %s\">%s</a></br>\n", href_dir_buf, ptr.fname, ptr.fname);
////        }
////    }

////		f_closedir(&dir);
//    //printf("%s", p3);
//		 p3 = href_dir_buf;
//    while(f_open(&fp,path,FA_READ)!=FR_OK);
//		f_read (&fp, buf, sizeof(buf),&Br);
//    f_close(&fp);


//    //删除<!--myHFSdir.--><!--/myHFSdir.-->内容
//    p1 = strstr(buf, "<!--myHFSdir.-->");
//    p1 = p1 + 16;
//    while (p1 != strstr(buf, "<!--/myHFSdir.-->"))
//    {
//        strdelete(p1);
//    }
//    //printf("%s", buf);

//    //在<!--myHFSdir.-->后面插入
//    p1 = strstr(buf, "<!--myHFSdir.-->");
//    p1 = p1 + 15;
//    while (*p3 != '\0')
//    {
//        insert(p1++, *p3++);
//    }
//    //删除末尾乱码
//    p1 = strstr(buf, "</html>");
//    p1 += 7;
//    while (*p1 != '\0')
//    {
//        strdelete(p1);
//    }
//		
//		while(f_open(&fp,path,FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK);
//		f_write(&fp,buf,strlen(buf),&Bw);

//    f_close(&fp);
//}
