#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// һ�� sieve ������һ��ɸ�ӽ׶Σ���� pleft ��ȡ�����һ������ p��ɸ�� p �����б���
// ͬʱ������һ stage �Ľ����Լ���Ӧ����ܵ� pright��Ȼ��ʣ�µ���������һ stage ����
void sieve(int pleft[2]) { // pleft �����Ը� stage ��˽��̵�����ܵ�
	int p;
	read(pleft[0], &p, sizeof(p)); // ����һ��������Ȼ������
	if(p == -1) { // ������ڱ� -1��������������ִ�����ϣ��˳�����
		exit(0);
	}
	printf("prime %d\n", p);

	int pright[2];
	pipe(pright); // ���������������һ stage �Ľ��̵�����ܵ� pright

	if(fork() == 0) {
		// �ӽ��� ����һ�� stage��
		close(pright[1]); // �ӽ���ֻ��Ҫ������ܵ� pright ���ж���������Ҫд�����Թص��ӽ��̵�����ܵ�д�ļ������������ͽ��̴򿪵��ļ�����������
		close(pleft[0]); // ����� pleft ��*������*������ܵ����ӽ����ò������ص�
		sieve(pright); // �ӽ����Ը����̵�����ܵ���Ϊ���룬��ʼ������һ�� stage �Ĵ���

	} else {
		// ������ ����ǰ stage��
		close(pright[0]); // ͬ�ϣ�������ֻ��Ҫ���ӽ��̵�����ܵ�����д������Ҫ�������Թص������̵Ķ��ļ�������
		int buf;
		while(read(pleft[0], &buf, sizeof(buf)) && buf != -1) { // ����˵Ľ��̶�������
			if(buf % p != 0) { // ɸ���ܱ��ý���ɸ��������
				write(pright[1], &buf, sizeof(buf)); // ��ʣ�������д���Ҷ˽���
			}
		}
		buf = -1;
		write(pright[1], &buf, sizeof(buf)); // ��д���� -1����ʾ������ɡ�
		wait(0); // �ȴ��ý��̵��ӽ�����ɣ�Ҳ������һ stage
		exit(0);
	}
}

int main(int argc, char **argv) {
	// ������
	int input_pipe[2];
	pipe(input_pipe); // ׼��������ܵ������� 2 �� 35 ֮�������������

	if(fork() == 0) {
		// ��һ�� stage ���ӽ���
		close(input_pipe[1]); // �ӽ���ֻ��Ҫ������ܵ���������Ҫд���ص��ӽ��̵Ĺܵ�д�ļ�������
		sieve(input_pipe);
		exit(0);
	} else {
		// ������
		close(input_pipe[0]); // ͬ��
		int i;
		for(i=2;i<=35;i++){ // ���� [2, 35]������ܵ��������
			write(input_pipe[1], &i, sizeof(i));
		}
		i = -1;
		write(input_pipe[1], &i, sizeof(i)); // ĩβ���� -1�����ڱ�ʶ�������
	}
	wait(0); // �ȴ���һ�� stage ��ɡ�ע�⣺�����޷��ȴ��ӽ��̵��ӽ��̣�ֻ�ܵȴ�ֱ���ӽ��̣��޷��ȴ�����ӽ��̡��� sieve() �л�Ϊÿ�� stage �ٸ���ִ�� wait(0)���γɵȴ�����
	exit(0);
}
