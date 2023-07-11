#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int main(int argc, char *argv[]){
    int p1[2];
    int p2[2];//创建两个整型数组 p1 和 p2 作为管道的读写端点 
    pipe(p1);
    pipe(p2);//创建管道,将读写端点分别存储在数组 p1 和 p2 中
    int pid = fork();//创建子进程，子进程会复制父进程
    if(pid == 0){//下面的代码应该不会执行 
        close(p1[1]);
        close(p2[0]);//关闭不需要的管道端口，即关闭 p1 的写端口和 p2 的读端口
        char son[2];       
        read(p1[0],son,1); //从 p1 的读端口读取一个字符到 son 数组中
        close(p1[0]);//关闭 p1 的读端口
        printf("%d: received ping\n",getpid());////打印子进程的进程ID
        write(p2[1],"a",2);//向管道写入内容
        close(p2[1]);//关闭 p2 的写端口
    }else if(pid > 0){//关闭不需要的管道端口，即关闭 p1 的读端口和 p2 的写端口
        close(p1[0]);
        close(p2[1]);      
        write(p1[1],"a",2); //向 p1 的写端口写入一个字符
        close(p1[1]);//关闭 p1 的写端口   
        char father[2];
        read(p2[0],father,1);//从 p2 的读端口读取一个字符到 father 数组中
        printf("%d: received pong\n",getpid());//打印父进程的进程ID
        close(p2[0]);//关闭 p2 的读端口
    }
    exit(0);
}
