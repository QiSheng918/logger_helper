#include"loggerHelper.h"

int main(){
    int i=1;
    std::string temp="hello world";
    LOG_TRACE("hello world {}",i);
    LOG_INFO("the log is {}",temp);
    return 0;
}