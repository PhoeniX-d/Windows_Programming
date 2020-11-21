using System;
using System.Runtime.InteropServices;
using AutomationDllServerTypeLibForDotNet;

public class AutomationDllServerCSharpClient
{
    public static void Main()
    {
        CMyMathClass objCMyMathClass = new CMyMathClass();
        IMyMath objIMyMath = (IMyMath)objCMyMathClass;
        int num1 = 125, num2 = 100, sum, sub;
        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum of " + num1 + " And " + num2 + " is " + sum);
        sub = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Subtraction of " + num1 + " And " + num2 + " is " + sub);
    }
}
