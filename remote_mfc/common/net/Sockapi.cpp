#include "Sockapi.h"

int SockApi::Socket(int domain, int type, int protocol, int& sockfd)
{
    int sock = socket(domain, type, protocol);

    if (sock < 0) {
    
        return GetLastError();
    }
    else {
    
        sockfd = sock;
        //½ûÓÃ¾ä±ú¼Ì³Ð
        SetHandleInformation((HANDLE)sockfd, HANDLE_FLAG_INHERIT, 0);

        return 0;
    }
}
