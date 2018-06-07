#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cstdio>
using namespace std;

#define HeroNum 15     //英雄数目
#define UserNum 50     //用户最大数目

void Str2int(int &int_t, const string &string_t); //string转int函数
void StrSplite(string str[], char buffer[], char c); //字符串分割函数，str存储分割后的string数组，buffer为待分割char数组，c为分割符
void Loading();      //加载函数，将文件信息全写入内存中
bool Login();        //登录函数，登录成功返回true，失败返回false
void Signup();       //注册函数
void PlayerRank();    //玩家胜场排行榜
void HeroRank();      //英雄胜率排行榜
void Signin();        //通过Login函数返回的值判断是否进入游戏
void StartGame();      //游戏主体

struct Hero           //用结构体存放英雄相关数据
{
	string Heroname;    //英雄名字
	int Skill[3];       //英雄技能，Skill[0],Skill[1],Skill[2]分别对应剪刀石头布
	int HeroAllRounds;  //英雄总场次
	int HeroWinRounds;  //英雄胜场
	float HeroWinRatio;  //英雄胜率
}Heros[HeroNum];

struct User        //用结构体存放用户相关数据
{
	string Username;   //用户名
	string Password;   //密码
	int UserWinRounds;   //玩家胜场数
}Users[UserNum];

string MyUser;   //登录用户名
string MyPass;   //登录密码
int MyUserIndex;   //我的用户在结构体数组中的序号（类似于身份证号那种）

int main()
{
	int Choice;     //菜单选项
	Loading();      //先将文件内容全部读出
	do
	{
		system("cls");
		cout << "\t\t欢迎来到王者农药" << endl;
		cout << "\t\t 1、登录" << endl;
		cout << "\t\t 2、注册" << endl;
		cout << "\t\t 3、玩家排行榜" << endl;
		cout << "\t\t 4、英雄胜率榜" << endl;
		cout << "\t\t 0、退出" << endl;
		cin >> Choice;    //输入选项
		switch (Choice)    //由选项进入对应功能界面
		{
		case 1:Signin(); break;
		case 2:Signup(); break;
		case 3:PlayerRank(); break;
		case 4:HeroRank(); break;
		default:break;
		}
	} while (Choice != 0);   //输入0则退出程序
	cout << "ByeBye!" << endl;	
	return 0;
}

void Str2int(int &int_t, const string &string_t)   //将string转换为int，实现方式类似于管道？？
{
	stringstream stream(string_t);
	stream >> int_t;
}

void StrSplite(string str[], char buffer[], char c)  //字符串分割
{
	int i = 0, j = 0;
	char *s = buffer;   //定义指针指向char数组的第一个下标
	while (*(s + i) != NULL)    //如果指针移动过程中指向空了就表明char数组读完了
	{
		if (*(s + i) == c)    //如果指针移动过程中遇到这个分隔符
		{
			*(s + i) = '\0';   //将其改为'\0'
			str[j] = s;       //并将其剩余部分作为字符串存入string数组
			j++;   //string数组下标+1
			s = s + i + 1;    //并将指针位置初始化为改为'\0'后的那个位置
			i = 0;  //指针移动标记初始化为0
		}
		else
			i++;
	}
}

void Loading()
{
	char Buffer[101];    //文件流读出的存储数组
	int index = 0;     //用户结构体数组下标
	ifstream HandS("HeroAndSkill.txt");     //以读的方式打开这个文件
	ifstream UandP("UserAndPass.txt");
	if (!HandS.is_open())   //没打开就直接报错溜掉
	{
		cout << "文件HeroAndSkill打开出错！" << endl;
		exit(1);
	}
	if (!UandP.is_open())
	{
		cout << "文件UserAndPass打开出错！" << endl;
		exit(1);
	}
	while (!HandS.eof())    //没读到最后就循环读
	{
		string str[6];    //待存分割后的字符串
		HandS.getline(Buffer, 100);   //读一行内容到char数组
		StrSplite(str, Buffer, '|');   //用'|'分割字符串
		Heros[index].Heroname = str[0];   //将文件读出来的数据一一存入结构体
		Str2int(Heros[index].Skill[0], str[1]);
		Str2int(Heros[index].Skill[1], str[2]);
		Str2int(Heros[index].Skill[2], str[3]);
		Str2int(Heros[index].HeroAllRounds, str[4]);
		Str2int(Heros[index].HeroWinRounds, str[5]);
		index++;   //结构体数组下标+1
	}
	HandS.close();   //已经用不到这个文件了可以关了
	index = 0;    //结构体数组下标+1，之后读用户信息还要用呢
	while (!UandP.eof())    //和上面一模一样
	{
		string str[3];
		UandP.getline(Buffer, 100);
		StrSplite(str, Buffer, '|');
		Users[index].Username = str[0];
		Users[index].Password = str[1];
		Str2int(Users[index].UserWinRounds, str[2]);
		index++;
	}
	UandP.close();   //用不着了，记得关文件
}

