#include <SDL2/SDL.h>
#include<stdio.h>
#include<string.h> 
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

#define MENU "\\H"
#define LOAD "\\L"
#define SAVE "\\S"
#define DESIGN "\\D"
#define GENERATE "\\G"
#define RUN "\\R"
#define EXIT "\\E"
#define QUIT "\\Q"
#define PRINT "\\P"
#define END "END"
#define BUFLEN 1024
#define WIDTH 600
#define HEIGHT 360
#define FRAMERATE 60

int COUNT_NEIGHBORS(int **p, int x, int y);
void PRINT_MAP(int **p);
void generate(int **p);
void MAIN_MENU();
void T_errors();
void design();
void R_function(int **p);
void SAVE_MAP(int **p);
void LOAD_MAP();
void run(int **p);

void event_loop(SDL_Surface *screen,SDL_Window *win){
    while(1){
        long begin = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                return;
            }
        }
        long current = SDL_GetTicks();
        long cost=current-begin;
        long frame=1000/FRAMERATE;
        long delay=frame-cost;
        if(delay>0){
            SDL_Delay(20);
        }
    }
}

int main(){
    if(SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Cannot init vedio,%s", SDL_GetError);
        return 3;
    }

    SDL_Window *win=SDL_CreateWindow("Life Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if(win==NULL){
        SDL_Log("Cannot create window,%s",SDL_GetError);
        return 4;
    }

    SDL_Delay(3000);

    SDL_Surface * screen=SDL_GetWindowSurface(win);
    SDL_Rect r={0,0,WIDTH,HEIGHT};
    SDL_FillRect(screen,&r,0xffffffff);
    SDL_UpdateWindowSurface(win);
    event_loop(screen,win);
    SDL_DestroyWindow(win);

    printf("---------------------------------\n");
    printf("---------------------------------\n");
    printf("            LIFE GAME\n");
    printf("---------------------------------\n");
    printf("---------------------------------\n"); 
    MAIN_MENU();
    T_errors();

    
    return 0;
}

void MAIN_MENU(){
    system("cls");
	printf("\t[\\H]\tPrint command prompt\n");
    printf("\t[\\P]\tPrint current map\n");
    printf("\t[\\L]\tLoad the map\n");
    printf("\t[\\S]\tSave the map\n");
    printf("\t[\\D]\tEnter map design mode\n");
    printf("\t[\\Q]\tQuit map design mode\n");
    printf("\t[\\G]\tTo generate the next generation of life\n");
    printf("\t[\\R]\tStart the game of life\n");
    printf("\t[\\E]\tStop the game of life\n");
    printf("\t[END]\tQuit the game\n");
}

void PRINT_MAP(int **p){
    int row,col;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf(p[i][j]>0?"¡ö":"¡õ");
        }
        printf("\n");
    }
}

int COUNT_NEIGHBORS(int **p, int x, int y){
    int row,col;
    int sum=0;
    for(int i=x-1;i<=x+1;i++) 
        for(int j=y-1;j<=y+1;j++)
        {
         if(i>=0&&i<row&&j>=0&&j<col)
         sum=sum+p[i][j];
        }
    sum=sum-p[x][y];
    return sum;
}

void generate(int **p){
    int row,col;
    int Livingcells[row][col];
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++){
            Livingcells[i][j] = COUNT_NEIGHBORS(p, i, j);
        }
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++){
         if(p[i][j]==1){
             if(Livingcells[i][j]<2)
        p[i][j]=0;
             else if(Livingcells[i][j]>3)
        p[i][j]=0;
         }
         else if(Livingcells[i][j]==3)
          p[i][j]=1;
        }
        PRINT_MAP(p);
}

void SAVE_MAP(int **p){
    int row,col;
	printf("Enter [filename] to save the map");
    char filename[BUFLEN];
    scanf("%s",filename);
    fflush(stdin);
    FILE *fpWrite;
	fpWrite=fopen(filename,"w");  
    if(fpWrite==NULL)  
    printf("Cannot open the file!\n");
    fprintf(fpWrite,"%d %d\n",row,col);   
         for(int i=0;i<row;i++){
             for(int j=0;j<col;j++){
                 fprintf(fpWrite,"%d ",p[i][j]); 
		     }
         fprintf(fpWrite,"\n"); 
         }
    fclose(fpWrite);
    printf("Saved map, file name%s\n",filename) ;
    R_function(p); 
}

void LOAD_MAP(){
    int row,col;
	printf("Enter [filename] to open the map"); 
    char filename[BUFLEN];
    scanf("%s",filename);
    fflush(stdin);
	FILE *fp;
    int i,j;
	fp=fopen(filename,"r");
    if(fp==NULL)
        printf("Cannot find the mapy!\n");
    fscanf(fp,"%d%d",&row,&col);
	int map[row][col];
    fscanf(fp,"%*[^\n]");
    for(i=0; i<row; i++){
        for(j=0; j<col; j++)
             fscanf(fp,"%d",&map[i][j]);
    }
	fclose(fp);
    for(i=0; i<row; i++){
        for(j=0; j<col; j++)
             printf(map[i][j]>0?"¡ö":"¡õ");
    printf("\n");
    }
    int *p[row] ;
    for(int i=0 ;i<row;i++)
       p[i]=map[i] ;
    R_function(p); 
}
 
