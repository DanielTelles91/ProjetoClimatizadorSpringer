#include <stdio.h>
#include <stdlib.h>
#include <IRremote.h>  // Biblioteca Controle Remoto by Ken Shirriff


// Variáveis
const int botaoUmidificar = 12;         // Botão Umidificador (PB4)
const int ledUmidificar = A3;          // LED Umidificador   (PC3)
int ledflagUmidificar = 0;            // Flag LED Umidificador

const int botaoOscilar = 11;          // Botão Oscilar       (PB3)
const int ledOscilar = A2;           // LED Oscilar         (PC2)
int ledflagOscilar = 0;             // Flag LED Oscilar

const int botaoPower = 9;          // Botão Power         (PB1)
const int ledPower = 3 ;          // LED Power           (PD3)
int ledflagPower = 0;            // Flag LED Power

const int botaoTimer = 7;         // Botão Timer    (PD7)
const int ledTimer1H = 0 ;       // Led Timer 1H (PD0)        
const int ledTimer2H = A5 ;     // Led Timer 2h (PC5) 
const int ledTimer4H = A4 ;    // Led Timer 4H (PC4) 
int ledflagTimer = 0;     

const int botaoRes = 8;        // Botão Reservatório           (PB0)
const int ledRes =  1;        // LED Reservatório             (PD1)
int ledflagRes = 0;          // Flag LED Ion


const int botaoIon = 6;      // Botão Ion           (PD6)
const int ledIon =  5;      // LED Ion             (PD5)
int ledflagIon = 0;        // Flag LED Ion

const int botaoVelocidade = 10;      // Botão Velocidade    (PB2)
const int ledVelocidade1 = 13 ;     // Led Velocidade Fraco(PB5)        
const int ledVelocidade2 = A0 ;    // Led Velocidade Médio(PC0) 
const int ledVelocidade3 = A1 ;   // Led Velocidade Alto (PC1) 
int ledflagVelocidade = 0;           


const int RECV_PIN =4; // Sensor Controle Remoto (PD4)

const int sensorNivelAgua = A6;        // Sensor Nivel Agua   (ADC6)

int countVelocidadeControle = 0;
int countUmidificadorControle = 0;
int countOsciladorControle = 0;
int countIonControle = 0;
int countPowerControle = 0;
int countTimerControle = 0;
int countLedReservatorioControle = 0;

long lastTime = 0;
long minutes = 0;
long hours = 0;
long horasSetada = 0;
int timerEnabled = 0;


// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;


//=============================================================Sinal sem água com som============================================================================

void sinalSemAgua(){

        tone(2,4000);
        digitalWrite(ledRes,LOW);        
        ledflagRes=1;
        delay(1000);
        noTone(2);
        
        tone(2,4000);
        digitalWrite(ledRes,HIGH);        
        ledflagRes=0;
        delay(1000);
        noTone(2);

        tone(2,4000);
        digitalWrite(ledRes,LOW);        
        ledflagRes=1;
        delay(1000);
        noTone(2);

        tone(2,4000);
        digitalWrite(ledRes,HIGH);        
        ledflagRes=0;
        delay(1000);
        noTone(2);

  
}

//=======================================================================================================================================================


//================================================================Buzzer=================================================================================

void buzzer1(){

               tone(2,4000);
               delay(300); 
               noTone(2); 
}

//=======================================================================================================================================================



//=========================================================Desliga o Climatizador========================================================================

void desligaFuncaoClimatizador(){

                digitalWrite(ledUmidificar,HIGH);        // Inicializa o Led Umidificador desligado
                ledflagUmidificar=0;

                digitalWrite(ledOscilar,HIGH);           // Inicializa o Led Oscilar desligado
                ledflagOscilar=0;

                digitalWrite(ledIon,HIGH);               // Inicializa o Led Ion desligado
                ledflagIon=0;

                digitalWrite(ledRes,HIGH);               // Inicializa o Led Reservatório desligado
                ledflagRes=0;

                digitalWrite(ledVelocidade1,HIGH);       // Inicializa o Led Velocidade Baixo desligado
                digitalWrite(ledVelocidade2,HIGH);       // Inicializa o Led Velocidade Médio desligado
                digitalWrite(ledVelocidade3,HIGH);       // Inicializa o Led Velocidade Alto desligado

                digitalWrite(ledTimer1H,HIGH);           // Inicializa o Led Timer 1H desligado
                digitalWrite(ledTimer2H,HIGH);           // Inicializa o Led Timer 2H desligado
                digitalWrite(ledTimer4H,HIGH);           // Inicializa o Led Timer 4H desligado
                ledflagTimer = 0;
                 
                digitalWrite(ledPower,HIGH);      // Acende o led vermelho
                ledflagPower=0;                 
                
                timerEnabled = 0;
                horasSetada = 0;                
                minutes = 0;
                hours = 0;
}

