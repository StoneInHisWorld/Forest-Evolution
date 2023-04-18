#include "declaration.h"

void free_stage_UI(Player *players, INT_DB db, int round)
{
	printf("________________\n");
	printf("第%d轮自由阶段，%d分钟计时开始，裁判可进行如下操作：\n", round, FREESTAGE_SPAN);
	printf("交换：jh\n");
	printf("查看某个玩家的血量、卡牌以及技能：ck\n");
	printf("结束：js\n");
	
	char cmd[3];
	do
	{
		printf("请输入命令：");
		scanf("%s", cmd);
		if (strcmp(cmd, "jh") == 0)
		{
			// 可以用血量或卡牌交换血量或者卡牌
			exchange_UI(players);
		}
		else if (strcmp(cmd, "ck") == 0)
		{
			// 输出某个玩家的血量以及剩余卡牌
			output_player_UI(players);
		}
		else if (strcmp(cmd, "js") == 0)
		{
			// 进入下一阶段
			break;
		}
		else
		{
			printf("输入的命令不正确，请重新输入！\n");
		}
		set_Paracitism(players, db);
	} while (1);
	return;
	printf("________________\n");
}

void exchange_UI(Player *players)
{
	printf("________________\n");
	printf("如返回上一级则输入：0\n");
	printf("请按照如下规则进行交换操作：\n");
	printf("玩家1序号 玩家1交换的血量 玩家1交换的卡牌 玩家2序号 玩家2交换的血量 玩家2交换的卡牌\n");
	printf("如玩家3用5号牌换玩家4的2号牌，则输入：3 0 5 4 0 2\n");
	printf("如玩家4用3滴血换玩家9的2号牌，则输入：4 3 0 9 0 2\n");
	do
	{
		int p1, p1_b, p1_c, p2, p2_b, p2_c;
		printf("请输入：");
		scanf("%d", &p1);
		if (0 == p1)
		{
			getchar();
			break;
		}
		else if (Exists(p1))
		{
			scanf("%d %d %d %d %d", &p1_b, &p1_c, &p2, &p2_b, &p2_c);
			// 检验玩家存在是否都存在
			if (Exists(p2))
			{
				exchange(players, p1, p1_c, p1_b, p2, p2_c, p2_b);
			}
			else
			{
				printf("玩家2不存在，请重新输入！\n");
			}
		}
		else
		{
			printf("玩家1不存在，请重新输入！\n");
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
			// 双方都使用了卡牌
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p1 - 1].card[p1_c - 1]--;
			players[p1 - 1].card[p2_c - 1]++;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			players[p2 - 1].card[p2_c - 1]--;
			players[p2 - 1].card[p1_c - 1]++;
			printf("%d号玩家使用%d号牌以及%d滴血交换了%d号玩家的%d号牌以及%d滴血。\n",
				p1, p1_c, p1_b, p2, p2_c, p2_b);
			return;
		}
		else if (p1_c == 0 && p2_c != 0)
		{
			// 玩家1不使用卡牌
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p1 - 1].card[p2_c - 1]++;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			players[p2 - 1].card[p2_c - 1]--;
			printf("%d号玩家使用%d滴血交换了%d号玩家的%d号牌以及%d滴血。\n",
				p1, p1_b, p2, p2_c, p2_b);
			return;
		}
		else if (p1_c != 0 && p2_c == 0)
		{
			// 玩家2不使用卡牌
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p1 - 1].card[p1_c - 1]--;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			players[p2 - 1].card[p1_c - 1]++;
			printf("%d号玩家使用%d号牌以及%d滴血交换了%d号玩家的%d滴血。\n",
				p1, p1_c, p1_b, p2, p2_b);
			return;
		}
		else
		{
			// 双方均不使用卡牌
			players[p1 - 1].blood -= p1_b;
			players[p1 - 1].blood += p2_b;
			players[p2 - 1].blood -= p2_b;
			players[p2 - 1].blood += p1_b;
			printf("%d号玩家使用%d滴血交换了%d号玩家的%d滴血。\n",
				p1, p1_b, p2, p2_b);
			return;
		}
	}
}

