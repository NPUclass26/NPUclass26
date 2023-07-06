#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define LEN sizeof(struct record) /*�Խṹ�峤�Ƚ��к궨��*/
void menu();/*�����˵�����*/
struct record*insert(struct record *head);/*������Ӻ��� */
struct record*delet(struct record *head); /*����ɾ������ */
struct record*alter(struct record *head); /*�����޸ĺ��� */
void search(struct record *head); /*�������Һ���*/
void show(struct record *head); /*������ʾ����*/
struct record *head; /*����ȫ�ֽṹ��ָ�����*/
int n=0; /*����ȫ�ֱ���*/
struct record /*�����ṹ��*/
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
* ������ *
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
* �˵����� *
* *
*******************************************************************************/
void menu()
{
    int choice;
    printf("\n\t\t******************** �绰�� ********************");
    printf("\n\t\t*********** 1-��Ӽ�¼ 2-��ѯ��¼ ************");
    printf("\n\t\t*********** 3-ɾ����¼ 4-�޸ļ�¼ ************");
    printf("\n\t\t*********** 5-��ʾ��¼ 6-�˳�ϵͳ ************");
    printf("\n\t\t************************************************");
    printf("\n\t\t��ѡ��");
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
        printf("\n\t\tллʹ��!!");
        break;
    }
}
/******************************************************************************
* *
* ��Ӻ��� *
* *
*******************************************************************************/
struct record *insert(struct record *head)
{
    struct record *pp,*p1,*p2;
    pp=(struct record *)malloc(LEN);
    printf("\n\t\t**************** �������û���Ϣ ****************\n");
    printf("\n\t\t�������:");
    scanf("%s",pp->number);
    rewind(stdin);
    printf("\n\t\t��������:");
    scanf("%s",pp->name);
    rewind(stdin);
    printf("\n\t\t����绰����:");
    scanf("%s",pp->phone);
    rewind(stdin);
    printf("\n\t\t�����ַ:");
    scanf("%s",pp->adress);
    rewind(stdin);
    printf("\n\t\t�����ʱ�:");
    scanf("%s",pp->postcode);
    rewind(stdin);
    printf("\n\t\t����e-mail:");
    scanf("%s",pp->e_mail);
    rewind(stdin);
    if(head==NULL)/*�ڱ�ͷ����1*/
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
                head=pp; /*�ڱ�ͷ����2*/
            else
                p2->next=pp;/*�ڱ��в���*/
            pp->next=p1;
        }
        else /*�ڱ�β����*/
        {
            p1->next=pp;
            pp->next=NULL;
        }
    }
    printf("\t��ӳɹ�!�����ѡ���ܼ�!\n\n");
    n=n+1;
    return(head);
}
/******************************************************************************
* *
* ɾ������ *
* *
*******************************************************************************/
struct record*delet(struct record * head)
{
    struct record *p1,*p2;
    char number[10];
    printf("\t������Ҫɾ���û������number:");
    scanf("%s",&number);
    rewind(stdin);
    if(head==NULL)
    {
        printf("\n\tͨѶ¼���û���Ϣ��¼!!\n");
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
            printf("\tɾ���ɹ�!�����ѡ���ܼ�!\n\n");
        }
        else
        {
            p2=p1->next;
            printf("\t��ɾ �����û������Ϊ:%s\n",number);
            printf("\tɾ���ɹ�!�����ѡ���ܼ�!\n\n");
        }
        n=n-1;
    }
    else
        printf("\tͨѶ¼�޸��û�����Ϣ��¼!\n ");
    return(head);
}
/******************************************************************************
* *
* ��ѯ���� *
* *
*******************************************************************************/
void search(struct record *head)
{
    int a;
    char f_name[20],f_number[10];
    struct record *p1,*p2;
    if(head==NULL)
    {
        printf("\tͨѶ¼���û���Ϣ��¼\n");
        return;
    }
    else
    {
        printf("\t����ѡ������ҵķ�ʽ:\n\n\t\t1:���\n\t\t2:����\n");
        printf("\t\t��ѡ��:");
        scanf("%d",&a);
        rewind(stdin);
        switch(a)
        {
        case 1:
            printf("\n\t������Ҫ�����û������number:");
            scanf("%s",&f_number);
            rewind(stdin);
            p1=head;
            while(strcmp(p1->number,f_number)!=0)
            {
                if(p1->next==NULL)
                {
                    printf("\n\tͨѶ¼�޴��û���Ϣ��¼\n");
                    return;
                }
                else
                {
                    p2=p1->next;
                    p1=p2;
                }
            }
            printf("\n\tҪ�����û��Ļ�����ϢΪ:\n");
            printf("\t\t���: %s\n\t\t����:%s\n\t\t�绰����:%s",p1->number,p1->name,p1->phone);
            printf("\n\t\t��ַ:%s\n\t\t�ʱ�:%s\n\t\te_mail:%s\n",p1->adress,p1->postcode,p1->e_mail);
            break;
        case 2:
            printf("\n\t������Ҫ�����û�������name:");
            scanf("%s",f_name);
            rewind(stdin);
            p1=head;
            while(strcmp(p1->name,f_name)!=0)
            {
                if(p1->next==NULL)
                {
                    printf("\n\tͨѶ¼�޴��û���Ϣ��¼\n");
                    return;
                }
                else
                {
                    p2=p1->next;
                    p1=p2;
                }
            }
            printf("\n\tҪ�����û��Ļ�����ϢΪ:\n");
            printf("\t\t���: %s\n\t\t����:%s\n\t\t�绰����:%s",p1->number,p1->name,p1->phone);
            printf("\n\t\t��ַ:%s\n\t\t�ʱ�:%s\n\t\te_mail:%s",p1->adress,p1->postcode,p1->e_mail);
            break;
        }
    }
}
/******************************************************************************
* *
* ��ʾ���� *
* *
*******************************************************************************/
void show(struct record *head)
{
    int i;
    struct record *p1,*p2;
    p1=head;
    if(head==NULL)
    {
        printf("\tͨѶ¼���û���Ϣ��¼\n");
        return;
    }
    else
    {
        for(i=1; i<=n; i++)
        {
            printf("\n\t��%d���û��Ļ�����ϢΪ:",i);
            printf("\n\t\t���: %s ����:%s �绰����:%s \n\t\t��ַ:%s �ʱ�:%s e_mail:%s\n"
                   ,p1->number,p1->name,p1->phone,p1->adress,p1->postcode,p1->e_mail);
            p2=p1->next;
            p1=p2;
        }
    }
}
/******************************************************************************
* *
* �޸ĺ��� *
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
        printf("ͨѶ¼���û���Ϣ��¼\n");
        return(head);
    }
    printf("\t������Ҫ�޸ĵ��û������number:");
    scanf("%s",alter_number);
    rewind(stdin);
    while(strcmp(p1->number,alter_number)!=0)
    {
        if(p1->next==NULL)
        {
            printf("\n\tͨѶ¼�޴��û���Ϣ��¼\n");
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
        printf("ͨѶ¼���û���Ϣ��¼\n");
        return(head);
    }
    else
    {
        printf("\tҪ�޸ĵ��û��Ļ�����ϢΪ:\n\t");
        printf("\t���: %s ����:%s �绰����:%s ��ַ:%s �ʱ�:%s e_mail:%s\n"
               ,p1->number,p1->name,p1->phone,p1->adress,p1->postcode,p1->e_mail);
    }
    while(1)
    {
        printf("\t���Ƿ�Ҫ�޸ĵ��û��Ļ�����Ϣ?(y&n)");
        scanf("%c",&choice2);
        rewind(stdin);
        if(choice2=='y')
        {
            printf("\t��ѡ����Ҫ�޸ĵ���Ŀ:\n\t");
            printf("1:���� 2:�绰���� 3:��ַ 4:�ʱ� 5:e_mail\n");
            printf("\t��ѡ������Ϊ: ");
            scanf("%d",&choice1);
            rewind(stdin);
            switch(choice1)
            {
            case 1:
                printf("\t��������ĺ������");
                scanf("%s",alter_name);
                rewind(stdin);
                strcpy(p1->name,alter_name);
                continue;
            case 2:
                printf("\t��������ĺ�ĵ绰����");
                scanf("%s",alter_phone);
                rewind(stdin);
                strcpy(p1->phone,alter_phone);
                continue;
            case 3:
                printf("\t��������ĺ�ĵ�ַ");
                scanf("%s",alter_adress);
                rewind(stdin);
                strcpy(p1->adress,alter_adress);
                continue;
            case 4:
                printf("\t��������ĺ���ʱ�");
                scanf("%s",&alter_postcode);
                rewind(stdin);
                strcpy(p1->postcode,alter_postcode);
                continue;
            case 5:
                printf("\t��������ĺ��e_mail");
                scanf("%s",alter_e_mail);
                rewind(stdin);
                strcpy(p1->e_mail,alter_e_mail);
                continue;
            }
            printf("\n\t�޸ĺ��û��Ļ�����ϢΪ:\n\t");
            printf("\t���: %s ����:%s �绰����:%s ��ַ:%s �ʱ�:%s e_mail\n"
                   ,p1->number,p1->name,p1->phone,p1->adress,p1->postcode,p1->e_mail);
        }
        else
        {
            printf("\n\t�޸ĳɹ�!!\n");
            break;
        }
    }
    return(head);
}