//=======================================================================================================================================================




//===========================================================Liga o Climatizador=========================================================================

void FuncaoClimatizador(){

//**********************************************************Comando Umidificador*************************************************************************

  if (digitalRead(botaoUmidificar)== HIGH || countUmidificadorControle == 2){ // Se o botão for pressionado ou o controle remoto

        if (analogRead(sensorNivelAgua)>1000){ // Se recebe 5v, libera umidificador (Nivel cheio água)
                         
             if (ledflagUmidificar==0) {             
                                          
                     digitalWrite(ledUmidificar,LOW); // Acende o led umidificador  
                     ledflagUmidificar=1;    
                     
             } 
      
             else {   
                                                    
              digitalWrite(ledUmidificar,HIGH);  // Apaga o led Umidificador 
              ledflagUmidificar=0;
                 
             }

             buzzer1();
             countUmidificadorControle = 0;
                      
      }

      else{
        sinalSemAgua();
        countUmidificadorControle = 0;
      }
    
 
  }

//=======================================================================================================================================================


//==================================================================Comando Oscilar======================================================================

  if (digitalRead(botaoOscilar)==HIGH || countOsciladorControle == 2){ // if button is pressed
    if (ledflagOscilar==0) {             // and the status flag is LOW
      ledflagOscilar=1;                  // make status flag HIGH
      digitalWrite(ledOscilar,LOW);     // and turn on the LED
      }                           // 
    else {                        // otherwise...
      ledflagOscilar=0;                  // make status flag LOW
      digitalWrite(ledOscilar,HIGH);      // and turn off the LED
    }
    
        buzzer1();
        countOsciladorControle = 0;
  
  }

//=======================================================================================================================================================


//==================================================================Comando Ion==========================================================================

  if (digitalRead(botaoIon)==HIGH || countIonControle ==2){ // if button is pressed
    if (ledflagIon==0) {             // and the status flag is LOW
      ledflagIon=1;                  // make status flag HIGH
      digitalWrite(ledIon,LOW);     // and turn on the LED
      }                           // 
    else {                        // otherwise...
      ledflagIon=0;                  // make status flag LOW
      digitalWrite(ledIon,HIGH);      // and turn off the LED
    }

          buzzer1();
          countIonControle = 0;
  
  }

//=======================================================================================================================================================



//==================================================================Comando Led Reservatório=============================================================

  if (digitalRead(botaoRes)==HIGH || countLedReservatorioControle ==2){ // if button is pressed
    if (ledflagRes==0) {             // and the status flag is LOW
      ledflagRes=1;                  // make status flag HIGH
      digitalWrite(ledRes,LOW);     // and turn on the LED
      }                           // 
    else {                        // otherwise...
      ledflagRes=0;                  // make status flag LOW
      digitalWrite(ledRes,HIGH);      // and turn off the LED
    }
          buzzer1();
          countLedReservatorioControle = 0;
  
  }

//=======================================================================================================================================================


//========================================================Comando Velocidade do Ventilador===============================================================
 
      if (digitalRead(botaoVelocidade)==HIGH || countVelocidadeControle == 2){ // if button is pressed
    
         if (ledflagVelocidade==0) {             // and the status flag is LOW
            digitalWrite(ledVelocidade3,HIGH);        // Vermelho apaga
             digitalWrite(ledVelocidade1,LOW);     // Verde acende
              ledflagVelocidade =1;
      }  

switch(ledflagVelocidade){

case 3: // Velocidade baixo
       digitalWrite(ledVelocidade3,HIGH); // Led Vermelho apaga
       digitalWrite(ledVelocidade1,LOW); // Led Verde acende
       ledflagVelocidade = 1;
       buzzer1();
 
break;


case 1: // Velocidade Médio
       digitalWrite(ledVelocidade1,HIGH); // Led Verde apaga
       digitalWrite(ledVelocidade2,LOW); // Led Amarelo acende
       ledflagVelocidade = 2;
       buzzer1();

break; 

case 2: // Velocidade Alto
        digitalWrite(ledVelocidade2,HIGH); // Led Amarelo apaga
        digitalWrite(ledVelocidade3,LOW); // Led Vermelho acende
        ledflagVelocidade = 3;
        buzzer1();

break;        
}



countVelocidadeControle = 0;
  
}

//=======================================================================================================================================================


//=====================================================================Comando Timer=====================================================================


if (digitalRead(botaoTimer)==HIGH || countTimerControle ==2){ // Se o botão timer for pressionado
         

switch(ledflagTimer){

case 0: // Timer 1H
        digitalWrite(ledTimer4H,HIGH);         
        digitalWrite(ledTimer2H,HIGH);        
        digitalWrite(ledTimer1H,LOW); // Aciona Led 1H  
        timerEnabled = 1;
        ledflagTimer = 1;
        buzzer1();
 
break;


case 1: // Timer 2H
       digitalWrite(ledTimer4H,HIGH);         
       digitalWrite(ledTimer2H,LOW); // Aciona Led 2H         
       digitalWrite(ledTimer1H,HIGH); 
       timerEnabled = 1;
       ledflagTimer = 2;
       buzzer1();

break; 


case 2: // Timer 3H
        digitalWrite(ledTimer4H,HIGH);         
        digitalWrite(ledTimer2H,LOW); // Aciona Led 3H         
        digitalWrite(ledTimer1H,LOW); 
        timerEnabled = 1;
        ledflagTimer = 3;
        buzzer1();

break;   


case 3: // Timer 4H
        digitalWrite(ledTimer4H,LOW); // Aciona Led 4H         
        digitalWrite(ledTimer2H,HIGH);         
        digitalWrite(ledTimer1H,HIGH);
        timerEnabled = 1; 
        ledflagTimer = 4;
        buzzer1();

break; 


case 4: // Timer 5H
        digitalWrite(ledTimer4H,LOW); // Aciona Led 5H         
        digitalWrite(ledTimer2H,HIGH);         
        digitalWrite(ledTimer1H,LOW); 
        timerEnabled = 1;
        ledflagTimer = 5;
        buzzer1();

break;   


case 5: // Timer 6H
        digitalWrite(ledTimer4H,LOW); // Aciona Led 6H         
        digitalWrite(ledTimer2H,LOW);         
        digitalWrite(ledTimer1H,HIGH); 
        timerEnabled = 1;
        ledflagTimer = 6;
        buzzer1();

break; 

case 6: // Timer 7H
        digitalWrite(ledTimer4H,LOW); // Aciona Led 7H         
        digitalWrite(ledTimer2H,LOW);         
        digitalWrite(ledTimer1H,LOW); 
        timerEnabled = 1;
        ledflagTimer = 7;
        buzzer1();

break; 


case 7: // DESLIGA
        digitalWrite(ledTimer4H,HIGH); // Aciona Led 7H         
        digitalWrite(ledTimer2H,HIGH);         
        digitalWrite(ledTimer1H,HIGH); 
        timerEnabled = 0;
        ledflagTimer = 0;
        buzzer1();

break;


  }
  
minutes = 0;
horasSetada = hours + ledflagTimer; 

countTimerControle = 0;

}

}

