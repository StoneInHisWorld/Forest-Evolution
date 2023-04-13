#include "declaration.h"

extern int dead_players[NUM_PLAYER]; // 须初始化成全0

#ifdef USER
void prey_stage_UI(Player *players, int basic_damage)
{
	int p1, p2;
	printf("每次捕食伤害为%d点\n捕食操作格式如下：\n", basic_damage);
	printf("“捕食玩家1序号 捕食玩家2序号 成功与否”，输入0 0则进入下一阶段\n");
	printf("如1号捕食2号成功则输入：1 2 %c\n", VICTORY);
	printf("如3号捕食4号失败则输入：1 2 %c\n", FAIL);
	while (1)
	{
		printf("\n");
		printf("本次捕食：");
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
			printf("输入有误，请重新输入\n");
		}
	}
	getchar();
}

int prey(Player *players, int p1, int p2, char res, int damage,
	int consume_card)
{
	printf("注：因无法得知捕食者是否交换过卡牌，因此此处不会判断捕食者是否有足够的捕食卡\n");
	if (consume_card == USE_CARD)
	{
		players[p1 - 1].card[p2 - 1]--;
		printf("%d号玩家消耗了%d号捕食卡一张！\n", p1, p2);
	}
	switch (res)
	{
	case VICTORY: // 成功捕食
		break;
	case FAIL: // 捕食失败
		{	
			int temp = p2;
			p2 = p1;
			p1 = temp;
		}
		break;
	default:
		printf("捕食结果输入有误，请重新输入！\n");
		return 0;
	}
	if (players[p2 - 1].blood <= damage)
	{
		// p2死亡
		deal_death(players, p1, p2, damage);
	}
	else
	{
		players[p2 - 1].blood -= damage;
		players[p1 - 1].blood += damage;
		printf("%d号玩家获得了%d号玩家的%d点生命值！\n", p1, p2, damage);
	}
	return 1;
}

void deal_death(Player *players, int no_winner, int no_death, int damage)
{
	Player *winner = &players[no_winner - 1];
	Player *death = &players[no_death - 1];
	printf("若%d号玩家未交换生命值，则此时%d号玩家应被淘汰！\n", no_death, no_death);
	printf("请询问裁判%d号玩家是否已死亡（死亡输入1，否则输入0）：", no_death);
	if (yes_or_no() == 1)
	{
		int card[NUM_PLAYER] = { 0 };
		// 将死亡玩家的卡牌和生命值全部给予捕食者玩家
		printf("请裁判告知%d号玩家的剩余卡牌(以空格为间隔，回车结尾)", no_death);
		printf("例如2张4号牌，1张3号牌则输入：4 4 3\n");
		printf("请输入：");
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
				printf("卡牌序号输入错误！\n");
				printf("请输入：");
			}
		} while (getchar() != '\n');
		printf("%d号玩家击杀%d号玩家得到了：\n", no_winner, no_death);
		printf("卡牌：");
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			printf("%d ", i + 1);
		}
		printf("\n数量：");
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			printf("%d ", card[i]);
			if (card[i] > 0)
			{
				winner->card[i] += card[i];
				death->card[i] -= card[i];
			}
		}
		printf("\n以及%d点生命值\n", death->blood);
		winner->blood += death->blood;
		death->blood -= death->blood;
		printf("%d号玩家已死亡！\n", no_death);
		dead_players[no_death - 1] = DEAD;
	}
	else
	{
		death->blood -= damage;
		winner->blood += damage;
		winner->card[no_death - 1] --;
		printf("由于无法得知%d号玩家的准确生命值，因此按照%d号玩家未死亡计算结果\n", 
			no_death, no_death);
		printf("%d号玩家获得了%d号玩家的%d点生命值！\n", no_winner, 
			no_death, damage);
	}
	return;
}
#endif // USER

#ifdef REFEREE
void prey_stage_UI(Player *players, int basic_damage)
{
	int p1, p2;
	printf("每次捕食伤害为%d点\n捕食操作格式如下：\n", basic_damage);
	printf("“捕食玩家1序号 捕食玩家2序号”，输入0 0则进入下一阶段\n");
	printf("如1号捕食2号成功则输入：1 2\n");
	while (1)
	{
		printf("本次捕食：");
		scanf("%d %d", &p1, &p2);
		if (p1 > 0 && p1 < NUM_PLAYER + 1 && p2 > 0 && p2 < NUM_PLAYER + 1)
		{
			getchar();
			char res =
				//int res = attack(players[p1 - 1], players[p2 - 1]);
				//if (res == 1)
				//{
				//	printf(" 胜利\n");
				//}
				//else if (res == 0)
				//{
				//	printf(" 失败\n");
				//}
				//else
				//{
				//	printf("出错\n");
				//}
		}
		else if (p1 == 0 && p2 == 0)
		{
			break;
		}
		else
		{
			printf("输入有误，请重新输入\n");
		}
	}
	getchar();
}
#endif // REFEREE
