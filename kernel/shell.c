#include <stdio.h>
#include <fat12.h>
#include "ia32.c"

void help(){
	printf(" \n");
	printf("Shell Luxur\n");
	printf(" \n");
	printf("ls - Lista el directorio actual\n");
	printf("cd [argv] - ingresa a un directorio o sale de el ejemplo: cd boot o cd ..\n");
	printf("exec [argv] - Ejecuta una Aplicacion ejemplo: exec hola.exe\n");
	printf("vi [argv] - Muestra el contenido de un archivo ejemplo: vi license.txt\n");
	printf(" \n");
}



void shell_cls(){
	cls();
}


void shell_ls(){ //lista ficheros
	ls();
}


void shell_cd(char *path){ //cambia de directorio
	cd(path);
}


void shell_exec(char *path){ //ejecuta un archivo

int filesize = get_file_size(path);

static char buff[70000];
file_open(path,buff);

unsigned int moduleptr = kmalloc(70000);
                    
memcpy((void*)moduleptr,(void*) buff, filesize);

exec(moduleptr);

}


void shell_vi(char *path){ //muestra el contenido de un archivo

int rec=0;
static char buff[70000];

	file_open(path,buff);

	while(buff[rec]!='\0'){
		putchar(buff[rec]);
		rec++;
	}

}


void shell(){

static char *comand;
static char cmd[200];
static char argv[200];
int argc=0;
int bb=0;
static int c;


for(;;){ 

	printf("\nroot@Luxur[/%s]: ",pwd()); //pwd devuelve el directorio actual
	comand = gets(); 

	//*********************separamos el comando del argumento****************************//
	while((c=*comand++)!=' ' && c != 0){
		cmd[bb]=(unsigned char)c;
		bb++;
	}

	//si es el final del comando es porque no hay argumentos
	if(c!=0)argc=1;
	else argc=0;

	cmd[bb]=0; //final del comando
	bb=0;

	while((c=*comand++)!= 0){
        argv[bb]=(unsigned char)c;
        bb++;
	}
	
	argv[bb]=0; //final del argumento
	bb=0;

/************se separo correctamente el comando y el argumento************************/


	if(strcmp(cmd,"ls")==0){
		printf(" \n");
		shell_ls();
		printf(" \n");
	}

	if(strcmp(cmd,"cd")==0){
		if(argc!=0)shell_cd(argv);
		else printf("No hay Argumentos\n");
	}

	if(strcmp(cmd,"exec")==0){
		if(argc!=0)shell_exec(argv);
		else printf("No hay Argumentos\n");
	}

	if(strcmp(cmd,"help")==0){
		help();
	}

	if(strcmp(cmd,"vi")==0){
		if(argc!=0)shell_vi(argv);
		else printf("No hay Argumentos\n");
	}

	if(strcmp(cmd, "reboot")==0){
		printf("Rebooting....\n\n");
		reboot();
	}

	if(strcmp(cmd, "cls") == 0){
		shell_cls();
	}


	if(strcmp(cmd, "echo") == 0){
		if(argc!=0){
			printf("\n%s", argv);
		}
	}




} //fin del for()

}


