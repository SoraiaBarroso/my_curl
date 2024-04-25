#include "my_curl.h"

char* get_resource(char* domain, const char* url)
{
    size_t i = strlen(domain) + strlen(HTTP) + 1;
    int index = 0;
    char *resource = malloc(sizeof(char) * 254);

    while(url[i] != '\0') {
        resource[index] = url[i];
        index++, i++;
    }

    resource[index] = '\0';
    return resource;
}

char* get_domain(const char* url)
{
    int i = strlen(HTTP), index = 0;
    char *domain = malloc(sizeof(char) * 254);

    while(url[i] != '/' && url[i] != '\0' && i < 253) {
        domain[index] = url[i];
        i++, index++;
    }

    domain[index] = '\0';
    return domain;
}
