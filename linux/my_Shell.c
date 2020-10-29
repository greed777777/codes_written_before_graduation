#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct CMD {                   // 명령에대한정보를담는구조체

	char *name;           // 명령이름
	char *desc;           // 명령설명
	int(*cmd)(int argc, char *argv[]);  //명령실행함수에대한포인터
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


struct CMD builtin[] = {        // 내장명령정보

	{ "cd", "작업디렉터리바꾸기", cmd_cd },
	{ "pwd","현재작업디렉터리는", cmd_pwd },
	{ "exit", "셸실행을종료합니다", cmd_exit },
	{ "help", "도움말보여주기", cmd_help },
	{ "echo", "적은내용을표준출력장치에그대로출력", cmd_echo },
	{ "history", "작업내역보여주기", cmd_history }
};

const int builtins = 6;        // 내장명령어의수

int main(void)
{

	int isExit;
	
	static struct sigaction act;
	void int_handler(int);
	
	act.sa_handler = int_handler;
	sigfillset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);

	while (1) {
		isExit = cmdProcessing();    // 명령처리루틴호출
		if (isExit) {			// 0이아닌값이반환되면
			fputs("Yun Shell을종료합니다\n", stdout);
			break;
		}
	}

	return 0;

}

#define STR_LEN 1024                    // 최대명령입력길이
#define MAX_TOKENS 128               // 공백으로분리되는명령어문자열최대수
#define RD_DRIGHT 2
#define RD_RIGHT 1
#define RD_NONE 0
#define RD_LEFT -1

int RdIs(char *tokenArray[]);
int GetRdPos(char *tokenArray[]);

