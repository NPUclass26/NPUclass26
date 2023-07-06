#include <iostream>
#include <vector>
#include <cmath>
#define Pi 3.1415926//宏定义Pi
using namespace std;
// 你可以将代码复制到电脑上阅读
// 答题区域会用“||||||”表示开始和结束，请注意识别
// 修改非答题区域代码将导致您零分
// 你可以在答题区域内创建任意形式、任意长度的代码
// 请注意代码的可读性和命名规范性
// 注释已经尽可能详细了，现实中的代码可不会有人这样细心的写注释的2333333

// ------                   BLOCK 1                    ------ //
// 此处为API声明区，可以帮助你快捷的了解该程序所使用的接口
// 你将需要调用其中的某些用于你编写的代码，请务必仔细阅读声明
// ------请注意，这不是作答区，修改此部分内容将直接导致您0分------ //

class Angle//角度类
{
private:
    double m_rad;
public:
    Angle();
    Angle(double rad);
    double getRadValue();//获取弧度制角度值
    operator double() const;//用于类型转换，可将角度类自动转换为double型
    //也就是说Angle类可以被直接当作double型数据使用
    Angle operator+(const Angle& another);
    Angle operator-(const Angle& another);
};

class obstacle//障碍物模型类
{
private:
    double m_relativeX;
    double m_relativeY;
    double m_fieldX;//预留的存放场地坐标X的数据成员
    double m_fieldY;//预留的存放场地坐标Y的数据成员
    bool m_field_able;//表示是否已经计算过场地坐标，未计算过为0，否则为1
public:
    obstacle(double x, double y);
    double getRelativeX();//获取障碍物相对机器人的X坐标
    double getRelativeY();//获取障碍物相对机器人的Y坐标
    double getDistance();//获取障碍物距机器人的距离
    void setFieldInfo(double field_x, double field_y, bool field_able);//->你需要用到的，设置场地坐标信息的函数
    double getFieldX();//获取障碍物的场地X坐标
    double getFieldY();//获取障碍物的场地Y坐标
};

class robot
{
private:
    double m_x;
    double m_y;
    Angle m_angle;
public:
    robot(double x, double y, Angle a);
    double getX();//获取机器人的X坐标值
    double getY();//获取机器人的Y坐标值
    Angle getAngle();//获取机器人的偏转角度
    vector<obstacle>obstacle_modules;//存放场地上的障碍物信息的集合
    void makeField();//->你需要完成的函数
    
};
// ------                 BLOCK 1 END                  ------ //


// ------                   BLOCK 2                    ------ //
// 此处为作答区，请按要求补全代码并复制《全部的程序》至OJ系统运行
// 
// 功能需求：当该函数被调用时，能逐一对obstacle_modules
// 容器中的元素进行操作，计算出它们的场地坐标并存储至每个obstacle
// 元素中预留好的m_fieldX和m_fieldY中，并修改m_field_able为真，
// 表示该障碍物的场地坐标已经完成了计算。
// 
// 总结下来就是：
// 1.转换vector容器内每个obstacle元素的相对坐标为场地坐标并存储
// 2.将m_field_able置为真，以表示场地坐标数据可用
// 3.通过调用上面提供的各种函数实现
void robot::makeField()
{
    //-----||||||答题区域开始||||||-----
    for (int i = 0; i < this->obstacle_modules.size(); i++)
	{
		obstacle tmp=obstacle_modules[i];
		double l=tmp.getDistance();
		double x=this->getX(),y=this->getY(),x1=tmp.getRelativeX(),y1=tmp.getRelativeY();
        Angle xita=this->getAngle(),fai;
        if(x1==0||y1==0)
        {
            if(!x1&&y1<0) fai=Pi*3/2.0;
            if(!x1&&y1>0) fai=Pi/2;
            if(x1>0&&!y1) fai=0;
            if(x1<0&&!y1) fai=Pi;
        }
        else 
        {
            fai=atan(y1/x1);
            if(x1<0) fai=(double)fai+Pi;
        }
        fai=fai+xita;
        double fx=x+l*cos(fai),fy=y+l*sin(fai);
        if(abs(fx-(long long)fx)<1e-7) fx=(long long)fx;
        if(abs(fy-(long long)fy)<1e-7) fy=(long long)fy;
        obstacle_modules[i].setFieldInfo(fx,fy,1);
	}
	
    //-----||||||答题区域结束||||||-----
}
// ------                 BLOCK 2 END                  ------ //


