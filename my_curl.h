#ifndef MY_CURL_H
#define MY_CURL_H
    #include <stdlib.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <sys/socket.h> 
    #include <unistd.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    #include <string.h>
    #include <errno.h>
    #include <netdb.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    // (HTTP) runs on TCP port 80
    #define HTTP_PORT 80
    #define HTTP "http://"
    #define MAX_BUFFER_SIZE 1023


    /* DOMAIN HELPER FUNCTIONS */
    char*   get_resource(char* domain, const char* url);
    char*   get_domain(const char* url);

    /* REQUEST RELATED FUNCTIONS */
    int     create_socket();
    void    read_socket(int socket_fd);
    int     write_http_request(int socket_fd, char* domain, char* resource);
    int     my_curl(char *url);
#endif