int cmdProcessing(void)
{

	char cmdLine[STR_LEN];          // 입력명령전체를저장하는배열
	char *cmdTokens[MAX_TOKENS]; // 입력명령을공백으로분리하여저장하는배열
	char delim[] = " \t\n\r";       // 토큰구분자에서사용
	char *token;                    // 하나의토큰을분리하는데사용
	int tokenNum;                   // 입력명령에저장된토큰수
	int status; 					// 부모프로세스의상태를바꾸는데사용
	int exitCode = 0;               // 종료코드
	int i,j;		             // for 루프안에서선언시의오류로인해루프밖에선언
	pid_t pid;                      // 외부함수호출을위한변수생성
	char buf[1024];                 // 현재작업디렉터리경로파악을위해사용
	int direction;					//리디렉션 방향 판별용변수
	int rdi;							//리디렉션 인덱스 
	int fd,oldFd;							//파일디스크립터
	char path[] = "/bin/";				//ls,cat등 쉘 외장명령의 저장위치
	char* histmp = '\0';						//히스토리 임시저장용
	int size=0;
	
	getcwd(buf,1024);

	fputs("[Yun Shell v0.1 :~", stdout);      // 프롬프트출력
	fputs(buf, stdout);
	fputs("]$ ",stdout);
	
	cmdLine[0] = '\0';

	fgets(cmdLine, STR_LEN, stdin);      // 한줄의명령입력
	


	tokenNum = 0;
	token = strtok(cmdLine, delim);       // 입력명령의문자열하나분리
	while (token) {                          // 문자열이있을동안반복
		cmdTokens[tokenNum++] = token; //분리된문자열을배열에저장
		token = strtok(NULL, delim);   //연속하여입력명령의문자열하나분리
	}
	
	
	cmdTokens[tokenNum] = NULL;
	if (tokenNum == 0)
		return exitCode;
	
	// !로시작하면 뒤에 숫자가 오는지 판단해서 히스토리내역의 명령으로 바꿔준다.
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
	//여기까지
	
	
	//여기서부터 명령을 임시저장하는 코드 
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
	//여기까지
	
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
	
	
	for (i = 0; i < builtins; ++i) { // 내장명령이면 해당함수호출
		if (strcmp(cmdTokens[0], builtin[i].name) == 0){
				history[histCount++] = histmp;
				return builtin[i].cmd(tokenNum, cmdTokens);
			}
		}
	
	// 내장명령 아니라면 프로세스 생성후 명령프로그램 호출	
	//printf("done until this\n");
	pid = fork();
	if (pid > 0) {          //부모라면
		if(direction){					
			if(direction == RD_DRIGHT || direction == RD_RIGHT)		//파일디스크립터 원래대로 돌려줌
				dup2(oldFd, STDOUT_FILENO);
			else
				dup2(oldFd, STDIN_FILENO);
			close(fd);
		}
		waitpid(pid,&status,0);
		history[histCount++] = histmp;
		return exitCode;
	}
	else if (pid == 0) {    //자식이라면
		strcat(path,cmdTokens[0]);		
		execv(path, cmdTokens);		//실행시키고
		
		if(direction){					
			if(direction == RD_DRIGHT || direction == RD_RIGHT)		//파일디스크립터 원래대로 돌려줌
				dup2(oldFd, STDOUT_FILENO);
			else
				dup2(oldFd, STDIN_FILENO);
			close(fd);
		}
		exit(0);
	}
	else               //fork 호출이실패할경우
	{
		fputs("프로세스를생성할수없음\n", stdout);
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
	struct stat fileinfo;   // 파일의정보를 저장

	if (argc == 1) {
		chdir(getenv("HOME")); // 홈의환경변수값을얻고디렉터리변경
	}
	else if (argc > 1) {
		if (stat(argv[1], &fileinfo) == -1) { //디렉터리를찾을수없을때
			fprintf(stdout, "%s 디렉터리없음\n", argv[1]);

			return 0;
		}
		if (chdir(argv[1]) == -1) { // 실패시 아래의문장출력
			if (access(argv[1], X_OK) == -1) { // 실행권한이 없으면
				fprintf(stdout, "%s에접근권한없음\n", argv[1]);
				
				return 0;
			}
			else
				fprintf(stdout, "%s는디렉터리가아님\n", argv[1]);
			return 0;
		}
	}
	else
		fputs("잘못된입력\n", stdout);

	return 0;
}

int cmd_pwd(int argc, char *argv[])
{
	char buffer[50];   // 현재작업디렉터리의경로를저장할버퍼
	if (getcwd(buffer, 50) == NULL) {
		fprintf(stdout,"현재작업중인디렉터리를알수없음\n");
	}
	fprintf(stdout, "%s\n", buffer); // 버퍼에 절대경로를 저장
	
	return 0;
}

int cmd_exit(int argc, char *argv[])
{
	return 1;
}

int cmd_help(int argc, char *argv[])
{
	int i;
	if (argc == 1){                 // 명령어없이 help만쳤을때모든가능한명령어에대한설명
		for (i = 0; i < builtins; ++i){
			fprintf(stdout, "%s : %s\n", builtin[i].name, builtin[i].desc);
		}
	}
	else if (argc == 2) {           // 명령어를뒤에붙였을때그에해당하는명령어에대해서만설명
		for (i = 0; i <= builtins; ++i){
			if (i == builtins) {
				fprintf(stdout,"해당하는명령어를찾을수없습니다\n");
				
				return 0;
			}
			if (strcmp(argv[1], builtin[i].name) == 0){
				fprintf(stdout, "%s : %s\n", builtin[i].name, builtin[i].desc);
				
				return 0;
			}
		}
	}
	else {                        // 인자값이개초과로들어왔을때오류
		fprintf(stdout,"잘못된입력입니다사용법명령어\n");
	}

	return 0;
}

int cmd_echo(int argc, char *argv[])
{
	int i;

	if (argc == 1) {              // echo만입력했을때사용방법출력
		fputs("사용법메시지\n", stdout);
	}

	else if (argc >= 2) {          // echo+메시지를 입력시메시지출력
		for (i = 1; i < argc; i++) {
			fprintf(stdout, "%s ", argv[i]);

		}
		fprintf(stdout,"\n");
	}

	else {                       // 오류메시지출력
		fputs("잘못된입력입니다사용법메시지\n", stdout);
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

