#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
using namespace std;

#define HeroNum 15

void Str2int(int &int_t, const string &string_t); //string转int函数
void StrSplite(string str[], char buffer[], char c); //字符串分割函数，str存储分割后的string数组，buffer为待分割char数组，c为分割符
void Loading();
bool Login();
void Signup();
//void PlayerRank();
//void HeroRank();
void Signin();
void StartGame();

string Heros[HeroNum];
int Skill[HeroNum][3];
string HeroAllRounds[HeroNum];
string HeroWinRounds[HeroNum];
string AllUsers[100];
string AllPass[100];
string MyUser;
string MyPass;

int main()
{
	int Choice;
	Loading();
	do
	{
		system("cls");
		cout << "\t\t欢迎来到王者农药" << endl;
		cout << "\t\t 1、登录" << endl;
		cout << "\t\t 2、注册" << endl;
		cout << "\t\t 3、玩家排行榜" << endl;
		cout << "\t\t 4、英雄胜率榜" << endl;
		cout << "\t\t 0、退出" << endl;
		cin >> Choice;
		switch (Choice)
		{
		case 1:Signin(); break;
		case 2:Signup(); break;
//		case 3:PlayerRank(); break;
//		case 4:HeroRank(); break;
		default:break;
		}
	} while (Choice != 0);
	cout << "ByeBye!" << endl;	
	return 0;
}

void Str2int(int &int_t, const string &string_t)
{
	stringstream stream(string_t);
	stream >> int_t;
}

void StrSplite(string str[], char buffer[], char c)
{
	int i = 0, j = 0;
	char *s = buffer;
	while (*(s + i) != NULL)
	{
		if (*(s + i) == '|')
		{
			*(s + i) = '\0';
			str[j] = s;
			j++;
			s = s + i + 1;
			i = 0;
		}
		else
			i++;
	}
}

void Loading()
{
	char Buffer[101];
	int index = 0;
	ifstream HandS("HeroAndSkill.txt");
	ifstream UandP("UserAndPass.txt");
	if (!HandS.is_open())
	{
		cout << "文件HeroAndSkill打开出错！" << endl;
		exit(1);
	}
	if (!UandP.is_open())
	{
		cout << "文件UserAndPass打开出错！" << endl;
		exit(1);
	}
	while (!HandS.eof())
	{
		string str[4];
		HandS.getline(Buffer, 100);
		StrSplite(str, Buffer, '|');
		Heros[index] = str[0];
		Str2int(Skill[index][0], str[1]);
		Str2int(Skill[index][1], str[2]);
		Str2int(Skill[index][2], str[3]);
		index++;
	}
	HandS.close();
	index = 0;
	while (!UandP.eof())
	{
		string str[2];
		UandP.getline(Buffer, 100);
		StrSplite(str, Buffer, '|');
		AllUsers[index] = str[0];
		AllPass[index] = str[1];
		index++;
	}
	UandP.close();
}

bool Login()
{
	cout << "请先登录:" << endl;
	cout << "Username:";
	cin >> MyUser;
	cout << "Password:";
	cin >> MyPass;
	char Buffer[101];
	bool flag = false;
	ifstream File("UserAndPass.txt");
	if (!File.is_open())
	{
		cout << "文件打开出错" << endl;
		exit(1);
	}
	while (!File.eof())
	{
		int i = 0, j = 0;
		string str[2];
		File.getline(Buffer, 100);
		char *s = Buffer;
		while (*(s + i) != NULL)
		{
			if (*(s + i) == '|')
			{
				*(s + i) = '\0';
				str[j] = s;
				j++;
				s = s + i + 1;
				i = 0;
			}
			else
				i++;
		}
		if (MyUser == str[0] && MyPass == str[1])
		{
			flag = true;
			break;
		}
	}
	File.close();
	return flag;
}

void Signup()
{
	string NewUser, NewPass;
	bool flag;
	do
	{
		flag = true;
		int i = 0;
		cout << "请输入想要注册的用户名：" << endl;
		cout << "NewUsername:";
		cin >> NewUser;
		cout << "NewPassword:";
		cin >> NewPass;
		while (AllUsers[i] != "")
		{
			if (NewUser == AllUsers[i])
			{
				flag = false;
				cout << "系统已存在该用户名，请重新输入！" << endl;
				break;
			}
			i++;
		}
		if (flag)
		{
			ofstream UandP("UserAndPass.txt",ios::out|ios::app);
			if (!UandP.is_open())
			{
				cout << "文件UserAndPass打开出错！" << endl;
				exit(1);
			}
			UandP << "\n" << NewUser << "|" << NewPass << "|";
			UandP.close();
			AllUsers[i] = NewUser;
			AllPass[i] = NewPass;
		}
	} while (!flag);
	cout << "恭喜你注册成功！" << endl;
	cout << "按回车键返回主界面" << endl;
	getchar();
	getchar();
}

