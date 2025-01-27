/**
*
*	Solution to course project #6
*	Introduction to programming course
*	Faculty of Mathematics and Informatics of Sofia University
*	Winter semester 2024/2025
*
*	@author Alexandar Srebrov
*	@idnumber 2MI0600450
*	@compiler VC
*
*	<main file>
*
*/

#include <iostream>
#include <fstream>

const size_t LINE_LENGTH = 1024;
const size_t MOVIE_LENGTH = 500;
const size_t YEAR_LENGTH = 5;
const size_t GENRE_LENGTH = 100;
const size_t DIRECTOR_LENGTH = 100;
const size_t ACTORS_LENGTH = 500;
const size_t RATING_LENGTH = 5;
const size_t REVIEWS_LENGTH = 100;
const size_t ADMIN_OPS_MIN = 1;
const size_t USER_OPS_MIN = 1;
const size_t ADMIN_OPS_MAX = 8;
const size_t USER_OPS_MAX = 7;
const char START_RATING[] = "5.0";
const char START_REVIEWS[] = "1";
const size_t ZERO_AS_CHAR = '0';
const size_t NINE_AS_CHAR = '9';
const double eps = 1e-3;
const char adminRole[] = "admin";
const char userRole[] = "user";
const char nameSep = '#';
const char yearSep = '$';
const char genreSep = '@';
const char directorSep = '*';
const char actorsSep = '^';
const char ratSep = '-';
const char movieFile[] = "moviesDB.txt";





struct Movie
{
	char* name;
	char* year;
	char* genre;
	char* director;
	char* actors;
	char* rating;
	char* reviews;
};




void checkInput(size_t& num)
{
	while (std::cin.fail())
	{
		std::cout << "Invalid input! Please select a number: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> num;
	}
}

size_t lenStr(const char* str)
{
	size_t cnt = 0;
	while (*str)
	{
		cnt++;
		str++;
	}
	return cnt;
}

void copyStr(char*& str, const char* input,size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		str[i] = input[i];
	}
	str[len] = '\0';
}

bool isAdmin(const char* str)
{
	size_t i = 0;
	while (*str && adminRole[i])
	{
		if (*str != adminRole[i++])
		{
			return false;
		}
		str++;
	}
	if (adminRole[i] || *str)
		return false;

	return true;
}

bool isUser(const char* str)
{
	size_t i = 0;
	while (*str && userRole[i])
	{
		if (*str != userRole[i++])
		{
			return false;
		}
		str++;
	}
	if (userRole[i] || *str)
		return false;

	return true;
}

bool checkRole(const char* str)
{
	if (str == nullptr)
		return false;

	if (isAdmin(str) || isUser(str))
			return true;

	return false;
}

char* getRole()
{
	std::cout << "Please select a role as as admin or a user: ";
	char input[LINE_LENGTH];
	std::cin.getline(input, LINE_LENGTH+1, '\n');
	size_t inputLen = lenStr(input);
	while (inputLen == 0 || !(checkRole(input)))
	{
		std::cout << "Invalid input!\nPlease select a role as as admin or a user : ";
		std::cin.getline(input, LINE_LENGTH+1, '\n');
		size_t inputLen = lenStr(input);
	}

	char* role = new char[inputLen+1];
	copyStr(role, input, inputLen);
	return role;
}

void showAdminOpts()
{
	std::cout<<"1.Add a movie\n2.Search by movie name\n3.Search by genre\n4.Show all movies\n";
	std::cout<<"5.Edit a movie\n6.Delete a movie\n7.Sort movies\n8.Exit the rpogram\n";
}

void showAdminOptionsAndSelect(size_t& num)
{
	std::cout << "\tThe options for your role are:\n";
	showAdminOpts();
	std::cout << "\tPlease select an option: ";
	std::cin >> num;
	checkInput(num);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (num < ADMIN_OPS_MIN || num>ADMIN_OPS_MAX)
	{
		std::cout << "Invalid number";
		showAdminOptionsAndSelect(num);
	}
}

void showUserOpts()
{
	std::cout << "1.Search by movie name\n2.Search by genre\n3.Show all movies\n";
	std::cout << "4.Sort movies\n5.Rate a movie\n6.Filter by rating\n7.Exit the program\n";
}

void showUserOptionsAndSelect(size_t& num)
{
	std::cout << "\tThe options for your role are:\n";
	showUserOpts();
	std::cout << "\tPlease select an option: ";
	std::cin >> num;
	checkInput(num);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (num < USER_OPS_MIN || num>USER_OPS_MAX)
	{
		std::cout << "Invalid number";
		showUserOptionsAndSelect(num);
	}
}

