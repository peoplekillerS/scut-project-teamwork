#include<iostream>
#include"scan_print.h"
using namespace std;

//¼����������
void scangroup(int& T)
{
    cout << "�����������(��Ϊ����Ǹ�����): " << endl;
    cin >> T;
}

void scandata(char& sign, std::string& s1, std::string& s2)
{
    cout << "�����������ͣ���'+' , '-' , '*' �� '/')" << endl;
    cin >> sign;

    cout << "�������������������� ����������ÿո��������ɻ�������)" << endl;
    cin >> s1 >> s2;
}

//������
void printhp(hpnum a, bool minus)
{
    cout << "����Ϊ��" << endl;

    int i = a.len, j = 0;

    //ǰ����Ĵ���
    while (!a.c[i] && i > 0) --i;
    if (i == 0)
    {
        cout << 0 << endl;  return;
    }     //����ȫΪ�㣬����Ϊ��
    if (i <= a.lenf)
    {
        i = a.lenf + 1;
    }             //����ȫΪ��������������λ�ϵ�0

    //С��ĩβ��Ĵ���
    while (!a.c[j] && j <= a.lenf) ++j;

    if (minus)
    {
        cout << '-';
    }   //�Ƿ������-���ţ�����Ϊ������

    for (; i >= j; i--)
    {
        if (i > a.lenf)
        {
            cout << a.c[i];

            if ((i - a.lenf) % 3 == 1 && (i - a.lenf) != 1)
            {
                cout << ',';
            }       //ÿ��λ���������һ��������
        }
        else
        {
            if (i == a.lenf)
            {
                cout << '.';
            }       //���С����

            cout << a.c[i];
        }
    }

    cout << endl;
}