#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

#include <stdio.h>

/*You can extend the structs (Book and BookArray) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/
struct book
{
	char num[20],nam[20],aut[20],pub[20];
	int  many;
	struct book*next;
};

struct reader
{
	int stu_account;
	char stu_name[20],time[20],book_name[20];
	struct reader *next;
};

struct land
{
	int zhanghao;
	char password[20];
	struct land*next;
};

int book_amount();
void show_main_menu();
void borrow_menu();

void administrator ();
void student ();
void show_administrator ();
void show_student ();

void search_book();
void add_book();
void delete_book();

void borrow_book();
void return_book();
void inquire_borrowed_books();

void stu_land();
void admin_land();
void creat_new_account();
void load_main();
/*typedef struct _Book {
	    unsigned int id; //Book ID
		char title[100]; //book title
		char author[100]; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //total number of copies the library has
		struct _Book* next;
}Book, *book;
//读者借阅信息
typedef struct stu_table{
	char stu_name[21];    //最后一个单元放'\0'
	char stu_num[13];
	char stu_mm[13];
	struct stu_table* next;
	Book* stu_book;
	int stu_already_len;
	int stu_can_len;
}table_stu,*stu;
//管理员信息
typedef struct man_table{
	char man_name[10];
	long man_num;
	long man_mm;
	struct man_table* next;
}table_admin,*admin;*/
//增加图书
/*
typedef struct _BookArray {
	 Book* array; // pointer to array (or linked list) of struct Book.
	 unsigned int length; // number of elements in the (Book*) array 
}BookArray;


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file);

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file);

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book);

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book);

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_title (const char *title);

//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_author (const char *author);

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_year (unsigned int year);
*/

#endif