bool Login()
{
	cout << "请先登录:" << endl;
	cout << "Username:";
	cin >> MyUser;
	cout << "Password:";
	cin >> MyPass;
	bool flag = false;    //将flag初始化为false，如果登录成功则改为true
	for (int i = 0; Users[i].Username != ""; i++)
	{
		if (MyUser == Users[i].Username && MyPass == Users[i].Password)
		{
			flag = true;
			MyUserIndex = i;    //将我的用户ID（临时的）赋值
			break;
		}
	}
	return flag;   //返回true就登录成功，否则就失败
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
		while (Users[i].Username != "")//用户名为空则表明用户全部读出来了
		{
			if (NewUser == Users[i].Username)  //如果注册用户名与已有用户名重复则报错
			{
				flag = false; //flag改为false表明注册失败
				cout << "系统已存在该用户名，请重新输入！" << endl;
				break;
			}
			i++;
		}
		if (flag)   //注册成功则将新用户信息写入文件
		{
			ofstream UandP("UserAndPass.txt",ios::out|ios::app);  //这部分文件操作与Loading里面一样
			if (!UandP.is_open())
			{
				cout << "文件UserAndPass打开出错！" << endl;
				exit(1);
			}
			UandP << "\n" << NewUser << "|" << NewPass << "|0|";
			UandP.close();
			Users[i].Username = NewUser;
			Users[i].Password = NewPass;
			Users[i].UserWinRounds = 0;
		}
	} while (!flag);   //注册失败的时候循环
	cout << "恭喜你注册成功！" << endl;
	cout << "按回车键返回主界面" << endl;
	getchar();
	getchar();
}

void Signin()
{
	while (!Login())
		cout << "密码错误或账户不存在，请重新登录" << endl;
	system("cls");   //清空屏幕
	cout << "\t\t 欢迎" << MyUser << "登录游戏！" << endl;
	StartGame();//登录成功后就开始游戏
}

