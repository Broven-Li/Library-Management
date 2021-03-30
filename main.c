#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "book_management.h"
#define LEN_BOOK sizeof(struct book)
#define LEN_READER sizeof(struct reader)
#define LEN_LOAD sizeof(struct land)

int book_amount()
{
	FILE *fp;
	int n;
	int copies;
	char tname[20] = {'\0'}, tauthor[20] = {'\0'}, tchuban[20] = {'\0'}, tshuhao[20] = {'\0'};
	fp = fopen("library.txt","r");
	for (n=0; !feof(fp); n++)
	fscanf(fp, "%s%s%s%s%d", tshuhao, tname, tauthor, tchuban, &copies);
	n--;
	fclose(fp);
	return (n);
}

int reader_amount()
{
FILE *fp;
int account=0,n;
char name[20]={'\0'},date[20]={'\0'},book[20]={'\0'};
fp=fopen("reader.txt","r");
for (n=0;!feof(fp);n++)
fscanf(fp,"%d%s%s%s ", &account, &name, &date, &book);
n--;
fclose(fp);
return (n);
}

int account_amount()
{
FILE *fp;
int zhao=0,n;
char mm[20]={'\0'};
fp=fopen("land.txt","r");
for (n=0;!feof(fp);n++)
fscanf(fp,"%d %s",&zhao,mm);
n--;
fclose(fp);
return (n);
}

void show_main_menu()
{
    system ("cls");
    printf("*************************************************\n");
    printf(" 1.Administrator \n\n");
    printf(" 2.Student \n\n");
    printf(" 3.Creat new acocunt \n\n");
    printf(" 4.Exit \n\n");
    printf(" Please enter and press ENTER to confirm.\n");
    printf("*************************************************\n");

    return;
}

void show_administrator ()
{
    system ("cls");
    printf("**************************************************\n");
    printf(" 1.Add book \n");
    printf(" 2.Delete book \n");
    printf(" 3.Back \n");
    printf("**************************************************\n");

    return;
}

void show_student ()
{
    system("cls");
    printf("***********************************************\n");
    printf(" 1.Search books \n");
    printf(" 2.Borrow books \n");
    printf(" 3.Return books \n");
    printf(" 4.Inquire borrowed books \n");
    printf(" 5.Return to the login page \n");
    printf("***********************************************\n");
}

void administrator ()
{
    char choose;
    show_administrator ();
    scanf(" %c", &choose);
    for(;;)
	{
		switch(choose)
        {
            case '1':
                add_book();
                break;
            case '2':
                delete_book();
                break;
            case '3':
                main_menu();
                break;
        }
	}
}

void student ()
{
    void show_student();
    char choose;
    show_student();
    scanf(" %c", &choose);
    for (;;)
    {
        switch(choose)
        {
	       case'1':
	           search_book();
	           break;
    	    case'2':
    	  	    borrow_book();
       	  	    break;
            case'3':
                return_book();
                break;
            case'4':
                inquire_borrowed_books();
                break;
	        case'5':
  	            system ("cls");
				main_menu();
	            break;
        }
    }
}

void main_menu()
{
	char choose;
	show_main_menu();
	scanf("%c",&choose);
	switch(choose)
    {
	    case'1':
	        administrator();
	        break;

	    case'2':
	        student();
	  	    break;

        case'3':
            creat_new_account();
            break;

	    case'4':
	  	    system("cls");
            getch();
  	        exit(0);
  	        system ("cls");
	        break;
    }
}

