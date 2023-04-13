#define _CRT_SECURE_NO_WARNINGS
#define ERROR -1
#define NUM_PLAYER 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Suit
{
	SPADE = 'h', HEART = 'H', CLUB = 'm', JOKER = 'J'
}Suit;

typedef enum Letter
{
	K = 'k', Q = 'q', J = 'j', Joker = 'J'
}Letter;

typedef struct Player {
	Suit suit;
	Letter letter;
}Player;

void output_id(Player p);
void print_allIDs(Player *players);
void regular_round(Player *players, int damage);
void big_round(Player *players, int *damage);
void input_players(Player *players);
int vali_input(char suit, char letter);
int attack(Player p1, Player p2);
char comp_suit(Suit s1, Suit s2);
char comp_letter(Letter l1, Letter l2);

int main()
{
	int choice = -1;
	Player *players = (Player *)malloc(NUM_PLAYER * sizeof(Player));
	printf("输入数字选择开局模式：1.输入身份牌开局 2.随机生成身份开局\n");
	printf("你的选择（回车结束）：");
	while (choice != 1 && choice != 2)
	{
		scanf("%d", &choice);
		if (choice == 1)
		{
			// erase enter
			getchar();
			input_players(players);
		}
		else if (choice == 2)
		{
			printf("待完善\n");
			return 0;
		}
		else
		{
			printf("输入不正确，请重新输入：\n");
		}
	}
	print_allIDs(players);
	for (int damage = 2; damage <= 3; damage++)
	{
		regular_round(players, damage);
	}
	for (int damage = 4; damage <= 7; damage++)
	{
		big_round(players, &damage);
	}
	printf("游戏结束！");
	return 0;
}

void print_allIDs(Player *players)
{
	printf("本局全体玩家身份如下：\n");
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		printf("%d号玩家身份：", i + 1);
		output_id(players[i]);
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void output_id(Player p)
{
	switch (p.suit)
	{
	case SPADE:printf("黑桃");
		break;
	case HEART:printf("红桃");
		break;
	case CLUB:printf("梅花");
		break;
	case JOKER:printf("Joker\n");
		return;
	default:printf("错误身份！");
		break;
	}
	switch (p.letter)
	{
	case K:printf("K\n");
		break;
	case Q:printf("Q\n");
		break;
	case J:printf("J\n");
		break;
	default:printf("错误身份！");
		break;
	}
}

void regular_round(Player *players, int damage) 
{
	printf("第%d轮自由阶段，计时开始（按任意键结束）\n", damage - 1);
	getchar();
	srand((unsigned)time(NULL));
	printf("第%d轮捕食阶段，从玩家%d号开始，", damage - 1, rand() % 10 + 1);
	int p1, p2;
	printf("每次捕食伤害为%d点\n捕食操作格式如下：\n", damage);
	printf("“捕食玩家1序号 捕食玩家2序号”，输入11 11则进入下一阶段\n");
	printf("如1号捕食2号则输入：1 2\n");
	while (1)
	{
		printf("本次捕食：");
		scanf("%d %d", &p1, &p2);
		if (p1 > 0 && p1 < NUM_PLAYER + 1 && p2 > 0 && p2 < NUM_PLAYER + 1)
		{
			if (attack(players[p1 - 1], players[p2 - 1]))
			{
				printf(" 胜利\n");
			}
			else
			{
				printf(" 失败\n");
			}
		}
		else if (p1 == 11 && p2 == 11)
		{
			break;
		}
		else
		{
			printf("输入有误，请重新输入\n");
		}
	}
	getchar();
	printf("第%d轮进化阶段开始（按回车键结束）\n", damage - 1);
	getchar();
	return;
}

void big_round(Player *players, int *damage) 
{
	printf("第%d轮自由阶段，计时开始（按任意键结束）\n", (*damage / 2) + 1);
	getchar();
	srand((unsigned)time(NULL));
	printf("第%d轮捕食阶段上半场，从玩家%d号开始，", *damage / 2 + 1, rand() % 10 + 1);
	printf("每次捕食伤害为%d点\n捕食操作格式如下：\n", *damage);
	printf("“捕食玩家1序号 捕食玩家2序号”，输入11 11则进入下一阶段\n");
	printf("如1号捕食2号则输入：1 2\n");
	int p1, p2;
	while (1)
	{
		printf("本次捕食：");
		scanf("%d %d", &p1, &p2);
		if (p1 > 0 && p1 < NUM_PLAYER + 1 && p2 > 0 && p2 < NUM_PLAYER + 1)
		{
			if (attack(players[p1 - 1], players[p2 - 1]))
			{
				printf(" 胜利\n");
			}
			else
			{
				printf(" 失败\n");
			}
		}
		else if (p1 == 11 && p2 == 11)
		{
			break;
		}
		else
		{
			printf("输入有误，请重新输入\n");
		}
	}
	(*damage)++;
	printf("第%d轮捕食阶段下半场，从玩家%d号开始（按回车键结束），", *damage / 2 + 1, rand() % 10);
	printf("每次捕食伤害为%d点\n捕食操作格式如下：\n", *damage);
	printf("“捕食玩家1序号 捕食玩家2序号”，输入11 11则进入下一阶段\n");
	printf("如1号捕食2号则输入：1 2\n");
	while (1)
	{
		printf("本轮捕食：");
		scanf("%d %d", &p1, &p2);
		if (p1 > 0 && p1 < NUM_PLAYER + 1 && p2 > 0 && p2 < NUM_PLAYER + 1)
		{
			if (attack(players[p1 - 1], players[p2 - 1]))
			{
				printf(" 胜利\n");
			}
			else
			{
				printf(" 失败\n");
			}
		}
		else if (p1 == NUM_PLAYER + 1 && p2 == NUM_PLAYER + 1)
		{
			break;
		}
		else
		{
			printf("输入有误，请重新输入\n");
		}
	}
	if (*damage == 7)
	{
		return;
	}
	getchar();
	printf("第%d轮进化阶段开始（按回车键结束）\n", *damage / 2 + 1);
	getchar();
}

void input_players(Player *players)
{
	printf("输入花色与字母请用以下规则：\n");
	printf("黑桃：h，红桃：H，梅花：m，JOKER：J\n");
	printf("K：k，Q：q，J：j，JOKER：J\n");
	printf("例如：黑桃K则输入：h k\n");
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		printf("请输入%d号玩家的字母和花色（中间用空格隔开，回车结束）：", i + 1);
		char suit, letter;
		scanf("%c %c", &suit, &letter);
		if (vali_input(suit, letter))
		{
			players[i].suit = (Suit)suit;
			players[i].letter = (Letter)letter;
		}
		else
		{
			i--;
			printf("未按规则输入字母与花色\n");
			getchar();
			continue;
		}
		// erase enter
		getchar();
	}
}

