# Balancer
This project implements a balancer for a ceailing fan.
An arduino with a mems accelerometer is used to measure acceleration. An
infrared diod and infrared sensor are used to detect the fan blades thus
creating a reference signal.

The data is transmitted to a computer where the final imbalance is calculated.

After calculating the imbalance the counter weights can be distributed onto
the blades.

## Notebooks
The jupyter notebooks can be viewed under:  
http://nbviewer.jupyter.org/github/svenmayer/balancer/blob/master/excentricity.ipynb

## Hardware
The hardware that is used is:
  * IDUINO ST1089 IR Receiver-Modul
  * MakersFactory 3-Axis Digital Acceleration Sensor
  * IR LED 940 nm
