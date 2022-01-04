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

char Bracket_group[] = { '(', ')', '{', '}', '[', ']', ';', ',', '"' };//符号集
char Sign_group[] = { '+', '-' };//正负号设置
char Typeidentify_group[] = { '%', '&' };//引导类型标识集（%d,&c)
char oneOPT_group[] = { '+', '-', '*', '/', '%', '&', '>', '<', '=' };//单个运算符集
string twoOPT_group[] = { "+=", "-=", "*=", "/=", "<=", ">=", "==","++", "--" };//双个运算符集
string Keyword_group[] = { "main",  "return","float", "if", "else", "do", "while", "for", "scanf", "printf", "sqrt", "abs" };
//关键字集
string Type_group[] = { "int", "double", "short", "char", "void" };//类型集
string Comment_group[] = { "/*", "*", "*/", "//" };//注释集
char underline = '_';//下划线
int line = 1;//行号
string str;//当前读入的输入内容中的某个字符或字符串
string result;//词法分析结果字符串

bool isInGroup(char group[], int n, char ch) //判断是否在字符集
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


bool isInGroup(string group[], int n, string str)//判断是否在字符串集
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

//是否是字母 
bool isChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	else
		return false;
}
// 是否是数字0-9
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
	if (isDigit(ch))//当前字符为十进制数字字符
	{
		digit(ch);
		return true;
	}

	else if (isInGroup(oneOPT_group, one_op, ch))//当前字符为单目运算符
	{
		Operator(ch);
		return true;
	}

	else if (isChar(ch) || ch == '_')//当前字符能构成英文词汇（为英文字母或者下划线）
	{
		identity(ch);
		return true;
	}

	else if (isInGroup(Bracket_group, bra, ch))//当前字符为符号集内字符
	{
		bracket(ch);
		return true;
	}

	else if (ch == EOF)//当前字符为结束操作
	{
		cout << result;
		return true;
	}

	else //空格处理，重新读下一个字符
	{
		ch = getchar();
		return start(ch);
	}
}


void digit(char ch) //判断当前数字字符或字符串是整数还是小数（包括数字字符串什么时候结束）
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
	if (isChar(ch) || ch == '_' || isDigit(ch))//当前字符是英文字母、下划线或数字（标识符后可为数字）递归
		identity(ch);
	else //英文字符串(后可接数字）结束，对整个标识符字符串进行处理，并回到开始状态
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

void type_identify(char ch) //当前字符为引导类型标识字符，进行处理，读取下一字符，回到开始状态
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
	if (isDigit(ch))//下一字符为数字，则递归直至读完整个分数
		decimal(ch);
	else if (ch == 'e') //下一字符为e，跳转至float型数据处理
		Float(ch);
	else//分数结束，回到开始状态
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
	if (isDigit(ch))//当前字符为数字，读完指数次数
		return Float(ch);

	else if (isInGroup(Sign_group, sign, ch))//指数的正负号
	{
		str += ch;
		ch = getchar();
		if (isDigit(ch)) //正负号后为数字，递归读完指数次数
			return Float(ch);
		else//正负号后不是数字，出错
		{
			str += ch;
			cout << "Error at Line " << line << ": Illegal floating point number \"" << str << "\".\n";
			return false;
		}
	}
	else//e后无数字或正负号
	{
		if (str.length() > 0 && str[str.length() - 1] == 'e')//e是指数串的最后一个字符，出错
		{
			cout << "Error at Line " << line << ": Illegal floating point number \"" << str << "\".\n";
			return false;
		}
		result += "line" + to_string(line) + ":(" + "float" + ", " + str + ")\n";
		str = ""; //float型数据正确，处理读完的整个float数据
		return start(ch);//回到开始状态
	}

}

void Operator(char ch)
{

	str += ch;
	ch = getchar();
	if (isDigit(ch)) //当前字符为数字字符，则运算符结束，进行相应处理，并跳到数字字符的处理模块
	{
		result += "line" + to_string(line) + ":(" + "OPT" + ", " + str + ")\n";
		str = "";
		digit(ch);
	}

	else if (isInGroup(oneOPT_group, one_op, ch) && isInGroup(twoOPT_group, two_op, str + ch))
		//当前字符为双目运算符，继续进行运算符处理，并读入下一个字符串，回到开始读入状态
	{
		str += ch;
		result += "line" + to_string(line) + ":(" + "OPT" + ", " + str + ")\n";
		str = "";
		ch = getchar();
		start(ch);
	}

	else if (isChar(ch))//当前字符为英文字母则跳转至引导标识符（%d &c形式）
	{
		type_identify(ch);
	}

	else if (isInGroup(oneOPT_group, one_op, ch) && isInGroup(Comment_group, com, str + ch))
		//注释集
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

	else//运算符号结束 处理相应符号集，回到开始状态
	{
		result += "line" + to_string(line) + ":(" + "OPT" + ", " + str + ")\n";
		str = "";
		start(ch);
	}

}

void bracket(char ch) //当前字符为普通符号
{
	str += ch;
	ch = getchar();
	result += "line" + to_string(line) + ":(" + "bracket" + ", " + str + ")\n";
	str = "";
	if (ch == '\n') //换行则行数相加 
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

