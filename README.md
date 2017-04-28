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
The system begins with the three modular sensors collecting data from the water that is pulled through the system. These sensors each have a dedicated microcontroller that continually take measurements of the sensor values and send these values to the main controller upon request. The first sensor that the water passes over is the chlorine sensor. The design of the chlorine sensor is as followed. The base for the sensor is the TSL235R-LF light intensity to frequency converter. Its purpose is to collect light within the enclosure into which the water will be pumped. The light source is for the sensor is an LED that is mounted in a tube in order to direct the light through the water directly onto the sensors photodiode. The other key element in making this sensor work is the DPD chemical that is added through the top of the sensors container. This substance changes the color of the water to a purple hugh based off of the amount of free chlorine present in it. Now, once the DPD is added and the water changes color, the purple color blocks some of the light to the sensor. So, in order for this sensor to give relevant data, a correlation between the outputted frequency and the amount of chlorine needed to be made. This was done by utilizing the pool test kit described earlier. A sample of water was taken from the source and used in the pool test kit which would give a value between 1 and 5 parts per million. At the same time the same water source that the sample for the pool test kit was taken from was run through the sensor and the DPD was applied. Thus, the frequency that was outputted would correlate with the results given from the pool test kit (10KHZ = 2ppm for example).  
    
The pH sensor works similar to an amperometric sensor listed above. The main difference being that there is a plastic shield over the electrodes. The sensor compares the water passing over it to a controlled water sample stored in the sensor. The sensor outputs an analog signal that correlates to the pH level. This was done by using a sample of distilled water and adding pH packets  that were provided with the sensor. These packets, when mixed with distilled water, create a solution of known pH level. This was how the sensor calibration was performed. An example of this would be if a pH 4 packet was added whatever analog signal was outputted is the signal for a pH of 4. 

Finally, the turbidity sensor senses the clearness of the water. This a key test in water quality and even though it does not necessarily fit into the proof of concept, it is a perfect example of how the The A.C.R.S. is adaptable to multiple scenarios. The same goes for the temperature sensor, they are simply helpful for the user to have and show the future possibilities of the project. 

### The App
In order to give the user the most personal experience with the A.C.R.S. system, a user interface was developed in the form of an Android application.  This medium was chosen because in the current day and age it is most convenient for the everyday pool owner.  The app is easy to download, sync to the main system via Bluetooth, control, and monitor.

There are many programs on the market that can be used for Android application development. After experimentation with Android Studio, it was decided that another option was needed.  Further research concluded that MIT App Inventor 2 was the best option for the A.C.R.S. project purposes.

Upon further development the application could be altered and formatted for tablets and other personal devices.  As of now, the application is designed specifically for smartphones.

## Pictures/Videos
Put pictures and videos here.

## Resumes
- [Stephen Gilliland](./Resumes/SGilliland_Resume.pdf)
- [Nicholas Zugates](./Resumes/N_ZugatesResume.pdf)
- [George Tittnich](./Resumes/GeorgeTittnich_Resume.pdf )