void Signin()
{
	bool IsLogin = false;
	while (!(IsLogin = Login()))
		cout << "密码错误或账户不存在，请重新登录" << endl;
	system("cls");
	cout << "\t\t 欢迎" << MyUser << "登录游戏！" << endl;
	StartGame();
	cout << Heros[0] << "+" << Skill[0][0] << "+" << Skill[0][1] << "+" << Skill[0][2] << endl;
}

void StartGame()
{
	int HeroChoice;    //选择英雄界面所选择序号
	int MyChoice[3];    //分别对应己方所选择的三个英雄（序号）
	int YouChoice[3];   //分别对应对方所选择的的三个英雄（序号）

	time_t t = time(0);
	char tmp[32] = { NULL };
	strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S.txt", localtime(&t));
	char Fold[] = { "Fighting/" };
	ofstream Fighting(strcat(Fold, tmp));
	if (!Fighting.is_open())
	{
		cout << "文件创建失败！" << endl;
		exit(1);
	}

	srand((unsigned)time(NULL));
	cout << "英雄列表：" << endl;
	for (int i = 0; i < HeroNum; i++)
		cout << i + 1 << "、" << Heros[i] << "(" << Skill[i][0] << "," << Skill[i][1] << "," << Skill[i][2] << ")" << endl;
	do
	{
		cout << "请选择第一个英雄（通过序号选择，下同）：";
		cin >> HeroChoice;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "英雄列表内找不到所选序号，请重新输入！" << endl;
	} while (HeroChoice > HeroNum || HeroChoice <= 0);
	cout << "你选择的第一个英雄是:" << Heros[HeroChoice - 1] << endl;
	MyChoice[0] = HeroChoice;
	do
	{
		cout << "请选择第二个英雄：";
		cin >> HeroChoice;
		if (HeroChoice == MyChoice[0])
			cout << "你所选择的第二个英雄与第一个重复，请重新输入！" << endl;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "英雄列表内找不到所选序号，请重新输入！" << endl;
	} while (HeroChoice == MyChoice[0] || (HeroChoice > HeroNum || HeroChoice <= 0));
	cout << "你选择的第二个英雄是:" << Heros[HeroChoice - 1] << endl;
	MyChoice[1] = HeroChoice;
	do
	{
		cout << "请选择第三个英雄：";
		cin >> HeroChoice;
		if (HeroChoice == MyChoice[0])
			cout << "你所选择的第三个英雄与第一个重复，请重新输入！" << endl;
		if (HeroChoice == MyChoice[1])
			cout << "你所选择的第三个英雄与第二个重复，请重新输入！" << endl;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "英雄列表内找不到所选序号，请重新输入！" << endl;
	} while ((HeroChoice == MyChoice[0] || HeroChoice == MyChoice[1]) || (HeroChoice > HeroNum || HeroChoice <= 0));
	cout << "你选择的第三个英雄是:" << Heros[HeroChoice - 1] << endl;
	MyChoice[2] = HeroChoice;
	MyChoice[0]--;
	MyChoice[1]--;
	MyChoice[2]--;
	/*己方所选择的三个英雄的技能数*/
	int MyHero[3][3] = {
		Skill[MyChoice[0]][0],Skill[MyChoice[0]][1], Skill[MyChoice[0]][2],
		Skill[MyChoice[1]][0],Skill[MyChoice[1]][1], Skill[MyChoice[1]][2],
		Skill[MyChoice[2]][0],Skill[MyChoice[2]][1], Skill[MyChoice[2]][2] };
	cout << "---------------------------" << endl;
	cout << "你所选择的三个英雄分别是：" << endl;
	cout << Heros[MyChoice[0]] << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	cout << Heros[MyChoice[1]] << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	cout << Heros[MyChoice[2]] << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	Fighting << "你所选择的三个英雄分别是：" << endl;
	Fighting << Heros[MyChoice[0]] << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	Fighting << Heros[MyChoice[1]] << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	Fighting << Heros[MyChoice[2]] << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	YouChoice[0] = rand() % HeroNum;
	do
	{
		YouChoice[1] = rand() % HeroNum;
	} while (YouChoice[1] == YouChoice[0]);
	do
	{
		YouChoice[2] = rand() % HeroNum;
	} while (YouChoice[2] == YouChoice[0] || YouChoice[2] == YouChoice[1]);
	/*对方所选择的三个英雄的技能数*/
	int YouHero[3][3] = { 
		Skill[YouChoice[0]][0],Skill[YouChoice[0]][1], Skill[YouChoice[0]][2],
		Skill[YouChoice[1]][0],Skill[YouChoice[1]][1], Skill[YouChoice[1]][2],
		Skill[YouChoice[2]][0],Skill[YouChoice[2]][1], Skill[YouChoice[2]][2] };
	cout << "---------------------------" << endl;
	cout << "对方选择的三个英雄分别是：" << endl;
	cout << Heros[YouChoice[0]] << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	cout << Heros[YouChoice[1]] << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	cout << Heros[YouChoice[2]] << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	cout << "---------------------------" << endl;
	Fighting << "---------------------------" << endl;
	Fighting << "对方选择的三个英雄分别是：" << endl;
	Fighting << Heros[YouChoice[0]] << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	Fighting << Heros[YouChoice[1]] << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	Fighting << Heros[YouChoice[2]] << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	Fighting << "---------------------------" << endl;
	cout << "按回车键开始本局游戏！" << endl;
	getchar();
	getchar();


	int My_Win = 0, You_Win = 0;

	for (int round = 1; round <= 9; round++)
	{
		bool Winner = false;   //如我方胜则将其修改为true，通过该bool变量，判断胜利条件则只用判断我方胜利条件，减少代码量；
		int You_Hero_On, You_Skill_On;
		int My_Hero_On, My_Skill_On;
		string SkillName[3] = { "剪刀","石头","布" };
		cout << "第" << round << "回合：" << endl;
		Fighting << "第" << round << "回合：" << endl;
		do
		{
			You_Hero_On = rand() % 3;
		} while (YouHero[You_Hero_On][0] + YouHero[You_Hero_On][1] + YouHero[You_Hero_On][2] == 0);
		do
		{
			You_Skill_On = rand() % 3;
		} while (YouHero[You_Hero_On][You_Skill_On] == 0);
		YouHero[You_Hero_On][You_Skill_On]--;
		cout << "对方选择英雄" << Heros[YouChoice[You_Hero_On]] << "出战,出招" << SkillName[You_Skill_On] << endl;
		Fighting << "对方选择英雄" << Heros[YouChoice[You_Hero_On]] << "出战,出招" << SkillName[You_Skill_On] << endl;
		cout << "请选择出战英雄（通过英雄序号选择）：" << endl;
		cout << "1、" << Heros[MyChoice[0]] << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
		cout << "2、" << Heros[MyChoice[1]] << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
		cout << "3、" << Heros[MyChoice[2]] << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
		do
		{
			cin >> My_Hero_On;
			My_Hero_On--;       //因为数组下标为0，1，2，而用户选择为1，2，3，所以要对应用户选择序号-1再进行判断
			if (My_Hero_On < 0 || My_Hero_On>2)
				cout << "请从1到3中间选择一个序号出战" << endl;
			if (MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0)
				cout << "你所选择的英雄" << Heros[MyChoice[My_Hero_On]] << "已经没有技能可用了!" << endl;
		} while ((My_Hero_On < 0 || My_Hero_On>2) || MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0);
		do
		{
			My_Skill_On = rand() % 3;
		} while (MyHero[My_Hero_On][My_Skill_On] == 0);
		MyHero[My_Hero_On][My_Skill_On]--;
		cout << "你选择了英雄" << Heros[MyChoice[My_Hero_On]] << "出战，该英雄出招" << SkillName[My_Skill_On] << endl;
		Fighting << "你选择了英雄" << Heros[MyChoice[My_Hero_On]] << "出战，该英雄出招" << SkillName[My_Skill_On] << endl;
		if (My_Skill_On == 0 && You_Skill_On == 2)Winner = true;//我剪刀你布，我胜
		else if (My_Skill_On == 1 && You_Skill_On == 0)Winner = true;//我石头你剪刀，我胜
		else if (My_Skill_On == 2 && You_Skill_On == 1)Winner = true;//我布你石头，我胜
		else Winner = false;  //其实这一行可以省略因为初始化即为false
		if (Winner)
		{
			My_Win++;
			cout << "第" << round << "回合结束：我方胜利！" << endl;
			Fighting << "第" << round << "回合结束：我方胜利！" << endl;
		}
		else
		{
			You_Win++;
			cout << "第" << round << "回合结束：对方胜利！" << endl;
			Fighting << "第" << round << "回合结束：对方胜利！" << endl;
		}
		system("pause");
		cout << endl;
		Fighting << "------------------------" << endl;
	}
	cout << endl;
	cout << "游戏结束!本局游戏，我方胜利" << My_Win << "回合，对方胜利" << You_Win << "回合" << endl;
	Fighting << "游戏结束!本局游戏，我方胜利" << My_Win << "回合，对方胜利" << You_Win << "回合" << endl;
	Fighting.close();
	if (My_Win > You_Win)cout << "本局游戏我方胜利!" << endl;
	else cout << "本局游戏对方胜利!" << endl;   //因为没有平局的情况，不是我赢就是你赢
	cout << endl;
	system("pause");
}