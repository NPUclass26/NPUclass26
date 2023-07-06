#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include<bits/stdc++.h>
using namespace std;
int n; // �����ֵĸ���
int m; // �����¼������
//------------BLOCK 1----------------
// �������Ŀ��Ҫ ��ȫUser��Ķ��� ���������빹�캯�����������
class User {
	private:
		double sum;double count;	
	public:
		double avg;string name;
		void init(string str,int x,int y,double z)
		{
			this->name=str;
			this->sum=x;this->count=y;this->avg=z;
		}
		void print()
		{
			cout<<this->name<<' ';
		}
};
//------------BLOCK 2-----------------
// createEmotionMap����ֻ����map��ʹ�ã��������ַ����Ĵ���
// �������Ŀ��Ҫ ��ȫcreateEmotionMap����
map<string, double> createEmotionMap() {
    map<string, double> emotionMap;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string emoticon; // ������
        double factor; // �������
        string line;
        
        getline(cin, line);
        // ��ȡһ�����룬�ָ�Ϊ�����ֺ��������������,�ָ���Ϊ����
        emoticon = line.substr(0, line.find(','));
        factor = stod(line.substr(line.find(',') + 1));
//------��ʵ�֣��������ֺ�������Ӵ���map��-------------        
        emotionMap.insert(pair<string,double>(emoticon,factor));
    }
    return emotionMap; // ����map����
}
//----------------BLOCK 3------------------
// analyzeChat�����У�����Ҫ����ַ����Ľ�����������User���󣬴���vector��
// �������Ŀ��Ҫ ��ȫanalyzeChat����
vector<User> analyzeChat(map<string, double> &emotionMap) {
    vector<User> users; // �����յ�vector
    // ����һ��������map�����ڴ洢ÿ���û��ķ��Դ���������ܺ�
    map<string, pair<int, double> > userMap;
    for (int i = 0; i < m; i++) {
        //-----------------��ʵ�֣��ַ����Ľ�����userMap�Ĺ���----------------
		string line,name,emoticon;
		getline(cin,line);
		name = line.substr(0, line.find(':'));
        emoticon =line.substr(line.find(' ') + 1);
        userMap[name]=pair<int,double>(userMap[name].first+1,userMap[name].second+emotionMap[emoticon]);
    }
    // ��������map�е�ÿ���û�
    for (auto it : userMap) {
        // ������û������ƽ��ֵ
        double sum = it.second.second;
        double count = it.second.first;
        double avg = sum / count;
        //cout<<"name is "<<it.first<<" count is "<<count<<" avg is "<<avg<<endl;
        //-----------------��ʵ�֣�users�Ĺ���----------------
        User tmp;
        string name=it.first;
        tmp.init(name,sum,count,avg);
		users.push_back(tmp);
    }
    return users;// ����vector����
}
//----------------BLOCK 4------------------
// �������Ŀ��Ҫ ��ȫcompare����
bool compare(User &a, User &b) { // �ȽϺ���
   if(a.avg==b.avg) return a.name<b.name;
   return a.avg<b.avg;
}
int main(){
    cin>>n>>m;
    map<string, double> emotionMap = createEmotionMap();
    vector<User> users = analyzeChat(emotionMap);
    sort(users.begin(), users.end(), compare);
    for (auto it : users) it.print();
    return 0;
}
