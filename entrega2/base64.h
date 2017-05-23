#ifndef _BASE64_H
#define _BASE64_H

int base64_encode(int fd_in, int fd_out);

int base64_decode(int fd_in, int fd_out);

#endif
