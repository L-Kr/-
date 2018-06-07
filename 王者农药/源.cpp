#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cstdio>
using namespace std;

#define HeroNum 15     //Ӣ����Ŀ
#define UserNum 50     //�û������Ŀ

void Str2int(int &int_t, const string &string_t); //stringתint����
void StrSplite(string str[], char buffer[], char c); //�ַ����ָ����str�洢�ָ���string���飬bufferΪ���ָ�char���飬cΪ�ָ��
void Loading();      //���غ��������ļ���Ϣȫд���ڴ���
bool Login();        //��¼��������¼�ɹ�����true��ʧ�ܷ���false
void Signup();       //ע�ắ��
void PlayerRank();    //���ʤ�����а�
void HeroRank();      //Ӣ��ʤ�����а�
void Signin();        //ͨ��Login�������ص�ֵ�ж��Ƿ������Ϸ
void StartGame();      //��Ϸ����

struct Hero           //�ýṹ����Ӣ���������
{
	string Heroname;    //Ӣ������
	int Skill[3];       //Ӣ�ۼ��ܣ�Skill[0],Skill[1],Skill[2]�ֱ��Ӧ����ʯͷ��
	int HeroAllRounds;  //Ӣ���ܳ���
	int HeroWinRounds;  //Ӣ��ʤ��
	float HeroWinRatio;  //Ӣ��ʤ��
}Heros[HeroNum];

struct User        //�ýṹ�����û��������
{
	string Username;   //�û���
	string Password;   //����
	int UserWinRounds;   //���ʤ����
}Users[UserNum];

string MyUser;   //��¼�û���
string MyPass;   //��¼����
int MyUserIndex;   //�ҵ��û��ڽṹ�������е���ţ����������֤�����֣�

int main()
{
	int Choice;     //�˵�ѡ��
	Loading();      //�Ƚ��ļ�����ȫ������
	do
	{
		system("cls");
		cout << "\t\t��ӭ��������ũҩ" << endl;
		cout << "\t\t 1����¼" << endl;
		cout << "\t\t 2��ע��" << endl;
		cout << "\t\t 3��������а�" << endl;
		cout << "\t\t 4��Ӣ��ʤ�ʰ�" << endl;
		cout << "\t\t 0���˳�" << endl;
		cin >> Choice;    //����ѡ��
		switch (Choice)    //��ѡ������Ӧ���ܽ���
		{
		case 1:Signin(); break;
		case 2:Signup(); break;
		case 3:PlayerRank(); break;
		case 4:HeroRank(); break;
		default:break;
		}
	} while (Choice != 0);   //����0���˳�����
	cout << "ByeBye!" << endl;	
	return 0;
}

void Str2int(int &int_t, const string &string_t)   //��stringת��Ϊint��ʵ�ַ�ʽ�����ڹܵ�����
{
	stringstream stream(string_t);
	stream >> int_t;
}

void StrSplite(string str[], char buffer[], char c)  //�ַ����ָ�
{
	int i = 0, j = 0;
	char *s = buffer;   //����ָ��ָ��char����ĵ�һ���±�
	while (*(s + i) != NULL)    //���ָ���ƶ�������ָ����˾ͱ���char���������
	{
		if (*(s + i) == c)    //���ָ���ƶ���������������ָ���
		{
			*(s + i) = '\0';   //�����Ϊ'\0'
			str[j] = s;       //������ʣ�ಿ����Ϊ�ַ�������string����
			j++;   //string�����±�+1
			s = s + i + 1;    //����ָ��λ�ó�ʼ��Ϊ��Ϊ'\0'����Ǹ�λ��
			i = 0;  //ָ���ƶ���ǳ�ʼ��Ϊ0
		}
		else
			i++;
	}
}

