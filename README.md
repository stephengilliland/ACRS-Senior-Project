# Aquatic Chemical Regulation System (ACRS)

#### Group Members:
- Stephen Gilliland
- Nicholas Zugates
- George Tittnitch

## What is ACRS?
ACRS is a water chemical regulation system which uses various sensors connected via I2C bus to take measurements of chemical content, temperature, pH and turbidity. These readings are used in order to make adjustments to the balance of chemicals in the water. The system is interfaced to the user via an Android app. The readings aquired by the system are logged in a microSD card for recordkeeping purposes.

The main goal of the system is modularity; meaning any of our sensors connected to the controller I2C bus will be automatically recognized and read. The I2C bus is compatible with up to 127 slave devices.


## Hardware

The project utilizes multiple microprocessors, one of which acts as a I2C Master, the rest are attached to the sensors and act as Slave devices. The master is a difference processor due to the need of more program space. The other device's programs are minimal thus they do not need much space.

Device | MicroController Used | Program Space | SRAM
------------ | ------------- | ------- | ----- 
Master device | ATmega2560 | 256KB | 8KB
Slave devices | ATmega328 | 32KB | 2KB

## Software
The project is programmed in C++ using the arduino programming environment.

### The Controller
The device chosen for this for the main controller is the Atmega2560. The Atmega2560 is an 8-bit microcontroller that is well suited for the application. There are many reasons that this controller was the right one for the application: it’s an Arduino compatible processor, it has the serial peripherals needed to communicate to the necessary devices, and it has enough memory space to hold the large main program. 

Arduino compatibility is a very beneficial advantage due to the large amount of libraries and support that are available. Arduino also has a very convenient windows application for writing code, compilation, and uploading. The controller also needed a number of serial peripherals in order to communicate to the necessary devices such as: UART for communication to the bluetooth chip (RN-42) , I2C in order to get sensor values, and SPI to write to the microSD card for data logging purposes.

Because of the large number of devices the controller needed to interface with, a PCB was created which contains most of the needed devices and supporting circuitry. Included in the controller PCB are: the controller (Atmega2560), voltage regulators (3.3V and 5V), a microSD slot with supporting level-translators, and a 12DC input power jack.


![Image of Main Board](https://github.com/stephengilliland/ACRS-Senior-Project/blob/master/Boards/SP1/BoardLayoutPIC.JPG)

### Data Logging
Data is logged to a microSD card using the SPI interface of the Atmega2560, with every set of values that are logged, a timestamp is also logged in order to give the user a record of data along with the date and time of the measurements.  An example of a data entry is as follows: 

“4/23/2017 20:23:59  pH=7.1  Temp=71.23  Chlorine=2.23  Trepidity=95”

### Sensors
Sensor code Overview

### The App
App example

## Pictures/Videos
Put pictures and videos here.

## Resumes
- [Stephen Gilliland](./Resumes/SGilliland_Resume.pdf)
- [Nicholas Zugates](./Resumes/N_ZugatesResume.pdf)
- [George Tittnich](./Resumes/GeorgeTittnich_Resume.pdf )
