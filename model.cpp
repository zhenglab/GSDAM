#include<iostream>
#include<string.h>

using namespace std;

int model(char *src)
{
    if(!strcmp(src,"-g"))
        return 0;
    else  if(!strcmp(src,"-x"))
        return 1;
    else  if(!strcmp(src,"-y"))
        return 2;
    else  if(!strcmp(src,"-z"))
        return 3;
    else  if(!strcmp(src,"-xz"))
        return 4;
    else  if(!strcmp(src,"-yz"))
        return 5;
    else  if(!strcmp(src,"-k"))
        return 6;
    else  if(!strcmp(src,"-b"))
        return 7;
    else  if(!strcmp(src,"-c"))
        return 8;
    else  if(!strcmp(src,"-o"))
        return 9;
    return 10;
}