void Loading()
{
	char Buffer[101];    //�ļ��������Ĵ洢����
	int index = 0;     //�û��ṹ�������±�
	ifstream HandS("HeroAndSkill.txt");     //�Զ��ķ�ʽ������ļ�
	ifstream UandP("UserAndPass.txt");
	if (!HandS.is_open())   //û�򿪾�ֱ�ӱ������
	{
		cout << "�ļ�HeroAndSkill�򿪳���" << endl;
		exit(1);
	}
	if (!UandP.is_open())
	{
		cout << "�ļ�UserAndPass�򿪳���" << endl;
		exit(1);
	}
	while (!HandS.eof())    //û��������ѭ����
	{
		string str[6];    //����ָ����ַ���
		HandS.getline(Buffer, 100);   //��һ�����ݵ�char����
		StrSplite(str, Buffer, '|');   //��'|'�ָ��ַ���
		Heros[index].Heroname = str[0];   //���ļ�������������һһ����ṹ��
		Str2int(Heros[index].Skill[0], str[1]);
		Str2int(Heros[index].Skill[1], str[2]);
		Str2int(Heros[index].Skill[2], str[3]);
		Str2int(Heros[index].HeroAllRounds, str[4]);
		Str2int(Heros[index].HeroWinRounds, str[5]);
		index++;   //�ṹ�������±�+1
	}
	HandS.close();   //�Ѿ��ò�������ļ��˿��Թ���
	index = 0;    //�ṹ�������±�+1��֮����û���Ϣ��Ҫ����
	while (!UandP.eof())    //������һģһ��
	{
		string str[3];
		UandP.getline(Buffer, 100);
		StrSplite(str, Buffer, '|');
		Users[index].Username = str[0];
		Users[index].Password = str[1];
		Str2int(Users[index].UserWinRounds, str[2]);
		index++;
	}
	UandP.close();   //�ò����ˣ��ǵù��ļ�
}

bool Login()
{
	cout << "���ȵ�¼:" << endl;
	cout << "Username:";
	cin >> MyUser;
	cout << "Password:";
	cin >> MyPass;
	bool flag = false;    //��flag��ʼ��Ϊfalse�������¼�ɹ����Ϊtrue
	for (int i = 0; Users[i].Username != ""; i++)
	{
		if (MyUser == Users[i].Username && MyPass == Users[i].Password)
		{
			flag = true;
			MyUserIndex = i;    //���ҵ��û�ID����ʱ�ģ���ֵ
			break;
		}
	}
	return flag;   //����true�͵�¼�ɹ��������ʧ��
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
		while (Users[i].Username != "")//�û���Ϊ��������û�ȫ����������
		{
			if (NewUser == Users[i].Username)  //���ע���û����������û����ظ��򱨴�
			{
				flag = false; //flag��Ϊfalse����ע��ʧ��
				cout << "ϵͳ�Ѵ��ڸ��û��������������룡" << endl;
				break;
			}
			i++;
		}
		if (flag)   //ע��ɹ������û���Ϣд���ļ�
		{
			ofstream UandP("UserAndPass.txt",ios::out|ios::app);  //�ⲿ���ļ�������Loading����һ��
			if (!UandP.is_open())
			{
				cout << "�ļ�UserAndPass�򿪳���" << endl;
				exit(1);
			}
			UandP << "\n" << NewUser << "|" << NewPass << "|0|";
			UandP.close();
			Users[i].Username = NewUser;
			Users[i].Password = NewPass;
			Users[i].UserWinRounds = 0;
		}
	} while (!flag);   //ע��ʧ�ܵ�ʱ��ѭ��
	cout << "��ϲ��ע��ɹ���" << endl;
	cout << "���س�������������" << endl;
	getchar();
	getchar();
}

void Signin()
{
	while (!Login())
		cout << "���������˻������ڣ������µ�¼" << endl;
	system("cls");   //�����Ļ
	cout << "\t\t ��ӭ" << MyUser << "��¼��Ϸ��" << endl;
	StartGame();//��¼�ɹ���Ϳ�ʼ��Ϸ
}

