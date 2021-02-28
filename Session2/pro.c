#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int V1,V2;
	printf("Enter V1: ");
	scanf("%d",&V1);
	printf("Enter V2: ");
	scanf("%d",&V2);
	char string[50], file_address[100];
	printf("Enter prefix: ");
	scanf("%s", string);
	printf("Enter file_address: ");
	scanf("%s", file_address);
	int i = 0;
	for(i = V1; i <= V2; i++){
		char command[50], str[6], temp[15];
		strcpy( command, "sudo adduser " );
		strcpy(temp, string);
		sprintf(str, "%d", i);
		strcat(temp, "-");
		strcat(temp, str);
		strcat(command, temp);
		system (command);
		temp[0]='\0';
		command[0]='\0';
		str[0]='\0';
	}
	 for(i = V1; i <= V2; i++){
        char command[150], str[6], temp[50];
		strcpy( command, "sudo cp -r " );
		strcat( command, file_address);
		strcat( command, " ");
		strcpy( temp, "/home/");
		strcat( temp, string);
		strcat( temp, "-");
		sprintf( str, "%d", i); 
		strcat( temp, str);
		strcat( command, temp);
		system (command);
		command[0]='\0';
		temp[0]='\0';
		str[0]='\0';
	}
	char command[50];
	strcpy(command1, "sudo cp ./prog.out /usr/local/bin");
	system(command1);
	return 0;
}

