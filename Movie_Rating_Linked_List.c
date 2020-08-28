/*
  17.5.c
  <TBC>
  Created by Chan Ho Park on <20200827>.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 40



struct movie
{
	char title[MAX_LEN];
	double rating;
	struct movie* next;
};

void search_movie(const struct movie* movie);

struct movie* file_read(struct movie*);

void file_write(struct movie*);

void print_movies(const struct movie*);

void print_a_movie(const struct movie*);

void print_menu(const struct movie*);

void edit_member(const struct movie*);

void edit_item(const struct movie*);

void insert_item(const struct movie*, int);

void delete_item(struct movie**, int);

void delete_all_items(const struct movie**);

void buf_clr();

int input_index(void);

struct movie* search_index(struct movie*, int);

void add_item(struct movie**);





int main()
{

	struct movie* head = NULL;

	head = file_read(head);

	print_menu(head);

	return 0;
}

void buf_clr()
{
	while (getchar() != '\n') continue;
	return;
}

int input_index(void)
{
	int index;

	printf("Input an index of item to do the function.\n>> ");

	while (scanf("%d", &index) != 1)
		printf("\nYou made a wrong input\n");

	buf_clr();

	return index;
}

struct movie* file_read(struct movie* head)
{
	FILE* fr;

	char* file_name = (char*)malloc(MAX_LEN);

	int count = 0;

	struct movie* new_node;

	struct movie* temp = NULL;

	printf("Please input filename to read and press [Enter].\n>> ");

	scanf("%s", file_name);

	if ((fr = fopen(file_name, "r")) == NULL)
	{
		printf("ERROR : Cannot Open File.");
		exit(1);
	}

	count = fgetc(fr) - 48; // ex. ASCII char '6' -> int 6

	

	for (int i = -1; i < count; i++)
	{
		if (i == -1)
		{
			fgetc(fr);
		}

		else
		{
			new_node = (struct movie*)malloc(sizeof(struct movie));

			if (head == NULL)
				head = new_node;
			else
				temp->next = new_node;


			fscanf(fr, "%[^\n]%*c", new_node->title);
			fscanf(fr, "%lf%*c", &(new_node->rating));

			temp = new_node;
			new_node->next = NULL;
		}
	}

	

	fclose(fr);

	printf("%d items read completed.\n\n\n", count);

	return head;
}

void file_write(struct movie* head)
{
	FILE* fw;

	char* file_name = (char*)malloc(MAX_LEN);

	printf("Please input filename to write and press [Enter].\n>> ");

	scanf("%s", file_name);

	if ((fw = fopen(file_name, "w")) == NULL)
	{
		printf("ERROR : Cannot Open File.");
		exit(1);
	}

	struct movie* search = head;

	int count = 0;

	while (search != NULL)
	{
		count++;
		search = search->next;
	}

	char ch = count + 48;

	for (int i = -1; i < count; i++) //fprintf 로 구현하면 훨씬 쉬울 것
	{
		if (i == -1)
		{
			fputc(ch, fw);
			fputc('\n', fw);
		}

		else
		{
			fprintf(fw, "%s\n%.1lf\n", head->title, head->rating);
			head = head->next;
		}
	}

	printf("%d items write completed.\n\n\n", count);

	fclose(fw);

	return;
}

void print_movies(const struct movie* head)
{
	struct movie* search = head;

	int count = 0;

	while(search != NULL)
	{
		printf("%d : ", count);
		count++;

		print_a_movie(search);

		search = search->next;
	}

	printf("\n\n");

	return;
}

void print_a_movie(const struct movie* search)
{
	printf("\"%s\", %.1f\n", search->title, search->rating);
}

void search_movie(const struct movie* head)
{
	int check = -1;
	char movie_title[MAX_LEN];

	struct movie* search = head;

	printf("Input title to search and press enter.\n>> ");

	scanf("%[^\n]%*c", movie_title);

	while (search != NULL)
	{

		if (strcmp(movie_title, search->title) != 0)
		{
			check++;
			search = search->next;
		}
		else
		{
			check++;
			break;
		}
	}


	if (check != -1)
		print_a_movie(search);
	else
		printf("No movie found.\n");
}

void print_menu(const struct movie* head)
{
	int check = 1;

	struct movie* temp;

	while (check)
	{
		int choice = -1;

		int option = 0;

		printf("\nPlease select an option and press [Enter].\n");
		printf("1. Print all items\t2. Print an item\n");
		printf("3. Edit an item\t\t4. Add an item\n");
		printf("5. Insert an item\t6. Delete an item\n");
		printf("7. Delete all items\t8. Save file\n");
		printf("9. Search by name\t10. Quit\n\n>> ");

		while (scanf("%d", &option) != 1)
			printf("\nYou made a wrong input\n");

		buf_clr();

		printf("\n");

		switch (option)
		{
		case 1:
			print_movies(head);
			break;

		case 2:
			choice = input_index();
			temp = search_index(head, choice);

			if (temp != NULL)
				print_a_movie(temp);

			printf("\n\n");
			break;

		case 3:
			edit_member(head);
			printf("\n\n");
			break;

		case 4:
			add_item(&head);
			break;

		case 5:
			choice = input_index();
			insert_item(head, choice);
			break;

		case 6:
			choice = input_index();
			delete_item(&head, choice);
			break;

		case 7:
			delete_all_items(&head);
			break;

		case 8:
			file_write(head);
			break;

		case 9:
			search_movie(head);
			break;

		case 10:
			printf("\n\nG O O D B Y E\n\n");
			delete_all_items(&head); // to free all nodes
			free(head);
			exit(1);
			break;

		default:
			printf("You chose a wrong number.\n\n");
			break;
		}

	}
}

void edit_member(const struct movie* head)
{
	struct movie* temp;

	int index;

	index = input_index();

	temp = search_index(head, index);

	print_a_movie(temp);

	edit_item(temp);

	return;
}

void edit_item(const struct movie* movie)
{
	printf("\nInput a new title and press enter.\n>> ");

	while (scanf("%[^\n]%*c", movie->title) != 1)
		printf("\naYou made a wrong input\n");

	printf("\nInput a new rating and press enter.\n>> ");

	while (scanf("%lf", &(movie->rating)) != 1)
		printf("\nbYou made a wrong input\n");

	buf_clr();
}

void add_item(struct movie** head_ptr)
{
	struct movie* new_node = (struct movie*)malloc(sizeof(struct movie));

	struct movie* temp = *head_ptr;


	edit_item(new_node);

	new_node->next = NULL;

	if (*head_ptr != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = new_node;
	}

	else
		*head_ptr = new_node;
}

void insert_item(struct movie* head, int index)
{
	struct movie* temp = search_index(head, index);

	struct movie* insert = search_index(head, index - 1);

	insert->next = NULL;

	add_item(head);

	(insert->next)->next = temp;

	return;
}

void delete_item(struct movie** head_ptr, int index)
{
	struct movie* temp;

	if (index != 0)
	{
		temp = search_index(*head_ptr, index);

		struct movie* before_deleted = search_index(*head_ptr, index - 1);

		before_deleted->next = temp->next;

		free(temp);
	}
	
	else
	{
		temp = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(temp);
	}

	return;
}

void delete_all_items(struct movie** head_ptr)
{	
	struct movie* node_free = *head_ptr;

	while ((*head_ptr) != NULL)
	{
		node_free = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(node_free);
	}

	return;
}

struct movie* search_index(const struct movie* head, const int num)
{
	struct movie* temp = head;

	for (int i = 0; i < num; i++)
	{
		if (i == 0)
			temp = head->next;
		else
			temp = temp->next;

		if (temp == NULL)
		{
			printf("Error! You inputted a wrong index");
			return NULL;
		}
	}

	return temp;
}
