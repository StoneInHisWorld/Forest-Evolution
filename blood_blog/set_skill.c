#include "declaration.h"

int set_Paracitism(Player * players, INT_DB db)
{
	// �������������δָ���ҵ������ӵ�м�������
	if (i_host == NOTFOUND &&
		players[i_parasite].skills[Paracitism])
	{
		printf("%d������Ƿ�Ҫ���ü���������\n", i_parasite + 1);
		if (yes_or_no())
		{
			int host;
			do
			{
				printf("������������ţ�");
				scanf("%d", &host);
			} while (!Exists(host));
			i_host = host - 1;
			printf("%d����ҷ����������ܣ�ָ������Ϊ%d�����",
				i_parasite + 1, i_host + 1);
			return 1;
		}
	}
	return 0;
}