#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
using namespace std;

#define HeroNum 15

void Str2int(int &int_t, const string &string_t); //stringתint����
void StrSplite(string str[], char buffer[], char c); //�ַ����ָ����str�洢�ָ���string���飬bufferΪ���ָ�char���飬cΪ�ָ��
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
		cout << "\t\t��ӭ��������ũҩ" << endl;
		cout << "\t\t 1����¼" << endl;
		cout << "\t\t 2��ע��" << endl;
		cout << "\t\t 3��������а�" << endl;
		cout << "\t\t 4��Ӣ��ʤ�ʰ�" << endl;
		cout << "\t\t 0���˳�" << endl;
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
		cout << "�ļ�HeroAndSkill�򿪳���" << endl;
		exit(1);
	}
	if (!UandP.is_open())
	{
		cout << "�ļ�UserAndPass�򿪳���" << endl;
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
	cout << "���ȵ�¼:" << endl;
	cout << "Username:";
	cin >> MyUser;
	cout << "Password:";
	cin >> MyPass;
	char Buffer[101];
	bool flag = false;
	ifstream File("UserAndPass.txt");
	if (!File.is_open())
	{
		cout << "�ļ��򿪳���" << endl;
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
		cout << "��������Ҫע����û�����" << endl;
		cout << "NewUsername:";
		cin >> NewUser;
		cout << "NewPassword:";
		cin >> NewPass;
		while (AllUsers[i] != "")
		{
			if (NewUser == AllUsers[i])
			{
				flag = false;
				cout << "ϵͳ�Ѵ��ڸ��û��������������룡" << endl;
				break;
			}
			i++;
		}
		if (flag)
		{
			ofstream UandP("UserAndPass.txt",ios::out|ios::app);
			if (!UandP.is_open())
			{
				cout << "�ļ�UserAndPass�򿪳���" << endl;
				exit(1);
			}
			UandP << "\n" << NewUser << "|" << NewPass << "|";
			UandP.close();
			AllUsers[i] = NewUser;
			AllPass[i] = NewPass;
		}
	} while (!flag);
	cout << "��ϲ��ע��ɹ���" << endl;
	cout << "���س�������������" << endl;
	getchar();
	getchar();
}

void Signin()
{
	bool IsLogin = false;
	while (!(IsLogin = Login()))
		cout << "���������˻������ڣ������µ�¼" << endl;
	system("cls");
	cout << "\t\t ��ӭ" << MyUser << "��¼��Ϸ��" << endl;
	StartGame();
	cout << Heros[0] << "+" << Skill[0][0] << "+" << Skill[0][1] << "+" << Skill[0][2] << endl;
}

