//********MAJJI DEEPIKA*****
//********19CS30027*******
//********LIBRARY MANAGEMENT SYSTEM******

#include<iostream>
#include<conio.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<vector>
#include<dirent.h>

using namespace std;

int SearchWord(string a,string b)
{	int x = a.length();
    int y = b.length();
	int i,j;
    for ( i = 0; i <=y-x; i++)
    {	for (j = 0; j <x; j++)
		{	if (b[i+j] !=a[j])
                break;
		}
		if (j == x)
            return 1;
    }

    return -1;
}

struct DATE{
	int day;
	int month;
	int year;
};


class BOOK
{
	private  :
	        string filename;
	        string name;
	        string author;
	        string type;
	        string filepath;
	public:
    BOOK(string str,const char*path)
    {	
	 	type = "Novel";
        filepath = (string)path + "/" + str;
        filename = str;
        cout<<filename<<endl;
        fstream NewFile;
        NewFile.open(path, ios::in);
        if (!NewFile)
            cout << "No such file exists" << endl;
		else
        {
            string term;
            while (!NewFile.eof())
            {
                NewFile>> term;
                if (term == "Title:")
                    getline(NewFile, name);

                if (term== "Author:")
                    getline(NewFile, author);

                if (term == "ACT")
                {
                    type = "Play";
                    break;
                }
            }
        }
        NewFile.close();
	}
	void print()
    {
        cout << filename << endl;
        cout << "Name:" << name << endl;
        cout << "Author:" << author << endl;
        cout << "Type: " << type << endl;
    }

    void PrintInFile(fstream &File)
    {
        File << "Name: " << name << " Type: " << type << endl;
    }

    string getName()
    {
        return name;
    }
	string getType()
    {
        return type;
    }
    string getPath()
    {
        return filepath;
    }

	int SearchTitle(string tit)
    {
        return SearchWord(tit, name);
    }

    int SearchAuthor(string str)
    {
        return SearchWord(str, author);
    }
    void AddBook();
	void DisplayAllBooks();
};



class Lbry_Mng_Syst
{	vector<BOOK> list;
    public:
    Lbry_Mng_Syst() {}

    void add(BOOK &text)
    {
        list.push_back(text);
    }
	void List()
    {
        int z = 0;
        cout << "List Size: " << list.size() << endl;
        while (z < list.size())
        {
            list.at(z).print();
            z++;;
        }
    }

    int getSize()
    {
        return list.size();
    }
	void SearchBook();
	void DisplayBook();
	void Tasks();
};
void list_dir(const char *path, Lbry_Mng_Syst &temp)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
    if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".DS_Store") == 0)
        continue;
    else
    {
        BOOK ex(entry->d_name, path);
        temp.add(ex);
    }
    }
    closedir(dir);
    
}

void Lbry_Mng_Syst::SearchBook()
{
    vector<string> MatchBooks;
    MatchBooks.clear();
    cout << "**To search for a book**" << endl;
    cout << "what will you use title/author" << endl;
    string note;
    cin >> note;
   

    if (note =="title")
    {
        cout << "Enter the title of the book" << endl;
        string ttle;
        getline(cin, ttle);
		int q = 0;
        while (q<list.size())
        {
            int w= list.at(q).SearchTitle(ttle);
            if (w!= -1)
                MatchBooks.push_back(list.at(q).getName());
            q++;
        }
        if (MatchBooks.size() == 0)
            cout << "No such book Found" << endl;
    }

    else if (note == "author")
    {
        cout << "Enter the name of author: " << endl;
        string A_name;
        getline(cin, A_name);

        int q = 0;
        while (q< list.size())
        {
            int w= list.at(q).SearchAuthor(A_name);
            if (w!= -1)
                MatchBooks.push_back(list.at(q).getName());
            q++;
        }
        if (MatchBooks.size() == 0)
            cout << "No such book has found" << endl;
    }
	else
        cout << "**Enter either title or author only**" << endl;

    if (MatchBooks.size() != 0)
    {
        cout << "The books found from the search are :" << endl;

        for (int i = 0; i < MatchBooks.size(); i++)
        {
            cout << MatchBooks[i] << endl;
        }
    }
}
void Lbry_Mng_Syst::DisplayBook()
{
    string tin;
    getline(cin, tin);
    cout << "Enter the name of the book to be displayed:" << endl;
    string ttle;
    getline(cin, ttle);

    int q = 0;
    string filePath = "empty";
    while (q < list.size())
    {
        int w= list[q].SearchTitle(ttle);
        if (w!= -1)
        {
			filePath = list[q].getPath();
        }
        q++;
    }

    if (filePath == "empty")
        cout << "Invalid Book Name" << endl;

    else
    {
        fstream Newfile;
        Newfile.open("filePath", ios::in);
        if (!Newfile)
            cout << "No such file exists" << endl;

        else
        {
            string line;
            while (!Newfile.eof())
            {
                getline(Newfile, line);
                int w= SearchWord("START OF THIS PROJECT GUTENBERG EBOOK", line);
				if (w!= -1)
                    break;
            }

            int count = 0;

            while (count < 50)
            {
                getline(Newfile, line);
                cout << line << endl;
                count++;
            }
        }
       Newfile.close();
    }
}







int bookOptions() {
	int selectedOpt = 0;
	cout << "1. Display list of all books"<< endl;
	cout << "2. Search a Book"<< endl;
	cout << "3. Display a book"<< endl;
	cout << "4. To add a book"<< endl;
	cout << "5. Exit"<< endl;
	cout << "--- Choose and enter any option ---" << endl;
	cin >> selectedOpt;
	return selectedOpt;
}
// *******DRIVER CODE******
int main()
{	int i,k;
	char *directory;
	cout<<"please input directory path";
	cin>>directory;
	
	Lbry_Mng_Syst dp;
	list_dir(directory,dp);
	do{
		int k;
		k=bookOptions();
		switch (k)
        {
        case 1:
            dp.List();
            break;
       case 2:
            dp.SearchBook();
            break;
       case 3:
             dp.DisplayBook();
             break;
       /* case 4:
            dp.AddBook();
            break; */
        case 5:
            exit(0);
        default:
            cout << "\a";
        }
    } while (k!=5);
	
	
	
  	return 0;
}


