# PSU_ftrace_2019

The goal of this project is to trace all functions in an ELF binary as well as syscalls and signals.  
This project passed **83.3%** on the Marvin TA.

Here is a simple output :

`Entering function main at 0x42ff231`  
`Entering function my_putstr at 0x42ff9fd`  
`Entering function my_putchar at 0x43aa123`
`Syscall write (0x1, 0xff3210123, 0x1) = 0x1`  
`Leaving function mu_putchar`  
`Entering function my_putchar at 0x43aa123`  
`Syscall write (0x1, 0xff3210124, 0x1) = 0x1`  
`Leaving function mu_putchar`  
`Entering function my_putchar at 0x43aa123`  
`Syscall write (0x1, 0xff3210125, 0x1) = 0x1`  
`Received signal SIGWINCH`  
`Leaving function mu_putchar`  
`Entering function my_putchar at 0x43aa123`  
`Syscall write (0x1, 0xff3210126, 0x1) = 0x1`  
`Leaving function mu_putchar`  
`Leaving function my_putstr`  
`Entering function printf at 0x877621fda31`  


If you wanna run this project you have to do the following commands:

`make re`  
`./ftrace [YOUR_BINARY]`

Enjoy !

### Credits :  
* **[Antoine Tréboutte](https://github.com/Zumtak)**  
* **[Martin Rabaud](https://github.com/EnderRM)**  
* **[Rémi Poulenard](https://github.com/Mireus1)**
