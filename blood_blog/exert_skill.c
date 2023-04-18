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
		printf("����%d������Ƿ�Ҫʹ�á�ӥ�ۼ��ܡ���", i + 1);
		if (yes_or_no())
		{
			// дһ��������ݵĽӿ�
			output_player_UI(player);
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("����н�����ҵ���ݵ�����֪%d�����\n", i + 1);
			printf("%d����ҷ�����ӥ�ۼ��ܣ�\n", i + 1);
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
	// ���ͬ��ɫ���ж�ʤ��
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

// ���ڽ������ϵͳ���ٽ����޸�
int exert_Cerberus(Player *player, int i_predator,
	int damage)
{
	if (player[i_predator - 1].skills[Cerberus])
	{
		for (int i = 0; i < CERBERUS_EFFECT; i++)
		{
			int i_prey;
			printf("\n");
			printf("��ѡ���%dͷ�Ĳ�ʳ�����Լ���ʳ�����",
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
				printf("������������������\n");
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
		printf("%d����ҷ�������Ѫ���ܣ�\n", i_predator);
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
		printf("%d����ҷ����˻���ͻ�似�ܣ�\n", i_buyer);
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
		printf("%d����ҷ����˼������ܣ�\n", i_parasite);
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Evasion(Player *players, INT_DB db, int *i_prey, int damage)
{
	// �������ӵ�����ܼ��������ܼ����п���
	if (players[*i_prey - 1].skills[Evasion] 
		&& evasion_chance == ACTIVE)
	{
		printf("%d����ҷ��������ܣ�", *i_prey);
		// �ж��Ƿ�����
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
		printf("����ʳ�������Ϊ%d�����\n", *i_prey);
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
		// ָ��һ�ֻ�ɫ����ȫ����֪�û�ɫ�Ͷ�Ӧ����ң�
		// ͬʱ���ǻ�ʧȥ5������ֵ��
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
			printf("��ѡ���%dͷ�Ĳ�ʳ�����Լ���ʳ�����",
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
				printf("������������������\n");
			}
		}
		printf("%d����ҷ�������ͷȮ��", i_scapegoat);
		return 1;
	}
	else
	{
		return 0;
	}
}

int exert_Scapegoat(Player *players, INT_DB db, int *i_prey, int damage)
{
	// �ܳ�Ϊ�����������ѳ��������������п���
	if (i_scapegoat != NOTFOUND && scapegoat_chance == ALIVE)
	{
		printf("����%d�������Ҫ��Ϊ%d����ҵ���������\n",
			i_scapegoat + 1, *i_prey);
		if (yes_or_no())
		{
			*i_prey = i_scapegoat;
			printf("%d����ҷ�����������", i_scapegoat);
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
		printf("������С��1��2�Ĳ�ʳ�����");
		// ��һֻС��
		res = getchar();
		prey(players, i_wolf_cub1, i_prey,
			res, damage, WITHOUT_CARD);
		if (res == VICTORY)
		{
			prey(players, i_predator, i_wolf_cub1, VICTORY,
				WOLFKING_EFFECT, WITHOUT_CARD);
		}
		// �����ո�
		getchar();
		// �ڶ�ֻС��
		res = getchar();
		prey(players, i_wolf_cub2, i_prey,
			res, damage, WITHOUT_CARD);
		if (res == VICTORY)
		{
			prey(players, i_predator, i_wolf_cub2, VICTORY,
				WOLFKING_EFFECT, WITHOUT_CARD);
		}
		printf("%d����ҷ����������ٻ���", i_predator);
		return 1;
	}
	else
	{
		return 0;
	}
}
#endif // USER



