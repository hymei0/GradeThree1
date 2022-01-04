#include <iostream>
#include <string>
using namespace std;

const int bra = 9;
const int sign = 2;
const int ty_id = 2;
const int one_op = 9;
const int two_op = 9;
const int key = 12;
const int ty = 5;
const int com = 4;

char Bracket_group[] = { '(', ')', '{', '}', '[', ']', ';', ',', '"' };//���ż�
char Sign_group[] = { '+', '-' };//����������
char Typeidentify_group[] = { '%', '&' };//�������ͱ�ʶ����%d,&c)
char oneOPT_group[] = { '+', '-', '*', '/', '%', '&', '>', '<', '=' };//�����������
string twoOPT_group[] = { "+=", "-=", "*=", "/=", "<=", ">=", "==","++", "--" };//˫���������
string Keyword_group[] = { "main",  "return","float", "if", "else", "do", "while", "for", "scanf", "printf", "sqrt", "abs" };
//�ؼ��ּ�
string Type_group[] = { "int", "double", "short", "char", "void" };//���ͼ�
string Comment_group[] = { "/*", "*", "*/", "//" };//ע�ͼ�
char underline = '_';//�»���
int line = 1;//�к�
string str;//��ǰ��������������е�ĳ���ַ����ַ���
string result;//�ʷ���������ַ���

bool isInGroup(char group[], int n, char ch) //�ж��Ƿ����ַ���
{
	bool judge = false;
	int i;
	for (i = 0;i < n;i++)
		if (group[i] == ch)
		{
			judge = true;
			break;
		}
	return judge;
}


bool isInGroup(string group[], int n, string str)//�ж��Ƿ����ַ�����
{

	bool judge = false;
	int i;
	for (i = 0; i < n; i++)
		if (str.compare(group[i]) == 0)
		{
			judge = true;
			break;
		}
	return judge;
}

//�Ƿ�����ĸ 
bool isChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	else
		return false;
}
// �Ƿ�������0-9
bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

bool start(char ch);
void digit(char ch);
void identity(char ch);
void type_identify(char ch);
void decimal(char ch);
bool Float(char ch);
void Operator(char ch);
void bracket(char ch);


bool start(char ch)
{
	if (isDigit(ch))//��ǰ�ַ�Ϊʮ���������ַ�
	{
		digit(ch);
		return true;
	}

	else if (isInGroup(oneOPT_group, one_op, ch))//��ǰ�ַ�Ϊ��Ŀ�����
	{
		Operator(ch);
		return true;
	}

	else if (isChar(ch) || ch == '_')//��ǰ�ַ��ܹ���Ӣ�Ĵʻ㣨ΪӢ����ĸ�����»��ߣ�
	{
		identity(ch);
		return true;
	}

	else if (isInGroup(Bracket_group, bra, ch))//��ǰ�ַ�Ϊ���ż����ַ�
	{
		bracket(ch);
		return true;
	}

	else if (ch == EOF)//��ǰ�ַ�Ϊ��������
	{
		cout << result;
		return true;
	}

	else //�ո������¶���һ���ַ�
	{
		ch = getchar();
		return start(ch);
	}
}


void digit(char ch) //�жϵ�ǰ�����ַ����ַ�������������С�������������ַ���ʲôʱ�������
{

	str += ch;
	ch = getchar();
	if (isDigit(ch))
		digit(ch);
	else if (ch == '.')
		decimal(ch);

	else
	{
		result += "line" + to_string(line) + ":(" + "integer" + ", " + str + ")\n";
		str = "";
		start(ch);
	}

}

void identity(char ch)
{
	str += ch;
	ch = getchar();
	if (isChar(ch) || ch == '_' || isDigit(ch))//��ǰ�ַ���Ӣ����ĸ���»��߻����֣���ʶ�����Ϊ���֣��ݹ�
		identity(ch);
	else //Ӣ���ַ���(��ɽ����֣���������������ʶ���ַ������д������ص���ʼ״̬
	{
		if (isInGroup(Keyword_group, key, str))
		{
			result += "line" + to_string(line) + ":(" + "keyword" + ", " + str + ")\n";
			str = "";
		}
		else if (isInGroup(Type_group, ty, str))
		{
			result += "line" + to_string(line) + ":(" + "type" + ", " + str + ")\n";
			str = "";
		}
		else
		{
			result += "line" + to_string(line) + ":(" + "identify" + ", " + str + ")\n";
			str = "";
		}
		start(ch);
	}

}

