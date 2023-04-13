#include "declaration.h"

extern int dead_players[NUM_PLAYER]; // ���ʼ����ȫ0

#ifdef USER
void prey_stage_UI(Player *players, int basic_damage)
{
	int p1, p2;
	printf("ÿ�β�ʳ�˺�Ϊ%d��\n��ʳ������ʽ���£�\n", basic_damage);
	printf("����ʳ���1��� ��ʳ���2��� �ɹ���񡱣�����0 0�������һ�׶�\n");
	printf("��1�Ų�ʳ2�ųɹ������룺1 2 %c\n", VICTORY);
	printf("��3�Ų�ʳ4��ʧ�������룺1 2 %c\n", FAIL);
	while (1)
	{
		printf("\n");
		printf("���β�ʳ��");
		scanf("%d %d", &p1, &p2);
		int prey_damage = basic_damage;
		if (Exists(p1) && Exists(p2))
		{
			getchar();
			char res = getchar();
			exert_BloodThirsty(players, p1, p2, res, &prey_damage);
			prey(players, p1, p2, res, prey_damage, USE_CARD);
			
		}
		else if (p1 == 0 && p2 == 0)
		{
			break;
		}
		else
		{
			printf("������������������\n");
		}
	}
	getchar();
}

int prey(Player *players, int p1, int p2, char res, int damage,
	int consume_card)
{
	printf("ע�����޷���֪��ʳ���Ƿ񽻻������ƣ���˴˴������жϲ�ʳ���Ƿ����㹻�Ĳ�ʳ��\n");
	if (consume_card == USE_CARD)
	{
		players[p1 - 1].card[p2 - 1]--;
		printf("%d�����������%d�Ų�ʳ��һ�ţ�\n", p1, p2);
	}
	switch (res)
	{
	case VICTORY: // �ɹ���ʳ
		break;
	case FAIL: // ��ʳʧ��
		{	
			int temp = p2;
			p2 = p1;
			p1 = temp;
		}
		break;
	default:
		printf("��ʳ��������������������룡\n");
		return 0;
	}
	if (players[p2 - 1].blood <= damage)
	{
		// p2����
		deal_death(players, p1, p2, damage);
	}
	else
	{
		players[p2 - 1].blood -= damage;
		players[p1 - 1].blood += damage;
		printf("%d����һ����%d����ҵ�%d������ֵ��\n", p1, p2, damage);
	}
	return 1;
}

void deal_death(Player *players, int no_winner, int no_death, int damage)
{
	Player *winner = &players[no_winner - 1];
	Player *death = &players[no_death - 1];
	printf("��%d�����δ��������ֵ�����ʱ%d�����Ӧ����̭��\n", no_death, no_death);
	printf("��ѯ�ʲ���%d������Ƿ�����������������1����������0����", no_death);
	if (yes_or_no() == 1)
	{
		int card[NUM_PLAYER] = { 0 };
		// ��������ҵĿ��ƺ�����ֵȫ�����貶ʳ�����
		printf("����и�֪%d����ҵ�ʣ�࿨��(�Կո�Ϊ������س���β)", no_death);
		printf("����2��4���ƣ�1��3���������룺4 4 3\n");
		printf("�����룺");
		do
		{
			int no_card;
			scanf("%d", &no_card);
			if (Exists(no_card))
			{
				card[no_card - 1] ++;
			}
			else
			{
				printf("��������������\n");
				printf("�����룺");
			}
		} while (getchar() != '\n');
		printf("%d����һ�ɱ%d����ҵõ��ˣ�\n", no_winner, no_death);
		printf("���ƣ�");
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			printf("%d ", i + 1);
		}
		printf("\n������");
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			printf("%d ", card[i]);
			if (card[i] > 0)
			{
				winner->card[i] += card[i];
				death->card[i] -= card[i];
			}
		}
		printf("\n�Լ�%d������ֵ\n", death->blood);
		winner->blood += death->blood;
		death->blood -= death->blood;
		printf("%d�������������\n", no_death);
		dead_players[no_death - 1] = DEAD;
	}
	else
	{
		death->blood -= damage;
		winner->blood += damage;
		winner->card[no_death - 1] --;
		printf("�����޷���֪%d����ҵ�׼ȷ����ֵ����˰���%d�����δ����������\n", 
			no_death, no_death);
		printf("%d����һ����%d����ҵ�%d������ֵ��\n", no_winner, 
			no_death, damage);
	}
	return;
}
#endif // USER

#ifdef REFEREE
void prey_stage_UI(Player *players, int basic_damage)
{
	int p1, p2;
	printf("ÿ�β�ʳ�˺�Ϊ%d��\n��ʳ������ʽ���£�\n", basic_damage);
	printf("����ʳ���1��� ��ʳ���2��š�������0 0�������һ�׶�\n");
	printf("��1�Ų�ʳ2�ųɹ������룺1 2\n");
	while (1)
	{
		printf("���β�ʳ��");
		scanf("%d %d", &p1, &p2);
		if (p1 > 0 && p1 < NUM_PLAYER + 1 && p2 > 0 && p2 < NUM_PLAYER + 1)
		{
			getchar();
			char res =
				//int res = attack(players[p1 - 1], players[p2 - 1]);
				//if (res == 1)
				//{
				//	printf(" ʤ��\n");
				//}
				//else if (res == 0)
				//{
				//	printf(" ʧ��\n");
				//}
				//else
				//{
				//	printf("����\n");
				//}
		}
		else if (p1 == 0 && p2 == 0)
		{
			break;
		}
		else
		{
			printf("������������������\n");
		}
	}
	getchar();
}
#endif // REFEREE
