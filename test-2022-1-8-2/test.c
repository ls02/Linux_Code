#include <stdio.h>

int main()
{
	////char arr[2] = "he";

	////int i = 0;
	//////for (i = 0; i < 2; i++)
	//////{
	//////	printf("%d ", arr[i]);
	//////}
	////printf("%s", arr);

	int arr[2][3] = { {1, 2, 3 }, { 4, 5, 6 } };

	int i = 0;
	int j = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("arr[%d][%d]µÄµØÖ·£º%p\n", i, j, &arr[i][j]);
		}
	}

	return 0;
}