char* readLineAndGetInfo(const size_t limit)
{
	char input[LINE_LENGTH+1];
	std::cin.getline(input, LINE_LENGTH+1, '\n');
	size_t lenInp = lenStr(input);
	while (lenInp >= limit || lenInp < 1)
	{
		std::cout << "The input is too long or none!";
		std::cin.getline(input, LINE_LENGTH + 1, '\n');
		lenInp = lenStr(input);
	}
	char* res = new char[lenInp+1];
	copyStr(res, input, lenInp);
	return res;
}

										// help functions
		



bool isNum(const char a)
{
	return a >= ZERO_AS_CHAR && a <= NINE_AS_CHAR;
}
bool checkIfAllNums(const char* str)
{
	while (*str)
	{
		if (!(isNum(*str)))
			return false;
		str++;
	}
	return true;
}
char* getYear(const size_t& num)
{
	char* check = readLineAndGetInfo(num);
	if (!(checkIfAllNums(check)) )
	{
		std::cout << "Please write a valid year:";
		check = getYear(num);
	}
	return check;
}
void addToFile(const char* name, const char* year, const char* genre,
	const char* director, const char* actors, const char* rating, const char* reviews)
{
	std::ofstream file(movieFile, std::ios::app);
	if (!file.is_open())
		return;
	file << name << nameSep << year << yearSep << genre << genreSep << director << directorSep
		<< actors << actorsSep << rating << ratSep << reviews<<std::endl;
	file.close();
}
void addMovie()
{
	char* movieName;
	char* movieYear;
	char* genre;
	char* director;
	char* actors;
	std::cout << "Please enter the movie name: ";
	movieName = readLineAndGetInfo(MOVIE_LENGTH);
	std::cout << "Please enter the producement year of the movie:";
	movieYear = getYear(YEAR_LENGTH);
	std::cout << "Please enter the genre of the movie: ";
	genre = readLineAndGetInfo(GENRE_LENGTH);
	std::cout << "Please enter the director's name: ";
	director = readLineAndGetInfo(DIRECTOR_LENGTH);
	std::cout << "Please enter the actors' names: ";
	actors = readLineAndGetInfo(ACTORS_LENGTH);


	addToFile(movieName, movieYear, genre, director, actors,START_RATING,START_REVIEWS);

	delete[] movieName;
	delete[] movieYear;
	delete[] genre;
	delete[] director;
	delete[] actors;
}
										// addMovie functions



bool isFound(char* str1, char* str2)
{
	if (str1 == nullptr || str2 == nullptr)
	{
		return false;
	}

	while (*str1)
	{
		if (*str1 != *str2)
			return false;
		str1++;
		str2++;
	}

	return true;
}
bool contains(char* str, char* search)
{
	if (str == nullptr)
		return false;
	while (*str)
	{
		if (*str == *search)
		{
			if (isFound(search + 1, str + 1))
				return true;
		}
		str++;
	}
	return false;
}
void printSearchedMovies(Movie* movies, size_t moviesCount, char* search)
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		if (contains(movies[i].name, search))
		{
			std::cout << "Movie name: " << movies[i].name << std::endl
				<< "\tYear: " << movies[i].year << std::endl
				<< "\tGenre: " << movies[i].genre << std::endl
				<< "\tDirector: " << movies[i].director << std::endl
				<< "\tActors: " << movies[i].actors << std::endl
				<< "\tRating: " << movies[i].rating << std::endl
				<< "\tNumber of reviews: " << movies[i].reviews << std::endl;
		}
	}
}
void getAllMoviesInfo(size_t moviesLen,Movie* movies)
{
	std::ifstream file(movieFile);
	if (!file.is_open())
		return;
	for (size_t i = 0; i < moviesLen; i++)
	{
		file.getline(movies[i].name, MOVIE_LENGTH, nameSep);
		file.getline(movies[i].year, MOVIE_LENGTH, yearSep);
		file.getline(movies[i].genre, MOVIE_LENGTH, genreSep);
		file.getline(movies[i].director, MOVIE_LENGTH, directorSep);
		file.getline(movies[i].actors, MOVIE_LENGTH, actorsSep);
		file.getline(movies[i].rating, RATING_LENGTH, ratSep);
		file.getline(movies[i].reviews, REVIEWS_LENGTH,'\n');
	}
	file.close();
}
size_t getMoviesLen()
{
	size_t cnt = 0;
	std::ifstream file(movieFile);
	if (!file.is_open())
		return 0;
	while (!file.eof())
	{
		if (file.get() == '\n')
			cnt++;
	}
	file.close();
	return cnt;
}
void deletearrMemory(Movie* movies, size_t moviesCount)
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		delete[] movies[i].name;
		delete[] movies[i].year;
		delete[] movies[i].genre;
		delete[] movies[i].director;
		delete[] movies[i].actors;
		delete[] movies[i].rating;
		delete[] movies[i].reviews;
	}
	delete[] movies;
}
void searchByName()
{
	char* search;
	std::cout << "Please type in what are you looking for: ";
	search = readLineAndGetInfo(MOVIE_LENGTH);
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount,movies);
	printSearchedMovies(movies, moviesCount, search);

	delete[] search;
	deletearrMemory(movies, moviesCount);
}
										// search by name functions




