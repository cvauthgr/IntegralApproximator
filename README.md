# IntegralApproximator

## How to run it 

To run this project you will need :

1) GCC 13 or newer 
2) GNU Make 4.0 or newer

Move all files from `src` and `headers` and the makefile to one directory.

In powershell execute these in succesion :

```
cd "PathOfTheDirectoryYouCreated"
make //If you installed make otherwise ignore it and execute the line below
g++ -std=c++23 -o integralCalculator integralCalculator.cpp
.\integralCalculator.exe
```

## Example 

Let's say we want to integrate the function `f(x)=e^(-x^2)` inside the domain {0,1} (inclusive) which cannot be computed analytically only approximated.

# Step 1 : 

The functions are hardcoded (as of yet i haven't made my own parser) so we need to change the function ourselves . We need to open the header file `integralClass.h` 

Navigate to line 26 and you should be seeing this :

<img width="690" height="115" alt="image" src="https://github.com/user-attachments/assets/f8323b35-cb42-4627-93f3-0406dd6cb57b" />

After the return field , delete the prexisting function and write yours . 

<img width="722" height="114" alt="image" src="https://github.com/user-attachments/assets/ee5e321f-e9b2-49f9-82f9-891c7859d67d" />

Save the changes you made .

# Step 2:

Now you can execute the program as per the instructions dictate :

<img width="967" height="217" alt="image" src="https://github.com/user-attachments/assets/12e808a5-95c5-49f7-b84f-74de4724ed73" />


The bounds are user defined and can be accurate untill 15 digits after 0 . We get the approximation and also an error margin of 95% confidence which is acceptable for those types of monte carlo approximations 

# Why does it work ( Theory behind it )
