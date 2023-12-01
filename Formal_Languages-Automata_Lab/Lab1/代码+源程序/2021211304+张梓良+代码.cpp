#include <bits/stdc++.h>
using namespace std;
const int MAX = 99;
int cnt = 0; // ��¼״̬��Ŀ

vector<vector<vector<int>>> Q1; // ״̬ת�ƺ���
set<int> isfinal1;              // ��ֹ״̬����

typedef struct
{
    int from;  // ��ǰ״̬
    int to[2]; // 0ת�ƺ��״̬ 1ת�ƺ��״̬
} shift;       // ״̬ת����Ϣ

vector<shift> Q2; // DFA״̬ת�ƺ���

typedef struct
{
    vector<int> State;
    int number;
} Stateset;

queue<int> Queue;           // ת��ʱ�õ��Ķ��У��洢״̬��״̬��StateList���±�
vector<Stateset> StateList; // DFA��״̬��ÿ��Ԫ�ش���һ��DFA�е�һ��״̬  number��״̬��ţ�һά����State���״̬��Ӧ�����NFA���״̬
set<int> isfinal2;          // DFA����̬��

void input() // ����NFA
{
    string s; // ����ÿһ�е��ַ���
    vector<vector<int>> temp1;
    vector<int> temp2;
    getline(cin, s); // �����һ��
    while (getline(cin, s))
    {
        temp1.clear();
        temp2.clear();
        if (s.find('e') != string::npos)
            isfinal1.insert(cnt);
        int loc = s.find(']') + 1; // �����￪ʼѰ��״̬
        while (loc < s.size())
        {
            int num = 0;       // ״̬���
            if (s[loc] == ']') // ����һ�����
            {
                temp1.push_back(temp2);
                temp2.clear();
            }
            else if (isdigit(s[loc])) // �������
            {
                for (loc; isdigit(s[loc]); loc++)
                    num = num * 10 + (int)(s[loc] - '0');
                temp2.push_back(num);
                loc--; // *����һλ
            }
            else if (s[loc] == 'N') // ������
            {
                temp2.push_back(-1);
                temp1.push_back(temp2);
                temp2.clear();
            }
            loc++;
        }
        Q1.push_back(temp1);
        cnt++;
    }
}

void output(vector<shift> Q2) // ���DFA
{
    cout << "\t\t0\t1" << endl;
    cout << "(s)q0\tq" << Q2[0].to[0] << "\tq" << Q2[0].to[1] << endl;
    for (int i = 1; i < Q2.size(); i++)
    {
        if (isfinal2.count(Q2[i].from)) // �ж��Ƿ�����ֹ״̬
            cout << "(e)";
        cout << "q" << Q2[i].from << "\t";
        if (Q2[i].to[0] == -1) // �ж��Ƿ��ǿ�
            cout << "N"
                 << "\t";
        else
            cout << "q" << Q2[i].to[0] << "\t";
        if (Q2[i].to[1] == -1) // �ж��Ƿ��ǿ�
            cout << "N" << endl;
        else
            cout << "q" << Q2[i].to[1] << endl;
    }
}

void transfer() // ת��
{
    int newnumber = Q1.size(); // �����

    Stateset temp1;
    temp1.State.push_back(0);
    temp1.number = 0;
    StateList.push_back(temp1);
    Queue.push(StateList.size() - 1); // ����DFA�ĳ�ʼ״̬q0 ��DFA״̬��Ͷ���

    while (Queue.size() != 0) // �����зǿ�
    {
        temp1 = StateList[Queue.front()];   // ȡ��ͷԪ��temp1;
        shift temp3 = {temp1.number, 0, 0}; // ��������Ӧת�Ʊ�temp3

        // ��0ת�ƺ�1ת�ƣ���temp1�а�����ÿһ��NFA�е�״̬����ת�����õ�ת�ƺ��״̬��
        for (int j = 0; j <= 1; j++) // j=0,0ת�ƣ� j=1,1ת�ƣ�
        {
            vector<int> State;
            State.clear();                               // �洢jת����õ�״̬������ʱ����
            for (int i = 0; i < temp1.State.size(); i++) // ���DFA��״̬temp1�����ĸ���NFA�е�״̬
            {
                if (Q1[temp1.State[i]][j][0] != -1) // ���temp1������״̬�ǿ�
                {
                    // ���ظ��ؼ���ת������NFA�е�״̬
                    for (int k = 0; k < Q1[temp1.State[i]][j].size(); k++)
                    {
                        if (!count(State.begin(), State.end(), Q1[temp1.State[i]][j][k]))
                            State.push_back(Q1[temp1.State[i]][j][k]);
                    }
                }
            }

            if (!State.size())
                temp3.to[j] = -1; // ���ת����״̬��Ϊ�գ���-1����
            else                  // ���ǿ�
            {
                sort(State.begin(), State.end()); // ״̬�����򣬱���֮��ıȽ�
                // ����״̬���Ƿ����³��ֵ����
                int flag = -1;
                for (int k = 0; k < StateList.size(); k++)
                {
                    if (State == StateList[k].State)
                    {
                        flag = k;
                        break;
                    }
                }
                Stateset temp2; // �洢����״̬����ʱ����
                if (flag == -1) // ������״̬
                {

                    temp2.State = State;
                    if (State.size() == 1)
                        temp2.number = State[0];
                    else
                        temp2.number = newnumber++; // ����״̬����ţ����Ǻ����NFA�е�״̬��ʹ���±�ţ�����ʹ�ö�ӦNFA��ţ� �� ��Ӧ��NFA״̬��

                    // �����״̬�Ƿ�Ϊ�ս�״̬ ���� ��isfinal2����
                    for (int j = 0; j < temp2.State.size(); j++)
                    {
                        if (isfinal1.count(temp2.State[j]) != 0)
                        {
                            isfinal2.insert(temp2.number);
                        }
                    }

                    // ����״̬��DFA״̬��͹�������
                    StateList.push_back(temp2);
                    Queue.push(StateList.size() - 1);
                }
                else
                    temp2.number = StateList[flag].number; // ��������״̬�� ����Ϊ��Ӧ����״̬���

                temp3.to[j] = temp2.number; // ���뷢��jת���ı��
            }
        }
        Q2.push_back(temp3); // ������ת����Ϣ����Q2
        Queue.pop();         // ɾ����ͷԪ��
    }
}

int compare(shift a, shift b)
{
    return a.from < b.from;
} // ����ʱ�õ��ıȽϺ���

int main()
{
    input();
    transfer();
    sort(Q2.begin(), Q2.end(), compare); // ת�ƺ�����Ŀ����״̬�������
    output(Q2);
    system("pause");
    return 0;
}
