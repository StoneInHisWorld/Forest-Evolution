#include "declaration.h"

int main()
{
	Player players[NUM_PLAYER];
	INT_DB db = (INT_DB)malloc(sizeof(int) * end_of_db);
	init_game(players, db);
	// 第一第二轮
	for (int damage = 2; damage <= 3; damage++)
	{
		printf("***************************\n");
		regular_round(players, db, damage);
	}
	// 第三第四轮
	for (int damage = 4; damage <= 7; damage++)
	{
		printf("***************************\n");
		big_round(players, db, &damage);
	}
	printf("游戏结束！\n");
}

void init_game(Player *players, INT_DB db)
{
	// 玩家初始化
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
	// 游戏其他数据初始化
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

	//// DEPRECATED：技能使用次数初始化
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
	printf("第%d轮捕食阶段，从玩家%d号开始，", damage - 1, rand() % 10 + 1);
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
		printf("%d号玩家不存在！", no_player + 1);
		return 0;
	}
}

void big_round(Player *players, INT_DB db, int *damage)
{
	free_stage_UI(players, db, (*damage / 2) + 1);
	preystage_refresh(db);
	srand((unsigned)time(NULL));
	printf("________________\n");
	printf("第%d轮捕食阶段上半场，从玩家%d号开始，", *damage / 2 + 1, rand() % 10 + 1);
	prey_stage_UI(players, db, *damage);
	(*damage)++;
	preystage_refresh(db);
	printf("________________\n");
	printf("第%d轮捕食阶段下半场，从玩家%d号开始，", *damage / 2 + 1, rand() % 10);
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
	printf("是则输入1，否则输入0：");
	while (choice != 1 && choice != 0)
	{
		scanf("%d", &choice);
		if (choice != 1 && choice != 0)
		{
			printf("输入有误，请重新输入：");
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