void design(){
    int row,col;
	printf("Enter map design mode\n");
	int row_live=0,col_live=0;
	printf("Please enter the number of rows and columns to create the map(ROW COLUM):");
	scanf("%d%d",&row,&col) ;
	fflush(stdin);  
	int map[row][col]; 
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++)
        map[i][j]=0;
    }
	for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++)
        printf("¡õ"); 
    printf("\n");
    } 
	char buf[BUFLEN];
    printf("Please enter the row and column of living cells(ROW COLUM)\n ([\\Q]Exit map design mode):") ;
    fgets(buf,BUFLEN,stdin);
    buf[strlen(buf) - 1] = '\0';
    
	while (strcmp(buf,QUIT) != 0){
		row_live=0,col_live=0;
		int i=0;
		while(buf[i]!=' ')
		    i++;
		for(int j=i-1,k=0;j>=0;k++,j--)
			row_live=row_live+(buf[k]-'0')*pow(10,j); 
		int m=i+1;
	    while(buf[m]!='\0')
	        m++;
	    int p;
	    for(int j=m-i-2,p=i+1;j>=0;j--,p++)
	        col_live=col_live+(buf[p]-'0')*pow(10,j);
        if((row_live>row||col_live>col)||(row_live<=0||col_live<=0)){
            printf("Please enter the row and column of living cells(ROW COLUM)\n([\\Q]Exit map design mode):");
		    fgets(buf,BUFLEN,stdin);
		    fflush(stdin); 
            buf[strlen(buf)-1] = '\0';
         }
	    else{
	    map[row_live-1][col_live-1]=1;
	        for(int i = 0; i < row; i++){
                for(int j = 0; j < col; j++){
                    if(map[i][j] == 1)
                        printf("¡ö");
                    else printf("¡õ"); 
	                }  
		    printf("\n"); 
            }
		printf("Please enter the row and column of living cells(ROW COLUM)\n([\\Q]Exit map design mode)£º");
        fgets(buf,BUFLEN,stdin);
		fflush(stdin); 
        buf[strlen(buf) - 1] = '\0';
        }
    }
    printf("You can Enter [\\S] to save the map in time\n");
	int *p[row] ;
    for(int i=0 ;i<row;i++)
       p[i]=map[i];
	R_function(p);
}

void run(int **p){
    char IMPUT,buf[BUFLEN];
    int SYMBOL=1;
	while(1){
     if(SYMBOL==1){
	 generate(p);
	 printf("You can pause by entering Enter, or exit the auto run by entering [\\E]\n");
	 Sleep(2000);
     }
     if(_kbhit()){
	 IMPUT=_getch();
		if(IMPUT==13)
		    SYMBOL*=-1;
	 else if(IMPUT=='\\'){
	 	 printf("%c",IMPUT);
	     IMPUT=getchar();
	     fflush(stdin); 
         if (IMPUT=='E'){
         printf("Exit the automatic mode\n");
         break;
         }
	}
	} 
    }
    R_function(p);
}

void T_errors(){
	char buf[BUFLEN];
    printf("Please enter instructions (Enter \\H to view all instructions): ");
    fgets(buf,BUFLEN,stdin);  
    buf[strlen(buf) - 1] = '\0';  
    if (strcmp(buf,MENU) == 0) {
    MAIN_MENU();
    T_errors();
	}else if(strcmp(buf,LOAD) == 0){
        LOAD_MAP();
    } else if(strcmp(buf,SAVE) == 0){
    	printf("No map! Please design a map or open an existing map first.");
        T_errors(); 
    } else if(strcmp(buf,DESIGN) == 0){
        design();
    } else if(strcmp(buf,GENERATE) == 0){
        printf("No map?");
        T_errors();
    }else if(strcmp(buf,RUN) == 0){
        printf("No map!"); 
        T_errors();
    } else if(strcmp(buf,QUIT) == 0){
        printf("No map!");
        T_errors();
    } else if(strcmp(buf,EXIT) == 0){
        printf("No map!"); 
        T_errors();
    } else if(strcmp(buf,PRINT) == 0){
        printf("No map!"); 
        T_errors();
    } else if(strcmp(buf,END) == 0){
        printf("Quit the game. Bye!");
        system("exit");
    } else {
        printf("Invalid order!\n");
        T_errors();
    }
}

void R_function(int **p){
    char buf[BUFLEN];
    printf("Please enter instructions (Enter \\H to view all instructions): ");
    fgets(buf,BUFLEN,stdin); 
    buf[strlen(buf) - 1] = '\0';
    if (strcmp(buf,MENU) == 0) {
    MAIN_MENU();
    R_function(p);
	}else if(strcmp(buf,LOAD) == 0){
        LOAD_MAP();
    } else if(strcmp(buf,SAVE) == 0){
    	SAVE_MAP(p);
    } else if(strcmp(buf,DESIGN) == 0){
        design();
    } else if(strcmp(buf,GENERATE) == 0){
        generate(p);
        printf("You can Enter \\G to continue to form the next generation of life\n");
        R_function(p);
    } else if(strcmp(buf,RUN) == 0){
        run(p);
    } else if(strcmp(buf,QUIT) == 0){
        printf("QUIT\n");
    } else if(strcmp(buf,EXIT) == 0){
        printf("EXIT\n");
        R_function(p);
    } else if(strcmp(buf,PRINT) == 0){
        PRINT_MAP(p);
        R_function(p);
    } else if(strcmp(buf,END) == 0){
        printf("Quit the game.Bye!");
        system("exit");
    } else {
        printf("Invalid order!\n");
        R_function(p);
    }
}
