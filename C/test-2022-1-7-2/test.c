#include <stdio.h>

void test1()
{
  int input = 0;
  printf("请输入一个数：");
  scanf("%d", &input);

  if (input != 0 && input % 2)
  {
    printf("%d是奇数！\n", input);
  }

  printf("\n");
}

void test2()
{
  int i = 1;

  for (i = 1; i < 100; i += 2)
  {
    printf("%d ", i);
  }

  printf("\n");
}

void test3()
{
  int n = 0;
  int i = 0;
  int sum = 1;
  
  printf("请输入：");
  scanf("%d", &n);

  for (i = 1; i < n + 1; i++)
  {
    sum *= i;
  }

  printf("n的阶乘为：%d\n", sum);
}

void test4()
{
  int i = 1;
  int j = 1;
  int sum = 0;
  int n = 0;
  int temp = 1;

  printf("请输入：");
  scanf("%d", &n);
  
  for ( i = 1; i <= n; i++ )
  {
   // int temp = 1;
   // 
   // for (j = 1; j <= i; j++)
   // {
   //   temp *= j;
   // }
   temp *= i;

    sum += temp;

  }

  printf("阶乘和为：%d\n", sum);
}

void test5()
{
  int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int sz = sizeof(arr) / sizeof(arr[0]);
  int left = 0;
  int right = sz - 1;
  int k = 0;
  int mid = 0;

  scanf("%d", &k);

  while (left <= right)
  {
    mid = (right + left) / 2;

    if (arr[mid] > k)
    {
      right--;
    }
    else if (arr[mid] < k)
    {
      left++;
    }
    else
    {
      break;
    }
  }
  if (arr[mid] == k)
  {
    printf("找到了！下标是：%d\n", mid);
  }
  else
  {
    printf("没找到！\n");
  }
}

int main()
{
  //test1(); 
  //test2();  
  //test3();  
  //test4();  
  test5();  

  return 0;
}
