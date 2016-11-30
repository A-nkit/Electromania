#include<mega16.h>
#include<delay.h>
#include<math.h>

int gunpos=3;
int enemy_arr[8][13]={0};
int bullet_arr[9][12]={0};
int score=0;
int game=1;


void display(int x,int y)  {
    
    int a=1;
    int b=1;
    
    if(y>7)  b=2;
    if(x>7)  a=2;
    y%=8;
    x%=8;

   PORTD=(a|(b<<2));
   PORTC=(x|(y<<4));
    delay_ms(10);
    PORTD=0;
    
}

void position(int x)  {
    display(x,0);
    display(x+1,0);
    display(x-1,0);
    display(x,1);
    return;
}

void disp_score()
{
  int unit,tens;
  unit=score%10;
  tens=score/10;
  PORTA=(unit|(tens<<4));
}

void shoot()
{
    bullet_arr[gunpos][2]==1;
    return;   
    }

void left()  {
    if(gunpos-1) { position(gunpos-1);
        gunpos-=1;}
    return;
}

void right()  {
    if(gunpos-7) { position(gunpos+1);
        gunpos+=1;}
    return;
}

interrupt [EXT_INT1] void ext_int1_isr(void)
{
left();
}

interrupt [EXT_INT0] void ext_int0_isr(void)
{
right();
}

interrupt [EXT_INT2] void ext_int2_isr(void)
{
shoot();
}

void disp_enemy(int x,int y)
{if(y==12)
    {  display(x,11);
        display(x+1,11);
    }

 if(y==0)
     {display(x,0);
     display(x+1,0);}

 else{ display(x,y);
       display(x+1,y);
       display(x,y+1);
       display(x+1,y+1);
   }
return;
}

void buzz(int time)
   {
      PORTB=1;
      delay_ms(time);
      PORTB=0;
   }

 void generate_enemy(int i)
 {
         i=(i+score)%9;
     enemy_arr[i][12]=1;
 return;
}




void check()
{
    int i,j;
    for(i=1;i<7;i++)
    for(j=0;j<12;j++)
        if(bullet_arr[i][j])
        {
            if(enemy_arr[i][j+1])
               { enemy_arr[i][j+1]=0;
                   bullet_arr[i][j]=0;
                score++;
                buzz(370);
              }
            if(enemy_arr[i-1][j+1])
                { enemy_arr[i-1][j+1]=0;
                   bullet_arr[i-1][j]=0;
                score++;
                buzz(370);

           }
    
     for(i=0;i<8;i++)enemy_arr[i][0]=0;
        }
 
return;}

void check2()
{
  if(enemy_arr[gunpos-2][1]==1) game=0;
  if(enemy_arr[gunpos+1][1]==1) game=0;
  if(enemy_arr[gunpos-1][2]==1) game=0;
  if(enemy_arr[gunpos][2]==1) game=0;
 return;
}

 void move_enemy()
 {
    int i,j;
    
    for(i=0;i<7;i++)
    for(j=0;j<12;j++)
        if(enemy_arr[i][j])disp_enemy(i,j); 

         for(i=0;i<8;i++)
      { for(j=0;j<12;j++)
        enemy_arr[i][j]=enemy_arr[i][j+1];    
        enemy_arr[i][12]=0;
      }
   
   check2();
     check();
      
   }

   

void move_bullet()
{   
    int i,j;
    for(i=0;i<8;i++)
    for(j=0;j<12;j++)
        if(bullet_arr[i][j])display(i,j); 

    for(i=0;i<8;i++)
      { for(j=11;j>2;j--)
        bullet_arr[i][j]=bullet_arr[i][j-1];    
        bullet_arr[i][3]=0;
      }
    
    check();
}
void main()
{   int i;
    DDRC=0xFF;
    DDRD=0xFF; 
   // DDRA=0xFF;
   // DDRB=0b00000001;
    
   
  
    for(;;i++)
  {  
     display(1,2);     
    /* position(gunpos);
      if(i%5000==1)generate_enemy(i);
     if(i%5000==1)move_enemy();
     if(game==0)break;
     if(i%1000==1)move_bullet(); 
     disp_score(); 
  }

  for(i=0;i<7;i++)
   { buzz(750);
     delay_ms(250);
    }

  for(i=4; i<7; i+=2)   {
    display(3,i);
    display(5,i);
    display(4,5);
  }  
  for(i=2; i<9; i++)  {
    display(3,i);
    display(5,i);
    display(2,7);
    display(3,6);
    display(4,5);
    display(5,6);
    display(6,7);
  }
  for(i=1; i<4; i++)  {
    display(i,9-i);
    display(i+4,5-i);
    display(i+4,i+5);
    display(i,i+1);
    display(4,5);
  }
  for(i=4; i<7; i+=2)  {
    display(3,i);
    display(5,i);
    display(4,5);
  */} 
  return;
}
