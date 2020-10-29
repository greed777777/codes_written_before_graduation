#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct CMD {                   // ��ɿ�������������±���ü

	char *name;           // ����̸�
	char *desc;           // ��ɼ���
	int(*cmd)(int argc, char *argv[]);  //��ɽ����Լ�������������
};

 

int cmd_cd(int argc, char *argv[]);
int cmd_pwd(int argc, char *argv[]);
int cmd_exit(int argc, char *argv[]);
int cmd_help(int argc, char *argv[]);
int cmd_echo(int argc, char *argv[]);
int cmd_history(int argc, char *argv[]);
int cmdProcessing(void);
int myatoi(char* string);
char *history[100];
int histCount = 0;


struct CMD builtin[] = {        // ����������

	{ "cd", "�۾����͸��ٲٱ�", cmd_cd },
	{ "pwd","�����۾����͸���", cmd_pwd },
	{ "exit", "�н����������մϴ�", cmd_exit },
	{ "help", "���򸻺����ֱ�", cmd_help },
	{ "echo", "����������ǥ�������ġ���״�����", cmd_echo },
	{ "history", "�۾����������ֱ�", cmd_history }
};

const int builtins = 6;        // �����ɾ��Ǽ�

int main(void)
{

	int isExit;
	
	static struct sigaction act;
	void int_handler(int);
	
	act.sa_handler = int_handler;
	sigfillset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);

	while (1) {
		isExit = cmdProcessing();    // ���ó����ƾȣ��
		if (isExit) {			// 0�̾ƴѰ��̹�ȯ�Ǹ�
			fputs("Yun Shell�������մϴ�\n", stdout);
			break;
		}
	}

	return 0;

}

#define STR_LEN 1024                    // �ִ����Է±���
#define MAX_TOKENS 128               // �������κи��Ǵ¸�ɾ�ڿ��ִ��
#define RD_DRIGHT 2
#define RD_RIGHT 1
#define RD_NONE 0
#define RD_LEFT -1

int RdIs(char *tokenArray[]);
int GetRdPos(char *tokenArray[]);

