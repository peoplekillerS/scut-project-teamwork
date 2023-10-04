#include<string>
#include<iostream>
#include"scan_print.h"
#include"data.h"
#include"plus_sub.h"
#include"trans_comp.h"
#include"div.h"
using namespace std;

//�����������̺���
void divi(string& s1, string& s2, bool &minus, hpnum& a)
{
    strfixdiv(s1, s2, minus);
    if (s2 < "0000001") 
    { 
        cout << "ERROR" << endl;  
        return; 
    }    //������С������;

    Divi(s1, s2, a);

    sisewuru(a);
    printhp(a, minus);
}

//����ר�õ��ַ������κ���
void strfixdiv(string& s1, string& s2, bool& minus)
{
    if (s1[0] == '-') { minus = (s2[0] != '-'); s1 = s1.substr(1); }
    else if ((minus = (s2[0] == '-')))     s2 = s2.substr(1);       //�жϡ�-����������ͬʱȥ����-����

    unsigned i, j;

    if ((i = s2.find('.')) != s2.npos) 
    { 
        s2.erase(i, 1); 

        s1.append(s2.size() - i, '0');   // ������С��������(���㣩
    }   

    if ((j = s1.find('.')) != s1.npos)
    {
        s1.erase(j, 1);

        if ((i = (s1.size() - j)) >= 11)    
            s1.erase(j + 11);
        else 
            s1.append(11 - i, '0');
    }
    else s1.append(11, '0');                                        //�������γ����뱻���� 

    j = s1.size(), i = s2.size();                                    //delete ','
    while (j--) { if (s1[j] == ',') s1.erase(j, 1); }
    while (i--) { if (s2[i] == ',') s2.erase(i, 1); }
}

//�����������ģ��
void Divi(string &s1, string &s2, hpnum& a)
{
    const string chushu = s2.substr(s2.find_first_not_of('0'));  //��ȡ������ȥǰ���㣩
    
    string temp;                                                 //�½����ַ���
    NUM* headchushu = NULL;
    str2lian(chushu, headchushu);                                //������������

    a.len = s1.size();                                      //������ĩλ���뱻��������
    a.lenf = 11;                                            //�γ����Ҫ����10λС���������������������11λС��

    for (int i = a.len; i > 0; --i)
    {
        temp += s1[a.len - i];                               //���õ���������
        if (temp == "0")
        {
            temp.erase();                    //�м�������Ϊ�㣬��ɾȥ�ˡ�0����������λ�ϵ�����
            continue;
        }

        while (!strcom(temp, chushu))
        {
            hpnum b;
            NUM* head1 = NULL;
            str2lian(temp, head1);
            Sub(head1, headchushu, b);
            a.c[i]++;
            hp2str(b, temp);

            if (temp == "0") { temp.erase(); break; }        //�м����Ϊ��ʱ��ֹͣ��λ���ϵ�����
        }
    }
}

//��������ģ��
void sisewuru(hpnum& a)                
{
    int i = 2;
    int j = (a.c[1] + 5) / 10;
    a.c[1] = 0;

    while (j)
    {
        a.c[i] += 1;
        j = a.c[i] / 10;
        a.c[i] %= 10;
        i++;
    }

    a.len++;      //���������У�����λ����1�����
}