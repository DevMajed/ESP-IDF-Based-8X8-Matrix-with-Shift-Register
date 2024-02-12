# MCU Datalogger with memory and clock  

## Project Overview: 
**Project Name:**  
ESP-IDF Based 8X8 LED Matrix with Shift Register  
URL: https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register.git  
Author: Majed Alharbi [ Majed Dev ]  

<img src="https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register/assets/66625688/c9134792-e255-4afc-8118-a956e33952b5" width="600"/>  

<br>  
<br>  

**Disclaimer :**  

1. While I have thoroughly tested and approved my code, please use it at your own risk.
2. You might come across some recurring comments in my code. I include them to ensure that readers
   can understand how everything works, even if they haven't seen my other projects. I apologize for any redundancy.
3. The purpose of these codes is to facilitate an understanding of how the ESP-IDF framework works,
   especially since I struggled to learn it due to the lack of available resources.
4. I consistently adopt a Code Modular Design approach for all my projects. This enhances readability, maintainability,
   and reusability. Be sure to explore other source files and headers to gain a complete understanding of the project.

    LICENSE
    Users are free to utilize, modify, or reproduce the code and its derivatives.
*/

<br>  

**Objective :**  
In this project, I will be experimenting with ESP-IDF using an 8x8 LED Matrix and a shift register.  
The project focuses on creating a monochrome LED matrix display or single-color LEDs.  

Key Components:  
In this project, the main components include:  

* 8x8 LED Matrix: Consisting of 64 LEDs arranged in an 8x8 grid.
* Two 8-bit shift registers : connected in a daisy chain, forming a 16-bit shift register.
* ESP32 MCU: The ESP32 Microcontroller Unit serves as the central processing unit for the project.

<br>  

## Configuration / Circuit Schematic :  

<img src="https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register/assets/66625688/a6830a99-3da3-4570-86a5-9efc763a7978" width="600"/>  
<br>  
<br>  
<img src="https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register/assets/66625688/cd599f04-d8ac-4ecb-af81-af8e94c96ff0" width="600"/>  

<br>  
<br>  
    
**Common Anode Configuration:**  
In a common anode LED matrix, positive poles of LEDs in each row are connected, and negative poles
of LEDs in each column are connected. This simplifies the wiring and control to save GPIO.


**Matrix & Scan Operation Principle:**  
The matrix operation functions similarly to the way old LCD and CRT displays operate, using either
row or column scanning. In our project, we initially designate 16 ports on the ESP32 to connect to
an 8x8 LED matrix, consisting of 8 rows and 8 columns.  

Since columns operate at a low level, they serve as the selection ports. By setting specific columns
to a low level, we can configure 8 ports in the row to display content in the selected column.
After adding a delay, we proceed to the next column, repeating the process.  

Scanning progresses through the connected columns one by one, turning on LEDs based on the row  
pattern for each row. This process is repeated, scanning columns sequentially. This column-by-column  
operation is commonly known as scanning.  

<br>  
<br>  

<img src="https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register/assets/66625688/d614da85-7668-4bdf-bc24-9673a3d83b9b" width="600"/>  

<br>  
<br>  

**Role of 74HC595 Shift Register:**  

A Shift Register is a device that facilitates Serial-To-Parallel and Parallel-To-Serial Data Conversion.  
Instead of directly connecting 8 bits to a Microcontroller Unit (MCU), we send 8 bits in series from  
the MCU to the Shift Register, which then distributes the bits among 8 outputs.  

To expand data capacity, two 74HC595 ICs can be daisy-chained. To achieve this, connect the ~Q7 pin of the first IC  
with the Serial input (DS) pin of the second 595 IC. Additionally, provide the same clock signal to both integrated circuits.  
This setup allows two 74HC595 ICs to function as a single 16-bit shift register. This process can be continued to  
connect as many ICs as needed, increasing the data width.  

In my circuit, two 74HC595 shift registers are utilized. One controls the columns, and the other controls the rows.  
While a 74HC595 shift register is originally an 8-bit shift register, cascading two of them results in a single 16-bit register  
This configuration aids in storing and shifting out 16 bits of data, ultimately saving GPIO pins.  

**Shift Register Pins Explained:**  

* QH (Pin 9)  
Serial Out. This output serial bits are outputted to the MCU,  
and it can be connected to serial data input (DS) of other shift registers to cascade

* MR (SRCLR) (Pin 10)  
Master Reset or Clear. When pulled low (connected to ground),  
it clears the internal register of the shift register. This is used to reset the shift register to a known state.

* SCH_CP (SRCLK) (Pin 11)  
Serial Clock Input. This is the clock input for shifting data into the shift register.  
The rising or falling edge of this clock signal is used to shift the data bits through the shift register.

* ST_CP (RCLK) (Pin 12)  
Storage Clock Input or Latch Clock. This is the clock input that latches the shifted data  
to the output pins. When the latch clock signal transitions,  
the data that has been shifted into the register is presented at the output pins (Q0 to Q7).

* OE ( Enable )  
Output Enable. When this pin is low, (connected to ground )  
The outputs of Q0 to Q7 are enabled.  
When it's high ( connected to VCC ) the outputs are disabled.  

* DS ( Data )  
Serial Data Input. This is where the external data is input to the shift register.  
Each rising or falling edge of the Serial Clock Input (SCH_CP) shifts the data into the register.  

* Q0 to Q7 (Pin 15, 1, 2, 3, 4, 5, 6, 7)  
These are the eight output pins. In my project, they are connected to the columns or rows of the LED matrix.  

<img src="https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register/assets/66625688/1e6cd857-03e8-49a1-90a1-95bdbd4dea3d" width="600"/>  
<br>  
<br>  

## The Code :  
The code is built on the ESP-IDF framework, a framework closer to pure C language that provides  
the opportunity to leverage all ESP-IDF capabilities, such as the Real-Time Operating System (RTOS).  

The code for this project is self-explanatory, and the steps involved are as follows:  

1. Preparing Shapes and Data:  
Define the shapes and data to be printed.  

2. Configuring GPIO:  
Configure the General-Purpose Input/Output (GPIO) pins.  

3. Initialize LATCH_PIN to 0 (Input State):  
Set the LATCH_PIN to 0, representing the input state.  

4. Taking 16-Bits of Row/Column Data:  
Take 16 bits of row/column data (numbers, letters, shapes) as an argument.  
  
5. Passing Row/Column Data Serially:  
Pass the row/column data to the DATA_PIN serially, bit by bit, by shifting Most Significant Bit (MSB) to Least Significant Bit (LSB).  

6. Toggling SRCLK to Shift Data:  
After each bit, toggle SRCLK to shift data to the Shift Register.  

6. Awaiting at Outputs Q0 to Q7:  
After completing 8 bits, the data is awaiting at outputs Q0 to Q7.  

7. Toggling LATCH_PIN to Take Snapshot:  
Toggle the LATCH_PIN to take a snapshot and display all data at Q0 - Q7.  

# Contact Info  
## If you have any questions email me : dev.majed.alharbi@gmail.com