void StartGame()
{
	int HeroChoice;    //ѡ��Ӣ�۽�����ѡ�����
	int MyChoice[3];    //�ֱ��Ӧ������ѡ�������Ӣ�ۣ���ţ�
	int YouChoice[3];   //�ֱ��Ӧ�Է���ѡ��ĵ�����Ӣ�ۣ���ţ�

	time_t t = time(0);
	char tmp[32] = { NULL };
	strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S.txt", localtime(&t));
	char Fold[] = { "Fighting/" };
	ofstream Fighting(strcat(Fold, tmp));
	if (!Fighting.is_open())
	{
		cout << "�ļ�����ʧ�ܣ�" << endl;
		exit(1);
	}

	srand((unsigned)time(NULL));
	cout << "Ӣ���б�" << endl;
	for (int i = 0; i < HeroNum; i++)
		cout << i + 1 << "��" << Heros[i] << "(" << Skill[i][0] << "," << Skill[i][1] << "," << Skill[i][2] << ")" << endl;
	do
	{
		cout << "��ѡ���һ��Ӣ�ۣ�ͨ�����ѡ����ͬ����";
		cin >> HeroChoice;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "Ӣ���б����Ҳ�����ѡ��ţ����������룡" << endl;
	} while (HeroChoice > HeroNum || HeroChoice <= 0);
	cout << "��ѡ��ĵ�һ��Ӣ����:" << Heros[HeroChoice - 1] << endl;
	MyChoice[0] = HeroChoice;
	do
	{
		cout << "��ѡ��ڶ���Ӣ�ۣ�";
		cin >> HeroChoice;
		if (HeroChoice == MyChoice[0])
			cout << "����ѡ��ĵڶ���Ӣ�����һ���ظ������������룡" << endl;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "Ӣ���б����Ҳ�����ѡ��ţ����������룡" << endl;
	} while (HeroChoice == MyChoice[0] || (HeroChoice > HeroNum || HeroChoice <= 0));
	cout << "��ѡ��ĵڶ���Ӣ����:" << Heros[HeroChoice - 1] << endl;
	MyChoice[1] = HeroChoice;
	do
	{
		cout << "��ѡ�������Ӣ�ۣ�";
		cin >> HeroChoice;
		if (HeroChoice == MyChoice[0])
			cout << "����ѡ��ĵ�����Ӣ�����һ���ظ������������룡" << endl;
		if (HeroChoice == MyChoice[1])
			cout << "����ѡ��ĵ�����Ӣ����ڶ����ظ������������룡" << endl;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "Ӣ���б����Ҳ�����ѡ��ţ����������룡" << endl;
	} while ((HeroChoice == MyChoice[0] || HeroChoice == MyChoice[1]) || (HeroChoice > HeroNum || HeroChoice <= 0));
	cout << "��ѡ��ĵ�����Ӣ����:" << Heros[HeroChoice - 1] << endl;
	MyChoice[2] = HeroChoice;
	MyChoice[0]--;
	MyChoice[1]--;
	MyChoice[2]--;
	/*������ѡ�������Ӣ�۵ļ�����*/
	int MyHero[3][3] = {
		Skill[MyChoice[0]][0],Skill[MyChoice[0]][1], Skill[MyChoice[0]][2],
		Skill[MyChoice[1]][0],Skill[MyChoice[1]][1], Skill[MyChoice[1]][2],
		Skill[MyChoice[2]][0],Skill[MyChoice[2]][1], Skill[MyChoice[2]][2] };
	cout << "---------------------------" << endl;
	cout << "����ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	cout << Heros[MyChoice[0]] << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	cout << Heros[MyChoice[1]] << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	cout << Heros[MyChoice[2]] << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	Fighting << "����ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
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
	/*�Է���ѡ�������Ӣ�۵ļ�����*/
	int YouHero[3][3] = { 
		Skill[YouChoice[0]][0],Skill[YouChoice[0]][1], Skill[YouChoice[0]][2],
		Skill[YouChoice[1]][0],Skill[YouChoice[1]][1], Skill[YouChoice[1]][2],
		Skill[YouChoice[2]][0],Skill[YouChoice[2]][1], Skill[YouChoice[2]][2] };
	cout << "---------------------------" << endl;
	cout << "�Է�ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	cout << Heros[YouChoice[0]] << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	cout << Heros[YouChoice[1]] << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	cout << Heros[YouChoice[2]] << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	cout << "---------------------------" << endl;
	Fighting << "---------------------------" << endl;
	Fighting << "�Է�ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	Fighting << Heros[YouChoice[0]] << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	Fighting << Heros[YouChoice[1]] << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	Fighting << Heros[YouChoice[2]] << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	Fighting << "---------------------------" << endl;
	cout << "���س�����ʼ������Ϸ��" << endl;
	getchar();
	getchar();


	int My_Win = 0, You_Win = 0;

	for (int round = 1; round <= 9; round++)
	{
		bool Winner = false;   //���ҷ�ʤ�����޸�Ϊtrue��ͨ����bool�������ж�ʤ��������ֻ���ж��ҷ�ʤ�����������ٴ�������
		int You_Hero_On, You_Skill_On;
		int My_Hero_On, My_Skill_On;
		string SkillName[3] = { "����","ʯͷ","��" };
		cout << "��" << round << "�غϣ�" << endl;
		Fighting << "��" << round << "�غϣ�" << endl;
		do
		{
			You_Hero_On = rand() % 3;
		} while (YouHero[You_Hero_On][0] + YouHero[You_Hero_On][1] + YouHero[You_Hero_On][2] == 0);
		do
		{
			You_Skill_On = rand() % 3;
		} while (YouHero[You_Hero_On][You_Skill_On] == 0);
		YouHero[You_Hero_On][You_Skill_On]--;
		cout << "�Է�ѡ��Ӣ��" << Heros[YouChoice[You_Hero_On]] << "��ս,����" << SkillName[You_Skill_On] << endl;
		Fighting << "�Է�ѡ��Ӣ��" << Heros[YouChoice[You_Hero_On]] << "��ս,����" << SkillName[You_Skill_On] << endl;
		cout << "��ѡ���սӢ�ۣ�ͨ��Ӣ�����ѡ�񣩣�" << endl;
		cout << "1��" << Heros[MyChoice[0]] << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
		cout << "2��" << Heros[MyChoice[1]] << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
		cout << "3��" << Heros[MyChoice[2]] << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
		do
		{
			cin >> My_Hero_On;
			My_Hero_On--;       //��Ϊ�����±�Ϊ0��1��2�����û�ѡ��Ϊ1��2��3������Ҫ��Ӧ�û�ѡ�����-1�ٽ����ж�
			if (My_Hero_On < 0 || My_Hero_On>2)
				cout << "���1��3�м�ѡ��һ����ų�ս" << endl;
			if (MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0)
				cout << "����ѡ���Ӣ��" << Heros[MyChoice[My_Hero_On]] << "�Ѿ�û�м��ܿ�����!" << endl;
		} while ((My_Hero_On < 0 || My_Hero_On>2) || MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0);
		do
		{
			My_Skill_On = rand() % 3;
		} while (MyHero[My_Hero_On][My_Skill_On] == 0);
		MyHero[My_Hero_On][My_Skill_On]--;
		cout << "��ѡ����Ӣ��" << Heros[MyChoice[My_Hero_On]] << "��ս����Ӣ�۳���" << SkillName[My_Skill_On] << endl;
		Fighting << "��ѡ����Ӣ��" << Heros[MyChoice[My_Hero_On]] << "��ս����Ӣ�۳���" << SkillName[My_Skill_On] << endl;
		if (My_Skill_On == 0 && You_Skill_On == 2)Winner = true;//�Ҽ����㲼����ʤ
		else if (My_Skill_On == 1 && You_Skill_On == 0)Winner = true;//��ʯͷ���������ʤ
		else if (My_Skill_On == 2 && You_Skill_On == 1)Winner = true;//�Ҳ���ʯͷ����ʤ
		else Winner = false;  //��ʵ��һ�п���ʡ����Ϊ��ʼ����Ϊfalse
		if (Winner)
		{
			My_Win++;
			cout << "��" << round << "�غϽ������ҷ�ʤ����" << endl;
			Fighting << "��" << round << "�غϽ������ҷ�ʤ����" << endl;
		}
		else
		{
			You_Win++;
			cout << "��" << round << "�غϽ������Է�ʤ����" << endl;
			Fighting << "��" << round << "�غϽ������Է�ʤ����" << endl;
		}
		system("pause");
		cout << endl;
		Fighting << "------------------------" << endl;
	}
	cout << endl;
	cout << "��Ϸ����!������Ϸ���ҷ�ʤ��" << My_Win << "�غϣ��Է�ʤ��" << You_Win << "�غ�" << endl;
	Fighting << "��Ϸ����!������Ϸ���ҷ�ʤ��" << My_Win << "�غϣ��Է�ʤ��" << You_Win << "�غ�" << endl;
	Fighting.close();
	if (My_Win > You_Win)cout << "������Ϸ�ҷ�ʤ��!" << endl;
	else cout << "������Ϸ�Է�ʤ��!" << endl;   //��Ϊû��ƽ�ֵ������������Ӯ������Ӯ
	cout << endl;
	system("pause");
}