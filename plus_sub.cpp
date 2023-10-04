#include<string>
#include"data.h"
#include"trans_comp.h"
#include"plus_sub.h"
#include"scan_print.h"
using namespace std;

//�Ӽ������̺���
void plus_sub(bool& minus, string& s1, string& s2, hpnum& a, char& sign)
{
    NUM* head1 = NULL, * head2 = NULL;        //��������

    strfixplus_sub(s1, s2, a);
    if ((judge(s1, s2, minus, sign, head1, head2)) == '+')
        Plus(head1, head2, a);
    else
        Sub(head1, head2, a);

    printhp(a, minus);
}

//�ж��������ͣ��Ǽӻ���������ء�-����+����˳������ַ����������ת�����Լ������ŵ��ж�
char judge(string& s1, string& s2, bool& minus, char& sign, NUM*& head1 , NUM*& head2 )
{
    char s1sign, s2sign, op;  //ǰ���߼�¼����������ĩ��Ϊ�������
    
    if (s1[0] == '-')                       
    { 
        s1sign = '-';
        s1 = s1.substr(1); 
    }
    else s1sign = '+';

    if (s2[0] == '-') 
    { 
        s2sign = '-';
        s2 = s2.substr(1); 
    }
    else s2sign = '+';

    op = (sign ^ s1sign ^ s2sign);   //λ���������
    
    if (strcom(s1, s2))             //ǰ��С�ں���
    {
        str2lian(s2, head1);
        str2lian(s1, head2);
        minus = (sign^s2sign);          //ͬ+��-
    }
    else
    {
        str2lian(s1, head1);
        str2lian(s2, head2);
        minus = (s1sign == '-');        //��ǰ������һ��
    }

    return op;
}

//�Ӽ����ַ�����������
void strfixplus_sub(string& s1, string& s2, hpnum& a)
{
    unsigned lentemp, len1f, len2f;

    if ((lentemp = s1.find('.')) == s1.npos) { len1f = 0; }
    else { len1f = s1.size() - lentemp - 1; s1.erase(lentemp, 1); }
    if ((lentemp = s2.find('.')) == s2.npos) { len2f = 0; }
    else { len2f = s2.size() - lentemp - 1; s2.erase(lentemp, 1); }

    if (len1f < len2f)
    {
        s1.append(len2f - len1f, '0');
        a.lenf = len2f;
    }
    else
    {
        s2.append(len1f - len2f, '0');
        a.lenf = len1f;
    }

    unsigned j = s1.size(), i = s2.size();                                    //delete ','
    while (j--) { if (s1[j] == ',') s1.erase(j, 1); }
    while (i--) { if (s2[i] == ',') s2.erase(i, 1); }
}

//�ӷ���������ģ��
void Plus(NUM* head1, NUM* head2, hpnum& a)
{
    int i = 1;
    for (; head1; head1 = head1->next, ++i)
    {
        if (head2)
        {
            a.c[i] += head1->num + head2->num;
            a.c[i + 1] += a.c[i] / 10;   //s2���ڵ�ʱ��
            a.c[i] %= 10;
            head2 = head2->next;
        }
        else                     //s2�ѱ�����
        {
            a.c[i] += head1->num;
            a.c[i + 1] += a.c[i] / 10;
            a.c[i] %= 10;
        }
    }

    a.len = i;
}

//������������ģ��
void Sub(NUM* head1, NUM* head2, hpnum& a)
{
    int i = 1;
    for (; head1; head1 = head1->next, ++i)
    {
        if (head2)
        {
            a.c[i] += head1->num - head2->num;
            if (a.c[i] < 0)
            {
                a.c[i + 1] -= 1;
                a.c[i] += 10;
            }
            head2 = head2->next;
        }

        else                     //s2�ѱ�����
        {
            a.c[i] += head1->num;
            a.c[i + 1] += a.c[i] / 10;
            a.c[i] %= 10;
            if (a.c[i] < 0)
            {
                a.c[i + 1] -= 1;
                a.c[i] += 10;
            }
        }
    }

    a.len = i;
}