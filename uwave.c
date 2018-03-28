
#include <18F4550.h> 
#include <stdlib.h>

#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,WDT2048
#use delay(clock=48000000)

#use rs232(baud=9600, xmit=PIN_D1, rcv=PIN_D0,invert,stream=pc,errors)
//============
//#include <16F877.H>
//#fuses XT, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP 
//#use delay(clock = 4000000) 

#include "lcd.c" 
#include "kpd.c"

#define tick 997

//=========================== 

    
//========================== 
void main() 
{ 

delay_ms(300);
output_low(PIN_E0);
output_low(PIN_E1);
lcd_init();  // Always call this first. 
kbd_init(); 
//!lcd_gotoxy(5, 1); 
//!lcd_putc("Hello Keybd"); 
//!lcd_gotoxy(4, 2); 
//!lcd_putc("Line 2"); 

start:

lcd_gotoxy(1, 1);
//========
char k=1;; 
int count=0;
char min[5],sec[5];
int minit,saat;
//============



printf("\r\Starting ..."); 
lcd_putc("\f"); 
lcd_putc("Enter min:"); 

while((count<3&&k!='#')) 
  { 
   k=kbd_getc(); 
   if(k!=0) 
     { 
      if(k=='*') {
         printf("%c", '*'); 
         lcd_putc("*");
         delay_ms(100);
      }
      else
      {
         printf("%c", k); 
         lcd_putc(k); 
         delay_ms(100);
         min[count]=k;
      }
       count++;
       printf("%u\n", count);
     }
    
     
  } 
     min[count]=0;
//==========
printf("done min...\n");
minit=atoi(min);
printf("%u\n",minit);
//=================

lcd_putc("\nEnter sec:"); 
k=1;
count=0;
while((count<3&&k!='#')) 
  { 
   k=kbd_getc(); 
   if(k!=0) 
     { 
      if(k=='*') {
         printf("%c", '*'); 
         lcd_putc("*");
         delay_ms(100);
      }
      else
      {
         printf("%c", k); 
         lcd_putc(k); 
         sec[count]=k;
         delay_ms(100);
      }
       count++;
       printf("%u\n", count);
     }
    
     
  } 
sec[count]=0;
printf("\ndone sec...");
saat=atoi(sec);
printf("%u\n",saat);

//==============================
lcd_putc("\f"); 
lcd_putc("Timer>"); 
printf(lcd_putc,"%u:%u",minit,saat); 
//=============mode====
lcd_gotoxy(1, 2); 
lcd_putc("Select Mode:>");

int mode;
k=kbd_getc();
while(k==0) {
k=kbd_getc();
}
mode=k;
lcd_putc(k);
//=====start====
k=kbd_getc();
while(k!='A') {
k=kbd_getc();
}

//==========
delay_ms(100);
int i,j;
int minit2,saat2;
minit2=minit;
saat2=saat;
//======turn ON uwave===
if (mode=='1') {
output_high(PIN_E0);
output_low(PIN_E1);

} else if (mode=='2') {
output_high(PIN_E1);
output_low(PIN_E0);


} else if (mode=='3') {
output_high(PIN_E0);
output_high(PIN_E1);
} else {
output_low(PIN_E0);
output_low(PIN_E1);

lcd_putc("\fInvalid Mode..."); 
delay_ms(2000);
    goto start;
}

//=================
for(j=0;j<saat;j++) {
    delay_ms(tick);
    
    if( !input(PIN_B0) ){
    output_low(PIN_E0);
    output_low(PIN_E1);
    lcd_putc("\fDoor Opened!"); 
    printf("Door Opened!\r\n");
    delay_ms(5000);
    goto start;
    }
    
    saat2--;
    lcd_gotoxy(7, 1);
    printf(lcd_putc,"%02u:%02u    ",minit,saat2);
    }
    
   saat2=60; 
   minit2=minit2-1;
   if (minit2<0) {
   minit2=0;
   }
for(i=0;i<minit;i++) {
    saat2=60;
    for(j=0;j<60;j++) {
    delay_ms(tick);
    
    if( !input(PIN_B0) ){
    output_low(PIN_E0);
    output_low(PIN_E1);
    lcd_putc("\fDoor Opened!"); 
    printf("Door Opened!\r\n");
    delay_ms(5000);
    goto start;
    }
    
    
    saat2--;
    lcd_gotoxy(7, 1);  
    printf(lcd_putc,"%02u:%02u   ",minit2,saat2);
    
    }
    minit2--;
}
output_low(PIN_E0);
output_low(PIN_E1);
lcd_putc("\nDone..."); 
delay_ms(500);
//=========buzer===

long buz_count=0;
for(i=0;i<2;i++){
buz_count=0;
while(buz_count<125)
{
output_high(PIN_D2);
delay_ms(4);
output_low(PIN_D2);
delay_ms(4);
buz_count++;
}
}
//================
    goto start;
//============
while(1); 
} 
