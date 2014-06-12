/*
 * SMTP Client
 * Authors: Roman Yakovenko & Benjamin Margueron
 *
 * Created on June 12, 2013
 * Last Update on potato day
 */

/*
 * Sources:
 * http://www.spi.ens.fr/beig/systeme/sockets.html
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


char* sender = "roman.yakovenko@he-arc.ch";
char* receiver = "benjamin.margueron@he-arc.ch";
//char* default_sender = "benjamin.margueron@he-arc.ch";
//char* default_reciever = "roman.yakovenko@he-arc.ch";
char* subject = "test";
char* message = "data";
char* host = "smtp.alphanet.ch";
const int port = 25; //25 (sans authentification), 465 (ssl) et 587 (authentification)

int connect_client(const char*);
void disconnect();
int send_message(const char*, const char*, const char*, const char*, const char*);
int read_message();
void write_message();
int error();

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

int send_message(const char* sender, const char* subject, const char* message, const char* host, const char* receiver) {

    int connection;

    printf("Hello world! Sending BANANA COOKIES for the win :)\n\n");

	printf("Initializing the banana mailer\n");
    connection = connect_client(host);

	return 1;

}

int connect_client(const char* host){

    int connection;

    connection = socket(AF_INET, SOCK_STREAM, 0);

    if (connection < -1) {
        perror("socket() creation failed.\n");
		return -1;
    }else{
        struct sockaddr_in serverEndpoint;
        struct hostent *hostPointer;
        hostPointer = gethostbyname(host);

        if (!hostPointer) {
			fprintf(stderr, "getHostByName() failed: %s.\n", hstrerror(h_errno));
			return -1;
        }else{
            serverEndpoint.sin_family = AF_INET;
            serverEndpoint.sin_port = htons(port);
            memcpy(&serverEndpoint.sin_addr, hostPointer->h_addr, sizeof(serverEndpoint.sin_addr));

			if (connect(connection, (struct sockaddr *) &serverEndpoint, sizeof(serverEndpoint)) != 0) {
				perror("connect() failed");
				return -1;
			}else{
				printf("Connected to Banana spammer\n");
				//FILE *f;
			}
		}
	}

	return connection;

}
