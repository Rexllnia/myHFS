//#include "myHFS_tcp.h"
//int tcp_bind(int listen_fd, short port)
//{
//    struct sockaddr_in client_addr;
//    int n;
//    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//    {
//        printf("Socket Error:%s\n\a", strerror(errno));
//        exit(1);
//    }

//    bzero(&client_addr, sizeof(struct sockaddr_in));
//    client_addr.sin_family = AF_INET;
//    client_addr.sin_port = htons(port);
//    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    n = 1;
//    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(int));
//    if (bind(listen_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
//    {
//        printf("Bind Error:%s\n\a", strerror(errno));
//        exit(1);
//    }
//    return listen_fd;
//}
//void SEND_FILE(int accept_fd, char *path)
//{
//    FILE *fp;
//    int buf[2000];
//    // char *buf;
//    int position = 0, size = 0;
//    fp = fopen(path, "rb");
//    fseek(fp, 0, SEEK_END);
//    size = ftell(fp);
//    printf("%d", size);
//    
//    rewind(fp);

//    while (ftell(fp) < size - 1)
//    {

//        fread(buf, 1, 1999, fp);
//        write(accept_fd, buf, 1999);
//    }
//    fclose(fp);
//}