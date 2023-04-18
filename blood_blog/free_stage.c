#include "declaration.h"

void free_stage_UI(Player *players, INT_DB db, int round)
{
	printf("________________\n");
	printf("��%d�����ɽ׶Σ�%d���Ӽ�ʱ��ʼ�����пɽ������²�����\n", round, FREESTAGE_SPAN);
	printf("������jh\n");
	printf("�鿴ĳ����ҵ�Ѫ���������Լ����ܣ�ck\n");
	printf("������js\n");
	
	char cmd[3];
	do
	{
		printf("���������");
		scanf("%s", cmd);
		if (strcmp(cmd, "jh") == 0)
		{
			// ������Ѫ�����ƽ���Ѫ�����߿���
			exchange_UI(players);
		}
		else if (strcmp(cmd, "ck") == 0)
		{
			// ���ĳ����ҵ�Ѫ���Լ�ʣ�࿨��
			output_player_UI(players);
		}
		else if (strcmp(cmd, "js") == 0)
		{
			// ������һ�׶�
			break;
		}
		else
		{
			printf("����������ȷ�����������룡\n");
		}
		set_Paracitism(players, db);
	} while (1);
	return;
	printf("________________\n");
}

void exchange_UI(Player *players)
{
	printf("________________\n");
	printf("�緵����һ�������룺0\n");
	printf("�밴�����¹�����н���������\n");
	printf("���1��� ���1������Ѫ�� ���1�����Ŀ��� ���2��� ���2������Ѫ�� ���2�����Ŀ���\n");
	printf("�����3��5���ƻ����4��2���ƣ������룺3 0 5 4 0 2\n");
	printf("�����4��3��Ѫ�����9��2���ƣ������룺4 3 0 9 0 2\n");
	do
	{
		int p1, p1_b, p1_c, p2, p2_b, p2_c;
		printf("�����룺");
		scanf("%d", &p1);
		if (0 == p1)
		{
			getchar();
			break;
		}
		else if (Exists(p1))
		{
			scanf("%d %d %d %d %d", &p1_b, &p1_c, &p2, &p2_b, &p2_c);
			// ������Ҵ����Ƿ񶼴���
			if (Exists(p2))
			{
				exchange(players, p1, p1_c, p1_b, p2, p2_c, p2_b);
			}
			else
			{
				printf("���2�����ڣ����������룡\n");
			}
		}
		else
		{
			printf("���1�����ڣ����������룡\n");
		}
	} while (1);
	printf("________________\n");
}

void exchange(Player *players, int p1, int p1_c, int p1_b, int p2, int p2_c, int p2_b)
{
	if (can_exc_Card(players, p1, p1_c, p2, p2_c)
		&& can_exc_Blood(players, p1, p1_b, p2, p2_b))
	{
		if (p1_c * p2_c != 0)
		{
			// ˫����ʹ���˿���
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p1 - 1].card[p1_c - 1]--;
			players[p1 - 1].card[p2_c - 1]++;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			players[p2 - 1].card[p2_c - 1]--;
			players[p2 - 1].card[p1_c - 1]++;
			printf("%d�����ʹ��%d�����Լ�%d��Ѫ������%d����ҵ�%d�����Լ�%d��Ѫ��\n",
				p1, p1_c, p1_b, p2, p2_c, p2_b);
			return;
		}
		else if (p1_c == 0 && p2_c != 0)
		{
			// ���1��ʹ�ÿ���
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p1 - 1].card[p2_c - 1]++;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			players[p2 - 1].card[p2_c - 1]--;
			printf("%d�����ʹ��%d��Ѫ������%d����ҵ�%d�����Լ�%d��Ѫ��\n",
				p1, p1_b, p2, p2_c, p2_b);
			return;
		}
		else if (p1_c != 0 && p2_c == 0)
		{
			// ���2��ʹ�ÿ���
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p1 - 1].card[p1_c - 1]--;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			players[p2 - 1].card[p1_c - 1]++;
			printf("%d�����ʹ��%d�����Լ�%d��Ѫ������%d����ҵ�%d��Ѫ��\n",
				p1, p1_c, p1_b, p2, p2_b);
			return;
		}
		else
		{
			// ˫������ʹ�ÿ���
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			printf("%d�����ʹ��%d��Ѫ������%d����ҵ�%d��Ѫ��\n",
				p1, p1_b, p2, p2_b);
			return;
		}
	}
}

