#include "my_curl.h"

int my_curl(char *url) 
{
    char *domain = NULL, *resource = NULL;
    domain    =  get_domain(url);
    resource  =  get_resource(domain, url);
    
    if (domain == NULL) {
        printf("Invalid url given: %s\n", url);
    } 

    // 1. create an endpoint for communication
    int socket_fd = create_socket();
    struct sockaddr_in saddr;
    struct hostent     *h;

    if ((h = gethostbyname(domain)) == NULL) {
        fprintf(stderr, "could not resolve host: %s\n", domain);
        exit(EXIT_FAILURE);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port   = htons(HTTP_PORT);
    memcpy((char*)&saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length); 

    // 2 connect to remote address.
    if ((connect(socket_fd, (struct sockaddr*) &saddr, sizeof(saddr))) < 0) {
        perror("Connect()");
        exit(EXIT_FAILURE);
    } 

    write_http_request(socket_fd, domain, resource);
    read_socket(socket_fd);

    return 0;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    } else {
        my_curl(argv[1]);
    }

    return 0;
}