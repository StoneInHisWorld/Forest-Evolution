#include "declaration.h"

#define GENEMUT_EFFECT 3
#define CERBERUS_EFFECT 3
#define WOLFKING_EFFECT 3

//int i_wolf_king = NOTFOUND, i_wolf_cub1 = NOTFOUND, i_wolf_cub2 = NOTFOUND;
//int i_scapegoat = NOTFOUND;
//extern int i_host;
//extern int evasion_chance[DAMAGE_ROUND_4_SH + 1];
//extern int scapegoat_chance[DAMAGE_ROUND_4_SH + 1];

#ifdef REFEREE
int exert_EagleEye(Player *player)
{
	int i;
	for (i = 0; i < NUM_PLAYER; i++)
	{
		if (player[i].skills[EagleEye] == 1)
		{
			break;
		}
	}
	if (i == NUM_PLAYER)
	{
		return 0;
	}
	else
	{
		printf("请问%d号玩家是否要使用“鹰眼技能”：", i + 1);
		if (yes_or_no())
		{
			// 写一个公布身份的接口
			output_player_UI(player);
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("请裁判将该玩家的身份单独告知%d号玩家\n", i + 1);
			printf("%d号玩家发动了鹰眼技能！\n", i + 1);
			player[i].skills[EagleEye] = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int exert_Amphibious(Player *player, int i_predator,
	int i_prey, int *res)
{
	// 如果同花色则判定胜利
	if (1)
	{
		*res = VICTORY;
		return 1;
	}
	else
	{
		return 0;
	}
}

// 请在接入身份系统后再进行修改
int exert_Cerberus(Player *player, int i_predator,
	int damage)
{
	if (player[i_predator - 1].skills[Cerberus])
	{
		for (int i = 0; i < CERBERUS_EFFECT; i++)
		{
			int i_prey;
			printf("\n");
			printf("请选择第%d头的捕食对象以及捕食结果：",
				i + 1);
			scanf("%d", &i_prey);
			if (Exists(i_prey))
			{
				getchar();
				char res = getchar();
				prey(player, i_predator, i_prey,
					res, damage, USE_CARD);
			}
			else if (i_prey == 0)
			{
				continue;
			}
			else
			{
				printf("输入有误，请重新输入\n");
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
#endif // REFEREE

#ifdef USER
int exert_BloodThirsty(Player *players, int i_predator,
	int i_prey, int res, int *damage)
{
	if (res == VICTORY &&
		players[i_predator - 1].skills[BloodThirsty] == ACTIVE)
	{
		(*damage) += 2;
		printf("%d号玩家发动了嗜血技能！\n", i_predator);
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_GeneMutation(Player *player, INT_DB db, int i_buyer,	int *price)
{
	if (player->skills[GeneMutation])
	{
		if (*price - GENEMUT_EFFECT <= 1)
		{
			*price = 1;
		}
		else
		{
			*price -= GENEMUT_EFFECT;
		}
		printf("%d号玩家发动了基因突变技能！\n", i_buyer);
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Paracitism(Player *players, INT_DB db, int i_predator,
	int i_prey, int damage, int res)
{
	if (res == FAIL)
	{
		int i_temp = i_predator;
		i_predator = i_prey;
		i_prey = i_temp;
	}
	if (i_parasite == NOTFOUND || i_host == NOTFOUND)
	{
		return 0;
	}
	if (i_predator == i_host)
	{
		prey(players, i_parasite, i_prey, VICTORY,
			damage, WITHOUT_CARD);
		printf("%d号玩家发动了寄生技能！\n", i_parasite);
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Evasion(Player *players, INT_DB db, int *i_prey, int damage)
{
	// 若本玩家拥有闪避技能且闪避技能尚可用
	if (players[*i_prey - 1].skills[Evasion] 
		&& evasion_chance == ACTIVE)
	{
		printf("%d号玩家发动了闪避！", *i_prey);
		// 判断是否死亡
		while (is_dead(*i_prey))
		{
			if (*i_prey == NUM_PLAYER - 1)
			{
				*i_prey = 0;
			}
			else
			{
				(*i_prey)++;
			}
		}
		printf("被捕食对象更改为%d号玩家\n", *i_prey);
		evasion_chance = USED;
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Extinction(Player *players, int i_predator)
{
	if (players[i_predator - 1].skills[Extinction])
	{
		// 指定一种花色，向全场告知该花色和对应的玩家，
		// 同时他们会失去5点生命值。
		players[i_predator - 1].skills[Extinction] = USED;
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Cerberus(Player *players, INT_DB db, int i_predator,	int damage)
{
	if (players[i_predator - 1].skills[Cerberus])
	{
		for (int i = 0; i < CERBERUS_EFFECT; i++)
		{
			int i_prey;
			printf("\n");
			printf("请选择第%d头的捕食对象以及捕食结果：",
				i + 1);
			scanf("%d", &i_prey);
			if (Exists(i_prey))
			{
				getchar();
				char res = getchar();
				prey(players, i_predator, i_prey,
					res, damage, USE_CARD);
			}
			else if (i_prey == 0)
			{
				continue;
			}
			else
			{
				printf("输入有误，请重新输入\n");
			}
		}
		printf("%d号玩家发动了三头犬！", i_scapegoat);
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Scapegoat(Player *players, INT_DB db, int *i_prey, int damage)
{
	// 能成为替罪羊的玩家已出现且替罪羊技能尚可用
	if (i_scapegoat != NOTFOUND && scapegoat_chance == ALIVE)
	{
		printf("请问%d号玩家你要成为%d号玩家的替罪羊吗？\n",
			i_scapegoat + 1, *i_prey);
		if (yes_or_no())
		{
			*i_prey = i_scapegoat;
			printf("%d号玩家发动了替罪羊！", i_scapegoat);
			scapegoat_chance = USED;
			return 1;
		}
	}
	return 0;
}

int exert_CallForWolfKing(Player *players, INT_DB db, int i_predator,
	int i_prey, int damage)
{
	if (players[i_predator - 1].skills[CallForWolfKing])
	{
		char res;
		printf("\n");
		printf("请输入小狼1、2的捕食结果：");
		// 第一只小狼
		res = getchar();
		prey(players, i_wolf_cub1, i_prey,
			res, damage, WITHOUT_CARD);
		if (res == VICTORY)
		{
			prey(players, i_predator, i_wolf_cub1, VICTORY,
				WOLFKING_EFFECT, WITHOUT_CARD);
		}
		// 消除空格
		getchar();
		// 第二只小狼
		res = getchar();
		prey(players, i_wolf_cub2, i_prey,
			res, damage, WITHOUT_CARD);
		if (res == VICTORY)
		{
			prey(players, i_predator, i_wolf_cub2, VICTORY,
				WOLFKING_EFFECT, WITHOUT_CARD);
		}
		printf("%d号玩家发动了狼王召唤！", i_predator);
		return 1;
	}
	else
	{
		return 0;
	}
}
#endif // USER



