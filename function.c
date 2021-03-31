#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "book_management.h"
#define LEN_BOOK sizeof(struct book)
#define LEN_READER sizeof(struct reader)

int book_amount()
{
	FILE *fp;
	int n;
	int copies;
	char book_name[20] = {'\0'}, book_author[20] = {'\0'}, publish_time[20] = {'\0'}, book_id[20] = {'\0'};
	fp = fopen("library.txt","r");
	for (n=0; !feof(fp); n++)
	fscanf(fp, "%s%s%s%s%d", book_id, book_name, book_author, publish_time, &copies);
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

void show_main_menu()
{
    system ("cls");
    printf("*************************************************\n");
    printf(" 1.Administrator \n\n");
    printf(" 2.Student \n\n");
    printf(" 3.Creat new account \n\n");
    printf(" 4.Exit \n\n");
    printf(" Please enter and press ENTER to confirm.\n");
    printf("*************************************************\n");

}

void show_administrator ()
{
    system ("cls");
    printf("**************************************************\n");
    printf(" 1.Add book \n");
    printf(" 2.Delete book \n");
    printf(" 3.Back \n");
    printf("**************************************************\n");

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
                load_main();
                break;
        }
	}
}

void student ()
{
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
				load_main();
	            break;
        }
    }
}

void add_book()
{
	FILE*fp;
	char i;
	int many=0;
    char  name[20]={'\0'}, author[20]={'\0'}, publication_year[20]={'\0'}, number[20]={'\0'};
    system ("cls");

	fp=fopen("library.txt","a");

	if (!fp)
    {
	    fp=fopen("library.txt","w");
    }

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
   	int copies=0,n=0,j,k;
   	char  book_name[20]={'\0'}, book_author[20]={'\0'}, publish_time[20]={'\0'}, book_number[20]={'\0'};
	char input_book_name[20]={'\0'};
	char i;
   	FILE *fp;   
	system ("cls");
	printf("\nPlease enter the book name you want to delete:");
    scanf("%s", input_book_name);
    printf("\nPress ENTER to confirm delete\nPress ESC to cancel \n ");
    i=getch();
    for (; i != 13 && i != 27; )
    {
		i=getch();
	}
    if (i==27)
	{
		administrator();
	}
	fp=fopen("library.txt","r");
	j=book_amount();
	for (k=0;k<j;k++)
    {
		fscanf(fp, "%s%s%s%s%d", book_number, book_name, book_author, publish_time, &copies);
		if (strcmp(input_book_name, book_name))
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
            strcpy(p1->num, book_number);
            strcpy(p1->nam,book_name);
            strcpy(p1->aut, book_author);
            strcpy(p1->pub, publish_time);
            p1->many=copies;
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
   		fprintf(fp,"%-8s%-9s%-14s%-16s%-7d\n",p->num,p->nam,p->aut,p->pub,p->many);
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
    char find_book[20]={'\0'};
    if ((fp=fopen("library.txt","r"))==NULL)
    {
		system ("cls");
        printf("Record file does not exist, please press any key to return.\n ");
  		getch();
		student();
    }
		system("cls");
    	printf("Please enter number, name, author or publication year to inquire ：\n");
    	scanf("%s", find_book);
       	system ("cls");
       	m=book_amount();
	for (n=0;n<m;n++)
	{
		fscanf(fp,"%s%s%s%s%d",number,name,author,publication_year,&many);
        if(!strcmp(find_book, number) || !strcmp(find_book, name) || !strcmp(find_book, author) || !strcmp(find_book, publication_year))
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
	int stu_account=0;
	int many=0;
	char book_name[20]={'\0'},book_author[20]={'\0'},publish_year[20]={'\0'},book_id[20]={'\0'},
         stu_name[20]={'\0'},date[20]={'\0'},borrow_book_name[20]={'\0'};
	system("cls");
	fp=fopen("library.txt","r");
    printf("\nPlease enter book name:\n");
	scanf("%s", borrow_book_name);
    k= book_amount();
	for (i=0;i<k;i++)
    {
    	fscanf(fp, "%s%s%s%s%d", book_id, book_name, book_author, publish_year, &many);
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
		strcpy(p1->num, book_id);
		strcpy(p1->nam, book_name);
		strcpy(p1->aut, book_author);
		strcpy(p1->pub, publish_year);
		p1->many=many;
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
		if(!(strcmp(p->nam, borrow_book_name)))
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
    		fprintf(fp,"%-8s%-9s%-14s%-16s%-7d\n",p->num,p->nam,p->aut,p->pub,p->many);
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
		printf("\nPlease enter the reader information as the following format :\n Account Name Date Book name:\n");
 		scanf("%d %s %s %s", &stu_account, stu_name, date, borrow_book_name);
		fprintf(fp3, "\n%-8d%-23s%-18s%-10s\n", stu_account, stu_name, date, borrow_book_name);
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
	char book_name[20]={'\0'},book_author[20]={'\0'},
	publish_year[20]={'\0'},book_id[20]={'\0'};
	int input_stu_account=0,stu_account=0,n=0,k=0,flag=0;
	char stu_name[20]={'\0'},borrow_time[20]={'\0'},tzname[20]={'\0'},input_stu_name[20]={'\0'};
	char press_key=0;
	system ("cls");
 	fp=fopen("reader.txt","r");
	printf("\nPlease enter the account and name:\nPlease enter:");
	scanf("%d %s", &input_stu_account, input_stu_name);
	k=reader_amount();
	for (i=0;i<k;i++)
    {
		fscanf(fp, "%d%s%s%s\n ", &stu_account, stu_name, borrow_time, tzname);
		if((input_stu_account == stu_account) && !strcmp(input_stu_name, tzname))
		flag=1;
	}
    fclose(fp);
	fp=fopen("reader.txt","r");
	if(flag)
	{
		for (i=0;i<k;i++)
	  		{
	  			fscanf(fp, "%d%s%s%s\n ", &stu_account, stu_name, borrow_time, tzname);
	  				if(!((input_stu_account == stu_account) && !strcmp(input_stu_name, tzname)))
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
		  				p1->stu_account=stu_account;
		  				strcpy(p1->stu_name, stu_name);
		 				strcpy(p1->time, borrow_time);
		  				strcpy(p1->book_name, tzname);
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
		      	fprintf(fp, "\n%-8d%-23s%-18s%-10s\n", p->stu_account, p->stu_name, p->time, p->book_name);
			  	p=p->next;
	      	}
		  	free(p);
		  	fclose(fp);
		}

	if(flag)
	{
		printf("Press ENTER to confirm return book");
		for (; press_key != 13 && press_key != 27;)
		{
            press_key=getch();
		}
		if (press_key == 13)
			printf("Successfully! Press any key to return!");
			n=0;flag=0;
			fp3=fopen("library.txt","r");
			k=book_amount();
			for (i=0;i<k;i++)
			{
				fscanf(fp3, "%s%s%s%s%d", book_id, book_name, book_author, publish_year, &txcl);
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
				strcpy(lp1->num, book_id);
				strcpy(lp1->nam, book_name);
			    strcpy(lp1->aut, book_author);
				strcpy(lp1->pub, publish_year);
				lp1->many=txcl;
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
			        if(!(strcmp(zp1->nam, input_stu_name)))
			            ++(zp1->many);
						zp1=zp1->next;
					}
					fclose(fp);
					fp3=fopen("library.txt","a");
					zp1=lhead1;
					for (;zp1!=NULL;)
					{
                         fprintf(fp3,"%-8s%-9s%-14s%-16s%-7d\n",
        				 zp1->num,zp1->nam,zp1->aut,zp1->pub,zp1->many);
						 zp1=zp1->next;
				    }
					fclose(fp3);
					getch();
					student();
					}
					else
					printf("Successfully returned!");
					getch();
					student();

}				

void inquire_borrowed_books()
{
	FILE *fp;
    int borrow_num=0,k=0,many=0,m=0,n=0;
    char  borrow_name[20]={'\0'},borrow_time[20]={'\0'},book_name[20]={'\0'};
    char find[20]={'\0'};
    fp=fopen("reader.txt","r");
	system("cls");
    printf("Please enter your name:\n");
    scanf("%s", find);
    system ("cls");
	m=book_amount();
	for (n=0;n<m;n++)
	{
		fscanf(fp, "%d%s%s%s", &borrow_num, borrow_name, borrow_time, book_name);
        if(!strcmp(find, borrow_name))
        {
        	if(k==0)
        	{
                printf("Inquired result:\n");
                printf("\nAccount\tUser name\tBorrow time\tBooks\n");
            }
				printf("\n%-8d%-17s%-16s%-10s\n", borrow_num, borrow_name, borrow_time, book_name);
            	k++;
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
    system("cls");
	fp=fopen("land.txt","a");
	if (!fp)
    {
	    fp=fopen("land.txt","w");
    }
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
	    	printf("The two password doesn't match，press ENTER to recreate, press ESC to return.");
	       	hit=getch();
		   	if(hit=27)
		   	system("cls");
		   	load_main();
	    }
	}
   	fclose(fp);
   	printf("Successfully created ! Press any key to return.\n");
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

	if(!fp)
    {
	    fp=fopen("land.txt","w");
    }

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
	int i = 2;
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
        printf("Login successfully !\n");
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
