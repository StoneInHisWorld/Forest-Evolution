#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define USER


// 游戏初始化常量
#define INI_BLOOD 20
#define INI_CARD 1
#define NUM_PLAYER 10
#define NUM_SKILLS 10
#define ALIVE 1 // 生存
#define DEAD 0 // 死亡

// 自由阶段的时间
#define FREESTAGE_SPAN 15

// 捕食阶段的参数
#define USE_CARD 1
#define WITHOUT_CARD 0
// 捕食成功与否标志
#define FAIL 's'
#define VICTORY 'c'
// 捕食阶段的伤害
#define DAMAGE_ROUND_1 3
#define DAMAGE_ROUND_2 4
#define DAMAGE_ROUND_3_FH 5
#define DAMAGE_ROUND_3_SH 6
#define DAMAGE_ROUND_4_FH 7
#define DAMAGE_ROUND_4_SH 8

// 技能参数
#define ACTIVE 1 // 生效
#define USED 0 // 作废
#define NOTFOUND -1

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// 玩家技能：
// 一轮
// 0、鹰眼EagleEye
//		在任意轮数的任意阶段，可知晓一名玩家的身份。
//		技能发动将会向全场告知技能已发动。只可使用一次。
// 1、嗜血BloodThirsty
// 2、基因突变Gene Mutation
// 二轮
// 3、两栖Amphibious
// 4、寄生Paracitism
// 5、闪避Evasion
// 6、物种消亡Extinction
// 三轮
// 7、三头犬Cerberus
// 8、替罪羊Scapegoat
// 9、狼王号召CallForWolfKing

#ifdef USER
typedef enum Skill {
	EagleEye = 0, BloodThirsty, GeneMutation,
	Amphibious, Paracitism, Evasion, Extinction,
	Cerberus, Scapegoat, CallForWolfKing
}SKIL;

typedef struct Player
{
	int blood;
	// 存储捕食卡数量
	int card[NUM_PLAYER];
	// 1表示拥有该技能，0表示无该技能
	int skills[NUM_SKILLS];
}Player;

// 整型数据获取方式
typedef enum I_INTDB {
	// 狼王下标
	i_wolf_king, 
	// 小狼1序号下标
	i_wolf_cub1, 
	// 小狼2序号下标
	i_wolf_cub2, 
	// 替罪羊序号下标
	i_scapegoat,
	// 寄生宿主序号下标
	i_host, 
	// 寄生生物序号下标
	i_parasite,
	// 闪避是否使用数据下标
	use_evasion,
	// 替罪羊是否使用数据下标
	use_scapegoat,
	// 数据库终止符
	end_of_db
}I_INTDB;

typedef int * INT_DB;
#define i_parasite db[i_parasite]
#define i_host db[i_host]
#define i_scapegoat db[i_scapegoat]
#define i_wolf_cub1 db[i_wolf_cub1]
#define i_wolf_cub2 db[i_wolf_cub2]
#define i_wolf_king db[i_wolf_king]
#define scapegoat_chance db[use_scapegoat]
#define evasion_chance db[use_evasion]
int dead_players[NUM_PLAYER]; // 须初始化成全ALIVE
//// 技能使用限制数组。将其初始化为全1
//int evasion_chance[DAMAGE_ROUND_4_SH + 1];
//int scapegoat_chance[DAMAGE_ROUND_4_SH + 1];

// 主流程
void init_game(Player *players, INT_DB db);
void regular_round(Player *players, INT_DB db, int damage);
void big_round(Player *players, INT_DB db, int *damage);

/*
功能函数
*/
// 判断该序号的玩家是否存在
int Exists(int no_player);
// “是否”回答函数，返回用户的回答结果，1表示是，0表示否
int yes_or_no();
// 判断玩家是否已经死亡
int is_dead(int no_player);
// 刷新捕食阶段技能使用次数限制
void preystage_refresh(INT_DB db);

// 自由阶段
void free_stage_UI(Player *players, INT_DB db, int round);
void exchange_UI(Player *players);
void exchange(Player *players, int p1, int p1_c, int p1_b, int p2, int p2_c, int p2_b);
int can_exc_Card(Player *players, int p1, int p1_c, int p2, int p2_c);
int can_exc_Blood(Player *players, int p1, int p1_b, int p2, int p2_b);
void output_player_UI(Player *players);
void output_player(Player p);


// 捕食阶段
void prey_stage_UI(Player *players, INT_DB db, int damage);
void deal_death(Player *players, int no_winner, int no_death, int damage);
int prey(Player *players, int p1, int p2, char res, int damage,
	int consume_card);


// 进化阶段
void evolve_stage(int round);
void evolve_stage_UI(Player *players, INT_DB db, int round);
void auction_UI(Player *players, INT_DB db, SKIL s);
char *skill_display(SKIL s);
int auction(Player *player, INT_DB db, SKIL skil, int buyer, int *price);

/******
技能相关
******/
//// 寄生宿主序号
//int i_host = NOTFOUND;
//// 寄生生物序号
//int i_parasite = NOTFOUND;
// 实施嗜血技能，增加捕食的伤害
int exert_BloodThirsty(Player *players, int i_predator,
	int i_prey, int res, int *damage); // completed
// 实施基因突变技能，减免购买技能卡所需血量
int exert_GeneMutation(Player *players, INT_DB db, int i_buyer,
	int *price); // completed
// 实施寄生技能，寄生生物获得宿主的血量
int exert_Paracitism(Player *players, INT_DB db, int i_predator,
	int i_prey, int damage, int res); // edited
// 实施闪避技能，躲避捕食
int exert_Evasion(Player *players, INT_DB db, int *i_prey,
	int damage); // checked
int exert_Extinction(Player *players, int i_predator);
int exert_Cerberus(Player *players, INT_DB db, int i_predator,
	int damage);
int exert_Scapegoat(Player *players, INT_DB db, int *i_prey,
	int damage); // checked
int exert_CallForWolfKing(Player *players, INT_DB db, int i_predator,
	int i_prey, int damage);
// 设置寄生技能宿主
int set_Paracitism(Player *players, INT_DB db); // checked


#endif // USER

#ifdef REFEREE

#endif // REFEREE
