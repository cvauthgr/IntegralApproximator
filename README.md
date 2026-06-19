# IntegralApproximator
![GCC](https://img.shields.io/badge/GCC-4EAA25?logo=gnu&logoColor=white)
![C++23](https://img.shields.io/badge/C%2B%2B23-00599C?logo=cplusplus&logoColor=white)
![Make](https://img.shields.io/badge/Make-A42E2B?logo=gnu&logoColor=white)
### What is this program

This program is a Monte Carlo integral approximator written in C++23 with no external dependencies . We can use it to approximate integrals over closed real-valued intervals of functions that cannot be computed analytically .

### How to run it 

To run this project you will need :

1) GCC 13 or newer 
2) GNU Make 4.0 or newer

Move all files from `src` and `headers` and the makefile to one directory.

In powershell execute these in succession :

```
cd "PathOfTheDirectoryYouCreated"
make #If you installed make otherwise ignore it and execute the line below
g++ -std=c++23 -o integralCalculator integralCalculator.cpp
.\integralCalculator.exe
```

### Example 

Let's say we want to integrate the function `f(x)=e^(-x^2)` inside the domain [0,1] (inclusive) but it's antiderivative cannot be expressed using elementary functions. So we are going to approximate it !!!

#### Step 1 : 

The functions are hardcoded (as of yet i haven't made my own parser) so we need to change the function ourselves . We need to open the header file `integralClass.h` 

Navigate to line 26 and you should be seeing this :

<img width="690" height="115" alt="image" src="https://github.com/user-attachments/assets/f8323b35-cb42-4627-93f3-0406dd6cb57b" />

After the return field , delete the pre-existing function and write yours . 

<img width="722" height="114" alt="image" src="https://github.com/user-attachments/assets/ee5e321f-e9b2-49f9-82f9-891c7859d67d" />

Save the changes you made .

#### Step 2:

Now you can execute the program as per the instructions above:

<img width="967" height="217" alt="image" src="https://github.com/user-attachments/assets/12e808a5-95c5-49f7-b84f-74de4724ed73" />

The bounds are user defined and can be accurate to 15 decimal points . We get the approximation and also an error margin of 95% confidence which is acceptable for these types of Monte Carlo approximations .

### Why does it work(Theory behind it)

The program utilizes the Riemann definition of the definite integral(not the Darboux one).

The definition is [here](RiemannDefinition.pdf)( in a LaTeX pdf I made ).

Our program takes a given interval and partitions it in N-th subintervals of equal size. Then in each one of them picks a random point (it can be the edges too) and passes it to our function . The function returns its value which is then multiplied by the length of the respective subinterval it is in . This calculation is added to our approximation. This happens N times until the program finishes execution .

### The statistical error margin 

As well as the approximation we get an error margin of 95% confidence which gives a bound of how far the approximation will likely be from the real value . By treating the function's values as statistical samples we are able to calculate the mean , variance and the standard error , which is later multiplied by 1.96 ( for the 95% confidence ) giving us that error margin .

### Some timed tests


Integrating e^(-x^2) over [0,1] with 100 million and 1 billion subpartiotions respectively :


1)100 million intervals 


<img width="864" height="647" alt="Screenshot 2026-06-12 200802" src="https://github.com/user-attachments/assets/2a5dda8a-10a4-4fb8-b26d-06bd1c5ea491" />


2)1 billion intervals


<img width="868" height="652" alt="Screenshot 2026-06-12 200809" src="https://github.com/user-attachments/assets/bd5534ab-87bf-4642-a3f8-705f7fd7fddc" />


Time complexity : Scales linearly , O(n) 

### Future features

1) In the future I am planning to add a mathematical function parser
2) Multithreaded implementation
