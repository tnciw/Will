#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

#define true 1
#define false 0

void gotoxy(int xpos, int ypos);//定位遊戲座標系統 

void showCursor(int visible);

typedef struct snake{//建立蛇的結構x,y變數 

    int x;

    int y;

}Snake;

Snake sBody[1000]; // range = 20*50 = 1000蛇的移動範圍=長乘寬=1000 

void printSnake(int i,int path);


//印牆 
void printWall();



void printInformation(int food, int speed, int bomb);



void setSite(int i, int site_x, int site_y);




void setStartSite();
void butterfly();

void pupa();


int GuessNumber(int ans, int min, int max,int counter);//第二個小遊戲函數，終極密碼 

 



// The player record output a file
int store_playerRecord( char name[100], int score,double time,int SorF);

int main()//主程式，包括蛇的連續移動、掉(吃)尾巴，吃0、x、盒子 
{
    int startBodyLengh = 5, startEatenFood = 0, bodyLengh,eatenFood;
    int startEatenBomb = 0,eatenBomb;
    clock_t total,present;
	int isevolve=0;

    int keyinFirst, keyinSecond;

    int i, j, gameOver = false, isFoodEaten = false, xyChanged = false;
    int isBombEaten = false;

    int path = 2; // 方向

    int snakeSpeed = 100;

    char gameKey = 'y';

    Snake foodSite, coor, last;
	Snake bombSite;
	int empty=NULL;
	srand(time(NULL));

    showCursor(0);

    while(1){

        if(gameKey == 'n' || gameKey == 'N') break;

        // 初始狀態

        setStartSite();//定位初始位置 

        printWall();//印牆 

        bodyLengh = startBodyLengh;

        eatenFood = startEatenFood;
        eatenBomb = startEatenBomb;
        

        coor.x = 1; 

        coor.y = 4; 

        path = 2; 

        isFoodEaten = false;
        isBombEaten = false;
        

        gameOver = false;

        xyChanged = false;

        snakeSpeed = 100;
        total=0;
        isevolve=0;

        printInformation(startEatenFood, snakeSpeed,startEatenBomb);//印出右側資訊 

        for(i=0; i<bodyLengh; i++)

            printSnake(i,path);


        do{

            gotoxy(55, 19);

            printf("Enter to start.");
            

			
            gameKey = getch();
         

            gotoxy(55,19);

            printf("               ");
            if(gameKey==13){
            	present=clock();
			}
            
        	
        
		}while(gameKey != 13);



        while( !gameOver ){

            printInformation(eatenFood, snakeSpeed, eatenBomb);//印出右側資訊 

            if( !isFoodEaten ){ // 如果沒食物, 隨機算出一個食物的位置

                foodSite.x = (rand()%23*2+1)+2;

                foodSite.y = rand()%17+2;

                isFoodEaten = true;

            }

            gotoxy(foodSite.x, foodSite.y);

            printf("@");

            xyChanged = false;

 			if(! isBombEaten){//若炸彈沒有被吃掉 
 				
 				bombSite.x = (rand()%23*2+1)+2;
 				
 				bombSite.y = rand()%17+2;
 				gotoxy(sBody[bodyLengh].x,sBody[bodyLengh].y);
 				printf(" ");
 				sBody[bodyLengh].x=empty;
 				sBody[bodyLengh].y=empty;
 				
 				isBombEaten = true;
			}
			 
			gotoxy(bombSite.x, bombSite.y);
			
			printf("X");
			
			
			
				
			

            if( kbhit() ){ // 鍵盤敲擊

                keyinFirst = getch();

                if(keyinFirst == 224) {  

                    keyinSecond = getch();

                    switch(keyinSecond){//定義鍵盤上下左右移動方式 

                        case 72: /* up, 1 */

                            coor.y--;

                            path = 1;

                            break;

                        case 80: /* down, 2 */

                            coor.y++;

                            path = 2;

                            break;

                        case 75: /* left, 3 */

                            coor.x-=2;

                            path = 3;

                            break;

                        case 77: /* right, 4 */

                            coor.x+=2;

                            path = 4;

                            break;

                    }

                    xyChanged = true;// 

                }

                if(keyinFirst == 'p' || keyinFirst == 'P'){//若按p的話停住 
					total=total+clock()-present;

                    do{

                        gotoxy(55, 19);

                        printf("Pause.Press P to continue.");//印出Pause 

                        gameKey = getch();

                        gotoxy(55, 19);

                        printf("                          ");//覆蓋 
                        
						if(gameKey == 'p' && gameKey == 'P'){
							present=clock();
						
						} 
                        
                    }while(gameKey != 'p' && gameKey != 'P');

                }

                if(keyinFirst == '='||keyinFirst=='+'){//直接用等於不用加SHIFT 加速 

                    if(snakeSpeed > 10) snakeSpeed -= 10;

                        keyinFirst = '\0';

                }

                if(keyinFirst == '-'){//減速 

                    if(snakeSpeed < 300) snakeSpeed += 10;

                        keyinFirst = '\0';

                }

  

            } else { // 沒有任何動作則順著path(方向)前進

                switch(path){

                    case 1: /* up, 1 */

                        coor.y--;

                        path = 1;

                        break;

                    case 2: /* down, 2 */

                        coor.y++;

                        path = 2;

                        break;

                    case 3: /* left, 3 */

                        coor.x-=2;

                        path = 3;

                        break;

                    case 4: /* right, 4 */

                        coor.x+=2;

                        path = 4;

                        break;

                    }

                    xyChanged = true;

                }

                for(i=1; i<bodyLengh; i++){ /* Did snake die? */

                    if(coor.x == sBody[i].x && coor.y == sBody[i].y){
                    	total=total+clock()-present;
						gameOver = true;
                    	
					}//若蛇碰到自己的身體則遊戲結束 

                        

                }

                if(gameOver == 0 && xyChanged == 1){ /* Snake moving */

                    if(coor.x>0 && coor.x<50 && coor.y>0 && coor.y<20){

                        last.x = sBody[bodyLengh-1].x;

                        last.y = sBody[bodyLengh-1].y;
                        

                        for(i=bodyLengh-1; i>=0; i--){

                            if(i == 0)

                                setSite(i, coor.x, coor.y);

                            else

                                setSite(i, sBody[i-1].x, sBody[i-1].y);

                    }

                    for(i=0; i<bodyLengh; i++){//印出蛇身長度 

                        printSnake(i,path);

                    }

                    Sleep(snakeSpeed);

                    gotoxy(last.x, last.y); // 清尾巴

                    printf(" ");

                }

                else {
                	total=total+clock()-present;
                	gameOver = true;
				}

              

                if(sBody[0].x == foodSite.x && sBody[0].y == foodSite.y){ /* Snake ate food */

                    isFoodEaten = false;

                    if(bodyLengh<1000) bodyLengh++; // 避免蛇身超出陣列長度

                    eatenFood++;
                    if((eatenFood-eatenBomb*5)>=10){
                    	system("CLS");
                    	printf("歡迎來玩\"終極密碼\"!\n請輸入1~100之間的數字\n電腦也會從1~100之間挑一個數字當\"密碼\"\n");
						printf("當玩家猜到密碼時，遊戲結束\n");
						printf("猜數數字小於7次時 則玩家獲得勝利\n\n");
						
						int answer;
						srand(time(NULL));
						answer=rand()%100+1;
	  
						isevolve=GuessNumber(answer,1,100,0);
						total=total+clock()-present;
						gameOver=true;
                    	
					}

                }
             
			    if(sBody[0].x == bombSite.x && sBody[0].y == bombSite.y){/* Snake ate bomb */
                	
                	isBombEaten = false;
                	if(bodyLengh>=1) bodyLengh--;
                	eatenBomb++;
                	
				}
				
				
            }

        }

        /* Game over ? */
		//遊戲結束畫面，印出分數 
        while(1){
			double time_taken = ((double)total)/CLOCKS_PER_SEC;
            system("CLS");

            printf("Your Grade: %d\n", eatenFood* 100); 
			
			printf("\nEaten bomb: %d\n", eatenBomb);
			printf("It took the caterpiller %.2f seconds to evolve", time_taken);
			if(isevolve){
				printf(" and the caterpiller made it.\n");
			}else{
				printf(" but the caterpiller failed.\n");
			}	
	
			printf("Game over.\nPlay again? (y/n) \n");

            gameKey = getch();

            if(gameKey == 'y' || gameKey == 'Y'){//要繼續玩 

                system("CLS");

                break;

            }
            if(gameKey == 'n' || gameKey == 'N'){//不要繼續玩 
				
				int save=0;

				printf("\nDo you want to save your record?(y/n)\n");				
				
				save=getch();
				
				if(save == 'y' || save == 'Y'){//要存檔，執行存檔函數 
					
					printf("\nYoue name:");
					
					char name[20]={0};
					
					scanf("%s",&name);
					int T_score=(eatenFood-eatenBomb*5)*100;
					
					if(store_playerRecord(name,T_score,time_taken,isevolve)==0){//存檔函數執行失敗 
						
						printf("\nWhoops! Fail to save the record.\n");
						
						break;
					}
					else{//存檔函數執行成功 
						
						printf("\nYes! Recored saved!.\n");

		                break;
						}
				}
				else if(save == 'n' || save == 'N'){//不要存檔跳出遊戲 
					
				    system("CLS");

	                break;
	
				}
				
			}

        }

    }
    printf("Bye!\n");

    system("pause");

    return 0;
}
void gotoxy(int xpos, int ypos)//定位遊戲座標系統 