//=======================================================================================================================================================



void setup() {

                irrecv.enableIRIn(); // Habilita IR Receiver
  

                pinMode(botaoUmidificar,INPUT);         // Define o botão Umidificador como Entrada 
                pinMode(ledUmidificar,OUTPUT);          // Define o Led Umidificador como Saída
                digitalWrite(ledUmidificar,HIGH);        // Inicializa o Led Umidificador desligado

                pinMode(botaoOscilar,INPUT);            // Define o botão Oscilar como Entrada 
                pinMode(ledOscilar,OUTPUT);             // Define o Led Oscilar como Saída
                digitalWrite(ledOscilar,HIGH);           // Inicializa o Led Oscilar desligado

                pinMode(botaoIon,INPUT);                // Define o botão Ion como Entrada 
                pinMode(ledIon,OUTPUT);                 // Define o Led Ion como Saída
                digitalWrite(ledIon,HIGH);               // Inicializa o Led Ion desligado

                pinMode(botaoPower,INPUT);              // Define o botão Power como Entrada 
                pinMode(ledPower,OUTPUT);               // Define o Led Power como Saída
                digitalWrite(ledPower,HIGH);             // Inicializa o Led Power desligado

                pinMode(botaoRes,INPUT);                // Define o botão Reservatório como Entrada 
                pinMode(ledRes,OUTPUT);                 // Define o Led Reservatório como Saída
                digitalWrite(ledRes,HIGH);               // Inicializa o Led Reservatório desligado


                pinMode(botaoVelocidade,INPUT);         // Define o botão Velocidade como Entrada 
                pinMode(ledVelocidade1,OUTPUT);         // Define o Led Velocidade Baixo como Saída
                digitalWrite(ledVelocidade1,LOW);       // Inicializa o Led Velocidade Baixo desligado
                pinMode(ledVelocidade2,OUTPUT);         // Define o Led Velocidade Médio como Saída
                digitalWrite(ledVelocidade2,HIGH);       // Inicializa o Led Velocidade Médio desligado
                pinMode(ledVelocidade3,OUTPUT);         // Define o Led Velocidade Alto como Saída
                digitalWrite(ledVelocidade3,HIGH);       // Inicializa o Led Velocidade Alto desligado

                pinMode(botaoTimer,INPUT);              // Define o botão Timer como Entrada 
                pinMode(ledTimer1H,OUTPUT);             // Define o Led Timer 1H como Saída
                digitalWrite(ledTimer1H,HIGH);           // Inicializa o Led Timer 1H desligado
                pinMode(ledTimer2H,OUTPUT);             // Define o Led Timer 2H como Saída
                digitalWrite(ledTimer2H,HIGH);           // Inicializa o Led Timer 2H desligado
                pinMode(ledTimer4H,OUTPUT);             // Define o Led Timer 4H como Saída
                digitalWrite(ledTimer4H,HIGH);           // Inicializa o Led Timer 4H desligado

                pinMode(sensorNivelAgua,INPUT);

                pinMode(2,OUTPUT); // Pino Buzzer     
 
}



