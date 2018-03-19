unsigned char i;
unsigned char j; 
/*Port Definitions*/
int Max7219_pinCLK = 14;
int Max7219_pinCS = 2;
int Max7219_pinDIN = 13;

// La conversione da bitmap a codice binario è stata fatta qui: 
// http://www.pial.net/post/8x8-Dot-matrix-font-generator-based-on-javascript-and-HTML.aspx
unsigned char disp1[10][8]={
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},//0
{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},//1
{B00000000,B00111100,B01100110,B00000110,B00001100,B00011000,B00110000,B01111110},//2
{B00000000,B00111100,B01100110,B00000110,B00001100,B00000110,B01100110,B00111100},//3
{B00000000,B00100000,B01100000,B01101100,B01101100,B01111110,B00001100,B00001100},//4
{B00000000,B01111110,B01100000,B01100000,B01111100,B00000110,B01100110,B00111100},//5
{B00000000,B00111100,B01100110,B01100000,B01111100,B01100110,B01100110,B00111100},//6
{B00000000,B01111110,B00000110,B00000110,B00001100,B00011000,B00011000,B00011000},//7
{B00000000,B00111100,B01100110,B01100110,B00111100,B01100110,B01100110,B00111100},//8
{B00000000,B00111100,B01100110,B01100110,B00111110,B00000110,B01100110,B00111100},//9
};

void Write_Max7219_byte(unsigned char DATA) 
{   
            unsigned char i;
	    digitalWrite(Max7219_pinCS,LOW);		
	    for(i=8;i>=1;i--)
          {		  
             digitalWrite(Max7219_pinCLK,LOW);
             digitalWrite(Max7219_pinDIN,DATA&0x80);// Extracting a bit data
             DATA = DATA<<1;
             digitalWrite(Max7219_pinCLK,HIGH);
           }                                 
}

void Write_Max7219(unsigned char address,unsigned char dat)
{
        digitalWrite(Max7219_pinCS,LOW);
        Write_Max7219_byte(address);           //address，code of LED
        Write_Max7219_byte(dat);               //data，figure on LED 
        digitalWrite(Max7219_pinCS,HIGH);
}

void Init_MAX7219(void)
{
 Write_Max7219(0x09, 0x00);       //decodifica: BCD
 Write_Max7219(0x0a, 0x06);       //luminosità 
 Write_Max7219(0x0b, 0x07);       //limite scan；8 LEDs
 Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
 Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}

void setup()
{
  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);
  Init_MAX7219();
}

void loop()
{ 
   for(j=0;j<10;j++)
  {
   for(i=1;i<9;i++)
    Write_Max7219(i,disp1[j][i-1]);
   delay(1000);
  } 		
}
