//01 Display “Welcome" on line1. Left Justified
// Solution in init_lcd function.
//02 Display “Welcome" on line1. Right Justified
// Solution in init_lcd function.
//04 Display “Welcome" on line2. Left Justified 
// Solution: in setup loop.
//steps for LCD:
/*  STEP 1:
initialize the pins on Arduino
//(port f for data output (D7 to D0) and 
//port k for enable and RS - register select)
*/
void init_pin(void);
/*  STEP 2:
send data from Port F (D7 to D0)
*/
void out_data(char);

/*  STEP 3:
send control from Port K (E and RS)
*/
void out_control(char);

/*  STEP 4:
set delay
*/
void delay_lcd(unsigned long);

/*  STEP 5:
Toggle the enable pulse on LCD to write the values.
*/
void lcd_toggle_enable(void);

/*  STEP 6:
Initialize the LCD by setting the:
1. Font size (F), number of lines (N) and data length (DL). (Instruction - function set)
2. Cursor blinking (Instruction- display ON/OFF)
3. Clear display (Instruction-Clear display)
4. auto increment (Instruction - entry mode set)
*/
void init_lcd(void);

/*  STEP 7:
write the values on LCD.
*/
void lcd_write_data(char);
void setup() 
{
  // put your setup code here, to run once:
  init_pin();
  init_lcd();
  /*
  //solution 4
  char blank[40] = {}; //create a buffer of 40 empty values.
  for(unsigned int i = 0; i<40; i++)
  {
      lcd_write_data(blank[i]); //40 empty digits in Line 1
  }
  write_string("Welcome"); //line 2
  */
  write_string("Welcome"); 
}
void loop() 
{
  // put your setup code here, to run once:
}

//Write string to parse data to lcd_write_data;
void write_string(char *ptr)
{
  while(*ptr != 0)
  {
    lcd_write_data(*ptr);
    *ptr++;
  }
}


/*  STEP 1:
initialize the pins on Arduino
//(port f for data output (D7 to D0) and 
//port k for enable and RS - register select)
*/
void init_pin()
{
  volatile char *dir_k = (volatile char *) 0x107;
  volatile char *dir_f = (volatile char *)  0x30;
  *dir_k=0x03;
  *dir_f=0xFF;
}


/*  STEP 2:
send data from Port F (D7 to D0)
*/
void out_data(char out_data_to_lcd)
{
  volatile char *port_f = (volatile char *) 0x31;
  *port_f = out_data_to_lcd;
}

/*  STEP 3:
send control from Port K (E and RS)
*/
void out_control(char out_control_to_lcd)
{
  volatile char *port_k = (volatile char *) 0x108;
  *port_k = out_control_to_lcd;
}

/*  STEP 4:
set delay
*/
void delay_lcd(unsigned long i)
{
  while(i)
  {
    i--;
  }
}

/*  STEP 5:
Toggle the enable pulse on LCD to write the values.
*/
void lcd_toggle_enable()
{
  out_control(0x01); //RS = 0, E = 1
  delay_lcd(10);
  out_control(0x00); //RS = 0, E = 0
  delay_lcd(10);
}

/*  STEP 6:
Initialize the LCD by setting the:
1. Font size (F), number of lines (N) and data length (DL). (Instruction - function set)
2. Cursor blinking (Instruction- display ON/OFF)
3. Clear display (Instruction-Clear display)
4. auto increment (Instruction - entry mode set)
*/
void init_lcd(void)
{
  out_data(0x38); //8 bit, 2 line.
  lcd_toggle_enable(); //send the above command to LCD.
  out_data(0x0F); //Set display ON with cursor blinking.
  lcd_toggle_enable(); //send the above command to LCD.
  out_data(0x01); //Clear display.
  lcd_toggle_enable(); //send the above command to LCD.
  out_data(0x06); //auto increment cursor. left justified.
  lcd_toggle_enable(); //send the above command to LCD.
  //out_data(0x07); //auto increment cursor. right justified.
  //lcd_toggle_enable(); //send the above command to LCD.

}

/*  STEP 7:
write the values on LCD.
*/
void lcd_write_data(char lcd_write)
{
  out_data(lcd_write); //send the data to write on D7 to D0.
  out_control(0x02); // RS = 1, E = 0
  delay_lcd(10);
  out_control(0x03); // RS = 1, E = 1
  delay_lcd(10);
  out_control(0x02); // RS = 1, E = 0. Enable gets toggled.
  delay_lcd(10);
}