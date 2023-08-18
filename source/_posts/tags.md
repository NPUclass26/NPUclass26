title: 测试完成
date: 2023-03-22 00:00:00
tags:
- Test
---
![cover](/images/arcaea.jpg)
只是个测试文章
## 以下我将展示学习成果
### 崔浩杰
![学习笔记](/崔浩杰/崔浩杰.jpg)
![学习笔记](/崔浩杰/崔浩杰(2).jpg)

### 杜浩南
<details>
<summary>杜浩男的代码，点开阅读</summary>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Stu
{
    int ID;//编号
    char name[25];//姓名
    char Gander[4];//性别
    char age[25];//出生年月日
    char ClassName[10];//班级名称//对比的一句
    float GS;//高等数学
    float DY;//大学英语
    float JC;//计算机基础
    float LL;//理论
    float TY;//体育
} Stu;
typedef struct Node
{
    Stu Data;
    struct Node *pnext;
} Node;
void Save(Node *head)
{
    Node *find = head->pnext;
    FILE *fp = fopen("Data.txt", "w");
    while (find)
    {
        fprintf(fp, "%d %s %s %s %s %.2f %.2f %.2f %.2f %.2f\n", find->Data.ID, find->Data.name, find->Data.Gander, find->Data.age,
                find->Data.ClassName, find->Data.GS, find->Data.DY, find->Data.JC, find->Data.LL, find->Data.TY);
        find = find->pnext;
    }
    fclose(fp);
}
void load(Node *head)
{
    Node *find = head;
    Node *pnew;
    FILE *fp = fopen("Data.txt", "r");
    if (fp == NULL)
        return;
    else
    {
        char ch = fgetc(fp);
        if (ch == EOF)
        {
            fclose(fp);
            return;
        }
        else
        {
            fclose(fp);
            fp = fopen("Data.txt", "r");
            while (!feof(fp))
            {
                pnew = (Node*)malloc(sizeof(Node));
                fscanf(fp, "%d %s %s %s %s %f %f %f %f %f\n", &pnew->Data.ID, pnew->Data.name, pnew->Data.Gander, pnew->Data.age,
                       pnew->Data.ClassName, &pnew->Data.GS, &pnew->Data.DY, &pnew->Data.JC, &pnew->Data.LL, &pnew->Data.TY);
                find->pnext = pnew;
                pnew->pnext = NULL;
                find = pnew;

            }
            fclose(fp);
        }
    }

}
int bijiao(char *str, char *str1)
{
    int i, j;
    int n = 0;
    for (i = 0; i < strlen(str1); i += 2)
    {
        for (j = 0; j < strlen(str); j += 2)
        {
            if (str1[i] == str[j] && str1[i + 1] == str[j + 1])
                n++;
        }
    }
    if (n == strlen(str) / 2)                 //除以二的原因是一个汉字占两个字节，但n计数原理是
        return 1;    //当相邻的两个字节都相等时，才自增一
    else
        return 0;
}
void DelAll(Node **head)
{
    Node *Del = (*head)->pnext;
    while (Del != NULL)
    {
        (*head)->pnext = Del->pnext;
        free(Del);
        Del = (*head)->pnext;

    }
    free((*head));
    (*head) = NULL;
}
void ShowOne(Node *pnew)
{
    printf("%d\t%s\t%s\t%s\t%s\t%4.2f\t%4.2f  %4.2f  %4.2f  %4.2f\n",
           pnew->Data.ID, pnew->Data.name, pnew->Data.Gander, pnew->Data.age, pnew->Data.ClassName,
           pnew->Data.GS, pnew->Data.DY, pnew->Data.JC, pnew->Data.LL, pnew->Data.TY);
}
void inputData(Node *pnew)
{
    printf("输入学号: ");
    scanf("%d", &pnew->Data.ID);
    printf("输入姓名: ");
    scanf("%s", pnew->Data.name);
    printf("输入性别: ");
    scanf("%s", pnew->Data.Gander);
    printf("输入生日: ");
    scanf("%s", pnew->Data.age);
    printf("输入班级名称: ");
    scanf("%s", pnew->Data.ClassName);
    printf("输入高等数学: ");
    scanf("%f", &pnew->Data.GS);
    printf("输入大学英语: ");
    scanf("%f", &pnew->Data.DY);
    printf("输入计算机基础: ");
    scanf("%f", &pnew->Data.JC);
    printf("输入大学理论: ");
    scanf("%f", &pnew->Data.LL);
    printf("输入体育成绩: ");
    scanf("%f", &pnew->Data.TY);

}
void CreateEmpty(Node **head)
{
    (*head) = (Node*)malloc(sizeof(Node));
    (*head)->pnext=NULL;
}
void InsertNode(Node *head)
{
    Node *Insert = head;
    while (Insert ->pnext)
    {
        Insert = Insert->pnext;
    }
    Node *pnew = (Node*)malloc(sizeof(Node));
    pnew->pnext = NULL;
    inputData(pnew);
    Insert->pnext = pnew;
    system("pause");
    system("cls");
    Save(head);

}
Node *findNode(Node *head,int flage)
{
    if (flage == 0)
    {
        int n;
        Node *find = head->pnext;
        Node *fe = head;
        printf("请输入学生的学号: ");
        scanf("%d", &n);
        while (find)
        {
            if (n == find->Data.ID)
            {
                return fe;//前驱返回来
            }
            find = find->pnext;
            fe = fe->pnext;
        }
        return NULL;
    }
    if (flage == 1)
    {
        int n;
        Node *find = head->pnext;
        printf("请输入学生的学号: ");
        scanf("%d", &n);
        while (find)
        {
            if (n==find->Data.ID)
            {
                return find;
            }
            find = find->pnext;
        }
        return NULL;
    }
    if (flage == 2)
    {
        char n[25];
        Node *find = head->pnext;
        printf("请输入学生的姓名: ");
        scanf("%s", n);
        while (find)
        {
            if (strcmp(n,find->Data.name)==0);
            {
                return find;
            }
            find = find->pnext;
        }
        return NULL;
    }
    if (flage == 3)
    {
        char n[25];
        Node *find = head->pnext;
        printf("请输入学生的姓氏: ");
        scanf("%s", n);
        while (find)
        {
            if(bijiao(n,find->Data.name)==1)
            {
                ShowOne(find);
            }
            find = find->pnext;
        }
        return NULL;
    }

}
void ReNode(Node *head)
{
    Node *St = findNode(head,1);
    if (St == NULL)
    {
        printf("没有找到此学生\n");
        system("pause");
        system("cls");
        return;
    }
    else
    {
        inputData(St);
        system("pause");
        system("cls");
        Save(head);

    }
}
void DelNode(Node *head)
{
    Node *find = findNode(head,0);
    if (find == NULL)
    {
        printf("没有找到这个这个学生\n");
        system("pause");
        system("cls");
        return;
    }
    else
    {
        Node *Del = find->pnext;
        find->pnext = find->pnext->pnext;
        free(Del);
        printf("删除成功\n");
        system("pause");
        system("cls");
        Save(head);
        return;
    }
}
void TJNode(Node *head)//0代表平均分，1-5代表其余的分
{
    int i, count = 0, num;//count记录链表结点的个数，num进行内层循环，
    Node *p, *q, *tail;//创建三个指针，进行冒泡排序
    p = head;
    while (p->pnext != NULL)//计算出结点的个数
    {
        count++;//注释①
        p = p->pnext;
    }
    for (i = 0; i < count - 1; i++)//外层循环，跟数组冒泡排序一样
    {
        num = count - i - 1;//记录内层循环需要的次数，跟数组冒泡排序一样，
        q = head->pnext;//令q指向第一个结点
        p = q->pnext;//令p指向后一个结点
        tail = head;//让tail始终指向q前一个结点，方便交换，也方便与进行下一步操作
        while (num--)//内层循环 次数跟数组冒泡排序一样
        {
            if ((q->Data.DY+ q->Data.GS+ q->Data.JC+ q->Data.LL+ q->Data.TY)/5<
                    (p->Data.DY + p->Data.GS + p->Data.JC + p->Data.LL + p->Data.TY) / 5)//如果该结点的值大于后一个结点，则交换
            {
                q->pnext = p->pnext;
                p->pnext = q;
                tail->pnext = p;
            }
            tail = tail->pnext;//注释②
            q = tail->pnext;//注释②
            p = q->pnext;//注释②
        }
    }
//开始统计
    int j = 1;
    char Buff[20];
    Node *pShow = head->pnext;
    Node *PCur = head;
    while (pShow)
    {

        if (pShow==head->pnext&&PCur==head)//第一个元素
        {
            sprintf(Buff, "第%d名", j, 20);
            printf("%s\t%d\t%s\t%.2f\n", Buff, pShow->Data.ID, pShow->Data.name,
                   (pShow->Data.DY + pShow->Data.GS + pShow->Data.JC + pShow->Data.LL + pShow->Data.TY) / 5);
        }
        if ((PCur->Data.DY + PCur->Data.GS + PCur->Data.JC + PCur->Data.LL + PCur->Data.TY) / 5==
                (pShow->Data.DY + pShow->Data.GS + pShow->Data.JC + pShow->Data.LL + pShow->Data.TY) / 5)//并列
        {

            sprintf(Buff, "第%d名", j, 20);
            printf("%s\t%d\t%s\t%.2f\n", Buff, pShow->Data.ID, pShow->Data.name,
                   (pShow->Data.DY + pShow->Data.GS + pShow->Data.JC + pShow->Data.LL + pShow->Data.TY) / 5);

        }
        if((PCur->Data.DY + PCur->Data.GS + PCur->Data.JC + PCur->Data.LL + PCur->Data.TY) / 5 >
                (pShow->Data.DY + pShow->Data.GS + pShow->Data.JC + pShow->Data.LL + pShow->Data.TY) / 5)
        {
            j++;
            sprintf(Buff, "第%d名", j, 20);
            printf("%s\t%d\t%s\t%.2f\n", Buff, pShow->Data.ID, pShow->Data.name,
                   (pShow->Data.DY + pShow->Data.GS + pShow->Data.JC + pShow->Data.LL + pShow->Data.TY) / 5);

        }
        pShow = pShow->pnext;
        PCur = PCur->pnext;
    }
    system("pause");
    system("cls");
}
void FJPJ(Node *head)
{
    float total = 0;
    int a, b, c, d, e;
    a = b = c = d = e = 0;
    Node *p = head->pnext;
    while (p)
    {
        total = (p->Data.DY + p->Data.GS + p->Data.JC + p->Data.LL + p->Data.TY) / 5;
        if (total<60)
        {
            a++;
        }
        if (total>=60&&total<70)
        {
            b++;
        }
        if (total>=70&&total<80)
        {
            c++;
        }
        if (total>=80&&total<90)
        {
            d++;
        }
        if (total>=90)
        {
            e++;
        }
        p = p->pnext;
    }
    printf("60分以下: %d人\n",a);
    printf("60-70分: %d人\n", b);
    printf("70-80分: %d人\n", c);
    printf("80-90分: %d人\n", d);
    printf("90-100分: %d人\n", e);
    system("pause");
    system("cls");

}
Node *Rehead(Node *head,char * number)
{
    Node *pnew;
    Node *find = head->pnext;
    Node *temp;
    Node *in;
    CreateEmpty(&temp);//分配新头结点
    in = temp;
    while (find)
    {
        if (strcmp(number,find->Data.ClassName)==0)
        {
            pnew = (Node*)malloc(sizeof(Node));
            pnew->Data = find->Data;
            pnew->pnext = NULL;
            in->pnext = pnew;
            in = pnew;
        }
        find = find->pnext;
    }
    return temp;
}
Node *ReGander(Node *head, char *ch)
{
    Node *pnew;
    Node *find = head->pnext;
    Node *temp;
    Node *in;
    CreateEmpty(&temp);//分配新头结点
    in = temp;
    while (find)
    {
        if (strcmp(ch,find->Data.Gander)==0)
        {
            pnew = (Node*)malloc(sizeof(Node));
            pnew->Data = find->Data;
            pnew->pnext = NULL;
            in->pnext = pnew;
            in = pnew;
        }
        find = find->pnext;
    }
    return temp;
}
void BJ(Node *head)
{
    char str[25];
    printf("请输入要查询的班级: ");
    scanf("%s",str);
    Node *ClassOne = Rehead(head, str);
    TJNode(ClassOne);
    DelAll(&ClassOne);
    system("pause");
    system("cls");

}
void Gander(Node *head)
{
    char gander[8];
    printf("请输入要统计的性别:男 女 ");
    scanf("%s",gander);
    Node *ClassOne=ReGander(head,gander);
    TJNode(ClassOne);
    DelAll(&ClassOne);
    system("pause");
    system("cls");
}
void ClassName(Node *head)
{
    char gander[10];
    printf("请输入要统计的班级名称:");
    scanf("%s", gander);
    Node *ClassOne = Rehead(head, gander);
    TJNode(ClassOne);
    DelAll(&ClassOne);
    system("pause");
    system("cls");
}
void TJBJG(Node *head)
{
    Node *find = head->pnext;
    while (find)
    {
        if (find->Data.DY < 60)
        {
            printf("姓名:%s 课程:大学英语 %.2f\n", find->Data.name, find->Data.DY);
        }
        if (find->Data.GS < 60)
        {
            printf("姓名:%s 课程:高等数学 %.2f\n", find->Data.name, find->Data.GS);

        }
        if (find->Data.JC < 60)
        {
            printf("姓名:%s 课程:计算机基础 %.2f\n", find->Data.name, find->Data.JC);

        }
        if (find->Data.LL < 60)
        {
            printf("姓名:%s 课程:理论 %.2f\n", find->Data.name, find->Data.LL);

        }
        if (find->Data.TY < 60)
        {
            printf("姓名:%s 课程:体育 %.2f\n", find->Data.name, find->Data.LL);

        }
        find = find->pnext;
    }
}
int main()
{
    int  n;
    Node *head;
    CreateEmpty(&head);
    load(head);
    while (1)
    {
        printf("1.添加学生信息\n");
        printf("2.删除学生信息\n");
        printf("3.修改学生信息\n");
        printf("4.统计班级排名\n");
        printf("5.分数段统计\n");
        printf("6.统计性别排名\n");
        printf("7.学生统计排名\n");
        printf("8.按学号查询\n");
        printf("9.按姓名查询\n");
        printf("10.按姓氏查询\n");
        printf("11.按科目统计不及格\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            InsertNode(head);
            break;
        case 2:
            DelNode(head);
            break;
        case 3:
            ReNode(head);
            break;
        case 4:
            ClassName(head);
            break;
        case 5:
            FJPJ(head);
            break;
        case 6:
            Gander(head);
            break;
        case 7:
            TJNode(head);
            break;
        case 8:
        {
            ShowOne(findNode(head, 1));
        }
        break;
        case 9:
        {

            ShowOne(findNode(head, 2));
        }
        break;
        case 10:
        {
            findNode(head, 3);
        }
        break;
        case 11:
        {
            TJBJG(head);
        }
        break;
        default:
            break;
        }
    }
}