void printSearchedGenres(Movie* movies, size_t moviesCount, char* search)
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		if (contains(movies[i].genre, search))
		{
			std::cout << "Movie name: " << movies[i].name << std::endl
				<< "\tYear: " << movies[i].year << std::endl
				<< "\tGenre: " << movies[i].genre << std::endl
				<< "\tDirector: " << movies[i].director << std::endl
				<< "\tActors: " << movies[i].actors << std::endl
				<< "\tRating: " << movies[i].rating << std::endl
				<< "\tNumber of reviews: " << movies[i].reviews << std::endl;
		}
	}
}
void searchByGenre()
{
	char* search;
	std::cout << "Please type in what are you looking for: ";
	search = readLineAndGetInfo(GENRE_LENGTH);
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	printSearchedGenres(movies, moviesCount, search);

	delete[] search;
	deletearrMemory(movies, moviesCount);
}
										//search by genre functions





void printAll(Movie* movies, size_t moviesCount)
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		std::cout << "Movie name: " << movies[i].name << std::endl
			<< "\tYear: " << movies[i].year << std::endl
			<< "\tGenre: " << movies[i].genre << std::endl
			<< "\tDirector: " << movies[i].director << std::endl
			<< "\tActors: " << movies[i].actors << std::endl
			<< "\tRating: " << movies[i].rating << std::endl
			<< "\tNumber of reviews: " << movies[i].reviews << std::endl;
	}
}
void showAllMovies()
{
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	printAll(movies, moviesCount);
	deletearrMemory(movies, moviesCount);
}
										//show all functions




size_t getIndex(Movie* movies, size_t moviesCount, char* search)
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		if (isFound(movies[i].name, search))
		{
			return i;
		}
	}
	std::cout << "Such movie doesn't exist in the database!";
	return -1;
}
void writeBackInFile(Movie* movies, size_t moviesCount, size_t indexToBeDeleted)
{
	std::ofstream file(movieFile);
	if (!file.is_open())
		return;
	for (size_t i = 0; i < moviesCount; i++)
	{
		if (i == indexToBeDeleted)
			continue;
		file << movies[i].name << nameSep << movies[i].year << yearSep << movies[i].genre
			<< genreSep << movies[i].director << directorSep << movies[i].actors 
			<< actorsSep << movies[i].rating << ratSep << movies[i].reviews << std::endl;
	}
	file.close();
}
void deleteMovie()
{
	char* search;
	std::cout << "Which movie do you want to delete? ";
	search = readLineAndGetInfo(GENRE_LENGTH);
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	size_t indexToBeDeleted = getIndex(movies, moviesCount, search);
	if (indexToBeDeleted == -1)
		return;
	writeBackInFile(movies, moviesCount, indexToBeDeleted);

	delete[] search;
	deletearrMemory(movies, moviesCount);
}
										//Delete functions




void editMovie()
{
	char* search;
	std::cout << "Which movie do you want to change? ";
	search = readLineAndGetInfo(MOVIE_LENGTH);
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	size_t indexToBeDeleted = getIndex(movies, moviesCount, search);
	if (indexToBeDeleted == -1)
		return;
	writeBackInFile(movies, moviesCount, indexToBeDeleted);
	addMovie();

	delete[] search;
	deletearrMemory(movies, moviesCount);
}
										//edit function




