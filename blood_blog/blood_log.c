#include "declaration.h"

//extern int evasion_chance[DAMAGE_ROUND_4_SH + 1];
//extern int scapegoat_chance[DAMAGE_ROUND_4_SH + 1];
//extern int dead_players[NUM_PLAYER];

int main()
{
	Player players[NUM_PLAYER];
	//Player *players = (Player *)malloc(NUM_PLAYER * sizeof(Player));
	// init_game(players);
	init_game(players);
	// 第一第二轮
	for (int damage = 2; damage <= 3; damage++)
	{
		printf("***************************\n");
		regular_round(players, damage);
	}
	// 第三第四轮
	for (int damage = 4; damage <= 7; damage++)
	{
		printf("***************************\n");
		big_round(players, &damage);
	}
	printf("游戏结束！\n");
}

void init_game(Player *players)
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
	// 技能使用次数初始化
	for (int i = 0; i < DAMAGE_ROUND_4_SH + 1; i++)
	{
		evasion_chance[i] = 1;
		scapegoat_chance[i] = 1;
	}
}

void regular_round(Player *players, int damage)
{
	free_stage_UI(players, damage - 1);
	srand((unsigned)time(NULL));
	printf("________________\n");
	printf("第%d轮捕食阶段，从玩家%d号开始，", damage - 1, rand() % 10 + 1);
	prey_stage_UI(players, damage);
	evolve_stage_UI(players, damage - 1);
	return;
}

int Exists(int no_player)
{
	if (no_player > 0 && no_player < NUM_PLAYER + 1)
	{
		return 1;
	}
	else return 0;
}

void big_round(Player *players, int *damage)
{
	free_stage_UI(players, (*damage / 2) + 1);
	srand((unsigned)time(NULL));
	printf("________________\n");
	printf("第%d轮捕食阶段上半场，从玩家%d号开始，", *damage / 2 + 1, rand() % 10 + 1);
	prey_stage_UI(players, *damage);
	(*damage)++;
	printf("________________\n");
	printf("第%d轮捕食阶段下半场，从玩家%d号开始，", *damage / 2 + 1, rand() % 10);
	prey_stage_UI(players, *damage);
	if (*damage == 7)
	{
		return;
	}
	evolve_stage_UI(players, *damage / 2 + 1);
}

int yes_or_no() 
{
	int choice = -1;
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
