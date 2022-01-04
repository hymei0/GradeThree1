
#include <iostream>
#include <string>
//#include <vector>
#include <stack>

using namespace std;
int flag = 1;
stack<char>Vn;//存放非终结符的堆栈
stack<char>Vt;//存放输入串
void Procedure_E();//E子程序
void Procedure_e();//E`子程序
void Procedure_T();//T子程序
void Procedure_t();//T`子程序
void Procedure_F();//F子程序



void Procedure_F()
{
  
    if (Vt.top() == 'a')//匹配a
    {
        Vt.pop();
        Vn.pop();
    }
    else if (Vt.top() == '(')
    {
        Vn.pop();
        Vn.push(')');
        Vn.push('E');
        Vn.push('(');

        if (Vt.top() == Vn.top())//匹配（
        {
            Vt.pop();
            Vn.pop();
        }

        Procedure_E();

        if (Vt.top() == Vn.top())//匹配）
        {
            Vn.pop();
            Vt.pop();
        }

        else {
            //cout << "Error on syntax analysis" << endl;
            flag = 0;
            return ;
        }
            

    }
    else {
        //cout << "Error on syntax analysis" << endl;
        //cout << 2;
       
        flag = 0;
        return;
    }
        

}

void Procedure_T()
{
   
    if (Vn.top() == 'T')
    {
        if (Vt.top() == 'a' || Vt.top() == '(')
        {
            Vn.pop();
            Vn.push('t');
            Vn.push('F');
            Procedure_F();
            Procedure_t();
        }
        else
        {
            //cout << "Error on syntax analysis" << endl;
            //cout << 3;
           
            flag = 0;
            return;
        }
    }

}

void Procedure_t()
{
   
    Vn.pop();
    if (Vt.top() == '*')
    {
        Vt.pop();
        Vn.push('t');
        Vn.push('F');
        Procedure_F();
        Procedure_t();
    }
    else if (Vt.top() == '+' || Vt.top() == ')')
    {
      //  Vn.pop();
        //Vt.pop();
    }
    else if (Vt.top() == '#')
    {
        if (Vn.top() == '#')
        {
            //cout << "Syntax analysis is right" << endl;
            //return true;
            return;
            
        }
    }
    else
    {
        //cout << "Error on syntax analysis" << endl;
        //cout << 4;
        
        flag = 0;
        return;
    }
}


void Procedure_e()
{
    
    if (Vn.top() != Vt.top())
    {
        if (Vt.top() == '+')
        {
            Vt.pop();
            Vn.pop();
            Vn.push('e');
            Vn.push('T');
            //Vn.push('+');
            Procedure_T();
            Procedure_e();

        }
        else if (Vt.top() == ')' || Vt.top() == '#')
        {
            Vn.pop();
            //return;
            return;
        }
        else

        {
            //cout << "Error on syntax analysis" << endl;
            //cout << 5;
            
            flag = 0;
            return;
        }
    }
    else if (Vn.top() == '#'&& Vt.top() == '#')
    {
        /*cout << "Syntax analysis is right" << endl;
        return true;*/
        return;
    }
    else {
        flag = 0;
        return;
    }
}

void Procedure_E()
{
   
    if (Vn.top() != Vt.top())
    {
        if (Vt.top() == 'a' || Vt.top() == '(')
        {
            Vn.pop();
            Vn.push('e');
            Vn.push('T');
            Procedure_T();
            Procedure_e();   
        }
        else {
            //cout << "Error on syntax analysis" << endl;
            //cout << 6;
           
            flag = 0;
            return;
        }
            
            
    }
    else if(Vn.top() == Vt.top() && Vn.top() == '#')
    {
        
        /*cout << "Syntax analysis is right" << endl;
        return true;*/
        return;
    }
   
        
    else {
       // cout << "Error on syntax analysis" << endl;
        //cout << 7;
        
        flag = 0;
        return;
    }
        
}

int main()
{
    string sentence;
    cin >> sentence;
    int n;
    n = sentence.length();
    Vt.push('#');
    Vn.push('#');
    Vn.push('E');
    for (int i = n-1; i >=0; i--)
        Vt.push(sentence[i]);
    Procedure_E();
   
    if (Vn.top() == '#')
    {
        if (Vt.top() != '#')
            flag = 0;
    }
    //cout << flag << endl;
    if (flag==1) {
       
        cout << "Syntax analysis is right" << endl;
    }
    else if(flag==0){
        cout << "Error on syntax analysis" << endl;
    }
   /* vector<char>arr(n);
   for (int i = 0; i < n; i++)
        arr[i] = sentence[i];
    for (int i = 0; i < n; i++)
        cout <<arr[i]<<endl;
    cout << arr.size() << endl;*/
    
}


