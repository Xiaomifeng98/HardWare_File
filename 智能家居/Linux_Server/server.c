#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>      
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <json/json.h>
#include <signal.h>

int get_json_int_filed(const char *json_data,const char *filed)
{
	int filed_value;
	json_object *jobject;

	jobject = json_tokener_parse(json_data);
	if(jobject == NULL){
		printf("Json data format error!\n");
		return -1;
	}
	
	struct json_object *filed_object = json_object_object_get(jobject,filed);
	if(filed_object == NULL){
		json_object_put(jobject);
		printf("Json object is not exist %s filed\n",filed);
		return -1;
	}
	
	filed_value = json_object_get_int(filed_object);
	json_object_put(filed_object);
	json_object_put(jobject);

	return filed_value;
}

char *get_json_string_filed(const char *json_data, const char *filed)
{
	char *str;
	const char *filed_value;
	json_object *jobject;

	jobject = json_tokener_parse(json_data);
	if(jobject == NULL){
		printf("Json data format error!\n");
		return NULL;
	}

	struct json_object *filed_object = json_object_object_get(jobject, filed);
	if(filed_object == NULL){
		json_object_put(jobject);
		printf("Json object is not exist %s filed!\n", filed);
		return NULL;
	}


	filed_value = json_object_get_string(filed_object);
	str = strdup(filed_value);
	json_object_put(filed_object);
	json_object_put(jobject);

	return str;
}
/*
void change_password(char *username, char *newPassword)
{
	FILE *fp1, *fp2;
	fp1 = fopen("user.txt", "r");
	if(fp1 = NULL){
		printf("Fail to open file.");
		return;
	}
	fp2 = fopen("user2.txt", "w+");
	if(fp2 = NULL){
		printf("Fail to open file.");
		return;
	}
	while(1){
		char _username[100];
		char _password[100];
		char _telphone[100];
		char _useremail[100];
		int ret = fscanf(fp1, "%[^:]:%[^:]:%[^:]:%s\n", _username, _password, _useremail, _telphone);
		if(ret == EOF){
			break;
		}
		if(strcmp(username, _username) == 0){
			fprintf(fp2, "%s:%s:%s:%s\n", _username, newPassword, _useremail, _telphone);
			continue;
		}
		fprintf(fp2, "%s:%s:%s:%s\n", _username, _password, _useremail, _telphone);
	}
	
	fclose(fp1);
	fclose(fp2);
	free(username);
	free(newPassword);
	system("rm user.txt");
	system("mv user2.txt user.txt");
	
}
*/
void control_device1(int controlStatu)
{
	if(controlStatu == 0){
		printf("Open device 1\n");
	}else{
		printf("Close device 1\n");
	}
}

void control_device2(int controlStatu)
{
	if(controlStatu == 0){
		printf("Open device 2\n");
	}else{
		printf("Close device 2\n");
	}
}
void control_device3(int controlStatu)
{
	if(controlStatu == 0){
		printf("Open device 3\n");
	}else{
		printf("Close device 3\n");
	}
}
void control_device4(int controlStatu)
{
	if(controlStatu == 0){
		printf("Open device 4\n");
	}else{
		printf("Close device 4\n");
	}
}

void ack_client_register(int sockfd, int exist_flag)
{
	const char *json_data;
	char *error_string;
	json_object *jobject;

	jobject = json_object_new_object();
	json_object_object_add(jobject, "functionId", json_object_new_int(1));
	json_object_object_add(jobject, "statu", json_object_new_int(exist_flag));
	if(exist_flag){
		error_string = "The user is exist!";
	}else{
		error_string = "";
	}
	json_object_object_add(jobject, "error", json_object_new_string(error_string));

	json_data = json_object_to_json_string(jobject);

	write(sockfd, json_data, strlen(json_data));
	json_object_put(jobject);

	return;
}

void ack_client_login(int sockfd, int exist_flag)
{
	const char *json_data;
	char *error_string;
	json_object *jobject;

	jobject = json_object_new_object();
	json_object_object_add(jobject, "functionId", json_object_new_int(2));
	json_object_object_add(jobject, "statu", json_object_new_int(exist_flag));
	if(exist_flag){
		error_string = "Wrong user or password!";
	}else{
		char clientId[100];
		error_string = "";
		sprintf(clientId, "%d", getppid());
		json_object_object_add(jobject, "clientId", json_object_new_string(clientId));
	}

	json_object_object_add(jobject, "error", json_object_new_string(error_string));

	json_data = json_object_to_json_string(jobject);

	write(sockfd, json_data, strlen(json_data));
	json_object_put(jobject);

	return;
}

void control_device(int deviceId, int controlStatu)
{
	switch(deviceId){
		case 1:
			control_device1(controlStatu);
			break;
		case 2:
			control_device2(controlStatu);
			break;
		case 3:
			control_device3(controlStatu);
			break;
		case 4:
			control_device4(controlStatu);
			break;
		default:
			break;
	}
}