int cmdProcessing(void)
{

	char cmdLine[STR_LEN];          // �Է¸����ü�������ϴ¹迭
	char *cmdTokens[MAX_TOKENS]; // �Է¸�����������κи��Ͽ������ϴ¹迭
	char delim[] = " \t\n\r";       // ��ū�����ڿ������
	char *token;                    // �ϳ�����ū���и��ϴµ����
	int tokenNum;                   // �Է¸�ɿ��������ū��
	int status; 					// �θ����μ����ǻ��¸��ٲٴµ����
	int exitCode = 0;               // �����ڵ�
	int i,j;		             // for �����ȿ���������ǿ��������ط����ۿ�����
	pid_t pid;                      // �ܺ��Լ�ȣ�������Ѻ�������
	char buf[1024];                 // �����۾����͸�����ľ������ػ��
	int direction;					//���𷺼� ���� �Ǻ��뺯��
	int rdi;							//���𷺼� �ε��� 
	int fd,oldFd;							//���ϵ�ũ����
	char path[] = "/bin/";				//ls,cat�� �� �������� ������ġ
	char* histmp = '\0';						//�����丮 �ӽ������
	int size=0;
	
	getcwd(buf,1024);

	fputs("[Yun Shell v0.1 :~", stdout);      // ������Ʈ���
	fputs(buf, stdout);
	fputs("]$ ",stdout);
	
	cmdLine[0] = '\0';

	fgets(cmdLine, STR_LEN, stdin);      // �����Ǹ���Է�
	


	tokenNum = 0;
	token = strtok(cmdLine, delim);       // �Է¸���ǹ��ڿ��ϳ��и�
	while (token) {                          // ���ڿ����������ȹݺ�
		cmdTokens[tokenNum++] = token; //�и��ȹ��ڿ����迭������
		token = strtok(NULL, delim);   //�����Ͽ��Է¸���ǹ��ڿ��ϳ��и�
	}
	
	
	cmdTokens[tokenNum] = NULL;
	if (tokenNum == 0)
		return exitCode;
	
	// !�ν����ϸ� �ڿ� ���ڰ� ������ �Ǵ��ؼ� �����丮������ ������� �ٲ��ش�.
	if(cmdTokens[0][0] == '!')
	{
		if(cmdTokens[0][1] == '!'){
			strcpy(cmdLine,history[histCount-1]);
			tokenNum = 0;
			token = strtok(cmdLine, delim);       // 

			while (token) {                          // 
				cmdTokens[tokenNum++] = token; //
				token = strtok(NULL, delim);   //
			}
			cmdTokens[tokenNum] = NULL;
		}
		else if(atoi(&cmdTokens[0][1])!=0)
		{
			strcpy(cmdLine,history[atoi(&cmdTokens[0][1])-1]);
			tokenNum = 0;
			token = strtok(cmdLine, delim);       // 

			while (token) {                          // 
				cmdTokens[tokenNum++] = token; //
				token = strtok(NULL, delim);   //
			}
			cmdTokens[tokenNum] = NULL;
		}
	}
	//�������
	
	
	//���⼭���� ����� �ӽ������ϴ� �ڵ� 
	for(j = 0; j<tokenNum; j++)
	{
		size = size + sizeof(cmdTokens[j]);
	}
	histmp = (char*)malloc(size);
	
	for(j = 0; j<tokenNum; j++)
	{
		strcat(histmp,cmdTokens[j]);
		if(j == tokenNum)
			break;
		strcat(histmp," ");
	}
	//�������
	
	direction = RdIs(cmdTokens) ;

	if(direction!=RD_NONE)
	{
		rdi = GetRdPos(cmdTokens);
		if(direction == RD_RIGHT)
		{
			fd = open(cmdTokens[rdi+1], O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);
			oldFd = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
		}
		else if(direction == RD_LEFT)
		{
			fd = open(cmdTokens[rdi+1], O_RDONLY);
			oldFd = dup(STDIN_FILENO);
			dup2(fd, STDIN_FILENO);
		}
		else
		{
			fd = open(cmdTokens[rdi+1],O_WRONLY|O_CREAT|O_APPEND,S_IRWXU|S_IRWXG|S_IRWXO);
			oldFd = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
		}
		cmdTokens[rdi] = NULL;
	}
	
	
	for (i = 0; i < builtins; ++i) { // �������̸� �ش��Լ�ȣ��
		if (strcmp(cmdTokens[0], builtin[i].name) == 0){
				history[histCount++] = histmp;
				return builtin[i].cmd(tokenNum, cmdTokens);
			}
		}
	
	// ������ �ƴ϶�� ���μ��� ������ ������α׷� ȣ��	
	//printf("done until this\n");
	pid = fork();
	if (pid > 0) {          //�θ���
		if(direction){					
			if(direction == RD_DRIGHT || direction == RD_RIGHT)		//���ϵ�ũ���� ������� ������
				dup2(oldFd, STDOUT_FILENO);
			else
				dup2(oldFd, STDIN_FILENO);
			close(fd);
		}
		waitpid(pid,&status,0);
		history[histCount++] = histmp;
		return exitCode;
	}
	else if (pid == 0) {    //�ڽ��̶��
		strcat(path,cmdTokens[0]);		
		execv(path, cmdTokens);		//�����Ű��
		
		if(direction){					
			if(direction == RD_DRIGHT || direction == RD_RIGHT)		//���ϵ�ũ���� ������� ������
				dup2(oldFd, STDOUT_FILENO);
			else
				dup2(oldFd, STDIN_FILENO);
			close(fd);
		}
		exit(0);
	}
	else               //fork ȣ���̽����Ұ��
	{
		fputs("���μ����������Ҽ�����\n", stdout);
	}
	
	return exitCode;
}

