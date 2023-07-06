#include <iostream>
#include <vector>
#include <cmath>
#define Pi 3.1415926//�궨��Pi
using namespace std;
// ����Խ����븴�Ƶ��������Ķ�
// ����������á�||||||����ʾ��ʼ�ͽ�������ע��ʶ��
// �޸ķǴ���������뽫���������
// ������ڴ��������ڴ���������ʽ�����ⳤ�ȵĴ���
// ��ע�����Ŀɶ��Ժ������淶��
// ע���Ѿ���������ϸ�ˣ���ʵ�еĴ���ɲ�����������ϸ�ĵ�дע�͵�2333333

// ------                   BLOCK 1                    ------ //
// �˴�ΪAPI�����������԰������ݵ��˽�ó�����ʹ�õĽӿ�
// �㽫��Ҫ�������е�ĳЩ�������д�Ĵ��룬�������ϸ�Ķ�����
// ------��ע�⣬�ⲻ�����������޸Ĵ˲������ݽ�ֱ�ӵ�����0��------ //

class Angle//�Ƕ���
{
private:
    double m_rad;
public:
    Angle();
    Angle(double rad);
    double getRadValue();//��ȡ�����ƽǶ�ֵ
    operator double() const;//��������ת�����ɽ��Ƕ����Զ�ת��Ϊdouble��
    //Ҳ����˵Angle����Ա�ֱ�ӵ���double������ʹ��
    Angle operator+(const Angle& another);
    Angle operator-(const Angle& another);
};

class obstacle//�ϰ���ģ����
{
private:
    double m_relativeX;
    double m_relativeY;
    double m_fieldX;//Ԥ���Ĵ�ų�������X�����ݳ�Ա
    double m_fieldY;//Ԥ���Ĵ�ų�������Y�����ݳ�Ա
    bool m_field_able;//��ʾ�Ƿ��Ѿ�������������꣬δ�����Ϊ0������Ϊ1
public:
    obstacle(double x, double y);
    double getRelativeX();//��ȡ�ϰ�����Ի����˵�X����
    double getRelativeY();//��ȡ�ϰ�����Ի����˵�Y����
    double getDistance();//��ȡ�ϰ��������˵ľ���
    void setFieldInfo(double field_x, double field_y, bool field_able);//->����Ҫ�õ��ģ����ó���������Ϣ�ĺ���
    double getFieldX();//��ȡ�ϰ���ĳ���X����
    double getFieldY();//��ȡ�ϰ���ĳ���Y����
};

class robot
{
private:
    double m_x;
    double m_y;
    Angle m_angle;
public:
    robot(double x, double y, Angle a);
    double getX();//��ȡ�����˵�X����ֵ
    double getY();//��ȡ�����˵�Y����ֵ
    Angle getAngle();//��ȡ�����˵�ƫת�Ƕ�
    vector<obstacle>obstacle_modules;//��ų����ϵ��ϰ�����Ϣ�ļ���
    void makeField();//->����Ҫ��ɵĺ���
    
};
// ------                 BLOCK 1 END                  ------ //


// ------                   BLOCK 2                    ------ //
// �˴�Ϊ���������밴Ҫ��ȫ���벢���ơ�ȫ���ĳ�����OJϵͳ����
// 
// �������󣺵��ú���������ʱ������һ��obstacle_modules
// �����е�Ԫ�ؽ��в�������������ǵĳ������겢�洢��ÿ��obstacle
// Ԫ����Ԥ���õ�m_fieldX��m_fieldY�У����޸�m_field_ableΪ�棬
// ��ʾ���ϰ���ĳ��������Ѿ�����˼��㡣
// 
// �ܽ��������ǣ�
// 1.ת��vector������ÿ��obstacleԪ�ص��������Ϊ�������겢�洢
// 2.��m_field_able��Ϊ�棬�Ա�ʾ�����������ݿ���
// 3.ͨ�����������ṩ�ĸ��ֺ���ʵ��
void robot::makeField()
{
    //-----||||||��������ʼ||||||-----
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
	
    //-----||||||�����������||||||-----
}
// ------                 BLOCK 2 END                  ------ //


// ------                   BLOCK 3                    ------ //
// �˴�Ϊ�������������������ǵ�OJϵͳ�Խӣ�����ɶ���������ȷ�Եļ��
// C++ѡ����ɴ��ⲻ��Ҫ���ⲿ�ִ��룡
// �����������ʱ���ԣ��Ҳ���Գ����Ķ�����������԰���������
// 
// Pythonѡ�ֺ����ˣ�����ֻ�迪��һ������������б���ֵ�洢���ݣ����ʵ��ת�����ܼ���
// �������û�STL���������
// ������Ϊ����������Ҫͨ���Ķ�BLOCK 3��C++�������˽�����IO������ɴ���
// ��д�������ν�������˵����ʾ
// 
// ------��ע�⣬�ⲻ�����������޸Ĵ˲������ݽ�ֱ�ӵ�����0��------ //
int main()
{
    double roboX = 0;
    double roboY = 0;
    double roboA = 0;
    cin >> roboX >> roboY >> roboA;//��ȡ�����˵�X��Y�ͽǶȲ�����rad��
    robot nao(roboX, roboY, Angle(roboA));
    int obstacle_number = 0;
    cin >> obstacle_number;//��ȡ�ϰ�������
    for (int i = 0; i < obstacle_number; i++)
    {
        int x = 0;
        int y = 0;
        cin >> x >> y;//��ȡ�ϰ��������������
        obstacle obs(x, y);
        nao.obstacle_modules.push_back(obs);//�����ϰ���������Ϣ
    }
    nao.makeField();//���ü��㺯��
    for (int i = 0; i < nao.obstacle_modules.size(); i++)
    {
        cout << nao.obstacle_modules[i].getFieldX() << " " << nao.obstacle_modules[i].getFieldY() << endl;
        //������
        //�м��пո�ÿ���лس�
    }
    return 0;
}
// ------                 BLOCK 3 END                  ------ //


// ------                   BLOCK 4                    ------ //
// �˴�Ϊʵ��ϸ������չ����ȫ����Ĵ���ʵ��ϸ��
// ������BLOCK 1���ֵ�ĳЩ�����е��ɻ󣬿��Գ����ſ�������
// ���������ϣ���ɴ��ⲻ��Ҫ���ⲿ�ִ��룡
// ------��ע�⣬�ⲻ�����������޸Ĵ˲������ݽ�ֱ�ӵ�����0��------ //
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