void type_identify(char ch) //��ǰ�ַ�Ϊ�������ͱ�ʶ�ַ������д�����ȡ��һ�ַ����ص���ʼ״̬
{
	str += ch;
	result += "line" + to_string(line) + ":(" + "typeidentify" + ", " + str + ")\n";
	str = "";
	ch = getchar();
	start(ch);
}

void decimal(char ch)//
{

	str += ch;
	ch = getchar();
	if (isDigit(ch))//��һ�ַ�Ϊ���֣���ݹ�ֱ��������������
		decimal(ch);
	else if (ch == 'e') //��һ�ַ�Ϊe����ת��float�����ݴ���
		Float(ch);
	else//�����������ص���ʼ״̬
	{
		result += "line" + to_string(line) + ":(" + "decimal" + ", " + str + ")\n";
		str = "";
		start(ch);
	}

}

bool Float(char ch)//
{

	str += ch;
	ch = getchar();
	if (isDigit(ch))//��ǰ�ַ�Ϊ���֣�����ָ������
		return Float(ch);

	else if (isInGroup(Sign_group, sign, ch))//ָ����������
	{
		str += ch;
		ch = getchar();
		if (isDigit(ch)) //�����ź�Ϊ���֣��ݹ����ָ������
			return Float(ch);
		else//�����ź������֣�����
		{
			str += ch;
			cout << "Error at Line " << line << ": Illegal floating point number \"" << str << "\".\n";
			return false;
		}
	}
	else//e�������ֻ�������
	{
		if (str.length() > 0 && str[str.length() - 1] == 'e')//e��ָ���������һ���ַ�������
		{
			cout << "Error at Line " << line << ": Illegal floating point number \"" << str << "\".\n";
			return false;
		}
		result += "line" + to_string(line) + ":(" + "float" + ", " + str + ")\n";
		str = ""; //float��������ȷ��������������float����
		return start(ch);//�ص���ʼ״̬
	}

}

void Operator(char ch)
{

	str += ch;
	ch = getchar();
	if (isDigit(ch)) //��ǰ�ַ�Ϊ�����ַ����������������������Ӧ���������������ַ��Ĵ���ģ��
	{
		result += "line" + to_string(line) + ":(" + "OPT" + ", " + str + ")\n";
		str = "";
		digit(ch);
	}

	else if (isInGroup(oneOPT_group, one_op, ch) && isInGroup(twoOPT_group, two_op, str + ch))
		//��ǰ�ַ�Ϊ˫Ŀ��������������������������������һ���ַ������ص���ʼ����״̬
	{
		str += ch;
		result += "line" + to_string(line) + ":(" + "OPT" + ", " + str + ")\n";
		str = "";
		ch = getchar();
		start(ch);
	}

	else if (isChar(ch))//��ǰ�ַ�ΪӢ����ĸ����ת��������ʶ����%d &c��ʽ��
	{
		type_identify(ch);
	}

	else if (isInGroup(oneOPT_group, one_op, ch) && isInGroup(Comment_group, com, str + ch))
		//ע�ͼ�
	{
		do
		{
			ch = getchar();
		} while (ch != '\n');
		line++;
		str = "";
		ch = getchar();
		start(ch);
	}

	else//������Ž��� ������Ӧ���ż����ص���ʼ״̬
	{
		result += "line" + to_string(line) + ":(" + "OPT" + ", " + str + ")\n";
		str = "";
		start(ch);
	}

}

void bracket(char ch) //��ǰ�ַ�Ϊ��ͨ����
{
	str += ch;
	ch = getchar();
	result += "line" + to_string(line) + ":(" + "bracket" + ", " + str + ")\n";
	str = "";
	if (ch == '\n') //������������� 
		line++;
	start(ch);
}

int main()
{
	char ch;
	ch = getchar();
	start(ch);
	return 0;
}