void StartGame()
{
	int HeroChoice;    //选择英雄界面所选择序号
	int MyChoice[3];    //分别对应己方所选择的三个英雄（序号）
	int YouChoice[3];   //分别对应对方所选择的的三个英雄（序号）

	time_t t = time(0);
	char tmp[32] = { NULL };
	strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S.txt", localtime(&t));  //获取本地时间
	char Fold[] = { "Fighting/" };  //文件夹名
	ofstream Fighting(strcat(Fold, tmp));   //每一局游戏根据当前时间命名文件并存放在统一文件夹便于管理
	if (!Fighting.is_open())
	{
		cout << "文件创建失败！" << endl;
		exit(1);
	}

	srand((unsigned)time(NULL));  //以系统时间作为随机种子，后面有用的
	cout << "英雄列表：" << endl;
	for (int i = 0; i < HeroNum; i++)  //将所有英雄信息打印到屏幕
		cout << i + 1 << "、" << Heros[i].Heroname << "(" << Heros[i].Skill[0] << "," << Heros[i].Skill[1] << "," << Heros[i].Skill[2] << ")" << endl;
	do //选择第一个英雄，要求在数字1到15之间
	{
		cout << "请选择第一个英雄（通过序号选择，下同）：";
		cin >> HeroChoice;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "英雄列表内找不到所选序号，请重新输入！" << endl;
	} while (HeroChoice > HeroNum || HeroChoice <= 0);
	cout << "你选择的第一个英雄是:" << Heros[HeroChoice - 1].Heroname << endl;
	MyChoice[0] = HeroChoice;   //我选的第一个英雄
	do  //选择第二个英雄，要求同上，并且不与第一个英雄重复
	{
		cout << "请选择第二个英雄：";
		cin >> HeroChoice;
		if (HeroChoice == MyChoice[0])
			cout << "你所选择的第二个英雄与第一个重复，请重新输入！" << endl;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "英雄列表内找不到所选序号，请重新输入！" << endl;
	} while (HeroChoice == MyChoice[0] || (HeroChoice > HeroNum || HeroChoice <= 0));
	cout << "你选择的第二个英雄是:" << Heros[HeroChoice - 1].Heroname << endl;
	MyChoice[1] = HeroChoice;  //我选的第二个英雄
	do  //选择第三个英雄，要求同上，并且不与第一、二个英雄重复
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
	cout << "你选择的第三个英雄是:" << Heros[HeroChoice - 1].Heroname << endl;
	MyChoice[2] = HeroChoice;  //我选的第三个英雄
	MyChoice[0]--;  //因为所选英雄序号是1到15，而数组是0到14，所以反应到数组的话需要自减1
	MyChoice[1]--;
	MyChoice[2]--;
	/*己方所选择的三个英雄的技能数*/
	int MyHero[3][3] = {
		Heros[MyChoice[0]].Skill[0],Heros[MyChoice[0]].Skill[1], Heros[MyChoice[0]].Skill[2],
		Heros[MyChoice[1]].Skill[0],Heros[MyChoice[1]].Skill[1], Heros[MyChoice[1]].Skill[2],
		Heros[MyChoice[2]].Skill[0],Heros[MyChoice[2]].Skill[1], Heros[MyChoice[2]].Skill[2] };
	cout << "---------------------------" << endl;
	cout << "你所选择的三个英雄分别是：" << endl;
	cout << Heros[MyChoice[0]].Heroname << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	cout << Heros[MyChoice[1]].Heroname << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	cout << Heros[MyChoice[2]].Heroname << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	Fighting << "你所选择的三个英雄分别是：" << endl;
	Fighting << Heros[MyChoice[0]].Heroname << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	Fighting << Heros[MyChoice[1]].Heroname << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	Fighting << Heros[MyChoice[2]].Heroname << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	YouChoice[0] = rand() % HeroNum;   //对方所选第一个英雄，没限制，取0到15以内的随机数即可
	do   //对方所选第二个英雄，要求不与第一个英雄重复，取0到15以内的随机数
	{
		YouChoice[1] = rand() % HeroNum;
	} while (YouChoice[1] == YouChoice[0]);
	do   //对方所选第二个英雄，要求不与第一、二个英雄重复，取0到15以内的随机数
	{
		YouChoice[2] = rand() % HeroNum;
	} while (YouChoice[2] == YouChoice[0] || YouChoice[2] == YouChoice[1]);
	/*对方所选择的三个英雄的技能数*/
	int YouHero[3][3] = { 
		Heros[YouChoice[0]].Skill[0],Heros[YouChoice[0]].Skill[1], Heros[YouChoice[0]].Skill[2],
		Heros[YouChoice[1]].Skill[0],Heros[YouChoice[1]].Skill[1], Heros[YouChoice[1]].Skill[2],
		Heros[YouChoice[2]].Skill[0],Heros[YouChoice[2]].Skill[1], Heros[YouChoice[2]].Skill[2] };
	cout << "---------------------------" << endl;
	cout << "对方选择的三个英雄分别是：" << endl;
	cout << Heros[YouChoice[0]].Heroname << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	cout << Heros[YouChoice[1]].Heroname << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	cout << Heros[YouChoice[2]].Heroname << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	cout << "---------------------------" << endl;
	Fighting << "---------------------------" << endl;
	Fighting << "对方选择的三个英雄分别是：" << endl;
	Fighting << Heros[YouChoice[0]].Heroname << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	Fighting << Heros[YouChoice[1]].Heroname << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	Fighting << Heros[YouChoice[2]].Heroname << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	Fighting << "---------------------------" << endl;
	cout << "按回车键开始本局游戏！" << endl;
	getchar();   //起暂停作用
	getchar();


	int My_Win = 0, You_Win = 0;   //我方胜场数与对方胜场数初始化为0

	for (int round = 1; round <= 9; round++)   //一共九个回合
	{
		bool Winner = false;   //如我方胜则将其修改为true，通过该bool变量，判断胜利条件则只用判断我方胜利条件，减少代码量；
		int You_Hero_On, You_Skill_On;  //对方所上阵的英雄及技能
		int My_Hero_On, My_Skill_On;   //我方所上阵的英雄及技能
		string SkillName[3] = { "剪刀","石头","布" };    //类似于枚举的功能？
		cout << "第" << round << "回合：" << endl;    //输出到屏幕
		Fighting << "第" << round << "回合：" << endl;   //输出到文件记录，下面也是一个道理
		do   //对方去一个3以内的随机数随机上场一个英雄，要求技能数不全为0
		{
			You_Hero_On = rand() % 3;
		} while (YouHero[You_Hero_On][0] + YouHero[You_Hero_On][1] + YouHero[You_Hero_On][2] == 0);
		do   //对方上场英雄里随机出一个技能，要求该技能数不为0
		{
			You_Skill_On = rand() % 3;
		} while (YouHero[You_Hero_On][You_Skill_On] == 0);
		YouHero[You_Hero_On][You_Skill_On]--;   //上场的该英雄所用的技能剩余数-1
		cout << "对方选择英雄" << Heros[YouChoice[You_Hero_On]].Heroname << "出战,出招" << SkillName[You_Skill_On] << endl;
		Fighting << "对方选择英雄" << Heros[YouChoice[You_Hero_On]].Heroname << "出战,出招" << SkillName[You_Skill_On] << endl;
		cout << "请选择出战英雄（通过英雄序号选择）：" << endl;
		cout << "1、" << Heros[MyChoice[0]].Heroname << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
		cout << "2、" << Heros[MyChoice[1]].Heroname << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
		cout << "3、" << Heros[MyChoice[2]].Heroname << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
		do  //手动选择上场英雄，要去1到3且技能数不全为0
		{
			cin >> My_Hero_On;   
			My_Hero_On--;       //因为数组下标为0，1，2，而用户选择为1，2，3，所以要对应用户选择序号-1再进行判断
			if (My_Hero_On < 0 || My_Hero_On>2)
				cout << "请从1到3中间选择一个序号出战" << endl;
			if (MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0)
				cout << "你所选择的英雄" << Heros[MyChoice[My_Hero_On]].Heroname << "已经没有技能可用了!" << endl;
		} while ((My_Hero_On < 0 || My_Hero_On>2) || MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0);
		do  //该英雄随机出招，要求技能剩余数不为0
		{
			My_Skill_On = rand() % 3;
		} while (MyHero[My_Hero_On][My_Skill_On] == 0);
		MyHero[My_Hero_On][My_Skill_On]--;   //上场英雄的技能数-1
		cout << "你选择了英雄" << Heros[MyChoice[My_Hero_On]].Heroname << "出战，该英雄出招" << SkillName[My_Skill_On] << endl;
		Fighting << "你选择了英雄" << Heros[MyChoice[My_Hero_On]].Heroname << "出战，该英雄出招" << SkillName[My_Skill_On] << endl;
		if (My_Skill_On == 0 && You_Skill_On == 2)Winner = true;//我剪刀你布，我胜
		else if (My_Skill_On == 1 && You_Skill_On == 0)Winner = true;//我石头你剪刀，我胜
		else if (My_Skill_On == 2 && You_Skill_On == 1)Winner = true;//我布你石头，我胜
		else Winner = false;  //其实这一行可以省略因为初始化即为false
		if (Winner)   //如果我方胜利
		{
			My_Win++;   //我方胜场数+1
			Heros[MyChoice[My_Hero_On]].HeroWinRounds++;   //我方上场英雄的胜场数+1
			Users[MyUserIndex].UserWinRounds++;    //玩家胜场+1
			cout << "第" << round << "回合结束：我方胜利！" << endl;
			Fighting << "第" << round << "回合结束：我方胜利！" << endl;
		}
		else   //如果对方胜利
		{
			You_Win++;   //对方胜场数+1
			cout << "第" << round << "回合结束：对方胜利！" << endl;
			Fighting << "第" << round << "回合结束：对方胜利！" << endl;
		}
		Heros[MyChoice[My_Hero_On]].HeroAllRounds++;   //不管输赢，上场英雄总场次+1
		system("pause");   //暂停一下，看结果
		cout << endl;
		Fighting << "------------------------" << endl;
	}
	cout << endl;
	cout << "游戏结束!本局游戏，我方胜利" << My_Win << "回合，对方胜利" << You_Win << "回合" << endl;
	Fighting << "游戏结束!本局游戏，我方胜利" << My_Win << "回合，对方胜利" << You_Win << "回合" << endl;
	Fighting.close();   //不用了记得关文件
	if (My_Win > You_Win)cout << "本局游戏我方胜利!" << endl;
	else cout << "本局游戏对方胜利!" << endl;   //因为没有平局的情况，不是我赢就是你赢
	cout << endl;

	ofstream Update_Hero("HeroAndSkill.txt",ios::trunc);   //更新英雄总场次与胜场数
	ofstream Update_User("UserAndPass.txt", ios::trunc);   //更新玩家胜场数
	if (!Update_Hero.is_open())
	{
		cout << "文件HerrAndSkill打开出错" << endl;
		exit(1);
	}
	if (!Update_User.is_open())
	{
		cout << "文件UserAndPass打开出错" << endl;
		exit(1);
	}
	for (int i = 0; i < HeroNum; i++)
		Update_Hero << Heros[i].Heroname << "|" << Heros[i].Skill[0] << "|" << Heros[i].Skill[1] << "|" << Heros[i].Skill[2] << "|" << Heros[i].HeroAllRounds << "|" << Heros[i].HeroWinRounds << "|" << endl;
	for (int i = 0; Users[i].Username != ""; i++)
		Update_User << Users[i].Username << "|" << Users[i].Password << "|" << Users[i].UserWinRounds << "|" << endl;
	Update_Hero.close();   //记得关文件呐
	Update_User.close();   //最后提醒一下了
	system("pause");
}