void ack_client_reset(int sockfd, int exist_flag)
{
	const char *json_data;
	char *error_string;
	json_object *jobject;

	jobject = json_object_new_object();
	json_object_object_add(jobject, "functionId", json_object_new_int(4));
	json_object_object_add(jobject, "statu", json_object_new_int(exist_flag));
	if(exist_flag == 1){
		error_string = "Your username or oldpassword is wrong!";
	}
	if(exist_flag == 0){
		error_string = "";
	}

	json_object_object_add(jobject, "error", json_object_new_string(error_string));

	json_data = json_object_to_json_string(jobject);

	write(sockfd, json_data, strlen(json_data));
	json_object_put(jobject);

	return;
	
}


void ack_client_forget(int sockfd, int exist_flag)
{
	const char *json_data;
	char *error_string;
	json_object *jobject;

	jobject = json_object_new_object();
	json_object_object_add(jobject, "functionId", json_object_new_int(5));
	json_object_object_add(jobject, "statu", json_object_new_int(exist_flag));
	if(exist_flag == 1){
		error_string = "Your information is Wrong!";
	}
	if(exist_flag == 0){
		error_string = "";
	}

	json_object_object_add(jobject, "error", json_object_new_string(error_string));

	json_data = json_object_to_json_string(jobject);

	write(sockfd, json_data, strlen(json_data));
	json_object_put(jobject);

	return;
	
}



void client_register(int sockfd, const char *json_data)
{
	FILE *fp;
	int exist_flag = 0;
	char *username = get_json_string_filed(json_data, "username");
	char *password = get_json_string_filed(json_data, "password");
	char *telphone = get_json_string_filed(json_data, "telphone");
	char *useremail= get_json_string_filed(json_data,"email");

	fp = fopen("user.txt", "a+");
	if(fp == NULL){
		perror("Fail to open file.");
		return;
	}

	while(1){
 		char _username[100];
		char _password[100];
		char _telphone[100];
		char _useremail[100];
		int ret = fscanf(fp, "%[^:]:%[^:]:%[^:]:%s\n",_username,_password,_useremail,_telphone);
		if(ret == EOF){
			break;
		}

		if((strcmp(username, _username)) == 0){
			exist_flag = 1;
			goto next;
		}
	}
	
	//save user's information to user.txt
	fprintf(fp, "%s:%s:%s:%s\n", username, password, useremail, telphone);

next:
	fclose(fp);
	free(username);
	free(password);
	free(useremail);
	free(telphone);
	ack_client_register(sockfd, exist_flag);

	return;
}

void client_login(int sockfd, const char *json_data)
{
	FILE *fp;
	int exist_flag = 1;
	char *username = get_json_string_filed(json_data, "username");
	char *password = get_json_string_filed(json_data, "password");

	fp = fopen("user.txt", "a+");
	if(fp == NULL){
		perror("Fail to open file.");
		return;
	}

	while(1){
		char _username[100];
		char _password[100];
		char _useremail[100];
		char _telphone[100];

		int ret = fscanf(fp, "%[^:]:%[^:]:%[^:]:%s\n", _username, _password, _useremail, _telphone);
		if(ret == EOF){
			break;
		}

		if((strcmp(username, _username) == 0) && (strcmp(password, _password) == 0))
		{
			exist_flag = 0;
		}
	}
	fclose(fp);
	free(username);
	free(password);
	ack_client_login(sockfd, exist_flag);

	return;

}

void client_control_device(int sockfd, const char *json_data)
{
	int controlStatu;
	int deviceId;
	char *clientId = get_json_string_filed(json_data, "clientId");

	if(clientId == NULL){
		return;
	}

	if(getppid() != atoi(clientId)){
		free(clientId);
		return;
	}

	controlStatu = get_json_int_filed(json_data, "controlStatu");
	deviceId = get_json_int_filed(json_data, "deviceId");

	control_device(deviceId, controlStatu);
	free(clientId);

	return;
}

void client_resetPassword(int sockfd, const char *json_data)
{
	FILE *fp1, *fp2;
	char *username = get_json_string_filed(json_data, "username");
	char *oldPassword = get_json_string_filed(json_data, "oldPassword");
	char *newPassword = get_json_string_filed(json_data, "newPassword");
	int exist_flag = 1;

	fp1 = fopen("user.txt", "r+");
	if(fp1 == NULL){
		perror("Fail to open file.");
		return;
	}

	fp2 = fopen("user2.txt", "w+");
	if(fp2 == NULL){
		perror("Fail to open file.");
		return;
	}
	
	while(1){
		char _username[100];
		char _oldPassword[100];
		char _useremail[100];
		char _telphone[100];

		int ret = fscanf(fp1, "%[^:]:%[^:]:%[^:]:%s\n", _username, _oldPassword, _useremail, _telphone);
		if(ret == EOF){
			break;
		}
		
		if(((strcmp(username, _username) == 0) && (strcmp(oldPassword, _oldPassword) == 0)))
		{
			fprintf(fp2, "%s:%s:%s:%s\n", username, newPassword, _useremail, _telphone);
			exist_flag = 0;
			continue;
		}
		fprintf(fp2, "%s:%s:%s:%s\n", username, _oldPassword, _useremail, _telphone);
	}

	fclose(fp1);
	fclose(fp2);
	system("rm user.txt");
	system("mv user2.txt user.txt");
	free(username);
	free(oldPassword);
	free(newPassword);
	ack_client_reset(sockfd, exist_flag);

	return;

}

