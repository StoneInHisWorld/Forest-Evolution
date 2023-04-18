#include "declaration.h"

int set_Paracitism(Player * players, INT_DB db)
{
	// 如果寄生宿主尚未指定且调用玩家拥有寄生技能
	if (i_host == NOTFOUND &&
		players[i_parasite].skills[Paracitism])
	{
		printf("%d号玩家是否要设置寄生宿主？\n", i_parasite + 1);
		if (yes_or_no())
		{
			int host;
			do
			{
				printf("请输入宿主序号：");
				scanf("%d", &host);
			} while (!Exists(host));
			i_host = host - 1;
			printf("%d号玩家发动寄生技能，指定宿主为%d号玩家",
				i_parasite + 1, i_host + 1);
			return 1;
		}
	}
	return 0;
}