int RdIs(char* tokenArray[])
{
	int direction=RD_NONE;
	int i = 0;
	for(i = 0; tokenArray[i] != NULL; i++)
		if(strcmp(tokenArray[i], ">")==0)
		{
			direction = RD_RIGHT;
			break;
		}
		else if(strcmp(tokenArray[i] , ">>")==0)
		{
			direction = RD_DRIGHT;
			break;
		}
		else if(strcmp(tokenArray[i] , "<")==0)
		{
			direction = RD_LEFT;
			break;
		}
	return direction;
}

int GetRdPos(char* tokenArray[]){
	int i = 0;
	for(; tokenArray[i] != NULL; i++){
		if(strcmp(tokenArray[i], ">")==0||strcmp(tokenArray[i] , ">>")==0||strcmp(tokenArray[i] , "<")==0)
			break;
	}
	
	return i;
}
 

int cmd_cd(int argc, char *argv[])
{
	struct stat fileinfo;   // ������������ ����

	if (argc == 1) {
		chdir(getenv("HOME")); // Ȩ��ȯ�溯�����������͸�����
	}
	else if (argc > 1) {
		if (stat(argv[1], &fileinfo) == -1) { //���͸���ã����������
			fprintf(stdout, "%s ���͸�����\n", argv[1]);

			return 0;
		}
		if (chdir(argv[1]) == -1) { // ���н� �Ʒ��ǹ������
			if (access(argv[1], X_OK) == -1) { // ��������� ������
				fprintf(stdout, "%s�����ٱ��Ѿ���\n", argv[1]);
				
				return 0;
			}
			else
				fprintf(stdout, "%s�µ��͸����ƴ�\n", argv[1]);
			return 0;
		}
	}
	else
		fputs("�߸����Է�\n", stdout);

	return 0;
}

int cmd_pwd(int argc, char *argv[])
{
	char buffer[50];   // �����۾����͸��ǰ�θ������ҹ���
	if (getcwd(buffer, 50) == NULL) {
		fprintf(stdout,"�����۾����ε��͸����˼�����\n");
	}
	fprintf(stdout, "%s\n", buffer); // ���ۿ� �����θ� ����
	
	return 0;
}

int cmd_exit(int argc, char *argv[])
{
	return 1;
}

int cmd_help(int argc, char *argv[])
{
	int i;
	if (argc == 1){                 // ��ɾ���� help����������簡���Ѹ�ɾ���Ѽ���
		for (i = 0; i < builtins; ++i){
			fprintf(stdout, "%s : %s\n", builtin[i].name, builtin[i].desc);
		}
	}
	else if (argc == 2) {           // ��ɾ�ڿ��ٿ������׿��ش��ϴ¸�ɾ���ؼ�������
		for (i = 0; i <= builtins; ++i){
			if (i == builtins) {
				fprintf(stdout,"�ش��ϴ¸�ɾã���������ϴ�\n");
				
				return 0;
			}
			if (strcmp(argv[1], builtin[i].name) == 0){
				fprintf(stdout, "%s : %s\n", builtin[i].name, builtin[i].desc);
				
				return 0;
			}
		}
	}
	else {                        // ���ڰ��̰��ʰ��ε�����������
		fprintf(stdout,"�߸����Է��Դϴٻ�����ɾ�\n");
	}

	return 0;
}

int cmd_echo(int argc, char *argv[])
{
	int i;

	if (argc == 1) {              // echo���Է���������������
		fputs("�����޽���\n", stdout);
	}

	else if (argc >= 2) {          // echo+�޽����� �Է½ø޽������
		for (i = 1; i < argc; i++) {
			fprintf(stdout, "%s ", argv[i]);

		}
		fprintf(stdout,"\n");
	}

	else {                       // �����޽������
		fputs("�߸����Է��Դϴٻ����޽���\n", stdout);
	}
	
	return 0;
}

int cmd_history(int argc, char *argv[])
{
	int i= 0;	
	
	if(argc == 1)
	{
		i = histCount - 10;
		if (i<0)
			i = 0;
		for(; i < histCount; i++)
				printf("%d\t%s\n", i+1, history[i]);
	}
	
	return 0;
}

void int_handler(int signum)
{
	fputs("\n",stdout);
}

