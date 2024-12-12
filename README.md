#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct 
{
    float real;
    float img;
}Complex;
Complex add_Complex(Complex a, Complex b)
{
    Complex c;
    c.real=a.real+b.real;
    c.img=a.img+b.img;
    return c;
}
void print_Complex(Complex a)
{
    if(a.img==0)
    printf("%.1f\n",a.real);
    else if (a.img>0)
        printf("%.1f+%.1fi\n", a.real, a.img);
    else
        printf("%.1f-%.1fi\n", a.real, -(a.img));   
}
Complex read_Complex()
{
    Complex ans;
    printf("Enter real part:");
    scanf("%f", &ans.real);
    printf("enter the imaginary part:");
    scanf("%f", &ans.img);
    return ans;
}
int Comapre_Complex(Complex a, Complex b)
{
    float magn1=sqrt(pow(a.real,2)+pow(a.img,2));
    float magn2=sqrt(pow(b.real,2)+pow(b.img,2));
    if(magn1==magn2)
    return 0;
    else if(magn1>magn2)
    return 1;
    else
    return -1;
}
int main()
{
    Complex Complex1,Complex2,Complex3;
    Complex sum1,sum2;
    printf("Enter the first complex number.\n");
    Complex1=read_Complex();
    printf("Enter the second complex number.\n");
    Complex2=read_Complex();
    printf("Enter the third complex number.\n");
    Complex3=read_Complex();
    printf("the three complex numbers are respectively :\n");
    print_Complex(Complex1);
    print_Complex(Complex2);
    print_Complex(Complex3);
    sum1=add_Complex(Complex1,Complex2);
    sum2=add_Complex(sum1,Complex3);
    printf("sum of 3 complex numbers is :");
    print_Complex(sum2);
    Complex max;
    max=Complex1;
    if(Comapre_Complex(Complex2,max)==1)
    max=Complex2;
    if(Comapre_Complex(Complex3,max)==1)
    max=Complex3;
    printf("the higher magnitude complex is :");
    print_Complex(max);
    return 0;
}
