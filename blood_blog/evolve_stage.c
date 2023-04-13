#include "declaration.h"

#ifdef USER
void evolve_stage_UI(Player *players, int round)
{
	printf("________________\n");
	printf("��%d�ֽ����׶Σ��ɽ������²�����\n", round);
	printf("������һ�ż����ƣ�pm\n");
	printf("�鿴ĳ����ҵ�Ѫ���������Լ����ܣ�ck\n");
	printf("������js\n");
	int num_skil = 0;
	SKIL *skil = NULL;
	// ���ܳ�ʼ��
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
	default:printf("��%d���޽����׶�", round);
		return;
	}
	int i = 0;
	// �������
	do
	{
		char cmd[3];
		printf("���������");
		scanf("%s", cmd);
		if (strcmp(cmd, "pm") == 0)
		{
			if (i >= num_skil)
			{
				printf("���ּ�����������ϣ�\n");
				continue;
			}
			// �������ܿ�
			auction_UI(players, skil[i]);
			i++;
		}
		else if (strcmp(cmd, "ck") == 0)
		{
			// ���ĳ����ҵ�Ѫ���Լ�ʣ�࿨��
			output_player_UI(players);
		}
		else if (strcmp(cmd, "js") == 0)
		{
			// ������һ�׶�
			if (i < num_skil)
			{
				printf("���ּ�����δ������ϣ���������ȫ���������˳���\n");
				continue;
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("����������ȷ�����������룡\n");
		}
	} while (1);
}

void auction_UI(Player *players, SKIL s)
{
	printf("\n");
	printf("������Ҫ�����ļ���Ϊ��");
	char *skil_str = skill_display(s);
	printf("���ļ�1������ֵ���밴�����¹������룺\n");
	printf("���� �ɽ���\n");
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
				printf("����ĳɽ��������0�����������룺");
			}
		}
		else
		{
			printf("����������Ų����ڣ����������룺\n");
		}
	} while (!flag);
	printf("%d�������%d��Ѫϰ����%s���ܣ�\n", buyer, price, skil_str);
}

char *skill_display(SKIL s)
{
	char *skil_str = NULL;
	switch (s)
	{
	case EagleEye:
		printf("ӥ��\n");
		printf("����������������׶Σ���֪��һ����ҵ���ݡ�");
		printf("���ܷ���������ȫ����֪�����ѷ�����ֻ��ʹ��һ�Ρ�\n");
		skil_str = "ӥ��";
		break;
	case BloodThirsty:
		printf("��Ѫ\n");
		printf("�����������Ĳ�ʳ�׶Σ���������ʳ��ʤ���ɶ�����2��������");
		printf("ʧ�ܷ���۳�����������\n");
		skil_str = "��Ѫ";
		break;
	case GeneMutation:
		printf("����ͻ��\n");
		printf("�����������Ľ����׶Σ��ĵõļ�����֧��3������ֵ��");
		printf("����֧��1������ֵ��\n");
		skil_str = "����ͻ��";
		break;
	case Amphibious:
		printf("����\n");
		printf("�����������Ĳ�ʳ�׶Σ�������ʳ����������ʳ������");
		printf("ͬ��ĸ��ͬ��ɫ����ң����ӻ�ɫ���ƾ���Ϊʤ����\n");
		skil_str = "����";
		break;
	case Paracitism:
		printf("����\n");
		printf("���������������ɽ׶Σ���ѡ����Լ�����������Ϊ������");
		printf("�����ڲ�ʳ�׶λ������ֵ���������ҿ��Ի��ͬ������������ֵ��\n");
		printf("����һ�����������ɸ���������\n");
		skil_str = "����";
		break;
	case Evasion:
		printf("����\n");
		printf("�����������Ĳ�ʳ�׶Σ�����ʳ��Ὣ��ʳ�����Ϊ��һ˳λ��ҡ�");
		printf("ÿ����ʳ�׶�ֻ��ʹ��һ�Ρ�\n");
		skil_str = "����";
		break;
	case Extinction:
		printf("��������\n");
		printf("ָ��һ�ֻ�ɫ����ȫ����֪�û�ɫ�Ͷ�Ӧ����ң�");
		printf("ͬʱ���ǻ�ʧȥ5������ֵ��\n");
		printf("ֻ��ʹ��һ�Ρ�\n");
		skil_str = "��������";
		break;
	case Cerberus:
		printf("��ͷȮ\n");
		printf("�����������Ĳ�ʳ�׶Σ�����ѡ��3λ��ʳ������ʳ��\n");
		printf("ÿ�β�ʳ�������Ķ�Ӧ��Һ���Ĳ�ʳ��һ�š�\n");
		skil_str = "��ͷȮ";
		break;
	case Scapegoat:
		printf("������\n");
		printf("�����������Ĳ�ʳ�׶Σ�������ҷ���ʳѡ����ʳĿ���");
		printf("�ɴ���ԭĿ���Ϊ����ʳ����\n");
		printf("����������ܲ���ͬʱ������\n");
		printf("ÿ����ʳ�׶�ֻ��ʹ��һ�Σ�ÿ�����ö��󲻿���ͬ��\n");
		skil_str = "������";
		break;
	case CallForWolfKing:
		printf("�����ٻ�\n");
		printf("��Ϊ�������������ɽ׶������������ѡ����λ��ΪС�ǡ�\n");
		printf("��ʳ�׶�����������ʳ��С��Ҳ�����򱻲�ʳ��������ʳ��\n");
		printf("С�ǲ�ʳ�������Ĳ�ʳ����ʤ������������ֵ����3��ָ�������\n");
		printf("С�ǲ�ʳʧ����������֧������ֵ��\n");
		printf("�������ܲ�ʳС�ǣ�С�ǲ��ɸ��ģ����ɾܾ���ΪС�ǡ�\n");
		printf("С�Ǳ��Ȳ�ʳʱ���ɷ�����ͷȮ����\n");
		skil_str = "�����ٻ�";
		break;
	default:printf("���ܴ���%d����\n", s);
		break;
	}
	return skil_str;
}

int auction(Player *player, SKIL skil, int buyer, int *price)
{
	exert_GeneMutation(player, buyer, price);
	if (player->blood - *price > 0 && player->blood - *price < 5)
	{
		printf("������%d����ҵ�����ֵ����ǳ��ͣ���Ҫ������\n", buyer);
		printf("����������1����һλ�������0��");
		if (yes_or_no() == 0)
		{
			printf("�����룺");
			return 0;
		}
	}
	else if (player->blood - *price <= 0)
	{
		printf("����%d����ң������ô��ڵ����Լ�����ֵ�ļ۸�������\n", buyer);
		printf("�����룺");
		return 0;
	}
	if (player->skills[skil] != 0)
	{
		printf("�����ü����ѱ���������գ�\n");
		printf("�����룺");
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