/*
 * SMTP Client
 * Authors: Roman Yakovenko & Benjamin Margueron
 *
 * Created on June 12, 2013
 * Last Update on potato day
 */


#include <stdio.h>
#include <stdlib.h>
//#include <netdb.h>
//#include <unistd.h>

char* sender = "roman.yakovenko@he-arc.ch";
char* receiver = "benjamin.margueron@he-arc.ch";
//char* default_sender = "benjamin.margueron@he-arc.ch";
//char* default_reciever = "roman.yakovenko@he-arc.ch";
char* subject = "test";
char* message = "data";
char* hostname = "localhost";

int connect();
void disconnect();
int send();
int read();
void write();
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
                hostname = argv[i];
                break;
            case 5:
                receiver = argv[i];
                break;
        }

    printf("Hello world! BANANA COOKIE for the win :)\n");
    return 0;
}