int can_exc_Card(Player *players, int p1, int p1_c, int p2, int p2_c)
{
	// ������1�Ŀ�����������Ƿ���ȷ
	if (Exists(p1_c))
	{
		// ������2�Ŀ�������Ƿ�������ȷ
		if (Exists(p2_c))
		{
			// ������1�Ŀ�������
			if (players[p1 - 1].card[p1_c - 1] > 0)
			{
				// ������2�Ŀ�������
				if (players[p2 - 1].card[p2_c - 1] > 0)
				{
					return 1;
				}
				else
				{
					printf("%d�����û��%d�ſ��ƣ����������룡\n", p2, p2_c);
					return 0;
				}
			}
			else
			{
				printf("%d�����û��%d�ſ��ƣ����������룡\n", p1, p1_c);
				return 0;
			}
		}
		else if (p2_c == 0)
		{
			// ���2��ʹ�ÿ���
			// ������1�Ŀ�������
			if (players[p1 - 1].card[p1_c - 1] > 0)
			{
				return 1;
			}
			else
			{
				printf("%d�����û��%d�ſ��ƣ����������룡\n", p1, p1_c);
				return 0;
			}
		}
		else
		{
			printf("���2�����������������������룺\n");
			return 0;
		}
	}
	else if (p1_c == 0)
	{
		// ���1��ʹ�ÿ���
		// ������2�Ŀ�������Ƿ�������ȷ
		if (Exists(p2_c))
		{
			// ������2�Ŀ�������
			if (players[p2 - 1].card[p2_c - 1] > 0)
			{
				return 1;
			}
			else
			{
				printf("%d�����û��%d�ſ��ƣ����������룡\n", p2, p2_c);
				return 0;
			}
		}
		else if (p2_c == 0)
		{
			// ���2��ʹ�ÿ���
			return 1;
		}
		else
		{
			printf("�����������������������룡\n");
			return 0;
		}
	}
	else
	{
		printf("�����������������������룡\n");
		return 0;
	}
}

int can_exc_Blood(Player *players, int p1, int p1_b, int p2, int p2_b)
{
	// ��֤���2��Ѫ��
	if (p2_b < players[p2 - 1].blood)
	{
		// ��֤���1��Ѫ��
		if (p1_b < players[p1 - 1].blood)
		{
			return 1;
		}
		else
		{
			printf("%d�����Ѫ�����㣡���������룺\n", p1);
			return 0;
		}
	}
	else
	{
		printf("%d�����Ѫ�����㣡���������룺\n", p2);
		return 0;
	}
}

#ifdef REFEREE

#endif // REFEREE


void output_player_UI(Player *players)
{
	int p;
	printf("________________\n");
	printf("������һ��������0\n");
	do
	{
		printf("������Ҫ�鿴�������ţ�");
		scanf("%d", &p);
		if (Exists(p))
		{
			output_player(players[p - 1]);
		}
		else if (p == 0)
		{
			break;
		}
		else
		{
			printf("������%d����ң����������룡\n", p);
		}
	} while (1);
	printf("________________\n");
	return;
}

void output_player(Player p)
{
	printf("Ѫ����%d\n", p.blood);
	printf("���ƣ�");
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		printf("%d ", i + 1);
	}
	printf("\n������");
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		printf("%d ", p.card[i]);
	}
	printf("\nӵ�еļ��ܣ�");
	for (int i = 0; i < NUM_SKILLS; i++)
	{
		if (p.skills[i])
		{
			switch (i)
			{
			case 0:printf("ӥ��"); break;
			case 1:printf("��Ѫ");  break;
			case 2:printf("����ͻ��"); break;
			case 3:printf("����"); break;
			case 4:printf("����"); break;
			case 5:printf("����"); break;
			case 6:printf("��������"); break;
			case 7:printf("��ͷȮ"); break;
			case 8:printf("������"); break;
			case 9:printf("��������"); break;
			default:printf("�����˴����ܣ�");
				break;
			}
			printf(" ");
		}
	}
	printf("\n");
}