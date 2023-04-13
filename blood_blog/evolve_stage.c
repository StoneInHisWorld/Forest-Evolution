#include "declaration.h"

#ifdef USER
void evolve_stage_UI(Player *players, int round)
{
	printf("________________\n");
	printf("第%d轮进化阶段，可进行如下操作：\n", round);
	printf("拍卖下一张技能牌：pm\n");
	printf("查看某个玩家的血量、卡牌以及技能：ck\n");
	printf("结束：js\n");
	int num_skil = 0;
	SKIL *skil = NULL;
	// 技能初始化
	switch (round)
	{
	case 1:num_skil = 3;
		skil = (SKIL *)malloc(num_skil * sizeof(SKIL));
		skil[0] = EagleEye;
		skil[1] = BloodThirsty;
		skil[2] = GeneMutation;
		break;
	case 2:num_skil = 4;
		skil = (SKIL *)malloc(num_skil * sizeof(SKIL));
		skil[0] = Amphibious;
		skil[1] = Paracitism;
		skil[2] = Evasion;
		skil[3] = Extinction;
		break;
	case 3:num_skil = 3;
		skil = (SKIL *)malloc(num_skil * sizeof(SKIL));
		skil[0] = Cerberus;
		skil[1] = Scapegoat;
		skil[2] = CallForWolfKing;
		break;
	default:printf("第%d轮无进化阶段", round);
		return;
	}
	int i = 0;
	// 命令待机
	do
	{
		char cmd[3];
		printf("请输入命令：");
		scanf("%s", cmd);
		if (strcmp(cmd, "pm") == 0)
		{
			if (i >= num_skil)
			{
				printf("本轮技能已拍卖完毕！\n");
				continue;
			}
			// 拍卖技能卡
			auction_UI(players, skil[i]);
			i++;
		}
		else if (strcmp(cmd, "ck") == 0)
		{
			// 输出某个玩家的血量以及剩余卡牌
			output_player_UI(players);
		}
		else if (strcmp(cmd, "js") == 0)
		{
			// 进入下一阶段
			if (i < num_skil)
			{
				printf("本轮技能暂未拍卖完毕，请先拍卖全部技能再退出！\n");
				continue;
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("输入的命令不正确，请重新输入！\n");
		}
	} while (1);
}

void auction_UI(Player *players, SKIL s)
{
	printf("\n");
	printf("接下来要拍卖的技能为：");
	char *skil_str = skill_display(s);
	printf("起拍价1个生命值，请按照如下规则输入：\n");
	printf("买主 成交价\n");
	int buyer = -1, price = 0, flag = 0;
	do
	{
		scanf("%d %d", &buyer, &price);
		if (Exists(buyer))
		{
			if (price > 0)
			{
				flag = auction(&players[buyer - 1], s, buyer, &price);
			}
			else
			{
				printf("输入的成交价须大于0！请重新输入：");
			}
		}
		else
		{
			printf("输入的买家序号不存在！请重新输入：\n");
		}
	} while (!flag);
	printf("%d号玩家以%d滴血习得了%s技能！\n", buyer, price, skil_str);
}

char *skill_display(SKIL s)
{
	char *skil_str = NULL;
	switch (s)
	{
	case EagleEye:
		printf("鹰眼\n");
		printf("在任意轮数的任意阶段，可知晓一名玩家的身份。");
		printf("技能发动将会向全场告知技能已发动。只可使用一次。\n");
		skil_str = "鹰眼";
		break;
	case BloodThirsty:
		printf("嗜血\n");
		printf("在任意轮数的捕食阶段，主动发起捕食并胜利可额外获得2点生命，");
		printf("失败方多扣除两点生命。\n");
		skil_str = "嗜血";
		break;
	case GeneMutation:
		printf("基因突变\n");
		printf("在任意轮数的进化阶段，拍得的技能少支付3点生命值。");
		printf("至少支付1点生命值。\n");
		skil_str = "基因突变";
		break;
	case Amphibious:
		printf("两栖\n");
		printf("在任意轮数的捕食阶段，遭遇捕食或者主动捕食，遇到");
		printf("同字母不同花色的玩家，无视花色克制均视为胜利。\n");
		skil_str = "两栖";
		break;
	case Paracitism:
		printf("寄生\n");
		printf("在任意轮数的自由阶段，可选择除自己以外的玩家作为宿主。");
		printf("宿主在捕食阶段获得生命值，则寄生玩家可以获得同样数量的生命值。\n");
		printf("技能一旦发动，不可更改宿主。\n");
		skil_str = "寄生";
		break;
	case Evasion:
		printf("闪避\n");
		printf("在任意轮数的捕食阶段，被捕食则会将捕食对象改为下一顺位玩家。");
		printf("每个捕食阶段只可使用一次。\n");
		skil_str = "闪避";
		break;
	case Extinction:
		printf("物种消亡\n");
		printf("指定一种花色，向全场告知该花色和对应的玩家，");
		printf("同时他们会失去5点生命值。\n");
		printf("只可使用一次。\n");
		skil_str = "物种消亡";
		break;
	case Cerberus:
		printf("三头犬\n");
		printf("在任意轮数的捕食阶段，最多可选择3位捕食对象发起捕食。\n");
		printf("每次捕食仍需消耗对应玩家号码的捕食卡一张。\n");
		skil_str = "三头犬";
		break;
	case Scapegoat:
		printf("替罪羊\n");
		printf("在任意轮数的捕食阶段，其他玩家发起捕食选定捕食目标后，");
		printf("可代替原目标成为被捕食对象。\n");
		printf("替罪羊和闪避不能同时发动。\n");
		printf("每个捕食阶段只可使用一次，每次适用对象不可相同。\n");
		skil_str = "替罪羊";
		break;
	case CallForWolfKing:
		printf("狼王召唤\n");
		printf("成为狼王，可在自由阶段在其余玩家中选择两位作为小狼。\n");
		printf("捕食阶段狼王发动捕食，小狼也必须向被捕食方发动捕食。\n");
		printf("小狼捕食无需消耗捕食卡，胜利则将所获生命值其中3点分给狼王。\n");
		printf("小狼捕食失败则需自行支付生命值。\n");
		printf("狼王不能捕食小狼，小狼不可更改，不可拒绝成为小狼。\n");
		printf("小狼被迫捕食时不可发动三头犬技能\n");
		skil_str = "狼王召唤";
		break;
	default:printf("技能代号%d出错！\n", s);
		break;
	}
	return skil_str;
}

int auction(Player *player, SKIL skil, int buyer, int *price)
{
	exert_GeneMutation(player, buyer, price);
	if (player->blood - *price > 0 && player->blood - *price < 5)
	{
		printf("拍卖后%d号玩家的生命值将会非常低，还要继续吗？\n", buyer);
		printf("继续请输入1，换一位玩家输入0：");
		if (yes_or_no() == 0)
		{
			printf("请输入：");
			return 0;
		}
	}
	else if (player->blood - *price <= 0)
	{
		printf("警告%d号玩家，不可用大于等于自己生命值的价格拍卖！\n", buyer);
		printf("请输入：");
		return 0;
	}
	if (player->skills[skil] != 0)
	{
		printf("出错！该技能已被该玩家掌握！\n");
		printf("请输入：");
		return 0;
	}
	else
	{
		player->blood -= *price;
		player->skills[skil] = ACTIVE;
		return 1;
	}
}
#endif // USER