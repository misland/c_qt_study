#include <stdio.h>

int num = 100;

typedef struct Person
{
  char name[50];
  int age;
} Person;

struct Person doctor;

void test(int *out)
{
  *out = num;
  // out = &num;//这种，out只是形参，离开函数区域即被销毁
  printf("out:%d\n", *out);
}

void test2(Person *out)
{
  // out = &doctor;
  printf("test2:docter age:%d\n", doctor.age);
  *out = doctor;
  out->age = 2;
  printf("test2:out.age:%d\n", out->age);
}

int main()
{
  doctor.age = 10;
  printf("-------------ONE----------------\n");
  int var1 = 100;
  char var2[10];
  printf("address of var1 is : %#X, var2 is : %#X \n", &var1, &var2);

  int *p = &var1;
  *p = 200;
  printf("value of a is : %d \n", *p);

  //空指针，指向内存地址0
  int *ptr = NULL;
  printf("address of ptr is : %#X \n", ptr);

  int arr[4] = {1, 2, 3, 4};
  //对于数组而言，变量名本身就是首个元素的地址，所以赋值时不能用&，用了反而报错
  int *ptrArray = arr;
  for (int i = 0; i < 4; i++)
  {
    printf("display by variable name, %dth element is : %d \n", i + 1, arr[i]);
    printf("display by pointer, %dth element is :`%d \n", (i + 1), *(ptrArray + i));
  }

  printf("-------------TWO----------------\n");
  int tem = 0;
  test(&tem);
  printf("tem:%d\n", tem);

  Person per;
  test2(&per);
  printf("age:%d\n", per.age);

  return 0;
}