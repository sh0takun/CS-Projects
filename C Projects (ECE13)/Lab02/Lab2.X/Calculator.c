// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double Average(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Round(double operand);


void CalculatorRun(void)
{   
    printf("\n\nWelcome to Shota's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);

    //Your code here
    while(1) {
        char op;
        double operand1, operand2, operand, result;
        
        printf("Enter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,r): ");
        scanf(" %c", &op);   

        switch(op)
        {
            case '+':
                printf("Enter the first operand: ");
                scanf("%lf", &operand1);
                printf("Enter the second operand: ");
                scanf("%lf", &operand2);
                result = Add(operand1, operand2);
                printf("Result of (%lf + %lf): %lf\n\n", operand1, operand2, result);
                break;
            case '-':
                printf("Enter the first operand: ");
                scanf("%lf", &operand1);
                printf("Enter the second operand: ");
                scanf("%lf", &operand2);
                result = Subtract(operand1, operand2);
                printf("Result of (%lf - %lf): %lf\n\n", operand1, operand2, result);
                break;
            case '*':
                printf("Enter the first operand: ");
                scanf("%lf", &operand1);
                printf("Enter the second operand: ");
                scanf("%lf", &operand2);
                result = Multiply(operand1, operand2);
                printf("Result of (%lf * %lf): %lf\n\n", operand1, operand2, result);
                break;
            case '/':
                printf("Enter the first operand: ");
                scanf("%lf", &operand1);
                printf("Enter the second operand: ");
                scanf("%lf", &operand2);
                result = Divide(operand1, operand2);
                if (result == HUGE_VAL){
                    printf("Divide by zero error!\n");                
                } else {
                    printf("Result of (%lf / %lf): %lf\n\n", operand1, operand2, result);     
                }
                break;
            case 'm':
                printf("Enter the first operand: ");
                scanf("%lf", &operand1);
                printf("Enter the second operand: ");
                scanf("%lf", &operand2);
                result = Average(operand1, operand2);
                printf("Result of average(%lf and %lf): %lf\n\n", operand1, operand2, result);
                break;
            case 'a':
                printf("Enter the first operand: ");
                scanf("%lf", &operand);
                result = AbsoluteValue(operand);
                printf("Result of |%lf|: %lf\n\n", operand, result);
                break;
            case 'c':
                printf("Enter the first operand: ");
                scanf("%lf", &operand);
                result = FahrenheitToCelsius(operand);
                printf("%lf degrees Fahrenheit is: %lf degrees Celsius\n\n", operand, result);
                break;
            case 'f':
                printf("Enter the first operand: ");
                scanf("%lf", &operand);
                result = CelsiusToFahrenheit(operand);
                printf("%lf degrees Celsius is: %lf degrees Fahrenheit\n\n", operand, result);
                break;
            case 't':
                printf("Enter the first operand: ");
                scanf("%lf",&operand);
                result = Tangent(operand);
                printf("Result of tan(%lf): %lf\n\n", operand, result);
                break;
            case 'q':
                exit(0);
                break;
            default:
                printf("Error, not a valid operator.\n\n");
                break;  
        
        }
    }
    BOARD_End();
}


/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    double result;
    result = operand1+operand2;
    return result;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
    double result;
    result = operand1-operand2;
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    double result;
    result = operand1*operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
	double result;
    result = operand1/operand2;
    if (operand2 == 0){
        return HUGE_VAL;
    } else {
        return result;
    }
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    double result;
    result = operand * ((operand > 0) - (operand < 0));
    return result;
           
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    double result;
    result = (operand - 32);
    result = result * 5;
    result = result / 9;
    return result;               
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    double result;
    result = (operand * 9);
    result = result / 5;
    result = result + 32;
    return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    double result;
    result = (operand1 + operand2) / 2;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
    double result;
    result = operand * (M_PI / 180);
    return tan(result);                
}
/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/