int can_exc_Card(Player *players, int p1, int p1_c, int p2, int p2_c)
{
	// 检查玩家1的卡牌输入序号是否正确
	if (Exists(p1_c))
	{
		// 检查玩家2的卡牌序号是否输入正确
		if (Exists(p2_c))
		{
			// 检查玩家1的卡牌余量
			if (players[p1 - 1].card[p1_c - 1] > 0)
			{
				// 检查玩家2的卡牌余量
				if (players[p2 - 1].card[p2_c - 1] > 0)
				{
					return 1;
				}
				else
				{
					printf("%d号玩家没有%d号卡牌！请重新输入！\n", p2, p2_c);
					return 0;
				}
			}
			else
			{
				printf("%d号玩家没有%d号卡牌！请重新输入！\n", p1, p1_c);
				return 0;
			}
		}
		else if (p2_c == 0)
		{
			// 玩家2不使用卡牌
			// 检查玩家1的卡牌余量
			if (players[p1 - 1].card[p1_c - 1] > 0)
			{
				return 1;
			}
			else
			{
				printf("%d号玩家没有%d号卡牌！请重新输入！\n", p1, p1_c);
				return 0;
			}
		}
		else
		{
			printf("玩家2卡牌序号输入错误，请重新输入：\n");
			return 0;
		}
	}
	else if (p1_c == 0)
	{
		// 玩家1不使用卡牌
		// 检查玩家2的卡牌序号是否输入正确
		if (Exists(p2_c))
		{
			// 检查玩家2的卡牌余量
			if (players[p2 - 1].card[p2_c - 1] > 0)
			{
				return 1;
			}
			else
			{
				printf("%d号玩家没有%d号卡牌！请重新输入！\n", p2, p2_c);
				return 0;
			}
		}
		else if (p2_c == 0)
		{
			// 玩家2不使用卡牌
			return 1;
		}
		else
		{
			printf("卡牌序号输入错误，请重新输入！\n");
			return 0;
		}
	}
	else
	{
		printf("卡牌序号输入错误，请重新输入！\n");
		return 0;
	}
}

int can_exc_Blood(Player *players, int p1, int p1_b, int p2, int p2_b)
{
	// 验证玩家2的血量
	if (p2_b < players[p2 - 1].blood)
	{
		// 验证玩家1的血量
		if (p1_b < players[p1 - 1].blood)
		{
			return 1;
		}
		else
		{
			printf("%d号玩家血量不足！请重新输入：\n", p1);
			return 0;
		}
	}
	else
	{
		printf("%d号玩家血量不足！请重新输入：\n", p2);
		return 0;
	}
}

#ifdef REFEREE

#endif // REFEREE


void output_player_UI(Player *players)
{
	int p;
	printf("________________\n");
	printf("返回上一级请输入0\n");
	do
	{
		printf("请输入要查看的玩家序号：");
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
			printf("不存在%d号玩家，请重新输入！\n", p);
		}
	} while (1);
	printf("________________\n");
	return;
}

void output_player(Player p)
{
	printf("血量：%d\n", p.blood);
	printf("卡牌：");
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		printf("%d ", i + 1);
	}
	printf("\n数量：");
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		printf("%d ", p.card[i]);
	}
	printf("\n拥有的技能：");
	for (int i = 0; i < NUM_SKILLS; i++)
	{
		if (p.skills[i])
		{
			switch (i)
			{
			case 0:printf("鹰眼"); break;
			case 1:printf("嗜血");  break;
			case 2:printf("基因突变"); break;
			case 3:printf("两栖"); break;
			case 4:printf("寄生"); break;
			case 5:printf("闪避"); break;
			case 6:printf("物种消亡"); break;
			case 7:printf("三头犬"); break;
			case 8:printf("替罪羊"); break;
			case 9:printf("狼王号召"); break;
			default:printf("出现了错误技能！");
				break;
			}
			printf(" ");
		}
	}
	printf("\n");
}