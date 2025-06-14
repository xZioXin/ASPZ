#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>

int main()
{
	struct rlimit rl;
	rl.rlim_cur = 100;
	rl.rlim_max = 100;
	if (setrlimit(RLIMIT_FSIZE, &rl) != 0)
	{
		perror("setrlimit");
		return 1;
	}
	FILE *f = fopen("dice_rolls.txt", "w");
	if (!f)
	{
		perror("fopen");
		return 1;
	}
	srand(time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		int roll = rand() % 6 + 1;
		if (fprintf(f, "Кидок %d: %d\n", i + 1, roll) < 0)
		{
			if (errno == EFBIG)
			{
				printf("Досягнуто ліміту розміру файлу!\n");
				break;
			}
			else
			{
				perror("fprintf");
				break;
			}
		}
	}
	fclose(f);
	return 0;
}