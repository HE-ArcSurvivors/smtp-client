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

//TESTETETJHAGSKDJ HKLSDA GA KSLDGJASDJK ASBJH;DJKASDJKASDGKASKJLDASKD

char* sender = "roman.yakovenko@he-arc.ch";
char* receiver = "benjamin.margueron@he-arc.ch";
//char* default_sender = "benjamin.margueron@he-arc.ch";
//char* default_reciever = "roman.yakovenko@he-arc.ch";
char* subject = "test";
char* message = "data";
char* host = "localhost";

int connect();
void disconnect();
int send(const char*, const char*, const char*, const char*, const char*);
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
                host = argv[i];
                break;
            case 5:
                receiver = argv[i];
                break;
        }

    printf("Welcome to our SMTP Client, epicness is coming to you\n");
    return 0;
}

int send(const char* sender, const char* subject, const char* message, const char* host, const char* receiver) {

    printf("Hello world! Sending BANANA COOKIES for the win :)\n");

}