int vali_input(char suit, char letter)
{
	if (letter == 'k' || letter == 'q' || letter == 'j')
	{
		if (suit == 'h' || suit == 'H' || suit == 'm')
		{
			return 1;
		}
	}
	else
	{
		if (letter == 'J' && suit == 'J')
		{
			return 1;
		}
	}
	return 0;
}

int attack(Player p1, Player p2)
{
	char res1 = comp_letter(p1.letter, p2.letter);
	if (res1 == '>')
	{
		return 1;
	}
	else if (res1 == '<')
	{
		return 0;
	}
	else if (res1 == '=')
	{
		char res2 = comp_suit(p1.suit, p2.suit);
		if (res2 == '>')
		{
			return 1;
		}
		else if (res2 == '<')
		{
			return 0;
		}
	}
	return ERROR;
}

char comp_suit(Suit s1, Suit s2)
{
	if (s1 == JOKER)
	{
		switch (s2)
		{
		case SPADE:return '>'; break;
		case HEART:return '>'; break;
		case CLUB:return '>'; break;
		default:break;
		}
	}
	else if (s1 == SPADE)
	{
		switch (s2)
		{
		case SPADE:return '=';break;
		case HEART:return '>';break;
		case CLUB:return '<';break;
		case JOKER:return '>';break;
		default:break;
		}
	}
	else if (s1 == HEART)
	{
		switch (s2)
		{
		case SPADE:return '<'; break;
		case HEART:return '='; break;
		case CLUB:return '>'; break;
		case JOKER:return '>'; break;
		default:break;
		}
	}
	else if (s1 == CLUB)
	{
		switch (s2)
		{
		case SPADE:return '>'; break;
		case HEART:return '<'; break;
		case CLUB:return '='; break;
		case JOKER:return '>'; break;
		default:break;
		}
	}
	return ERROR;
}

char comp_letter(Letter l1, Letter l2)
{
	if (l1 == Joker)
	{
		switch (l2)
		{
		case K: return '>';
			break;
		case Q: return '>';
			break;
		case J: return '>';
			break;
		default:
			break;
		}
	}
	else if (l1 == K)
	{
		switch (l2)
		{
		case K:return '=';
			break;
		case Q:return '>';
			break;
		case J:return '<';
			break;
		case Joker:return '>';
			break;
		default:
			break;
		}
	}
	else if (l1 == Q)
	{
		switch (l2)
		{
		case K:return '<';
			break;
		case Q:return '=';
			break;
		case J:return '>';
			break;
		case Joker:return '>';
			break;
		default:
			break;
		}
	}
	else if (l1 == J)
	{
		switch (l2)
		{
		case K:return '>';
			break;
		case Q:return '<';
			break;
		case J:return '=';
			break;
		case Joker:return '>';
			break;
		default:
			break;
		}
	}
	return ERROR;
}