{

    COORD scrn;//定義XY座標 

    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);//取得輸出的控制權

    scrn.X = xpos; scrn.Y = ypos;

    SetConsoleCursorPosition(hOuput,scrn);//去指定座標 

}

void showCursor(int visible)

{

    CONSOLE_CURSOR_INFO ConCurInf;//右方控制器的資訊 

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//取得輸出的控制權 

    GetConsoleCursorInfo(hStdOut, &ConCurInf);

    ConCurInf.bVisible = visible;

    SetConsoleCursorInfo(hStdOut, &ConCurInf);


}

void printSnake(int i,int path){//印出蛇的函數 

    gotoxy(sBody[i].x, sBody[i].y);
    if(i==0){
    	switch(path)
		{
    		case 1:
    			printf("^");
    			break;
    		case 2:
    			printf("v");
    			break;
    		case 3:
    			printf("<");
    			break;
    		case 4:
    			printf(">");
    			break;
		}
    	
	}else{
		printf("O");
	}

    

}
//印牆 
void printWall(){

    int i, j;

    for(i=0; i<21; i++){

        for(j=0; j<51; j+=2){

            if(i==0 || i==20 || j==0 || j==50){

                gotoxy(j, i);

                printf("*");

            }

        }

    }

}

void printInformation(int food, int speed, int bomb){//印出右側資訊，遊戲規則、速度、積分等 

    gotoxy(55, 1);

    printf("Use + to increase the");

    gotoxy(55, 2);

    printf("snake moving speed.");

    gotoxy(55, 4);

    printf("Use - to decrease the");

    gotoxy(55, 5);

    printf("snake moving speed.");

    gotoxy(55, 7);

    printf("Use P to pause.");

    gotoxy(55, 9);

    printf("Grade: %d", food * 100 - bomb * 500);

    gotoxy(55, 11);

    if(speed == 10) printf("Speed: %3d (The fastest)", 310-speed);//速度底限 

    else if(speed == 300) printf("Speed: %3d (The slowest)", 310-speed);//速度上限 

    else printf("Speed: %3d              ", 310-speed);
    
    gotoxy(55,13);
    
    printf("Egg(s): %d", food);
    
    gotoxy(55,15);
    
	printf("Bomb(s): %d", bomb);
	
	
	gotoxy(55,20);
            
	printf("Eat an egg \"@\": increase one \"O\" and get 100 points.");
			
	gotoxy(55,21);
			
	printf("Eat a bomb \"X\": cut one \"O\" and lose 500 points.");
}

