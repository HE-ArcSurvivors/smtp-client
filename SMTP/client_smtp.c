/*
 * SMTP Client
 * Authors: Roman Yakovenko & Benjamin Margueron
 *
 * Created on June 12, 2013
 * Last Update on potato day
 */

/*
 * Sources:
 * http://www.spi.ens.fr/beig/systeme/sockets.html //sockets
 * http://man.he.net/man3/h_errno //gethostbyname
 * http://man7.org/linux/man-pages/man3/fopen.3.htm //fopen
 * http://www.bien-programmer.fr/pthreads.htm //Thread
 * http://www.developpez.net/forums/d1188490/c-cpp/c/fork-langage-c/ //Fork
 * http://www.samlogic.net/articles/smtp-commands-reference.htm //SMTP commands
 * http://www.serversmtp.com/en/smtp-error //SMTP error codes
 * http://email.about.com/cs/standards/a/smtp_error_code.htm //SMTP error codes in a nutshell
 * http://pic.dhe.ibm.com/infocenter/tpfhelp/current/index.jsp?topic=%2Fcom.ibm.ztpf-ztpfdf.doc_put.cur%2Fgtpc2%2Fcpp_write.html //write
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
//#include <pthread.h>

//char* sender = "roman.yakovenko@he-arc.ch";
//char* receiver = "benjamin.margueron@he-arc.ch";
char* sender = "benjamin.margueron@he-arc.ch";
char* receiver = "roman.yakovenko@he-arc.ch";
char* subject = "The Penguin god is coming";
char* message = "Do you have some time to talk about our savior, the Banana King?";
//char* host = "smtp.alphanet.ch";
char* host = "157.26.64.10";
const int port = 25; //25 (sans authentification), 465 (ssl) et 587 (authentification)

int connect_client(const char* host);
void disconnect_client(int connection);
int send_message(const char* sender, const char* subject, char* message, const char* host, const char* receiver);
int read_server(const int connection);
void create_message(const int connection, char* lineToAdd);
int error_tester(const int connection);

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
        switch (i) {
            case 1:
                sender = argv[i];
                break;
            case 2:
                subject = argv[i];
                break;
            case 3:
                message = argv[i];
                break;
            case 4:
                host = argv[i];
                break;
            case 5:
                receiver = argv[i];
                break;
        }

    printf("Welcome to our SMTP Client, epicness is coming to you\n");

    send_message(sender,subject,message,host,receiver);

    return 0;
}

int send_message(const char* sender, const char* subject, char* message, const char* host, const char* receiver){

    int connection;
	FILE *build_message;
	char buffer[1024];


    printf("Hello world! Sending BANANA COOKIES for the win :)\n\n");

	printf("Initializing the banana mailer\n");
    connection = connect_client(host);
	
	printf("\nLet\'s build our Banana Spam now\n");
	printf("\nTalk to me Banana Spammer\n");
	
	sprintf(buffer, "HELO client\r\n");
	create_message(connection, buffer);
	read_server(connection);
	
	sprintf(buffer, "MAIL FROM:<%s>\r\n", sender);
	create_message(connection, buffer);
	read_server(connection);
	
	sprintf(buffer, "RCPT TO:<%s>\r\n", receiver);
	create_message(connection, buffer);
	read_server(connection);
	
	create_message(connection, "DATA");
	read_server(connection);
	
	//sprintf(buffer, "From: %s", sender);
	sprintf(buffer, "From: 'Banana King' <banana@penguin-king.com>");
	create_message(connection, buffer);
	sprintf(buffer, "To: %s", receiver);
	create_message(connection, buffer);
	sprintf(buffer, "Subject: %s\r\n", subject);
	create_message(connection, buffer);
	//create_message("\r\n", buffer);
	
	create_message(connection, message);

	printf("\nLet\'s send this :)\n");
	create_message(connection, "\r\n.\r\n");
	read_server(connection);
	create_message(connection, "QUIT\r\n");
	read_server(connection);
	
	printf("\nByebye my Banana Spamer <3\n");
	disconnect_client(connection);

	

	return 1;

}

int connect_client(const char* host){

    int connection;

    connection = socket(AF_INET, SOCK_STREAM, 0);

    if (connection < -1){
        perror("socket() creation failed.\n");
		return -1;
		
    }else{
        struct sockaddr_in serverEndpoint;
        struct hostent *hostPointer;
        hostPointer = gethostbyname(host);

        if (!hostPointer){
			fprintf(stderr, "getHostByName() failed: %s.\n", hstrerror(h_errno));
			return -1;
			
        }else{
            serverEndpoint.sin_family = AF_INET;
            serverEndpoint.sin_port = htons(port);
            memcpy(&serverEndpoint.sin_addr, hostPointer->h_addr, sizeof(serverEndpoint.sin_addr));

			if (connect(connection, (struct sockaddr *) &serverEndpoint, sizeof(serverEndpoint)) != 0){
				perror("connect() failed");
				return -1;
				
			}else{
				printf("Connected to Banana spammer\n");
			}
		}
	}
	return connection;
}

void disconnect_client(const int connection) {
    shutdown(connection, 2);
    close(connection);
}

int read_server(const int connection){
	
	int goodToGo;
	
	do{
		goodToGo=1;
		if(error_tester(connection)==1){
			goodToGo=0;
			printf("Oh noooo, am I greylisted? Lets try again in 6 mins\n");
			sleep(360);
		}}while (goodToGo == 0);
	
	return 1;
}

int error_tester(const int connection){
	
	char buffer[1024];

	read(connection, buffer, sizeof(buffer));
	
	printf("%c%c%c ", buffer[0],buffer[1],buffer[2]);
	
	switch (buffer[0]){
		case '1':
		perror("The server does not respond\n");
			switch (buffer[1]){
				case '0':
				perror("The server is unable to connect.\n");
				case '1':
				perror("Connection refused or inability to open an SMTP stream.\n");
				default:
				perror("What a potato.. The error code is not possible =( \n");
			}
		return -1;
			
	    case '2':
		printf("The server has completed the task successfully.\n");
		return 0;
		
	    case '3':
		printf("The server has understood the request, but requires further information to complete it.\n");
		return 0;
		
	    case '4':
		perror("The server has encountered a temporary failure.\n");
		return 1;
		
	    case '5':
	    perror("The server has encountered an error.\n");
		return -1;
	    
		default:
		//printf("%s ", buffer);
	    perror("What a potato.. The error code is not possible =( \n");
		return -1;
    	}
}

void create_message(const int connection, char* lineToAdd){
    printf("%s\n", lineToAdd);
    write(connection, lineToAdd, strlen(lineToAdd));
    write(connection, "\r\n", 2);
}