void add_book()
{
	FILE*fp;
	char i;
	int many=0;
    char  name[20]={'\0'}, author[20]={'\0'}, publication_year[20]={'\0'}, number[20]={'\0'};
    system ("cls");

    if ((fp=fopen("library.txt","r"))==NULL)
	{
    	fp=fopen("library.txt","w");
    	fclose(fp);
    }
	fp=fopen("library.txt","a");
	
	printf("Please enter the book information in the following format: \nBook_ID  Name  Author  Publication_Year  Quantity");
	
	for(;i!=27;)//Press ESC to exit
	{
		printf("\nPlease enter:\n");
		scanf("%s%s%s%s%d",number,name,author,publication_year,&many);
		fprintf(fp,"%-8s%-9s%-14s%-18s%-8d\n",number, name, author, publication_year, many);
	    printf("Press ENTER to continue input.\nPress ESC to finish input.\n");
        i=getch();
        for ( ;i!=13 && i!=27; )
        {
			i=getch();
		}
    }

	fclose(fp);
    printf("Successfully loaded, press any key to return.");
    getch();
	administrator();
}

void delete_book()
{
	struct book *head=NULL;
	struct book *p,*p1,*p2;
   	int tmany=0,n=0,j,k;
   	char  tname[20]={'\0'}, tauthor[20]={'\0'}, tpub[20]={'\0'}, tnum[20]={'\0'};
	char jjnam[20]={'\0'};
	char i;
   	FILE *fp;   
	system ("cls");
	printf("\nPlease enter the book name you want to delete:");
    scanf("%s",jjnam);
    printf("\nPress ENTER to confirm delete\nPress ESC to cancel \n ");
    i=getch();
    for (; i != 13 && i != 27; )
    {
		i=getch();
	}
    if (i==27)
	{
		administrator();
	 	fp=fopen("library.txt","r");
	 	j=book_amount();
	}
	for (k=0;k<j;k++)
    {
		fscanf(fp,"%s%s%s%s%s%d",tnum,tname,tauthor,tpub,&tmany);
		if (strcmp(jjnam,tname))
		{
			n++;
	        if (n==1)
            {
		    	p1=p2=(struct book*)malloc(LEN_BOOK);
                head=p1;
			}
            else
			{
			    p2->next=p1;
				p2=p1;
                p1=(struct book*)malloc(LEN_BOOK);
            }
            strcpy(p1->num,tnum);
            strcpy(p1->nam,tname);
            strcpy(p1->aut,tauthor);
            strcpy(p1->pub,tpub);
            p1->many=tmany;
        }
    }
    if (n==0)
	{
		head=NULL;
	}
	else
	{
		p2->next=p1;
		p1->next=NULL;
		fclose(fp);
	}
   	fp=fopen("library.txt","w");
   	fclose(fp);
   	fp=fopen("library.txt","a");
   	p=head;
   	for (;p!=NULL;)
	{
   		fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->num,p->nam,p->aut,p->pub,p->cat,p->many,p->price);
   		p=p->next;
	}
   	fclose(fp);
   	system ("cls");
   	printf("\nSuccessfully deleted\nPress any key to return\n");
   	getch();
   	administrator();
}

void search_book()
{
	FILE *fp;
	int k=0,m=0,n=0,many=0;
    char name[20]={'\0'}, author[20]={'\0'}, publication_year[20]={'\0'}, number[20]={'\0'};
    char i;
    char chazhao[20]={'\0'};
    if ((fp=fopen("library.txt","r"))==NULL)
    {
		system ("cls");
        printf("Record file does not exist, please press any key to return.\n ");
  		getch();
		student();
    }
		system("cls");
    	printf("Please enter number, name, author or publication year to inquire £º\n");
    	scanf("%s",chazhao);
       	system ("cls");
       	m=book_amount();
	for (n=0;n<m;n++)
	{
		fscanf(fp,"%s%s%s%s%d",number,name,author,publication_year,&many);
        if(!strcmp(chazhao,number)||!strcmp(chazhao,name)||!strcmp(chazhao,author)||!strcmp(chazhao,publication_year))
        {
        	if(k==0)
            {
			  	printf("Inquire Result:\n");
			 	printf("Book id\t Name\t Author \tpublication year\t Amount\t \n");
				printf("%-8s%-9s%-14s%-18s%-7d\n",number, name, author, publication_year, many);
        		k++;
			}
        }
	}
    if (k==0)
    { 
		system ("cls");
        printf("\nNo such book!\n");
        getch();
        student();
	}
	fclose(fp);
	getch();
	student();
}
	
