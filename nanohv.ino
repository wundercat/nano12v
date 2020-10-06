
//  generate 12 volts from 5, with an external switch, diode, and inductor

const int chargethecoil = 12;    // write a 1 to pull current into the coil
                                 // write 0 to release energy to the output
const int anled = 2;     //debug LED
int tx;

//  1=output
//  unused GPIOs are driven, to prevent floating to bad levels. 
unsigned const int directionbits = 0b1111111100111110 ; 
unsigned const int howmanyDpins = 14 ;

//  FYI
#define  PORTB  0x05
#define  PORTD  0x0b



void setup() {
  unsigned int bits = directionbits;
  
  for (tx=0; tx < howmanyDpins; tx++){
    if( bits & 0x0001){
      pinMode(tx, OUTPUT);
      digitalWrite(tx, LOW);
    }else{
     pinMode(tx, INPUT);
    }
    bits = bits >> 1 ;
  }
} 


void loop() {
  if (bit_is_set(ACSR, ACO)){            //  if feedback voltage < 3.3v reference 
    // digitalWrite(anled, LOW);
    asm volatile(  "sbi 0x0b,2 \n\t" );
    asm volatile(  "sbi 0x05,4 \n\t" );  // set PORTB bit4 which is Arduino D12 
    delayMicroseconds(3);                //1.9 us
    asm volatile(  "cbi 0x05,4 \n\t" );
    delayMicroseconds(5);
  }else{
    asm volatile(  "cbi 0x0b,2 \n\t" );  // digitalWrite(anled, LOW);
  }
}

 
