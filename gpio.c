#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void initGpio (int gpio) {
	FILE *arquivo;
	char setValue [3];
	arquivo = fopen ("/sys/class/gpio/export", "ab");
	
	if (arquivo == NULL){
		printf ("DEU RUIIMM LEK!!");
	}
	rewind (arquivo);
	sprintf (setValue, "%d", gpio);
	fwrite (&setValue, sizeof (char), 3, arquivo);
	fclose (arquivo);
}

void setDirection (int gpio, int flag){
	char set_value_out [] = "out";
	char set_value_in [] = "in";
	char path [100];
	FILE *arquivo;
	sprintf (path, "/sys/class/gpio/gpio%d/direction", gpio);
	arquivo = fopen (path, "ab");
	if (arquivo == NULL){
		printf ("DEU RUIM LEK!!");
	}
	rewind (arquivo);
	if (flag == 0){
		fwrite (&set_value_out, sizeof (char), 3, arquivo);
	}
	else {
		fwrite (&set_value_in, sizeof (char), 2, arquivo);
	}
}

void setValue (int gpio, int value){
	char path [40];
	char set_value [3];
	FILE *arquivo;
	sprintf (path, "/sys/class/gpio/gpio%d/value", gpio);
	arquivo = fopen (path, "ab");
	rewind (arquivo);
	sprintf (set_value, "%d", value);
	fwrite (&set_value, sizeof (char), 1, arquivo);
	fclose (arquivo);
}
	
	
int main () {
	initGpio (60);
	srand( (unsigned)time(NULL) );
	while (1){
		int menu;
		menu = (rand () % 2) + 1;
		printf ("LIGAR OU DESLIGAR ALEATORIAMENTE!!!!\n");
		
		if (menu == 1){
			setDirection (60, 0);
			setValue (60, 1);
		}
		else {
			setDirection (60, 0);
			setValue (60, 0);
		}
		sleep (1);
	}
	
	return 0;
}
