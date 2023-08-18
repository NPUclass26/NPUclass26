#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include<bits/stdc++.h>
using namespace std;
int n; // 颜文字的个数
int m; // 聊天记录的行数
//------------BLOCK 1----------------
// 请根据题目需要 补全User类的定义 包括属性与构造函数、输出函数
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
// createEmotionMap函数只考察map的使用，不考察字符串的处理
// 请根据题目需要 补全createEmotionMap函数
map<string, double> createEmotionMap() {
    map<string, double> emotionMap;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string emoticon; // 颜文字
        double factor; // 情感因子
        string line;
        
        getline(cin, line);
        // 读取一行输入，分割为颜文字和情感因子两部分,分隔符为逗号
        emoticon = line.substr(0, line.find(','));
        factor = stod(line.substr(line.find(',') + 1));
//------请实现：将颜文字和情感因子存入map中-------------        
        emotionMap.insert(pair<string,double>(emoticon,factor));
    }
    return emotionMap; // 返回map对象
}
//----------------BLOCK 3------------------
// analyzeChat函数中，你需要完成字符串的解析，并构建User对象，存入vector中
// 请根据题目需要 补全analyzeChat函数
vector<User> analyzeChat(map<string, double> &emotionMap) {
    vector<User> users; // 创建空的vector
    // 创建一个辅助的map，用于存储每个用户的发言次数和情感总和
    map<string, pair<int, double> > userMap;
    for (int i = 0; i < m; i++) {
        //-----------------请实现：字符串的解析与userMap的构建----------------
		string line,name,emoticon;
		getline(cin,line);
		name = line.substr(0, line.find(':'));
        emoticon =line.substr(line.find(' ') + 1);
        userMap[name]=pair<int,double>(userMap[name].first+1,userMap[name].second+emotionMap[emoticon]);
    }
    // 遍历辅助map中的每个用户
    for (auto it : userMap) {
        // 计算该用户的情感平均值
        double sum = it.second.second;
        double count = it.second.first;
        double avg = sum / count;
        //cout<<"name is "<<it.first<<" count is "<<count<<" avg is "<<avg<<endl;
        //-----------------请实现：users的构建----------------
        User tmp;
        string name=it.first;
        tmp.init(name,sum,count,avg);
		users.push_back(tmp);
    }
    return users;// 返回vector对象
}
//----------------BLOCK 4------------------
// 请根据题目需要 补全compare函数
bool compare(User &a, User &b) { // 比较函数
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