bool isSmaller(char* str1, char* str2)
{
	if (str1 == nullptr || str2 == nullptr)
		return false;

	while (*str1)
	{
		if (*str1 > *str2)
			return true;
		else if (*str1 < *str2)
			return false;

		str2++;
		str1++;
	}
	return false;
}
void sortStrArr(char** arr, size_t len)
{
	for (size_t i = 0; i < len-1; i++)
	{
		for (size_t j = i+1; j < len; j++)
		{
			if (isSmaller(arr[i], arr[j]))
			{
				char* temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
void sortMoviesByNames(Movie* movies, size_t moviesCount)
{
	char** names = new char* [moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		names[i] = new char[MOVIE_LENGTH];
		copyStr(names[i], movies[i].name,strlen(movies[i].name));
	}
	sortStrArr(names, moviesCount);
	for (size_t i = 0; i < moviesCount; i++)
	{
		printSearchedMovies(movies, moviesCount, names[i]);
	}
	for (size_t i = 0; i < moviesCount; i++)
	{
		delete[] names[i];
	}
	delete[] names;
}
void sortByName()
{
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	sortMoviesByNames(movies, moviesCount);

	deletearrMemory(movies, moviesCount);
}
double StrToDouble(char* rating)
{
	double num = 0;
	while (*rating)
	{
		if (*rating == '.')
		{
			num += (*(rating + 1) - ZERO_AS_CHAR) / 10.0;
			break;
		}
		num *= 10;
		num += (*rating - ZERO_AS_CHAR);
		rating++;
	}
	return num;
}
void swapDbl(double& num1, double& num2)
{
	double temp = num1;
	num1 = num2;
	num2 = temp;
}
void reverse(char* str)
{
	size_t len = lenStr(str);
	int barrier = len/2;
	for (size_t i = 0; i < barrier; i++)
	{
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len - 1 - i] = temp;
	}
}
char* DblToSTr(double num)
{
	char* res = new char[RATING_LENGTH];
	num *= 10;
	int a = (int)num;
	int i = 0;
	while (a)
	{
		if (i == 1)
		{
			res[i++] = '.';
			continue;
		}
		res[i++] = (a % 10) + ZERO_AS_CHAR;
		a /= 10;
	}
	res[i] = '\0';
	reverse(res);
	return res;
}
void printSearchedByRating(Movie* movies,size_t moviesCount,double* rating)
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		if (contains(movies[i].rating, DblToSTr(rating[i])))
		{
			std::cout << "Movie name: " << movies[i].name << std::endl
				<< "\tYear: " << movies[i].year << std::endl
				<< "\tGenre: " << movies[i].genre << std::endl
				<< "\tDirector: " << movies[i].director << std::endl
				<< "\tActors: " << movies[i].actors << std::endl
				<< "\tRating: " << movies[i].rating << std::endl
				<< "\tNumber of reviews: " << movies[i].reviews << std::endl;
		}
	}
	delete[] rating;
}
void sort(double* ratings, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		for (size_t j = i+1; j < len; j++)
		{
			if (ratings[i] - ratings[j] < eps)
				swapDbl(ratings[i], ratings[j]);
		}
	}
}
void sortMoviesByRating(Movie* movies, size_t moviesCount)
{
	double* ratings = new double[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		ratings[i] = StrToDouble(movies[i].rating);
	}
	sort(ratings,moviesCount);
	printSearchedByRating(movies, moviesCount, ratings);
}
void sortByRating()
{
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	sortMoviesByRating(movies, moviesCount);

	deletearrMemory(movies, moviesCount);
}
void sortMovies()
{
	size_t operation = 0;
	std::cout << "How do you want to sort?\n1.By name\n";
	std::cout << "2.By rating\n\tChoose a number between 1 and 2: ";
	std::cin >> operation;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (operation < 1 || operation > 2)
	{
		std::cout << "Invalid number selected! ";
		std::cin >> operation;
		checkInput(operation);
	} 

	switch (operation)
	{
	case 1:
		sortByName();
		break;
	case 2:
		sortByRating();
		break;
	default:
		break;
	}
}
										//sort functions