void StartGame()
{
	int HeroChoice;    //ѡ��Ӣ�۽�����ѡ�����
	int MyChoice[3];    //�ֱ��Ӧ������ѡ�������Ӣ�ۣ���ţ�
	int YouChoice[3];   //�ֱ��Ӧ�Է���ѡ��ĵ�����Ӣ�ۣ���ţ�

	time_t t = time(0);
	char tmp[32] = { NULL };
	strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S.txt", localtime(&t));  //��ȡ����ʱ��
	char Fold[] = { "Fighting/" };  //�ļ�����
	ofstream Fighting(strcat(Fold, tmp));   //ÿһ����Ϸ���ݵ�ǰʱ�������ļ��������ͳһ�ļ��б��ڹ���
	if (!Fighting.is_open())
	{
		cout << "�ļ�����ʧ�ܣ�" << endl;
		exit(1);
	}

	srand((unsigned)time(NULL));  //��ϵͳʱ����Ϊ������ӣ��������õ�
	cout << "Ӣ���б�" << endl;
	for (int i = 0; i < HeroNum; i++)  //������Ӣ����Ϣ��ӡ����Ļ
		cout << i + 1 << "��" << Heros[i].Heroname << "(" << Heros[i].Skill[0] << "," << Heros[i].Skill[1] << "," << Heros[i].Skill[2] << ")" << endl;
	do //ѡ���һ��Ӣ�ۣ�Ҫ��������1��15֮��
	{
		cout << "��ѡ���һ��Ӣ�ۣ�ͨ�����ѡ����ͬ����";
		cin >> HeroChoice;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "Ӣ���б����Ҳ�����ѡ��ţ����������룡" << endl;
	} while (HeroChoice > HeroNum || HeroChoice <= 0);
	cout << "��ѡ��ĵ�һ��Ӣ����:" << Heros[HeroChoice - 1].Heroname << endl;
	MyChoice[0] = HeroChoice;   //��ѡ�ĵ�һ��Ӣ��
	do  //ѡ��ڶ���Ӣ�ۣ�Ҫ��ͬ�ϣ����Ҳ����һ��Ӣ���ظ�
	{
		cout << "��ѡ��ڶ���Ӣ�ۣ�";
		cin >> HeroChoice;
		if (HeroChoice == MyChoice[0])
			cout << "����ѡ��ĵڶ���Ӣ�����һ���ظ������������룡" << endl;
		if (HeroChoice > HeroNum || HeroChoice <= 0)
			cout << "Ӣ���б����Ҳ�����ѡ��ţ����������룡" << endl;
	} while (HeroChoice == MyChoice[0] || (HeroChoice > HeroNum || HeroChoice <= 0));
	cout << "��ѡ��ĵڶ���Ӣ����:" << Heros[HeroChoice - 1].Heroname << endl;
	MyChoice[1] = HeroChoice;  //��ѡ�ĵڶ���Ӣ��
	do  //ѡ�������Ӣ�ۣ�Ҫ��ͬ�ϣ����Ҳ����һ������Ӣ���ظ�
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
	cout << "��ѡ��ĵ�����Ӣ����:" << Heros[HeroChoice - 1].Heroname << endl;
	MyChoice[2] = HeroChoice;  //��ѡ�ĵ�����Ӣ��
	MyChoice[0]--;  //��Ϊ��ѡӢ�������1��15����������0��14�����Է�Ӧ������Ļ���Ҫ�Լ�1
	MyChoice[1]--;
	MyChoice[2]--;
	/*������ѡ�������Ӣ�۵ļ�����*/
	int MyHero[3][3] = {
		Heros[MyChoice[0]].Skill[0],Heros[MyChoice[0]].Skill[1], Heros[MyChoice[0]].Skill[2],
		Heros[MyChoice[1]].Skill[0],Heros[MyChoice[1]].Skill[1], Heros[MyChoice[1]].Skill[2],
		Heros[MyChoice[2]].Skill[0],Heros[MyChoice[2]].Skill[1], Heros[MyChoice[2]].Skill[2] };
	cout << "---------------------------" << endl;
	cout << "����ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	cout << Heros[MyChoice[0]].Heroname << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	cout << Heros[MyChoice[1]].Heroname << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	cout << Heros[MyChoice[2]].Heroname << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	Fighting << "����ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	Fighting << Heros[MyChoice[0]].Heroname << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
	Fighting << Heros[MyChoice[1]].Heroname << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
	Fighting << Heros[MyChoice[2]].Heroname << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
	YouChoice[0] = rand() % HeroNum;   //�Է���ѡ��һ��Ӣ�ۣ�û���ƣ�ȡ0��15���ڵ����������
	do   //�Է���ѡ�ڶ���Ӣ�ۣ�Ҫ�����һ��Ӣ���ظ���ȡ0��15���ڵ������
	{
		YouChoice[1] = rand() % HeroNum;
	} while (YouChoice[1] == YouChoice[0]);
	do   //�Է���ѡ�ڶ���Ӣ�ۣ�Ҫ�����һ������Ӣ���ظ���ȡ0��15���ڵ������
	{
		YouChoice[2] = rand() % HeroNum;
	} while (YouChoice[2] == YouChoice[0] || YouChoice[2] == YouChoice[1]);
	/*�Է���ѡ�������Ӣ�۵ļ�����*/
	int YouHero[3][3] = { 
		Heros[YouChoice[0]].Skill[0],Heros[YouChoice[0]].Skill[1], Heros[YouChoice[0]].Skill[2],
		Heros[YouChoice[1]].Skill[0],Heros[YouChoice[1]].Skill[1], Heros[YouChoice[1]].Skill[2],
		Heros[YouChoice[2]].Skill[0],Heros[YouChoice[2]].Skill[1], Heros[YouChoice[2]].Skill[2] };
	cout << "---------------------------" << endl;
	cout << "�Է�ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	cout << Heros[YouChoice[0]].Heroname << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	cout << Heros[YouChoice[1]].Heroname << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	cout << Heros[YouChoice[2]].Heroname << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	cout << "---------------------------" << endl;
	Fighting << "---------------------------" << endl;
	Fighting << "�Է�ѡ�������Ӣ�۷ֱ��ǣ�" << endl;
	Fighting << Heros[YouChoice[0]].Heroname << "(" << YouHero[0][0] << "," << YouHero[0][1] << "," << YouHero[0][2] << ")" << endl;
	Fighting << Heros[YouChoice[1]].Heroname << "(" << YouHero[1][0] << "," << YouHero[1][1] << "," << YouHero[1][2] << ")" << endl;
	Fighting << Heros[YouChoice[2]].Heroname << "(" << YouHero[2][0] << "," << YouHero[2][1] << "," << YouHero[2][2] << ")" << endl;
	Fighting << "---------------------------" << endl;
	cout << "���س�����ʼ������Ϸ��" << endl;
	getchar();   //����ͣ����
	getchar();


	int My_Win = 0, You_Win = 0;   //�ҷ�ʤ������Է�ʤ������ʼ��Ϊ0

	for (int round = 1; round <= 9; round++)   //һ���Ÿ��غ�
	{
		bool Winner = false;   //���ҷ�ʤ�����޸�Ϊtrue��ͨ����bool�������ж�ʤ��������ֻ���ж��ҷ�ʤ�����������ٴ�������
		int You_Hero_On, You_Skill_On;  //�Է��������Ӣ�ۼ�����
		int My_Hero_On, My_Skill_On;   //�ҷ��������Ӣ�ۼ�����
		string SkillName[3] = { "����","ʯͷ","��" };    //������ö�ٵĹ��ܣ�
		cout << "��" << round << "�غϣ�" << endl;    //�������Ļ
		Fighting << "��" << round << "�غϣ�" << endl;   //������ļ���¼������Ҳ��һ������
		do   //�Է�ȥһ��3���ڵ����������ϳ�һ��Ӣ�ۣ�Ҫ��������ȫΪ0
		{
			You_Hero_On = rand() % 3;
		} while (YouHero[You_Hero_On][0] + YouHero[You_Hero_On][1] + YouHero[You_Hero_On][2] == 0);
		do   //�Է��ϳ�Ӣ���������һ�����ܣ�Ҫ��ü�������Ϊ0
		{
			You_Skill_On = rand() % 3;
		} while (YouHero[You_Hero_On][You_Skill_On] == 0);
		YouHero[You_Hero_On][You_Skill_On]--;   //�ϳ��ĸ�Ӣ�����õļ���ʣ����-1
		cout << "�Է�ѡ��Ӣ��" << Heros[YouChoice[You_Hero_On]].Heroname << "��ս,����" << SkillName[You_Skill_On] << endl;
		Fighting << "�Է�ѡ��Ӣ��" << Heros[YouChoice[You_Hero_On]].Heroname << "��ս,����" << SkillName[You_Skill_On] << endl;
		cout << "��ѡ���սӢ�ۣ�ͨ��Ӣ�����ѡ�񣩣�" << endl;
		cout << "1��" << Heros[MyChoice[0]].Heroname << "(" << MyHero[0][0] << "," << MyHero[0][1] << "," << MyHero[0][2] << ")" << endl;
		cout << "2��" << Heros[MyChoice[1]].Heroname << "(" << MyHero[1][0] << "," << MyHero[1][1] << "," << MyHero[1][2] << ")" << endl;
		cout << "3��" << Heros[MyChoice[2]].Heroname << "(" << MyHero[2][0] << "," << MyHero[2][1] << "," << MyHero[2][2] << ")" << endl;
		do  //�ֶ�ѡ���ϳ�Ӣ�ۣ�Ҫȥ1��3�Ҽ�������ȫΪ0
		{
			cin >> My_Hero_On;   
			My_Hero_On--;       //��Ϊ�����±�Ϊ0��1��2�����û�ѡ��Ϊ1��2��3������Ҫ��Ӧ�û�ѡ�����-1�ٽ����ж�
			if (My_Hero_On < 0 || My_Hero_On>2)
				cout << "���1��3�м�ѡ��һ����ų�ս" << endl;
			if (MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0)
				cout << "����ѡ���Ӣ��" << Heros[MyChoice[My_Hero_On]].Heroname << "�Ѿ�û�м��ܿ�����!" << endl;
		} while ((My_Hero_On < 0 || My_Hero_On>2) || MyHero[My_Hero_On][0] + MyHero[My_Hero_On][1] + MyHero[My_Hero_On][2] == 0);
		do  //��Ӣ��������У�Ҫ����ʣ������Ϊ0
		{
			My_Skill_On = rand() % 3;
		} while (MyHero[My_Hero_On][My_Skill_On] == 0);
		MyHero[My_Hero_On][My_Skill_On]--;   //�ϳ�Ӣ�۵ļ�����-1
		cout << "��ѡ����Ӣ��" << Heros[MyChoice[My_Hero_On]].Heroname << "��ս����Ӣ�۳���" << SkillName[My_Skill_On] << endl;
		Fighting << "��ѡ����Ӣ��" << Heros[MyChoice[My_Hero_On]].Heroname << "��ս����Ӣ�۳���" << SkillName[My_Skill_On] << endl;
		if (My_Skill_On == 0 && You_Skill_On == 2)Winner = true;//�Ҽ����㲼����ʤ
		else if (My_Skill_On == 1 && You_Skill_On == 0)Winner = true;//��ʯͷ���������ʤ
		else if (My_Skill_On == 2 && You_Skill_On == 1)Winner = true;//�Ҳ���ʯͷ����ʤ
		else Winner = false;  //��ʵ��һ�п���ʡ����Ϊ��ʼ����Ϊfalse
		if (Winner)   //����ҷ�ʤ��
		{
			My_Win++;   //�ҷ�ʤ����+1
			Heros[MyChoice[My_Hero_On]].HeroWinRounds++;   //�ҷ��ϳ�Ӣ�۵�ʤ����+1
			Users[MyUserIndex].UserWinRounds++;    //���ʤ��+1
			cout << "��" << round << "�غϽ������ҷ�ʤ����" << endl;
			Fighting << "��" << round << "�غϽ������ҷ�ʤ����" << endl;
		}
		else   //����Է�ʤ��
		{
			You_Win++;   //�Է�ʤ����+1
			cout << "��" << round << "�غϽ������Է�ʤ����" << endl;
			Fighting << "��" << round << "�غϽ������Է�ʤ����" << endl;
		}
		Heros[MyChoice[My_Hero_On]].HeroAllRounds++;   //������Ӯ���ϳ�Ӣ���ܳ���+1
		system("pause");   //��ͣһ�£������
		cout << endl;
		Fighting << "------------------------" << endl;
	}
	cout << endl;
	cout << "��Ϸ����!������Ϸ���ҷ�ʤ��" << My_Win << "�غϣ��Է�ʤ��" << You_Win << "�غ�" << endl;
	Fighting << "��Ϸ����!������Ϸ���ҷ�ʤ��" << My_Win << "�غϣ��Է�ʤ��" << You_Win << "�غ�" << endl;
	Fighting.close();   //�����˼ǵù��ļ�
	if (My_Win > You_Win)cout << "������Ϸ�ҷ�ʤ��!" << endl;
	else cout << "������Ϸ�Է�ʤ��!" << endl;   //��Ϊû��ƽ�ֵ������������Ӯ������Ӯ
	cout << endl;

	ofstream Update_Hero("HeroAndSkill.txt",ios::trunc);   //����Ӣ���ܳ�����ʤ����
	ofstream Update_User("UserAndPass.txt", ios::trunc);   //�������ʤ����
	if (!Update_Hero.is_open())
	{
		cout << "�ļ�HerrAndSkill�򿪳���" << endl;
		exit(1);
	}
	if (!Update_User.is_open())
	{
		cout << "�ļ�UserAndPass�򿪳���" << endl;
		exit(1);
	}
	for (int i = 0; i < HeroNum; i++)
		Update_Hero << Heros[i].Heroname << "|" << Heros[i].Skill[0] << "|" << Heros[i].Skill[1] << "|" << Heros[i].Skill[2] << "|" << Heros[i].HeroAllRounds << "|" << Heros[i].HeroWinRounds << "|" << endl;
	for (int i = 0; Users[i].Username != ""; i++)
		Update_User << Users[i].Username << "|" << Users[i].Password << "|" << Users[i].UserWinRounds << "|" << endl;
	Update_Hero.close();   //�ǵù��ļ���
	Update_User.close();   //�������һ����
	system("pause");
}