void setSite(int i, int site_x, int site_y){//定位蛇的位置 

    sBody[i].x = site_x;

    sBody[i].y = site_y;

}

void setStartSite(){//定位蛇的初始位子 

    int i;

    sBody[0].x = sBody[1].x = sBody[2].x = sBody[3].x = sBody[4].x = 1;

    for(i=0; i<5; i++) sBody[i].y = abs(5 - i);

}
void butterfly(){
	system("CLS");
	
 	printf(" / `._                     _.' |\n");
 	printf("( @ : `.                 .' : @)\n");  
 	printf(" \\  `.  `.  ._     _.  .'  .'  /\n"); 
	printf("  \\;' `.  `.  \\  /  .'  .' `;/\n"); 
	printf("   \\`.  `.  \\ \\_/  /  .'  .'/\n"); 
	printf("   ) :-._`. \\ (:) / .'_.-: (\n"); 
	printf("   (`.....,`.\\/:\\/.',.....')\n"); 
	printf("    >------._|:::|_.------<\n"); 
	printf("   / .'._>_.-|:::|-._<_.'. \n"); 
	printf("   |o _.-'_.-^|:|^-._`-._ o|\n"); 
	printf("   |`'   ;_.-'|:|`-._;   `'|\n"); 
 	printf("   '.o_.-' ;.'|:|'.; `-._o.'\n"); 
 	printf("    '.__.'    \\:/   '.__.'\n"); 
 	system ("pause");
}

