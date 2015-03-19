#include<string>
#include<string.h>

using namespace std;

int check(char *src)
{
            string  file(src);
            if(file.length()>=4)
            {
                        int len=file.length()-file.find_last_of(".");
                        string  form=file.substr(file.find_last_of("."),len);
                        if((form==".tif")||(form==".jpg")||(form==".bmp")||(form==".png"))
                                return 1;
                        else
                                return 0;
            }
            else
            {
                        if((file=="-g")||(file=="-x")||(file=="-y")||(file=="-z")||(file=="-xz")||(file=="-yz")||(file=="-o")||(file=="-k")||(file=="-b")||(file=="-c"))
                                return 1;
                        else
                                return 0;
            }
}