void loop() {

//========================================================Inicializa o contador (Horas + Minutos)========================================================

           if(millis()-lastTime > 60000){
            
               minutes++;
               lastTime = millis();
               
           }
           
           if(minutes > 60){
            
              hours++;
              minutes = 0;
              
           }
//====================================================Quando o tempo setado for verdadeiro===============================================================


           if(horasSetada == hours && timerEnabled == 1){ //Quando o tempo setado for verdadeiro
 
              //timerEnabled = 0;
            //  horasSetada = 0;
              desligaFuncaoClimatizador();
    //  ledflagPower=0;                  // make status flag LOW
     // digitalWrite(ledPower,HIGH);      // and turn off the LED
     // ledflagTimer = 0;
     
    }

//=======================================================================================================================================================


//=================================================Função recebe comando do Controle Remoto==============================================================
               
            

//=======================================================================================================================================================





//==================================================================Comando Power========================================================================

   if (digitalRead(botaoPower)==HIGH || countPowerControle ==2){ // if button is pressed
          if (ledflagPower==0) {             // and the status flag is LOW
                 ledflagPower=1;                  // make status flag HIGH
                 digitalWrite(ledPower,LOW);     // and turn on the LED
                 digitalWrite(ledVelocidade1,LOW); // Quando liga o aparelho, já aciona o motor na velocidade 1
                 ledflagVelocidade = 1;
      
          }                           
          else {                        
                 ledflagPower=0;                  
                 digitalWrite(ledPower,HIGH);      
          }

          countPowerControle=0;
          buzzer1();
  }
  

   if(ledflagPower ==1){ // Se estiver ligado, libera as funções do climatizador
  
          FuncaoClimatizador();


                        if (analogRead(sensorNivelAgua)<1000){ // Em tempo real fica analisando o nivel do reservatório
                          digitalWrite(ledUmidificar,HIGH); 
                          ledflagUmidificar = 1;
                          
                          // sinalSemAgua();
                        }


               if (irrecv.decode(&results)){ 

                   switch(results.value){
                   case 0xA32AB931:
                   countPowerControle ++;
                   break; 

                  
                   case 0x371A3C86:
                   countVelocidadeControle ++;
                   break;
                   case 0x143226DB:
                   countUmidificadorControle ++;
                   break;
                   case 0x4E87E0AB:
                   countOsciladorControle ++;
                   break;
                   case 0x4EA240AE:
                   countIonControle ++;
                   break;
                 
                   case 0xE0984BB6:
                   countTimerControle ++;
                   break;
                   case 0x39D41DC6:
                   countLedReservatorioControle ++;
                   break;
                   
     
                 }

                  irrecv.resume();
                 delay(10); //INTERVALO DE 10 MILISSEGUNDOS     
                   
             }





                        

 
   }

   if (ledflagPower ==0){ // Climatizador em StandBy
    
          desligaFuncaoClimatizador(); 

             if (irrecv.decode(&results)){ 

                   switch(results.value){
                   case 0xA32AB931:
                   countPowerControle ++;
                   break; 
                   
                 }

                  irrecv.resume();
                 delay(10); //INTERVALO DE 10 MILISSEGUNDOS     
                   
             }
   }

//=======================================================================================================================================================

}
