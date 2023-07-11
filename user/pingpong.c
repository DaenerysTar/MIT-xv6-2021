#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int main(int argc, char *argv[]){
    int p1[2];
    int p2[2];//���������������� p1 �� p2 ��Ϊ�ܵ��Ķ�д�˵� 
    pipe(p1);
    pipe(p2);//�����ܵ�,����д�˵�ֱ�洢������ p1 �� p2 ��
    int pid = fork();//�����ӽ��̣��ӽ��̻Ḵ�Ƹ�����
    if(pid == 0){//����Ĵ���Ӧ�ò���ִ�� 
        close(p1[1]);
        close(p2[0]);//�رղ���Ҫ�Ĺܵ��˿ڣ����ر� p1 ��д�˿ں� p2 �Ķ��˿�
        char son[2];       
        read(p1[0],son,1); //�� p1 �Ķ��˿ڶ�ȡһ���ַ��� son ������
        close(p1[0]);//�ر� p1 �Ķ��˿�
        printf("%d: received ping\n",getpid());////��ӡ�ӽ��̵Ľ���ID
        write(p2[1],"a",2);//��ܵ�д������
        close(p2[1]);//�ر� p2 ��д�˿�
    }else if(pid > 0){//�رղ���Ҫ�Ĺܵ��˿ڣ����ر� p1 �Ķ��˿ں� p2 ��д�˿�
        close(p1[0]);
        close(p2[1]);      
        write(p1[1],"a",2); //�� p1 ��д�˿�д��һ���ַ�
        close(p1[1]);//�ر� p1 ��д�˿�   
        char father[2];
        read(p2[0],father,1);//�� p2 �Ķ��˿ڶ�ȡһ���ַ��� father ������
        printf("%d: received pong\n",getpid());//��ӡ�����̵Ľ���ID
        close(p2[0]);//�ر� p2 �Ķ��˿�
    }
    exit(0);
}
