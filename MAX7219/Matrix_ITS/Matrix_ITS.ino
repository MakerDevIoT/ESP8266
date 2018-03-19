#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 2; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )

//ARDUINO CONNECT MAX_MATRIX7219
//CS ----- PIN10
//DIN ----- PIN11
//CLK ----- PIN13

//VCC - 3.3V
//GND - GND
//DIN -  D7
//CS - D4
//CLK - D5 snap90


int numberOfHorizontalDisplays = 1;  //số trong Hiển thị theo chiều ngang
int numberOfVerticalDisplays = 4;   // Số trong hiển thị theo chiều dọc.

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays); // cấu hình matrix

String tape = "<<< Information Technology >>>";   // ký tự muốn truyền lên matrix "Youtube: Nhomreview - Gmail: nhomreview@gmail.com >>>TRONGSANG.FEE<<<"
int wait = 100; // thời gian chạy chữ.  

int spacer = 1; // khoảng cách cách chữ
int width = 5 + spacer; // độ rộng của font là 5 fixel 

void setup() {

                matrix.setIntensity(15); // cài đặt giá trị độ tương phản từ 0 đến 15.
              
               // điều chỉnh hiển thị theo nhu câu của người dùng.
              //  matrix.setPosition(0, 1, 3);  // The first display is at <0, 0>   
             //   matrix.setPosition(1, 1, 0);  // The second display is at <1, 0>
             //   matrix.setPosition(2, 2, 0);  // The third display is at <2, 0>
              //  matrix.setPosition(3, 3, 0);  // And the last display is at <3, 0>
               //  ...
               // matrix.setRotation(0, 2);    // Màn hình hiển thị đầu tiên là vị trí đảo ngược
                 matrix.setRotation(3);    // The same hold for the last display
              }

void loop() {

            for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) 
            {
          
              matrix.fillScreen(LOW);
          
              int letter = i / width;
              int x = (matrix.width() - 1) - i % width;
              int y = (matrix.height() - 8) / 2; // center the text vertically
          
              while ( x + width - spacer >= 0 && letter >= 0 ) {
                if ( letter < tape.length() ) {
                  matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
                }
          
                letter--;
                x -= width;
              }
          
              matrix.write(); // Send bitmap to display
          
              delay(wait);
            }
            
}