void pupa(){
	system("CLS");
	printf("                       **\n"
		   "                     ******\n"
		   "                  ***********\n"
		   "                ***************\n"
		   "              ******************\n"
		   "              *******************\n"
		   "             ********************\n"
		   "             *********************\n"
		   "              *    ********** **\n"
		   "                 *  *******  ****\n"
		   "               ****  *****  ******\n"
		   "                ****  ***  ******\n"
		   "                 ****     ******\n"
		   "                 *****   ******\n"
		   "                  ****** *****\n"
		   "                   **********\n"
		   "                    ********\n"
		   "                    *******\n"
		   "                     *****\n"
		   "                      ***\n"
		   "                       *\n");
								  
	system("pause");
}

int GuessNumber(int ans, int min, int max,int counter)//第二個小遊戲函數，終極密碼 
{
	int n;
	int result;
	if(7>counter){
			printf("You still have %d chances.\n",7-counter);
			printf("Enter a number between %d and %d:\n",min,max);
	scanf("%d",&n);
	
	if(n>=1 && n<=100)
	{	
		if(n>min && n<max)
		{	
			
			counter++;
			
			if(n == ans)
			{
				result = 1;
			}
		
			else
			{
				if(n>ans)
				{
					max = n;	
				}
			
				else
				{
					min = n;
				}
				result = 0;
		
				printf("\nThe number is between %d and %d\n",min,max);
				printf("Keep guessing!!!\n\n");
				
				GuessNumber(ans,min,max,counter);
			}
			
		}
		else
		{
			printf("\nPlease type a number between \"%d~%d\"!\n\n",min,max);
			GuessNumber(ans,min,max,counter);
		}
		
	}
	
	else
	{
		printf("\nPlease type a number between \"1~100\"!\n\n");
		GuessNumber(ans,min,max,counter);
	}
		
	}
	else{
		printf("\nYou lose!!!\n");
		printf("\nBoom!\nThe number is:%d\n",ans);
		system ("pause");
		pupa();
		return 0;
	}
	
	

	if(result==1)
	{
		system("CLS");
		printf("\nBoom!\nThe number is:%d\n",ans);
		printf("\nGame over!\n");
		
		printf("\nYou win!!!\n");
		system ("pause");
		butterfly();
		return 1;
	}
}

// The player record output a file.SorF=success or fail
int store_playerRecord( char name[100], int score,double time,int SorF){
	
	FILE *fptr1;
	FILE *fptr2;// file pointer
	char H_score[20];
	double h_score;
	char c;
	if((fptr1 = fopen("AllplayersRecord.txt", "r")) == NULL){// 沒有檔案則創最新紀錄 
		fclose(fptr1);
		fptr1 = fopen("AllplayersRecord.txt", "w");
		fprintf(fptr1,"Highest score:10000.00 seconds\n");
		fclose(fptr1);
	}
	
	if( (fptr1 = fopen("AllplayersRecord.txt", "a")) == NULL ){  // open file with "append" mode
		
		printf("\nError: the file cannot be opened.");
	
		return 0;
		
	}
	else{  // record player's name, score, bombs
		fprintf(fptr1, "\n%s", "~~Players Record~~");
		puts("");
		fprintf(fptr1, "\nName: %s\n", name);
		// eat one food plus score 100, thus eat one bomb minus score 500 
		fprintf(fptr1, "Total score: %d\n",score);
		fprintf(fptr1, "Total time: %.2f seconds,",time);
		if(SorF){
			fprintf(fptr1, "Success.\n",time);
		}else{
			fprintf(fptr1, "Failure.\n",time);
		}
		fclose(fptr1);   // close the file
		if(SorF){//假設不成功進化不會有最高紀錄 
			fptr1 = fopen("AllplayersRecord.txt", "r");
			fseek(fptr1,14,SEEK_SET);
			fgets(H_score,20,fptr1);
			h_score=atol(H_score);//string to double
			if(h_score>time){
				fptr2=fopen("temp.txt","w");//將資料暫存另一檔案 
				fprintf(fptr2,"Highestscore: %.2f seconds\n",time);
				fprintf(fptr2,"Record holder: %s\n",name);
				fgets(H_score,20,fptr1);
				while((c = fgetc(fptr1)) != EOF) { 
        			fputc(c, fptr2);
    			}
    			fclose(fptr2);
    			fclose(fptr1);
    			fptr1 = fopen("AllplayersRecord.txt", "w");
    			fptr2=fopen("temp.txt","r");
    			while((c = fgetc(fptr2)) != EOF) { //移回來 
        			fputc(c, fptr1);
    			}
    			fclose(fptr2);
    			fclose(fptr1);
    			unlink("temp.txt");//刪除多餘檔案 
			}
		} 
		return 1;
	}
	
}