void PlayerRank()
{
	cout << "����\t�û���\tʤ����" << endl;
	int index = 0;   //�ṹ�������±�
	for (index; Users[index].Username != ""; index++);  //�ó���ǰ�û���Ŀ
	int Win_Rounds[UserNum];   //����һ����ʱ������ʱ���һ�����ʤ����
	for (int i = 0; i < index; i++)   //�Ȱ�ʤ������ֵ����ʱ������ȥ
		Win_Rounds[i] = Users[i].UserWinRounds;
	for (int i = 0; i < index; i++)   //����
	{
		int big = Win_Rounds[0];
		int bigindex = 0;
		for (int j = 0; j < index; j++)  
		{
			if (Win_Rounds[j] > big)  //�ҳ����ֵ���޸ĵ�ǰ���ֵ
			{
				big = Win_Rounds[j];
				bigindex = j;
			}
		}
		Win_Rounds[bigindex] = -1;   //����ʱ����������ֵ��Ϊ-1�����ֵ�Ͳ�������Ϊ���ֵ
		cout << i + 1 << "��\t" << Users[bigindex].Username << "\t" << Users[bigindex].UserWinRounds << endl;  //����ÿ�α����õ����ֵ�����±�ȷ���ṹ�������ʤ�������ֵ�Ľṹ��λ��
	}
	system("pause");
	system("cls");
}

void HeroRank()   //�����������а����һģһ�����Ͳ�׸����
{
	cout << "����\t\tӢ��\t\t�ܳ���\t\tʤ��\t\tʤ��" << endl;
	for (int i = 0; i < HeroNum; i++)   //ֻ����Ҫע��һ����ʤ��
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
		cout.width(16);//ǿ�н������Ϊ�����Ʊ����ô��������룬����ֱ����"\t"�Ļ�������ĳЩӢ������ռ���������Ʊ���������޷�����
		cout.setf(ios::left);//����뷽ʽ
		cout << i + 1;
		cout.width(16);
		cout << Heros[bigindex].Heroname ;
		cout.width(16);
		cout << Heros[bigindex].HeroAllRounds;
		cout.width(16);
		cout << Heros[bigindex].HeroWinRounds;
		cout << Heros[bigindex].HeroWinRatio * 100 << "%" << endl;
//		cout << i + 1 << "��\t\t" << Heros[bigindex].Heroname << "\t\t" << Heros[bigindex].HeroAllRounds << "\t\t" << Heros[bigindex].HeroWinRounds << "\t\t" << Heros[bigindex].HeroWinRatio * 100 << "%" << endl;
	}
	system("pause");
	system("cls");
}