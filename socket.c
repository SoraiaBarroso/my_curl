#include "my_curl.h"

int create_socket() 
{
    int socket_fd = 0;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        perror("Socket()");
        return 1;
    } 
    
    return socket_fd;
}

int write_http_request(int socket_fd, char* domain, char* resource) 
{
    char request[1000];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", resource, domain);
        
    if (write(socket_fd, request, strlen(request)) == -1) {
        perror("Write failed");
        return 1;
    }

    free(domain);
    free(resource);
    return 0;
}

void read_socket(int socket_fd) 
{
    char buffer[MAX_BUFFER_SIZE];
    long bytes_part;
    unsigned long bytes_total    = 0;
    unsigned long content_length = 0;

    while ((bytes_part = read(socket_fd, buffer, MAX_BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_part] = '\0';

        if (content_length == 0) {
            char *cl_start = strstr(buffer, "Content-Length: ");

            if (cl_start != NULL) {
                cl_start += strlen("Content-Length: ");
                int i = 0;
                
                while(cl_start[i] >= '0' && cl_start[i] <= '9') {
                    content_length = content_length * 10 + (cl_start[i] - '0');
                    i++;
                }
            }

            char *content_start = strstr(buffer, "\r\n\r\n");
            if (content_start != NULL) {
                content_start += strlen("\r\n\r\n");
                bytes_total   += strlen(content_start);
                printf("%s", content_start);
            }
        } else {
            bytes_total += bytes_part;
            printf("%s", buffer);
        }

        if (bytes_part < MAX_BUFFER_SIZE) {
            if (bytes_total < content_length) {
                //sleep(1);
                continue;
            } else {
                break;
            }
        }
    }

    close(socket_fd);
}