void PlayerRank()
{
	cout << "名次\t用户名\t胜场数" << endl;
	int index = 0;   //结构体数组下标
	for (index; Users[index].Username != ""; index++);  //得出当前用户数目
	int Win_Rounds[UserNum];   //定义一个临时数组暂时存放一下玩家胜场数
	for (int i = 0; i < index; i++)   //先把胜场数赋值到临时数组里去
		Win_Rounds[i] = Users[i].UserWinRounds;
	for (int i = 0; i < index; i++)   //遍历
	{
		int big = Win_Rounds[0];
		int bigindex = 0;
		for (int j = 0; j < index; j++)  
		{
			if (Win_Rounds[j] > big)  //找出最大值并修改当前最大值
			{
				big = Win_Rounds[j];
				bigindex = j;
			}
		}
		Win_Rounds[bigindex] = -1;   //将临时数组里的最大值改为-1，则该值就不可能再为最大值
		cout << i + 1 << "、\t" << Users[bigindex].Username << "\t" << Users[bigindex].UserWinRounds << endl;  //根据每次遍历得到最大值所在下标确定结构体数组的胜场数最大值的结构体位置
	}
	system("pause");
	system("cls");
}

void HeroRank()   //这个和玩家排行榜设计一模一样，就不赘述了
{
	cout << "名次\t\t英雄\t\t总场次\t\t胜场\t\t胜率" << endl;
	for (int i = 0; i < HeroNum; i++)   //只不过要注意一下算胜率
	{
		if (Heros[i].HeroWinRounds == 0 || Heros[i].HeroAllRounds == 0)
			Heros[i].HeroWinRatio = 0;
		else
			Heros[i].HeroWinRatio = (float)Heros[i].HeroWinRounds / Heros[i].HeroAllRounds;
	}
	float Ratio[HeroNum];
	for (int i = 0; i < HeroNum; i++)
		Ratio[i] = Heros[i].HeroWinRatio;
	for (int i = 0; i < HeroNum; i++)
	{
		float big = Ratio[0];
		int bigindex = 0;
		for (int j = 0; j < HeroNum; j++)
		{
			if (Ratio[j] >= big)
			{
				big = Ratio[j];
				bigindex = j;
			}
		}
		Ratio[bigindex] = -1;
		cout.width(16);//强行将宽度设为两个制表符那么宽，方便对齐，若是直接用"\t"的话，由于某些英雄名字占用了两个制表符宽度则会无法对齐
		cout.setf(ios::left);//左对齐方式
		cout << i + 1;
		cout.width(16);
		cout << Heros[bigindex].Heroname ;
		cout.width(16);
		cout << Heros[bigindex].HeroAllRounds;
		cout.width(16);
		cout << Heros[bigindex].HeroWinRounds;
		cout << Heros[bigindex].HeroWinRatio * 100 << "%" << endl;
//		cout << i + 1 << "、\t\t" << Heros[bigindex].Heroname << "\t\t" << Heros[bigindex].HeroAllRounds << "\t\t" << Heros[bigindex].HeroWinRounds << "\t\t" << Heros[bigindex].HeroWinRatio * 100 << "%" << endl;
	}
	system("pause");
	system("cls");
}