// ------                   BLOCK 3                    ------ //
// 此处为主函数区域，它将与我们的OJ系统对接，以完成对您代码正确性的检查
// C++选手完成此题不需要读这部分代码！
// 不过如果觉得时间宽裕你也可以尝试阅读？（或许可以帮助分析）
// 
// Python选手很幸运，你们只需开发一个函数，结合列表或字典存储数据，最后实现转换功能即可
// 甚至不用会STL和面向对象（
// 但是作为补偿，你们要通过阅读BLOCK 3的C++代码来了解程序的IO，并完成代码
// 编写，样例段将不会有说明提示
// 
// ------请注意，这不是作答区，修改此部分内容将直接导致您0分------ //
int main()
{
    double roboX = 0;
    double roboY = 0;
    double roboA = 0;
    cin >> roboX >> roboY >> roboA;//获取机器人的X，Y和角度参数（rad）
    robot nao(roboX, roboY, Angle(roboA));
    int obstacle_number = 0;
    cin >> obstacle_number;//获取障碍物数量
    for (int i = 0; i < obstacle_number; i++)
    {
        int x = 0;
        int y = 0;
        cin >> x >> y;//获取障碍物的相对坐标参数
        obstacle obs(x, y);
        nao.obstacle_modules.push_back(obs);//存入障碍物数据信息
    }
    nao.makeField();//调用计算函数
    for (int i = 0; i < nao.obstacle_modules.size(); i++)
    {
        cout << nao.obstacle_modules[i].getFieldX() << " " << nao.obstacle_modules[i].getFieldY() << endl;
        //输出结果
        //中间有空格，每行有回车
    }
    return 0;
}
// ------                 BLOCK 3 END                  ------ //


// ------                   BLOCK 4                    ------ //
// 此处为实现细节区域，展现了全部类的代码实现细节
// 如果你对BLOCK 1部分的某些函数感到疑惑，可以尝试着看看这里
// 但是理论上，完成此题不需要读这部分代码！
// ------请注意，这不是作答区，修改此部分内容将直接导致您0分------ //
Angle::Angle()
{
    m_rad = 0;
}

Angle::Angle(double rad)
{
    double tmp = rad;
    while (tmp >= Pi * 2)
    {
        tmp = tmp - Pi * 2;
    }
    while (tmp < 0)
    {
        tmp = tmp + Pi * 2;
    }
    m_rad = tmp;
}

double Angle::getRadValue()
{
    return m_rad;
}

Angle::operator double() const
{
    return m_rad;
}

Angle Angle::operator+(const Angle& another)
{
    double tmp = m_rad + another.m_rad;
    while (tmp >= Pi * 2)
    {
        tmp = tmp - Pi * 2;
    }
    while (tmp < 0)
    {
        tmp = tmp + Pi * 2;
    }
    return Angle(tmp);
}

Angle Angle::operator-(const Angle& another)
{
    Angle tmp(-another.m_rad);
    return *this + tmp;
}

obstacle::obstacle(double x, double y)
{
    m_relativeX = x;
    m_relativeY = y;
    m_fieldX = 0;
    m_fieldY = 0;
    m_field_able = false;
}

double obstacle::getRelativeX()
{
    return m_relativeX;
}

double obstacle::getRelativeY()
{
    return m_relativeY;
}

double obstacle::getDistance()
{
    return sqrt(m_relativeX * m_relativeX + m_relativeY * m_relativeY);
}

void obstacle::setFieldInfo(double field_x, double field_y, bool field_able)
{
    m_fieldX = field_x;
    m_fieldY = field_y;
    m_field_able = field_able;
}

double obstacle::getFieldX()
{
    if (m_field_able == true)
        return m_fieldX;
    else abort();
}

double obstacle::getFieldY()
{
    if (m_field_able == true)
        return m_fieldY;
    else abort();
}

robot::robot(double x, double y, Angle a)
{
    m_x = x;
    m_y = y;
    m_angle = a;
}

double robot::getX()
{
    return m_x;
}

double robot::getY()
{
    return m_y;
}

Angle robot::getAngle()
{
    return m_angle;
}
// ------                 BLOCK 4 END                  ------ //