void borrow_book()
{
	FILE *fp,*fp3;
	struct book *head=NULL;
    struct book *p,*p1,*p2;
    int i,loop,k,n=0,flag=0,s=0;
	int jnum=0;
	int many=0;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tchuban[20]={'\0'},tkind[20]={'\0'},tshuhao[20]={'\0'},
         ttname[20]={'\0'},mingzi[20]={'\0'},date[20]={'\0'},zname[20]={'\0'};
	char hit=0;
	system("cls");
	fp=fopen("library.txt","r");
    printf("\nPlease enter book name:\n");
	scanf("%s",zname);
    k= book_amount();
	for (i=0;i<k;i++)
    {
    	fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&many,&tprice);
		n++;
		if(n==1)
		{
			p1=p2=(struct book*)malloc(LEN_BOOK);
			head=p1;
		}
		else
        {
            p2->next=p1;
            p2=p1;
            p1=(struct book*)malloc(LEN_BOOK);
        }
		strcpy(p1->num,tshuhao);
		strcpy(p1->nam,tname);
		strcpy(p1->aut,tauthor);
		strcpy(p1->pub,tchuban);
		strcpy(p1->cat,tkind);
		p1->many=many;
		p1->price=tprice;
	}
    if(n==0)
 	head=NULL;
	else
	{
		p2->next=p1;
	 	p1->next=NULL;
	 	fclose(fp);
	}
	p=head;
	for (;p!=NULL;)
	{
		if(!(strcmp(p->nam,zname)))
		{	
        	flag=1;
		 	loop=p->many;
			(p->many)--;
		}
		p=p->next;
  	}
	if(flag&&(loop>0))
    {
		fp=fopen("library.txt","w");
    	fclose(fp);
    	fp=fopen("library.txt","a");
    	p=head;
		for(;p !=NULL;)
    	{
    		fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->num,p->nam,p->aut,p->pub,p->cat,p->many,p->price);
   		   	p=p->next;
		}
		free(p);
		fclose(fp);
		if ((fp3=fopen("reader.txt","r"))==NULL)
        {
			fp3=fopen("reader.txt","w");
            fclose(fp3);
        }
		fp3=fopen("reader.txt","a");
		printf("\nPlease enter the reader information as the following format :\n Account Name Date Book name\n:");
 		scanf("%d %s %s %s",&jnum,mingzi,date,zname);
		fprintf(fp3,"\n%-8d%-23s%-18s%-10s\n",jnum,mingzi,date,zname);
	    fclose(fp3);
        printf("Successfully borrowed!\n");
		getch();
		student();
	}
	else
	{
    	if(flag!=0)
        printf("this book has been borrowed!");
		else
		printf("No such book! press any key to return! ");
	}
	    getch();
    	student();

}

