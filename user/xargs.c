#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// �������б�ִ��ĳ������
void run(char *program, char **args) {
	if(fork() == 0) { // child exec
		exec(program, args);
		exit(0);
	}
	return; // parent return
}

int main(int argc, char *argv[]){
	char buf[2048]; // ����ʱʹ�õ��ڴ��
	char *p = buf, *last_p = buf; // ��ǰ�����Ľ�������ʼָ��
	char *argsbuf[128]; // ȫ�������б��ַ���ָ�����飬���� argv �������Ĳ����� stdin ����Ĳ���
	char **args = argsbuf; // ָ�� argsbuf �е�һ���� stdin ����Ĳ���
	for(int i=1;i<argc;i++) {
		// �� argv �ṩ�Ĳ������뵽���յĲ����б���
		*args = argv[i];
		args++;
	}
	char **pa = args; // ��ʼ�������
	while(read(0, p, 1) != 0) {
		if(*p == ' ' || *p == '\n') {
			// ����һ��������ɣ��Կո�ָ����� `echo hello world`���� hello �� world ��Ϊһ��������
			*p = '\0';	// ���ո��滻Ϊ \0 �ָ������������������ֱ��ʹ���ڴ���е��ַ�����Ϊ�����ַ���
						// �����ö��⿪�ٿռ�
			*(pa++) = last_p;
			last_p = p+1;

			if(*p == '\n') {
				// ����һ�����
				*pa = 0; // �����б�ĩβ�� null ��ʶ�б����
				run(argv[1], argsbuf); // ִ�����һ��ָ��
				pa = args; // ���ö������ָ�룬׼��������һ��
			}
		}
		p++;
	}
	if(pa != args) { // ������һ�в��ǿ���
		// ��β���һ������
		*p = '\0';
		*(pa++) = last_p;
		// ��β���һ��
		*pa = 0; // �����б�ĩβ�� null ��ʶ�б����
		// ִ�����һ��ָ��
		run(argv[1], argsbuf);
	}
	while(wait(0) != -1) {}; // ѭ���ȴ������ӽ�����ɣ�ÿһ�� wait(0) �ȴ�һ��
	exit(0);
}

