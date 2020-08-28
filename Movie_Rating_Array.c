/*
  17.1.c
  <TBC>
  Created by Chan Ho Park on <20200802>.
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
};



struct movie* file_read(struct movie*, int* );

void file_write(struct movie*, int);

void print_movies(const struct movie*, int);

void print_a_movie(const struct movie*, int, int);

void print_menu(const struct movie*, int);

void edit_member(const struct movie*, int);

void edit_item(const struct movie*, int, int);

void insert_item(const struct movie*, int, int);

void delete_item(struct movie*, int, int);

void buf_clr();

int input_index(void);

void alloc_mem(struct movie*, int);






int main()
{
	int num = 0;


	struct movie* movie_list = NULL;

	movie_list = file_read(movie_list, &num);

	print_menu(movie_list, num);


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

struct movie* file_read(struct movie* temp_movies, int* n_ptr)
{
	FILE* fr;

	char* file_name = (char*)malloc(MAX_LEN);

	int count = 0;

	printf("Please input filename to read and press [Enter].\n>> ");

	scanf("%s", file_name);

	if ((fr = fopen(file_name, "r")) == NULL)
	{
		printf("ERROR : Cannot Open File.");
		exit(1);
	}

	*n_ptr = fgetc(fr) - 48; // ex. ASCII char '6' -> int 6

	temp_movies = (struct movie*)malloc(sizeof(struct movie) * (*n_ptr));
	
	for (int i = -1; i < *n_ptr; i++)
	{
		if (i == -1)
		{
			fgetc(fr);
		}

		else
		{
			fscanf(fr, "%[^\n]%*c", (temp_movies + i)->title);
			fscanf(fr, "%lf%*c", &((temp_movies + i)->rating));
			count++;
		}
	}

	fclose(fr);

	printf("%d items read completed.\n\n\n", count);

	return temp_movies;
}

void file_write(struct movie* movies, int num)
{
	FILE* fw;

	char* file_name = (char*)malloc(MAX_LEN);

	int count = 0;

	printf("Please input filename to write and press [Enter].\n>> ");

	scanf("%s", file_name);

	if ((fw = fopen(file_name, "w")) == NULL)
	{
		printf("ERROR : Cannot Open File.");
		exit(1);
	}

	char ch = num + 48;
	
	for (int i = -1; i < num; i++) //fprintf 로 구현하면 훨씬 쉬울 것
	{
		if (i == -1)
		{
			fputc(ch, fw);
			fputc('\n', fw);
		}

		else
		{
			for (int k = 0; k < strlen((movies + i)->title); k++)
			{
				ch = (movies + i)->title[k];
				fputc(ch, fw);
			}
			fputc('\n', fw);

			for (int k = 0; k < 2; k++)
			{
				if (k == 0)
					ch = ((movies + i)->rating) / 1;
				else
					ch = (int)floor( ( ( (movies + i)->rating) / 1) + 0.5);

				fputc(ch + 48, fw);

				if (k == 0)
					fputc('.', fw);

				(movies + i)->rating -= ch;
				(movies + i)->rating *= 10;
			}

			fputc('\n', fw);

			count++;
		}
	}

	printf("%d items write completed.\n\n\n", count);
	
	fclose(fw);

	return;
}

void print_movies(const struct movie* movies, int count)
{
	for (int i = 0; i < count; i++)
	{
		print_a_movie(movies, i, count);
	}

	printf("\n\n");

	return;
}

void print_a_movie(const struct movie* movie, int index, int num)
{
	if (index >= num)
	{
		printf("\aInvalid index.\n");
		return;
	}
	
	printf("%d : \"%s\", %.1f\n", index, (movie + index)->title, (movie + index)->rating);
}

void search_movie(const struct movie* movie, int num)
{
	int check = -1;
	char movie_title[MAX_LEN];

	printf("Input title to search and press enter.\n>> ");

	scanf("%[^\n]%*c", movie_title);

	for (int i = 0; i < num; i++)
	{
		if (strcmp(movie_title, (movie+i)->title) == 0)
			check = i;
	}

	if (check != -1)
		print_a_movie(movie, check, num);
	else
		printf("No movie found.\n");
}

void print_menu(const struct movie* movie_list, int n)
{
	int num = n;
	int check = 1;

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
			print_movies(movie_list, num);
			break;

		case 2:
			choice = input_index();

			print_a_movie(movie_list, choice, num);
			printf("\n\n");
			break;

		case 3:
			edit_member(movie_list, num);
			printf("\n\n");
			break;

		case 4:
			num++;
			alloc_mem(movie_list, num);
			edit_item(movie_list, num - 1, num);
			break;

		case 5:
			num++;
			alloc_mem(movie_list, num);
			choice = input_index();
			insert_item(movie_list, choice, num);
			break;

		case 6:
			choice = input_index();
			delete_item(movie_list, choice, num);
			num--;
			break;

		case 7:
			while (num)
			{
				delete_item(movie_list, 0, num);
				num--;
			}
			break;

		case 8:
			file_write(movie_list, num);
			break;

		case 9:
			search_movie(movie_list, num);
			break;

		case 10:
			printf("\n\nG O O D B Y E\n\n");
			free(movie_list);
			exit(1);
			break;

		default:
			printf("You chose a wrong number.\n\n");
			break;
		}

	}
}

void edit_member(const struct movie* movies, int num)
{
	int index;

	index = input_index();

	print_a_movie(movies, index, num);

	edit_item(movies, index, num);

	return;
}

void edit_item(const struct movie* movies, int index, int num)
{
	printf("\nInput a new title and press enter.\n>> ");

	while (scanf("%[^\n]%*c", (movies + index)->title) != 1)
		printf("\naYou made a wrong input\n");

	printf("\nInput a new rating and press enter.\n>> ");

	while (scanf("%lf", &((movies + index)->rating)) != 1)
		printf("\nbYou made a wrong input\n");

	buf_clr();
}

void insert_item(struct movie* movie, int index, int num)
{

	for (int i = num-1; i > index; i--)
	{
		(movie + i)->rating = (movie + i - 1)->rating;
		strcpy((movie + i)->title, (movie + i - 1)->title);
	}


	edit_item(movie, index, num);
}

void delete_item(struct movie* movie, int index, int num)
{
	for (int i = index; i < num - 1; i++)
	{
		(movie + i)->rating = (movie + i + 1)->rating;
		strcpy((movie + i)->title, (movie + i + 1)->title);
	}

	alloc_mem(movie, num-1);
}

void alloc_mem(struct movie* movie, const int num)
{
	movie = (struct movie*)realloc(movie, sizeof(struct movie) * (num));

	return;
}