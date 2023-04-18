#include "declaration.h"

int main()
{
	Player players[NUM_PLAYER];
	INT_DB db = (INT_DB)malloc(sizeof(int) * end_of_db);
	init_game(players, db);
	// ��һ�ڶ���
	for (int damage = 2; damage <= 3; damage++)
	{
		printf("***************************\n");
		regular_round(players, db, damage);
	}
	// ����������
	for (int damage = 4; damage <= 7; damage++)
	{
		printf("***************************\n");
		big_round(players, db, &damage);
	}
	printf("��Ϸ������\n");
}

void init_game(Player *players, INT_DB db)
{
	// ��ҳ�ʼ��
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		dead_players[i] = ALIVE;
		players[i].blood = INI_BLOOD;
		for (int j = 0; j < NUM_PLAYER; j++)
		{
			players[i].card[j] = INI_CARD;
		}
		for (int j = 0; j < 10; j++)
		{
			players[i].skills[j] = USED;
		}
	}
	// ��Ϸ�������ݳ�ʼ��
	{
		i_wolf_king = NOTFOUND;
		i_wolf_cub1 = NOTFOUND;
		i_wolf_cub2 = NOTFOUND;
		i_scapegoat = NOTFOUND;
		i_host = NOTFOUND;
		i_parasite = NOTFOUND;
		//evasion_chance = ACTIVE;
		//scapegoat_chance = ACTIVE;
	}

	//// DEPRECATED������ʹ�ô�����ʼ��
	//for (int i = 0; i < DAMAGE_ROUND_4_SH + 1; i++)
	//{
	//	evasion_chance[i] = 1;
	//	scapegoat_chance[i] = 1;
	//}
}

void regular_round(Player *players, INT_DB db, int damage)
{
	free_stage_UI(players, db, damage - 1);
	preystage_refresh(db);
	srand((unsigned)time(NULL));
	printf("________________\n");
	printf("��%d�ֲ�ʳ�׶Σ������%d�ſ�ʼ��", damage - 1, rand() % 10 + 1);
	prey_stage_UI(players, db, damage);
	evolve_stage_UI(players, db, damage - 1);
	return;
}

int Exists(int no_player)
{
	if (no_player > 0 && no_player < NUM_PLAYER + 1)
	{
		return 1;
	}
	else 
	{
		printf("%d����Ҳ����ڣ�", no_player + 1);
		return 0;
	}
}

void big_round(Player *players, INT_DB db, int *damage)
{
	free_stage_UI(players, db, (*damage / 2) + 1);
	preystage_refresh(db);
	srand((unsigned)time(NULL));
	printf("________________\n");
	printf("��%d�ֲ�ʳ�׶��ϰ볡�������%d�ſ�ʼ��", *damage / 2 + 1, rand() % 10 + 1);
	prey_stage_UI(players, db, *damage);
	(*damage)++;
	preystage_refresh(db);
	printf("________________\n");
	printf("��%d�ֲ�ʳ�׶��°볡�������%d�ſ�ʼ��", *damage / 2 + 1, rand() % 10);
	prey_stage_UI(players, db, *damage);
	if (*damage == 7)
	{
		return;
	}
	evolve_stage_UI(players, db, *damage / 2 + 1);
}

int yes_or_no() 
{
	int choice = -1;
	printf("��������1����������0��");
	while (choice != 1 && choice != 0)
	{
		scanf("%d", &choice);
		if (choice != 1 && choice != 0)
		{
			printf("�����������������룺");
		}
	}
	return choice;
}

int is_dead(int no_player)
{
	return dead_players[no_player - 1] == DEAD ? 1 : 0;
}

void preystage_refresh(INT_DB db)
{
	scapegoat_chance = ACTIVE;
	evasion_chance = ACTIVE;
}