void client_forgetPassword(int sockfd, const char *json_data)
{
	FILE *fp1,*fp2;
	char *username = get_json_string_filed(json_data, "username");
	char *useremail = get_json_string_filed(json_data, "useremail");
	char *telphone = get_json_string_filed(json_data, "telphone");
	char *newPassword = get_json_string_filed(json_data, "newPassword");
	int exist_flag = 1;

	fp1 = fopen("user.txt", "r+");
	if(fp1 == NULL){
		perror("Fail to open file.");
		return;
	}

	fp2 = fopen("user2.txt", "w+");
	if(fp2 == NULL){
		perror("Fail to open file.");
		return;
	}
	
	while(1){
		char _username[100];
		char _oldPassword[100];
		char _useremail[100];
		char _telphone[100];

		int ret = fscanf(fp1, "%[^:]:%[^:]:%[^:]:%s\n", _username, _oldPassword, _useremail, _telphone);
		if(ret == EOF){
			break;
		}

		if((strcmp(username, _username) == 0) && (strcmp(useremail, _useremail) == 0) && (strcmp(telphone, _telphone) == 0))
		{
			fprintf(fp2, "%s:%s:%s:%s\n", username, newPassword, _useremail, _telphone);
			exist_flag = 0;
			continue;
		}
		fprintf(fp2, "%s:%s:%s:%s\n", username, _oldPassword, _useremail, _telphone);
	}


	fclose(fp1);
	fclose(fp2);
	system("rm user.txt");
	system("mv user2.txt user.txt");
	free(username);
	free(telphone);
	free(useremail);
	free(newPassword);
	ack_client_forget(sockfd, exist_flag);

	return;

}

	


void process_task(int sockfd, const char *json_data)
{
	int functionId;

	functionId = get_json_int_filed(json_data, "functionId");
	if(functionId < 0){
		return;
	}

	switch(functionId){
		case 1:
			client_register(sockfd, json_data);
			break;
		case 2:
			client_login(sockfd, json_data);
			break;
		case 3:
			client_control_device(sockfd, json_data);
			break;
		case 4:
			client_resetPassword(sockfd, json_data);
			break;
		case 5:
			client_forgetPassword(sockfd, json_data);
			break;
		default:
			break;
	}
	return;
}

void do_client(int sockfd)
{
	int ret;
	char buf[1024];

	while(1){
	
		printf("---------------Read------------------\n");
		//6.Read the data form client terminal
		ret = read(sockfd, buf, sizeof(buf) - 1);
		if(ret <= 0){
			break;
		}
		buf[ret] = '\0';
		printf("Read %d bytes: %s\n", ret, buf);

		process_task(sockfd, buf);
	}
	exit(0);
}


int main(int argc, const char *argv[])
{
	int ret;
	int listenfd;
	int clientfd;
	pid_t pid;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t addrlen = sizeof(client_addr);

	signal(SIGCHLD, SIG_IGN);

	//1.Create tcp socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0){
		perror("Fail to create socket");
		return -1;
	}
	printf("socket id : %d\n", listenfd);

	//2.Server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("192.168.43.128");
	
	//3.Bind server address
	ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret < 0){
		perror("Fail to bind");
		return -1;
	}

	//4.Set socket to listen mode
	ret = listen(listenfd, 128);
	if(ret < 0){
		perror("Fail to listen");
		return -1;
	}
	printf("listening...\n");
	
	//5.Extract request queue client request
	while(1){

		printf("---------------Accept---------------\n");
		clientfd = accept(listenfd, (struct sockaddr *)&client_addr, &addrlen);
		if(clientfd < 0){
			perror("Fail to accept");
			return -1;
		}
		printf("clientfd    : %d\n", clientfd);
		printf("client ip   : %s\n", inet_ntoa(client_addr.sin_addr));
		printf("client port : %d\n", ntohs(client_addr.sin_port));

		pid = fork();
		if(pid < 0){
			perror("Fail to fork");
			return -1;
		}
		if(pid == 0){
			close(listenfd);
			//child process
			do_client(clientfd);
		}
		
		close(clientfd);

	}
	
	return 0;
}
