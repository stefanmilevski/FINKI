#include<iostream>
#include<cstring>

using namespace std;

enum Extension {pdf, txt, exe};

class File
{
private:
    char * ime;
    Extension ekstenzija;
    char * sopstvenik;
    int golemina;

public:
    File()
    {
        this->ime = new char[0];
        this->golemina = 0;
        this->sopstvenik = new char[0];
    }

    File(char * ime, char * sopstvenik, int golemina, Extension ekstenzija)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);

        this->sopstvenik = new char[strlen(sopstvenik)+1];
        strcpy(this->sopstvenik, sopstvenik);

        this->golemina = golemina;
        this->ekstenzija = ekstenzija;
    }

    File(const File & other)
    {
        this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime, other.ime);

        this->sopstvenik = new char[strlen(other.sopstvenik)+1];
        strcpy(this->sopstvenik, other.sopstvenik);

        this->golemina = other.golemina;
        this->ekstenzija = other.ekstenzija;

    }

    File & operator = (const File & other)
    {
        if(this != & other)
        {
            delete [] ime;
            delete [] sopstvenik;

            this->ime = new char[strlen(other.ime)+1];
            strcpy(this->ime, other.ime);

            this->sopstvenik = new char[strlen(other.sopstvenik)+1];
            strcpy(this->sopstvenik, other.sopstvenik);

            this->golemina = other.golemina;
            this->ekstenzija = other.ekstenzija;
        }
        return *this;
    }

    ~File()
    {
        delete [] ime;
        delete [] sopstvenik;
    }

    void print()
    {
        char ext[4];
        if(this->ekstenzija==0) strcpy(ext,"pdf");
        if(this->ekstenzija==1) strcpy(ext,"txt");
        if(this->ekstenzija==2) strcpy(ext,"exe");

        cout << "File name: " << this->ime << "." << ext << endl;
        cout << "File owner: " << this->sopstvenik << endl;
        cout << "File size: " << this->golemina << endl;
    }

    bool equals(const File & that)
    {
        if(!strcmp(this->ime, that.ime) && !strcmp(this->sopstvenik, that.sopstvenik) && this->ekstenzija==that.ekstenzija)
        {
            return true;
        }
        return false;
    }

    bool equalsType(const File & that)
    {
        if(!strcmp(this->ime,that.ime) && this->ekstenzija==that.ekstenzija)
        {
            return true;
        }
        return false;
    }

};

class Folder
{
private:
    char * ime;
    int brojNaFajlovi;
    File * files;

public:
    Folder()
    {
        this->ime = new char[0];
        this->brojNaFajlovi = 0;
        this->files = new File[0];
    }

    Folder(const char * name)
    {
        this->ime = new char[strlen(name)+1];
        strcpy(this->ime,name);
        this->brojNaFajlovi = 0;
        this->files = new File[0];
    }

    ~Folder()
    {
        delete [] files;
    }

    void print()
    {

        cout << "Folder name: " << this->ime << endl;
        for(int i = 0; i < brojNaFajlovi; i++)
        {
            this->files[i].print();
        }
    }

    void remove(const File & file)
    {
        int removeIndex = this->brojNaFajlovi;
        for(int i = 0; i < brojNaFajlovi; i++)
        {
            if(this->files[i].equals(file))
            {
                removeIndex = i;
                break;
            }
        }

        if(removeIndex == this->brojNaFajlovi)
        {
            return;
        }
        this->brojNaFajlovi--;
        for(int i = removeIndex; i < this->brojNaFajlovi; i++)
        {
            this->files[i]= this->files[i+1];
        }

    }


    void add(const File & file)
    {
        File * tmp = new File[this->brojNaFajlovi+1];
        for(int i = 0; i < this->brojNaFajlovi; i++)
        {
            tmp[i] = this->files[i];
        }
        tmp[this->brojNaFajlovi++] = file;

        delete[]files;
        this->files = tmp;
    }




};





int main()
{
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1)
    {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2)
    {
        cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3)
    {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4)
    {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0)
        {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else
    {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0)
        {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
