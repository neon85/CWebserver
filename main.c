#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>

#include "getcontenttype.c"

#define port 8080


// Short Version of getContentType()
/*
char* getContentType(char *path) {
    int len;
    int temp = 1;
    char filename[512];
    char ext[16];
    // get filename
    while(temp < strlen(path)) {
        len = temp;
        temp += strcspn(path+temp+1, "/") + 1;
    }
    strcpy(filename, path+len+1);

    // get Extension
    if ( (len = strcspn(filename, ".")) != strlen(filename) ) {
        len += 1;
        strcpy(ext, &filename[len]);
    }

    if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm")) {
        return "Content-Type: text/html\r\n\r\n";
    } else if (strcmp(ext, ".js") == 0) {
        return "Content-Type: text/javascript\r\n\r\n";
    } else if (strcm(ext, "json") == 0) {
        return "Content-Type: application/json\r\n\r\n";
    } else if (strcmp(ext, ".png") == 0) {
        return "Content-Type: image/png\r\n\r\n";
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        return "Content-Type: image/jpeg\r\n\r\n";
    } else if (strcmp(ext, ".mp3") == 0) {
        return "Content-Type: audio/mpeg\r\n\r\n";
    } else if (strcmp(ext, ".mp4") == 0) {
        return "Content-Type: video/mp4"\r\n\r\n";
    } else {
        return "Content-Type: text/plain\r\n\r\n";
    }
}
*/

void notFound(int client_sock) {
    char *res = 
        "HTTP/1.1 404 NotFound\r\n"
        "Connection: Closed\r\n\r\n"
        "<html><h1>404 NotFound</h1></html>";

    write(client_sock, res, strlen(res));
    close(client_sock);
}

void retFile(int client_socket, char *abs_path) {
    printf("File Detected\n");
    FILE *fd;
    char temp[64];
    unsigned file_size;
    char *resHeader =
        "HTTP/1.1 200 OK\r\n"
        "Server: SimpleCServer\r\n";

    printf("Open File: %s\n", abs_path);
    fd = fopen(abs_path, "rb");
    if (fd == NULL) {
        perror("ERROR");
        notFound(client_socket);
    } else {
        fseek(fd, 0L, SEEK_END);
        file_size = ftell(fd);
        rewind(fd);
        char *file_buf = malloc(file_size);
        fread(file_buf, file_size, 1, fd);
        fclose(fd);

        write(client_socket, resHeader, strlen(resHeader));
        sprintf(temp, "Content-Length: %u\r\n", file_size);
        write(client_socket, temp, strlen(temp));

        strcpy(temp, getContentType(abs_path));
        printf("TYPE -> %s\n", temp);
        write(client_socket, temp, strlen(temp));

        write(client_socket, file_buf, file_size);

        free(file_buf);
        close(client_socket);
    }
}

int main(void) {
    int rsock, wsock;
    struct sockaddr_in addr, client;
    unsigned len;
    int ret;
    char cwd[PATH_MAX];

    getcwd(cwd, sizeof(cwd));
    printf("Current Directory: %s\n", cwd);
    rsock = socket(AF_INET, SOCK_STREAM, 0);

    if (rsock < 0) {
        fprintf(stderr, "Error. Cannot make socket\n");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(rsock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        fprintf(stderr, "Error. Cannot bind socket\n");
        return 1;
    }

    listen(rsock, 10);
    printf("Listening at %d\n", port);


    while (1) {
        len = sizeof(client);
        if ((wsock = accept(rsock, (struct sockaddr *)&client, &len)) < 0) {
            perror("Accept Failed\n");
            continue;
        }
        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);
        printf("Incomming Connection from %s:%d\n", client_ip, client_port);
        char *req_buff = calloc(2048, sizeof(char));

        int  r_size = recv(wsock, req_buff, 2048, 0);

        printf("Accepted data size: %d\n", r_size);
        printf("[Request Header]\n'%s'\n", req_buff);

        char *ptr = req_buff; // pointer for query
        // Read first line to req_buff
        printf("req_buff =\n%s\n", req_buff);
        int mem_len = strcspn(ptr, " ");

        char method[16];
        if (mem_len < sizeof(method)) {
            strncpy(method, ptr, mem_len);
            method[mem_len] = '\0';
            printf("method = %s\n", method);
        }

        ptr += mem_len + 1;
        mem_len = strcspn(ptr, " ");

        char path[2048];
        if (mem_len < sizeof(path)) {
            strncpy(path, ptr, mem_len);
            path[mem_len] = '\0';
            printf("Path = %s\n", path);
        }
        free(req_buff);

        char abs_path[PATH_MAX];
        strcpy(abs_path, cwd);
        strcat(abs_path, path);

        // if file exists
        if ( strlen(method) != 0 && strlen(path) != 0 && access(abs_path, F_OK) != -1 ) {
            printf("File Exists\n");
            char *resHeader = 
                "HTTP/1.1 200 OK\r\n"
                "Server: SimpleCServer\r\n";
            struct stat path_stat;
            stat(abs_path, &path_stat);

            // if the path is Directory
            if (S_ISDIR(path_stat.st_mode)){
                printf("Directory Detected\n");
                DIR *dir;
                struct dirent *ent;
                char temp[512] = "Content-Type: text/html\r\n\r\n";
                int dir_len = strlen(abs_path);

                printf("Directory path  = %s\n", abs_path);
                strcat(abs_path, "/index.html");
                // If found index.html in directory
                if (access(abs_path, F_OK) != -1) {
                    retFile(wsock, abs_path);
                    continue;
                }
                printf("index.html not found in directory\n");
                abs_path[dir_len] = '\0';

                if ((dir = opendir(abs_path)) == NULL) {
                    perror("ERROR");
                    notFound(wsock);
                    continue;
                } else {
                    write(wsock, resHeader, strlen(resHeader));
                    write(wsock, temp, strlen(temp));
                    strcpy(temp, "<html><body><ul>");
                    write(wsock, temp, strlen(temp));
                    while((ent = readdir(dir)) != NULL) {
                        printf("File Found: %s\n", ent->d_name);
                        strcpy(temp, "<li><a href=\"");
                        strcat(temp, path+1);
                        strcat(temp, "/");
                        strcat(temp, ent->d_name);
                        strcat(temp, "\">");
                        strcat(temp, ent->d_name);
                        strcat(temp, "</a></li>");
                        write(wsock, temp, strlen(temp));
                    }
                    strcpy(temp, "</ul></body></html>");
                    write(wsock, temp, strlen(temp));

                    closedir(dir);
                    close(wsock);
                    continue;
                }
            }

            retFile(wsock, abs_path);
            continue;
        } else {
            printf("The File does not exist\n");
            notFound(wsock);
            continue;
        }

        printf("Unwelcome request\n");
        char *forbidden =
            "HTTP/1.1 403 Forbidden\r\n"
            "Connection: Closed\r\n\r\n"
            "<html><h1>403 Forbidden<h1></html>";
        write(wsock, forbidden, strlen(forbidden));
        close(wsock);
    }

    close(rsock);

    return 0;
}
