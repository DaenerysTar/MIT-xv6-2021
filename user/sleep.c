#include "kernel/types.h"//包含头文件，它们定义了在 Xv6 操作系统中使用的数据类型和函数
#include "user/user.h"

int main(int argc, char **argv)//程序的入口函数，argc 和 argv 是命令行参数的计数和参数数组
{
    if (argc != 2) {//检查命令行参数的数量是否等于 2
        fprintf(2,"sleep.c: wants 1 parameters, get %d parameter(s).\n",argc-1);//若不等于2，打印一条错误消息
        exit(1);//1 表示程序退出时的返回值，表示程序执行失败 
    }
    int time;//使用 atoi 函数将参数数组中的第二个参数转换为整数。atoi 是一个用户空间的字符串转换为整数的函数
    time = atoi(argv[1]);//user/ulib.c中定义的的字符串转数字函数
    // If time == 0, return ASAP.
    if (time <= 0)
		exit(1);//传递的时间不合法，程序执行失败
    sleep(time);//sleep 函数调用，它暂停程序的执行，将程序置于休眠状态，持续指定的时间间隔
    exit(0);//0 表示程序退出时的返回值，表示程序执行成功。
}

//在一些操作系统环境中，特别是像 Unix/Linux 这样的环境中，约定俗成地使用 exit 函数来终止程序的执行并返回退出状态码