</details>

### 高博栋
![寒假计划表](./高博栋/假期学习总结(高博栋).pdf)(点击上面空白部分阅读pdf)

### 贾新璐
![学习笔记](/贾新璐/贾新璐.jpg)
![学习笔记](/贾新璐/贾新璐(2).jpg)

### 李昊轩
![学习笔记](/李昊轩/李昊轩.jpg)
![学习笔记](/李昊轩/李昊轩(2).jpg)
![学习笔记](/李昊轩/李昊轩(3).jpg)

### 李可期

### 李思源
![寒假计划表](./李思源/假期学习总结(李思源).pdf)(点击上面空白部分阅读pdf)

### 刘博
![学习笔记](/刘博/刘博.jpg)

### 刘硕
![学习笔记](/刘硕/刘硕.jpg)
![学习笔记](/刘硕/刘硕(2).jpg)

### 彭勇
![寒假计划表](./彭勇/假期学习总结(彭勇).pdf)(点击上面空白部分阅读pdf)

### 宋向南
![学习笔记](/宋向南/宋向南.jpg)
![学习笔记](/宋向南/宋向南(2).jpg)
![学习笔记](/宋向南/宋向南(3).jpg)

### 田丰淇
![学习笔记](./田丰淇/田丰淇.jpg)
![学习笔记](./田丰淇/田丰淇(2).jpg)
