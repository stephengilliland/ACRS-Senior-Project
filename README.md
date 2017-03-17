# Aquatic Chemical Regulation System (ACRS)

#### Group Members:
- Stephen Gilliland
- Nicholas Zugates
- George Tittnitch

## What is ACRS?
A water chemical regulation system which uses various sensors connected via I2C bus to take measurements of chemical content, temperature, pH and turbidity. These readings are used in order to make adjustments to the balance of chemicals in the water. The system is interfaced to the user via an Android App. The readings aquired by the system are logged in a microSD card for recordkeeping purposes.

The main goal of the system is modularity; meaning any of our sensors connected to the controller I2C bus will be automatically recognized and read.  

## Hardware

The project utilizes multiple Microprocessors, one of which acts as a I2C Master, the rest are attached to the sensors and act as Slave devices.

Device | MicroController Used
------------ | -------------
Master device | ATMega2560
Slave devices | ATMega328

## Software
Insert code here

## Pictures/Videos
Put pictures and videos here.

## Resumes
- [Stephen Gilliland](./Resumes/SGilliland_Resume.pdf)
