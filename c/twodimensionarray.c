#include <stdio.h>

void print_array1(int *arr, int row, int column);

void print_array2(int arr[][3], int row, int column);

int main(int argc, char *argv[])
{
  // 声明时直接初始化
  // int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
  // 也可以这样初始化，系统会根据声明的数组大小自动分配
  int arr[2][3] = {1, 2, 3, 4, 5, 6};
  // 如果缺失了部分值，默认补0
  // int arr[2][3] = {11, 23, 33, 46, 84};
  // 最基本的获取数组元素的方法:通过下标获取
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      printf("arr[%d][%d]:%d\n", i, j, arr[i][j]);
    }
  }

  // 因为arr是二维数组，且arr指向的是二维数组的开始地址，可以将arr当作一个指针
  // 根据下一行的输出，可以看到，对于arr来说，是以一行为单位
  // 这样，arr+1的作用就是移到二维数组的下一行开始
  printf("%x,%x\n", arr, arr + 1); // 61fe20,61fe2c
  // 基于上面说的，tem指向第二行开始，将其强制转为int类型指针，强制程序按int类型来取数据，即一次取4位（根据不同编译器来定）
  int *tem = (int *)(arr + 1);
  printf("%x\n", tem); //61fe2c
  printf("%d,%d,%d,%d,%d,%d\n", *(tem - 3), *(tem - 2), *(tem - 1), *tem, *(tem + 1), *(tem + 2));

  printf("---------------------FUNCTION 1---------------------\n");
  // 由于接收的是int *类型参数，这里将数组第一个元素的地址传递过去，因为数组声明时是int，这里表示传递的是一个int类型的指针
  // arr存放的也是第一个元素的地址，但是他们类型不同，arr增加时是以行为单位增加的，所以这里不能直接将arr地址传递进去
  print_array1(&arr[0][0], 2, 3);
  
  printf("---------------------FUNCTION 2---------------------\n");
  // 直接将数组的起始地址传递即可
  print_array2(arr, 2, 3);

  return 0;
}

// 当不知道二维数组到底有多少元素时，用这种方法
// 只要知道存放的数据类型，根据数组元素存放时是连续存放的特点，也可以逐个读取出来
// 调用时，必须要将行和列传递进来
void print_array1(int *arr, int row, int column)
{
  int i, j;
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      printf("%d\n", *(arr + i * column + j));
    }
  }
}

// 知道数组的行、列时，用这种方法，直接用下标的方式读取，比较方便
void print_array2(int arr[][3], int row, int column)
{
  int i, j;
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      printf("%d\n", arr[i][j]);
    }
  }
}
