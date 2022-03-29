/*
 ============================================================================
 Name        : SystemConsole.c
 Author      : Maxim Savenkov
 Version     :
 Copyright   : © Maxim Savenkov 2022
 Description : System Restart Menu
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void init();
void scup();
void msleep(int t);
void listen();
void selectM(int i, int p);
void rebootM(int i);
void *clockMain(void *threadid);
int w = 1;
int c = 1;
int a = 1;
int sup = 0;
int res = 0;
int useless = 1;
void gotoxy(int x, int y) {
	printf("%c[%d;%df",0x1B,y,x);
}
void *wifiError(void *t) {
	while (w == 0) {
		system("networksetup -setairportpower en0 off");
		msleep(50);
	}
	system("networksetup -setairportpower en0 on");
	return NULL;
}

void *displayError(void *t) {
	while (c == 0) {
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0");
		msleep(20 + rand() % 10);
		system("brightness 0");
		msleep(10 + rand() % 20);
		system("brightness 0.05");
		msleep(10 + rand() % 10);
	}
	system("brightness 1");
	return NULL;
}

void *audioError(void *t) {
	while (a == 0) {
		system("osascript -e 'set Volume 0'");
		msleep(50);
	}
	system("osascript -e 'set Volume 5'");
	return NULL;
}

short unsigned int selection = 1;

int main(void) {
	srand(time(NULL));
	pthread_t pt;
	int rc = pthread_create(&pt, NULL, clockMain, (void *)2);
	      if (rc) {
	         printf("Error:unable to create thread, %d\n", rc);
	         exit(-1);
	}
	init();
	pthread_exit(NULL);
}

void *clockMain(void *threadid) {
	if (useless == 12) {
		return NULL;
	}
	msleep(1000);
	if (res == 0) {
		if (rand() % 300 == 1 && w == 1) {
			w = 0;
			printf("\a");
			pthread_t pt;
			int rc = pthread_create(&pt, NULL, wifiError, (void *)5);
			if (rc) {
				printf("Error:unable to create thread, %d\n", rc);
				exit(-1);
			}
			if (sup == 1) {
				gotoxy(23, 7);
				printf("\x1b[31merror\x1b[0m");
				gotoxy(0, 11);
				fflush(stdout);
			}
		}
		else if (rand() % 100 == 1 && c == 1) {
			c = 0;
			pthread_t pt;
			int rc = pthread_create(&pt, NULL, displayError, (void *)3);
			      if (rc) {
			         printf("Error:unable to create thread, %d\n", rc);
			         exit(-1);
			}
			if (sup == 1) {
			      gotoxy(23, 6);
			      printf("\x1b[31merror\x1b[0m");
			      gotoxy(0, 11);
			      fflush(stdout);
			}
		}
		else if (rand() % 150 == 1 && a == 1) {
			a = 0;
			system("osascript -e 'set Volume 1'");
			system("afplay /usr/local/etc/e.mp3");
			pthread_t pt;
			int rc = pthread_create(&pt, NULL, audioError, (void *)7);
			if (rc) {
				printf("Error:unable to create thread, %d\n", rc);
				exit(-1);
			}
			if (sup == 1) {
				gotoxy(23, 5);
				printf("\x1b[31merror\x1b[0m");
				gotoxy(0, 11);
				fflush(stdout);
			}
		}
	}
	clockMain(threadid);
	return NULL;
}

void init() {
	if (useless == 12) {
		return;
	}
	system("clear");
	printf("\x1b[0m\n\n\n\n\n\n\n\n\n\n\n             |^^^^^^^^^^|");
	gotoxy(0, 0);
	system("/bin/stty raw");
	char c = 0;
	while (c != 'w') {
		c = getchar();
	}
	system("/bin/stty cooked");
	scup();
	init();
}

void scup() {
	sup = 1;
	char one[128] = "\x1b[31merror\x1b[0m";
	char two[128] = "\x1b[31merror\x1b[0m";
	char three[128] = "\x1b[31merror\x1b[0m";
	if (a == 1) {
		strcpy(one, "");
	}
	if (c == 1) {
		strcpy(two, "");
	}
	if (w == 1) {
		strcpy(three, "");
	}
	selection = 1;
	system("clear");
	printf(""
			"\n system restart"
			"\n menu>>>"
			"\n"
			"\n  >>>  audio devices  %s"
			"\n       display system %s"
			"\n       wlan internet  %s"
			"\n"
			"\n       reboot all"
			"\n       exit\n", one, two, three);
	listen();
}

void selectM(int i, int p) {
	if (i < 4) {
		gotoxy(0, i + 4);
		printf("  >>>");
	}
	else {
		gotoxy(0, i + 5);
		printf("  >>>");
	}
	if (p < 4) {
		gotoxy(0, p + 4);
		printf("     ");
	}
	else {
		gotoxy(0, p + 5);
		printf("     ");
	}
	gotoxy(0, 11);
}

void listen() {
	int c;
	system ("/bin/stty raw");
	c = getchar();
	switch(c) {
	case 115:
		if (selection < 5) {
			selectM(selection + 1, selection);
			selection++;
		}
		else {
			selectM(1, selection);
			selection = 1;
		}
		break;
	case 119:
		if (selection > 1) {
			selectM(selection - 1, selection);
			selection--;
		}
		else {
			selectM(5, selection);
			selection = 5;
		}
		break;
	case 13:
		if (selection == 5) {
			system("/bin/stty cooked");
			sup = 0;
			return;
			break;
		}
		else {
			rebootM(selection);
		}
		break;
	default:
		break;
	}
	//up = 279165
	//down = 279166
	//enter = 13
	//e = 101
	system ("/bin/stty cooked");
	listen();
}

void rebootM(int i) {
	res = 1;
	srand(time(NULL));
	if (i == 4) {
		for (int j = 0; j < (4 + rand() % 3); j++) {
				gotoxy(23, i + 5);
				printf("\a");
				fflush(stdout);
				msleep(200);
				gotoxy(24, i + 5);
				fflush(stdout);
				msleep(200);
				gotoxy(25, i + 5);
				fflush(stdout);
				msleep(200);
				gotoxy(26, i + 5);
				printf("\a");
				fflush(stdout);
				msleep(200);
				gotoxy(27, i + 5);
				fflush(stdout);
				msleep(200);
				if (j > 1) {
					c = 1;
				}
			}
			gotoxy(22, 5);
			printf("         ");
			gotoxy(22, 6);
			printf("         ");
			gotoxy(22, 7);
			printf("         ");
			gotoxy(0, 11);
			fflush(stdout);
			a = 1;
			w = 1;
	}
	else {
		gotoxy(22, i + 4);
		printf("         ");
		for (int j = 0; j < (3 + rand() % 3); j++) {
			gotoxy(23, i + 4);
			printf("\a");
			fflush(stdout);
			msleep(200);
			gotoxy(24, i + 4);
			fflush(stdout);
			msleep(200);
			gotoxy(25, i + 4);
			fflush(stdout);
			msleep(200);
			gotoxy(26, i + 4);
			printf("\a");
			fflush(stdout);
			msleep(200);
			gotoxy(27, i + 4);
			fflush(stdout);
			msleep(200);
			if (i == 2 && j == 2) {
				c = 1;
			}
		}
		gotoxy(0, 11);
		if (i == 1) {
			a = 1;
		}
		else if (i == 3) {
			w = 1;
		}
	}
	res = 0;
}

void msleep(int t) {
	usleep(t * 1000);
}
