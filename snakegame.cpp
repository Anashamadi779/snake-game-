#include <iostream>
#include <conio.h>
#include <ctime>

enum direction {Stop = 0 , Left , Right , Up , Down};
void setup(direction &dir , int &x , int &y , int &fruitX , int &fruitY , int &score , int &width , int &height , bool &gameover);
void draw(int &x , int &y , int &width , int &height , int &fruitY , int &fruitX , std::string &name , int &score, int &nTAil , int *TailX , int *TailY);
void Play(direction &dir,bool &gameover);
void Logic(direction &dir , int &x , int &y , int &fruitX , int &fruitY,bool &gameover,int &score, int &width , int &height , int &nTail , int *TailX , int *TailY);

int main(){

    srand(time(0));
    std::string name = "************** Snake Game **************";
    bool gameover;
    int width = 30;
    int height = 20;
    int x , y , fruitX , fruitY , score;
    direction dir;
    int nTail = 0;
    int TailX[30] , TailY[30];

    setup(dir,x,y,fruitX,fruitY,score ,width,height,gameover);
    while(!gameover){
        draw(x,y,width,height,fruitY , fruitX, name,score , nTail , TailX, TailY);
        Play(dir , gameover);
        Logic(dir , x , y ,fruitX , fruitY,gameover,score ,width,height , nTail , TailX, TailY);
        _sleep(100);
    }

    return 0;
}

void setup(direction &dir , int &x , int &y , int &fruitX , int &fruitY , int &score , int &width , int &height , bool &gameover){
    dir = Stop ;
    gameover = false;
    x = width/2;
    y = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0; 
}

void draw(int &x , int &y , int &width , int &height , int &fruitY , int &fruitX , std::string &name , int &score , int &nTail , int *TailX , int *TailY){
    
    system("cls");
    std::cout<<name<<"\n";
    std::cout<<"\n";
    std::cout<<"PRESS MOVES KEYS TO PLAY\nPRESS Q TO QUIT\n";
    std::cout<<"\n";

    for(int i = 0 ; i < width + 2 ;i++ ){
        std::cout<<"#";
    }
    std::cout<<"\n";
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            if(j == 0){
                std::cout<<"#";
            }
            if(i == y && j == x){
                std::cout<<"O";
            }
            else if (i == fruitY && j == fruitX){
                std::cout<<"F";
            }
            else{
                bool follow = false;
                for(int k = 0 ; k < nTail ; k++){
                    if(TailX[k] == j && TailY[k] == i){
                        std::cout<<"o";
                        follow = true;
                    }
                }
                if(!follow){
                    std::cout<<" ";
                }
            }
            if(j == width - 1){
                std::cout<<"#";
            }
            
            

        }
        std::cout<<"\n";
    }

    for(int i = 0 ; i < width + 2 ;i++ ){
        std::cout<<"#";
    }
    std::cout<<"\n";
    std::cout<<"Score : "<<score<<"\n";
}

void Play(direction &dir,bool &gameover){
    if(_kbhit()){
        int ch = _getch();
        if(ch == 224){
            switch(_getch()){
                case 75 : dir = Left;
                    break;
                case 77 : dir = Right;
                    break;
                case 72 : dir = Up;
                    break;
                case 80 : dir = Down;
                    break;
            }
        }
        else{
            switch(ch){
                case 'Q':
                case 'q': gameover = true; 
                    std::cout<<"************** Game Over **************";
                        break;
            }
        }
    }
}

void Logic(direction &dir , int &x , int &y , int &fruitX , int &fruitY,bool &gameover,int &score, int &width , int &height , int &nTail , int *TailX , int *TailY){
    
    int prevX = TailX[0];
    int prevY = TailY[0]; 
    TailX[0] = x;
    TailY[0] = y;
    int prev2X , prev2Y ;
    for(int i = 1 ; i < nTail ; i++){
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir){
        case Left : x--;
            break;
        case Right : x++;
            break;
        case Down : y++;
            break;
        case Up : y--;
            break;
        default :
            break;
    }

    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    if(x >= width){
        x = 0;
    }
    else if(x < 0){
        x = width - 1;
    }
    if(y >= height){
        y = 0;
    }
    else if(y < 0){
        y = height - 1;
    }

    for(int i = 0 ; i < nTail ; i++){
        if(TailX[i] == x && TailY[i] == y){
            gameover = true;
            std::cout<<"************** Game Over **************";
        }
    }

    if(score >= 250){
        gameover = true;
        std::cout<<"************** YOU WIN!! **************";
    }
}