size_t ratingToSizeT(char* a)
{
	size_t num = 0;
	num += (a[2] - ZERO_AS_CHAR);
	num += (a[0] - ZERO_AS_CHAR);
	return num;
}
size_t reviewToSizeT(char* str)
{
	size_t a = 0;
	while (str)
	{
		a *= 10;
		a += (*str - ZERO_AS_CHAR);
		str++;
	}
	return a;
}
int strToInt(char* str)
{
	int a = 0;
	while (*str)
	{
		a *= 10;
		a += (*str - ZERO_AS_CHAR);
		str++;
	}
	return a;
}
void intToStr(int a,char* reviews)
{
	while (a)
	{
		*(reviews++) = ((a % 10) + ZERO_AS_CHAR);
		a /= 10;
	}
	reverse(reviews);
}
void changeRating(char*& rating, char* reviews)
{
	double addRating = 0;
	std::cout << "Please rate the movie from 1 to 10: ";
	std::cin >> addRating;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (!addRating || addRating > 10)
	{
		std::cout << "Invalid number! ";
		std::cin >> addRating;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	double currRating = StrToDouble(rating);
	int reviewsCount = strToInt(reviews);
	double newRating = ((currRating * reviewsCount) + addRating) / (reviewsCount + 1);
	intToStr(++reviewsCount,reviews);
	delete[] rating;
	rating = DblToSTr(newRating);
	
}
void rateMovie()
{ 
	char* search;
	std::cout << "Which movie do you want to rate: ";
	search = readLineAndGetInfo(MOVIE_LENGTH);
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	size_t indexToRate = getIndex(movies, moviesCount, search);
	if (indexToRate == -1)
		return;
	writeBackInFile(movies, moviesCount, indexToRate);
	changeRating(movies[indexToRate].rating, movies[indexToRate].reviews);


	addToFile(movies[indexToRate].name, movies[indexToRate].year, movies[indexToRate].genre,
		movies[indexToRate].director, movies[indexToRate].actors, movies[indexToRate].rating,
		movies[indexToRate].reviews);
	deletearrMemory(movies, moviesCount);
}
										//rate functions




void printFilteredMovies(Movie* movies,size_t moviesCount,double filter)
{
	std::cout << filter;
	for (size_t i = 0; i < moviesCount; i++)
	{
		if (StrToDouble(movies[i].rating)  - filter >= 0)
		{
			std::cout << "Movie name: " << movies[i].name << std::endl
				<< "\tYear: " << movies[i].year << std::endl
				<< "\tGenre: " << movies[i].genre << std::endl
				<< "\tDirector: " << movies[i].director << std::endl
				<< "\tActors: " << movies[i].actors << std::endl
				<< "\tRating: " << movies[i].rating << std::endl
				<< "\tNumber of reviews: " << movies[i].reviews << std::endl;
		}
	}
}
void filterMovies()
{
	double filter = 0;
	std::cout << "Please filter the moviesbby rating from 1 to 10: ";
	std::cin >> filter;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (!filter || filter > 10)
	{
		std::cout << "Invalid number! ";
		std::cin >> filter;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	size_t moviesCount = getMoviesLen();
	Movie* movies = new Movie[moviesCount];
	for (size_t i = 0; i < moviesCount; i++)
	{
		movies[i].name = new char[MOVIE_LENGTH];
		movies[i].year = new char[YEAR_LENGTH];
		movies[i].genre = new char[GENRE_LENGTH];
		movies[i].director = new char[DIRECTOR_LENGTH];
		movies[i].actors = new char[ACTORS_LENGTH];
		movies[i].rating = new char[RATING_LENGTH];
		movies[i].reviews = new char[REVIEWS_LENGTH];
	}
	getAllMoviesInfo(moviesCount, movies);
	printFilteredMovies(movies, moviesCount, filter);
}
										//filter functions



int main()
{
	char* role = getRole();					
	size_t operation = 0;

	
	if (isAdmin(role))
	{
		showAdminOptionsAndSelect(operation);
		switch (operation)
		{
		case 1:
			addMovie();
			break;
		case 2:
			searchByName();
			break;
		case 3:
			searchByGenre();
			break;
		case 4:
			showAllMovies();
			break;
		case 5:
			editMovie();
			break;
		case 6:
			deleteMovie();
			break;
		case 7:
			sortMovies();
			break;
		case 8:
			return 0;
			break;
		default:
			break;
		}
	}
	else if (isUser(role))
	{
		showUserOptionsAndSelect(operation);
		switch (operation)
		{
		case 1:
			searchByName();
			break;
		case 2:
			searchByGenre();
			break;
		case 3:
			showAllMovies();
			break;
		case 4:
			sortMovies();
			break;
		case 5:
			rateMovie();
			break;
		case 6:
			filterMovies();
			break;
		case 7:
			return 0;
			break;
		default:
			break;
		}
	}
	delete[] role;
}