OperatingSystemSimulation-
==========================

This Program will simulate CPU different operations , ie. processes life cycle, hard disk scheduling, virtual memory,... 
============================================================================================================================
* this program will simulate the CPU handling of processes and interruptions from users or processes,the program simulate the processes life cycle and its movement to different system and devices queues as a result of a signal or intruption
The program contains three vectors that contain the devices - hard disks , printers and CD/RW
Each device contain its own queue that along with the ready queues will be used to simulate a process life cycle
Each device has its own ID , also each process has its own PCB
The program contains four classes, one for the process and one for each device
The program contains three global variables - number of devices- since it is needed to be available for all functions
The main function contains  two functions only, one for system setting mode and the other for running mode 
================================================================================================================================
