#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define LEN sizeof(struct record) /*对结构体长度进行宏定义*/
void menu();/*声明菜单函数*/
struct record*insert(struct record *head);/*声明添加函数 */
struct record*delet(struct record *head); /*声明删除函数 */
struct record*alter(struct record *head); /*声明修改函数 */
void search(struct record *head); /*声明查找函数*/
void show(struct record *head); /*声明显示函数*/
struct record *head; /*定义全局结构体指针变量*/
int n=0; /*定义全局变量*/
struct record /*声明结构体*/
{
    char number[10];
    char name[20];
    char phone[20];
    char adress[40];
    char postcode[10];
    char e_mail[30];
    struct record *next;
};
/******************************************************************************
* *
* 主函数 *
* *
*******************************************************************************/
main()
{
    head=NULL;
    menu();
    rewind(stdin);
}
/******************************************************************************
* *
* 菜单函数 *
* *
*******************************************************************************/
void menu()
{
    int choice;
    printf("\n\t\t******************** 电话簿 ********************");
    printf("\n\t\t*********** 1-添加纪录 2-查询纪录 ************");
    printf("\n\t\t*********** 3-删除纪录 4-修改记录 ************");
    printf("\n\t\t*********** 5-显示纪录 6-退出系统 ************");
    printf("\n\t\t************************************************");
    printf("\n\t\t请选择：");
    scanf("%d",&choice);
    rewind(stdin);
    printf("\n");
    switch (choice)
    {
    case 1:
        head=insert(head);
        rewind(stdin);
        menu();
        break;
    case 2:
        search(head);
        rewind(stdin);
        menu();
        break;
    case 3:
        head=delet(head);
        rewind(stdin);
        menu();
        break;
    case 4:
        head=alter(head);
        rewind(stdin);
        menu();
        break;
    case 5:
        show(head);
        rewind(stdin);
        menu();
        break;
    default:
        printf("\n\t\t谢谢使用!!");
        break;
    }
}
/******************************************************************************
* *
* 添加函数 *
* *
*******************************************************************************/
struct record *insert(struct record *head)
{
    struct record *pp,*p1,*p2;
    pp=(struct record *)malloc(LEN);
    printf("\n\t\t**************** 请输入用户信息 ****************\n");
    printf("\n\t\t输入序号:");
    scanf("%s",pp->number);
    rewind(stdin);
    printf("\n\t\t输入姓名:");
    scanf("%s",pp->name);
    rewind(stdin);
    printf("\n\t\t输入电话号码:");
    scanf("%s",pp->phone);
    rewind(stdin);
    printf("\n\t\t输入地址:");
    scanf("%s",pp->adress);
    rewind(stdin);
    printf("\n\t\t输入邮编:");
    scanf("%s",pp->postcode);
    rewind(stdin);
    printf("\n\t\t输入e-mail:");
    scanf("%s",pp->e_mail);
    rewind(stdin);
    if(head==NULL)/*在表头插入1*/
    {
        head=pp;
        pp->next=NULL;
    }
    else
    {
        p1=head;
        while((strcmp(pp->number,p1->number)>0)&&(p1->next!=NULL))
        {
            p2=p1;
            p1=p1->next;
        }
        if(strcmp(pp->number,p1->number)<=0)
        {
            if(head==p1)
                head=pp; /*在表头插入2*/
            else
                p2->next=pp;/*在表中插入*/
            pp->next=p1;
        }
        else /*在表尾插入*/
        {
            p1->next=pp;
            pp->next=NULL;
        }
    }
    printf("\t添加成功!请继续选择功能键!\n\n");
    n=n+1;
    return(head);
}
/******************************************************************************
* *
* 删除函数 *
* *
*******************************************************************************/
struct record*delet(struct record * head)
{
    struct record *p1,*p2;
    char number[10];
    printf("\t请输入要删除用户的序号number:");
    scanf("%s",&number);
    rewind(stdin);
    if(head==NULL)
    {
        printf("\n\t通讯录无用户信息记录!!\n");
        return(head);
    }
    p1=head;
    while(strcmp(number,p1->number)!=0&&p1->next!=NULL)
    {
        p2=p1;
        p1=p1->next;
    }
    if(strcmp(number,p1->number)==0)
    {
        if(p1==head)
        {
            head=p1->next;
            printf("\t删除成功!请继续选择功能键!\n\n");
        }
        else
        {
            p2=p1->next;
            printf("\t已删 除的用户的序号为:%s\n",number);
            printf("\t删除成功!请继续选择功能键!\n\n");
        }
        n=n-1;
    }
    else
        printf("\t通讯录无该用户的信息记录!\n ");
    return(head);
}
/******************************************************************************
* *
* 查询函数 *
* *
*******************************************************************************/
void search(struct record *head)
{
    int a;
    char f_name[20],f_number[10];
    struct record *p1,*p2;
    if(head==NULL)
    {
        printf("\t通讯录无用户信息记录\n");
        return;
    }
    else
    {
        printf("\t请你选择你查找的方式:\n\n\t\t1:序号\n\t\t2:姓名\n");
        printf("\t\t请选择:");
        scanf("%d",&a);
        rewind(stdin);
        switch(a)
        {
        case 1:
            printf("\n\t请输入要查找用户的序号number:");
            scanf("%s",&f_number);
            rewind(stdin);
            p1=head;
            while(strcmp(p1->number,f_number)!=0)
            {
                if(p1->next==NULL)
                {
                    printf("\n\t通讯录无此用户信息记录\n");
                    return;
                }
                else
                {
                    p2=p1->next;
                    p1=p2;
                }
            }
            printf("\n\t要查找用户的基本信息为:\n");
            printf("\t\t序号: %s\n\t\t姓名:%s\n\t\t电话号码:%s",p1->number,p1->name,p1->phone);
            printf("\n\t\t地址:%s\n\t\t邮编:%s\n\t\te_mail:%s\n",p1->adress,p1->postcode,p1->e_mail);
            break;
        case 2:
            printf("\n\t请输入要查找用户的姓名name:");
            scanf("%s",f_name);
            rewind(stdin);
            p1=head;
            while(strcmp(p1->name,f_name)!=0)
            {
                if(p1->next==NULL)
                {
                    printf("\n\t通讯录无此用户信息记录\n");
                    return;
                }
                else
                {
                    p2=p1->next;
                    p1=p2;
                }
            }
            printf("\n\t要查找用户的基本信息为:\n");
            printf("\t\t序号: %s\n\t\t姓名:%s\n\t\t电话号码:%s",p1->number,p1->name,p1->phone);
            printf("\n\t\t地址:%s\n\t\t邮编:%s\n\t\te_mail:%s",p1->adress,p1->postcode,p1->e_mail);
            break;
        }
    }
}
/******************************************************************************
* *
* 显示函数 *
* *
*******************************************************************************/
void show(struct record *head)
{
    int i;
    struct record *p1,*p2;
    p1=head;
    if(head==NULL)
    {
        printf("\t通讯录无用户信息记录\n");
        return;
    }
    else
    {
        for(i=1; i<=n; i++)
        {
            printf("\n\t第%d个用户的基本信息为:",i);
            printf("\n\t\t序号: %s 姓名:%s 电话号码:%s \n\t\t地址:%s 邮编:%s e_mail:%s\n"
                   ,p1->number,p1->name,p1->phone,p1->adress,p1->postcode,p1->e_mail);
            p2=p1->next;
            p1=p2;
        }
    }
}
/******************************************************************************
* *
* 修改函数 *
* *
*******************************************************************************/
struct record*alter(struct record*head)
{
    struct record *p1,*p2;
    int choice1;
    char alter_number[10],alter_name[20],alter_phone[20],alter_adress[40],alter_postcode[10],alter_e_mail[30],choice2;
    p1=head;
    if(head==NULL)
    {
        printf("通讯录无用户信息记录\n");
        return(head);
    }
    printf("\t请输入要修改的用户的序号number:");
    scanf("%s",alter_number);
    rewind(stdin);
    while(strcmp(p1->number,alter_number)!=0)
    {
        if(p1->next==NULL)
        {
            printf("\n\t通讯录无此用户信息记录\n");
            return(head);
        }
        else
        {
            p2=p1;
            p1=p1->next;
        }
    }
    if(strcmp(p1->number,alter_number)!=0)
    {
        printf("通讯录无用户信息记录\n");
        return(head);
    }
    else
    {
        printf("\t要修改的用户的基本信息为:\n\t");
        printf("\t序号: %s 姓名:%s 电话号码:%s 地址:%s 邮编:%s e_mail:%s\n"
               ,p1->number,p1->name,p1->phone,p1->adress,p1->postcode,p1->e_mail);
    }
    while(1)
    {
        printf("\t你是否要修改的用户的基本信息?(y&n)");
        scanf("%c",&choice2);
        rewind(stdin);
        if(choice2=='y')
        {
            printf("\t请选择你要修改的项目:\n\t");
            printf("1:姓名 2:电话号码 3:地址 4:邮编 5:e_mail\n");
            printf("\t你选择的序号为: ");
            scanf("%d",&choice1);
            rewind(stdin);
            switch(choice1)
            {
            case 1:
                printf("\t请输入更改后的姓名");
                scanf("%s",alter_name);
                rewind(stdin);
                strcpy(p1->name,alter_name);
                continue;
            case 2:
                printf("\t请输入更改后的电话号码");
                scanf("%s",alter_phone);
                rewind(stdin);
                strcpy(p1->phone,alter_phone);
                continue;
            case 3:
                printf("\t请输入更改后的地址");
                scanf("%s",alter_adress);
                rewind(stdin);
                strcpy(p1->adress,alter_adress);
                continue;
            case 4:
                printf("\t请输入更改后的邮编");
                scanf("%s",&alter_postcode);
                rewind(stdin);
                strcpy(p1->postcode,alter_postcode);
                continue;
            case 5:
                printf("\t请输入更改后的e_mail");
                scanf("%s",alter_e_mail);
                rewind(stdin);
                strcpy(p1->e_mail,alter_e_mail);
                continue;
            }
            printf("\n\t修改后用户的基本信息为:\n\t");
            printf("\t序号: %s 姓名:%s 电话号码:%s 地址:%s 邮编:%s e_mail\n"
                   ,p1->number,p1->name,p1->phone,p1->adress,p1->postcode,p1->e_mail);
        }
        else
        {
            printf("\n\t修改成功!!\n");
            break;
        }
    }
    return(head);
}