void return_book ()
{
 	FILE *fp,*fp3;
	struct reader *head=NULL;
	struct reader *p,*p1,*p2;
	struct book *lhead1=NULL;
	struct book *zp1,*lp1,*lp2;
	int txcl=0,i;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tkind[20]={'\0'},
	tchuban[20]={'\0'},ttname[20]={'\0'},tshuhao[20]={'\0'};
	int ttzhenghao=0,tzhenghao=0,n=0,k=0,t=0,flag=0;
	char tmingzi[20]={'\0'},tdate[20]={'\0'},tzname[20]={'\0'},ttzname[20]={'\0'};
	char hitkey=0;
	system ("cls");
 	fp=fopen("reader.txt","r");
	printf("\nPlease enter the account and name:\nPlease enter:");
	scanf("%d %s",&ttzhenghao,ttzname);
	k=reader_amount();
	for (i=0;i<k;i++)
    {
		fscanf(fp,"%d%s%s%s\n ",&tzhenghao,tmingzi,tdate,tzname);
		if((ttzhenghao==tzhenghao)&&!strcmp(ttzname,tzname))
		flag=1;
	}
    fclose(fp);
	fp=fopen("reader.txt","r");
	if(flag)
	{
		for (i=0;i<k;i++)
	  		{
	  			fscanf(fp,"%d%s%s%s\n ",&tzhenghao,tmingzi,tdate,tzname);
	  				if(!((ttzhenghao==tzhenghao)&&!strcmp(ttzname,tzname)))
	  				{
          				n++;
		  				if (n==1)
		  				{
		      				p1=p2=(struct reader*)malloc(LEN_READER);
			  				head=p1;
		  				}
		  				else
		  				{
		        			p2->next=p1;
							p2=p1;
							p1=(struct reader*)malloc(LEN_READER);
          				}
		  				p1->jnum=tzhenghao;
		  				strcpy(p1->jnam,tmingzi);
		 				strcpy(p1->time,tdate);
		  				strcpy(p1->tsnam,tzname);
		  			}
			}
		  	if (n==0)
		  	head=NULL;
		  	else
		  	{
		    	p2->next=p1;
				p1->next=NULL;
			   	fclose(fp);
	      	}
		  	fp=fopen("reader.txt","w");
		  	fclose(fp);
		  	fp=fopen("reader.txt","a");
		  	p=head;
		  	for (;p!=NULL;)
		  	{
		      	fprintf(fp,"\n%-8d%-23s%-18s%-10s\n",p->jnum,p->jnam,p->time,p->tsnam);
			  	p=p->next;
	      	}
		  	free(p);
		  	fclose(fp);
		}
	
	

	if(flag)
	{
		printf("Press ENTER to confirm return book");
		for (;hitkey!=13&&hitkey!=27;)
		{
			hitkey=getch();
		}
		if (hitkey==13)
			printf("Successfully! Press any key to return!");
			n=0;flag=0;
			fp3=fopen("library.txt","r");
			k=book_amount();
			for (i=0;i<k;i++)
			{
				fscanf(fp3,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
				n++;
				if (n==1)
				{
				    lp1=lp2=(struct book*)malloc(LEN_BOOK);
					lhead1=lp1;
				}
				else
				{
			    	lp2->next=lp1;
					lp2=lp1;
					lp1=(struct book*)malloc(LEN_BOOK);
				}
				strcpy(lp1->num,tshuhao);
				strcpy(lp1->nam,tname);
			    strcpy(lp1->aut,tauthor);
				strcpy(lp1->pub,tchuban);
				strcpy(lp1->cat,tkind);
				lp1->many=txcl; 
				lp1->price=tprice;
			}
			if (n==0)
			{
 	  		    lhead1=NULL;
			}
			else
			{
				lp2->next=lp1;
				lp1->next=NULL;
				fclose(fp3);	   
			}
				   zp1=lhead1;
				   for (;zp1!=NULL;)
				   {
				        if(!(strcmp(zp1->nam,ttzname)))
						++(zp1->many);
						zp1=zp1->next;
					}
					fp3=fopen("library.txt","w");
					fclose(fp);
					fp3=fopen("library.txt","a");
					zp1=lhead1;
					for (;zp1!=NULL;)
					{
                         fprintf(fp3,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",
        				 zp1->num,zp1->nam,zp1->aut,zp1->pub,zp1->cat,zp1->many,zp1->price);
						 zp1=zp1->next;
				    }
					fclose(fp3);
					getch();
					student();
					}
					else
					printf("Not exist! Press any key to return!");
					getch();
					student();

}				

void inquire_borrowed_books()
{
	FILE *fp;
    int borrow_num=0,k=0,many=0,m=0,n=0;
    char  borrow_name[20]={'\0'},jstime[20]={'\0'},tsnam[20]={'\0'};
    char i;
    char chazhao[20]={'\0'};
    fp=fopen("reader.txt","r");
	system("cls");
    printf("Please enter your name£º\n");
    scanf("%s",chazhao);
    system ("cls");
	m=book_amount();
	for (n=0;n<m;n++)
	{
		fscanf(fp,"%d%s%s%s",&borrow_num,borrow_name,jstime,tsnam);
        if(!strcmp(chazhao,borrow_name))
        {
        	if(k==0)
            {
				printf("Inquired result:\n\n");
			  	printf("\nAccount\tUser name\t\tBorrow time \tBooks\n");
				printf("\n%-8d%-23s%-18s%-10s\n",borrow_num,borrow_name,jstime,tsnam);
            	k++;
			}
        }
    }
    
	if (k==0)
    { 
		system ("cls");
        printf("\nNo borrowed books!\n");
        getch();
        student();
	}
    fclose(fp);
	getch();
	student();
}

void load_main()
{
	char choose;
	show_main_menu();
	scanf(" %c",&choose);
	switch(choose)
    {
	    case'1':
	        admin_land();
	        break;
	    case'2':
	  	    stu_land();
	  	    break;
	  	case'3':
	  	    creat_new_account();
	  	    break;
	    case'4':
	  	    system("cls");
            getch();
  	        exit(0);
  	        system ("cls");
	        break;
    }
}

void creat_new_account()
{
	FILE *fp;
	int account;
	char password[20],password1[20];
	char name[20];
	char hit=0;
	if ((fp=fopen("land.txt","r"))==NULL)
	{
    	fp=fopen("land.txt","w");
    	fclose(fp);
    }
    system("cls");
	fp=fopen("land.txt","a");
	for(;;)//confirm the two password are the same
	{
		printf("Please enter the account as the following format: Username, Account, Password\n");
		printf("Please enter:");
		scanf(" %s %d %s",name,&account,password);
    	printf("Please enter the password again:\n");
		scanf("%s",password1);
		if(strcmp(password,password1)==0)
	   	{
	    	fprintf(fp," %s %d %s\n", name, account, password);
		   	break;
       	}
       	else
	   	{
	    	printf("The two password doesn't match£¬press ENTER to recreate, press ESC to return.");
	       	hit=getch();
		   	if(hit=27)
		   	system("cls");
		   	load_main();
	    }
	}
   	fclose(fp);
   	printf("Seccessfully created ! Press any key to return.\n");
   	getch();
   	system("cls");
   	load_main();
}

int match(int m,char a[20])
{
	FILE*fp;
	int n=0,i=0;
	int account;
	char name[20];
	char password[20];

	fp=fopen("land.txt","r");

    for(; !feof(fp); )
    {
        fscanf(fp, "%s%d%s", name, &account, password);
        if(m == account)
        {
            if(strcmp(a,password)==0)
			    return 1;
			else
			    return -1;
	    }
	  }
	    return 0;
    }

void stu_land()
{
	int account;
	char password[20];
	int i=2,j,k,n;
	char hit=0;
	system("cls");
	printf("Please enter your account number:\n");
    scanf("%d", &account);   
	printf("Please enter your password:\n");
	scanf(" %s", password);
    i=match(account,password);
    if(i==1)
	{
        printf("Login successfully! Please press any key to continue");
        getch();
        student();
	}
	else if (i == -1)
	{
		printf("Wrong Password !");
		getch();
        stu_land();
	}
	else if (i == 0)
    {
	    printf("User doesn't exist");
	    getch();
	    system("cls");
	    load_main();
    }
    
}

void admin_land()
{
	char admin_password[20] = "admin";
    char user_input_password[20];
    system("cls");
    printf("Please enter the administrator password \n");
    scanf("%s",user_input_password);
    if(strcmp(admin_password, user_input_password)==0)
    {
        printf("Login sucessfully !\n");
        printf("Please enter any key to continue \n");
        getch();
        administrator();
    }
    else
    {
        printf("Wrong password, please reenter !");
        printf("Please enter any key to continue");
        getch();
        admin_land();
    }
}

int main()
{
	load_main();
	return 0;
}































