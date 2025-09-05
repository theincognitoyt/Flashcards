#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <limits>
#include <cstdlib>
#include <windows.h>
using namespace std;
string path = "";
struct Node{
    string word;//sth I want to learn f.e. a french word
    string defi;//strict definition/translation f.e. to english
    string desc;//additional description f.e. of the word
    int lvl;//lvl represents a box from Leitner system.
    bool done;//it shows if it this was attempted this day; 0 - not done, 1 - done
    string source;
    struct Node* next;};
Node* L[6];
unsigned l_len(Node* p){
  unsigned c = 0;
  while(p)
  {
    c++;
    p = p->next;
  }
  return c;}
unsigned l_len_undone(Node* p){
  unsigned c = 0;
  while(p)
  {
    if(p->done==0)c++;
    p = p->next;
  }
  return c;}
void l_push_front(Node * & head, string word, string defi, string desc, int lvl, bool done, string source){
  Node * p = new Node;
  p->word = word;
  p->defi = defi;
  p->desc = desc;
  p->next = head;
  p->lvl = lvl;
  p->done = done;
  p->source = source;
  head = p;
}
void l_pop_front(Node * & head){
  Node * p;
  p = head;
  if(p)
  {
    head = p->next;
    delete p;
  }
}
void determineList(string word, string defi, string desc, int lvl, bool done, string source){
  Node * p, * e;
  e = new Node;
  e->next = NULL;
  e->word = word;
  e->defi = defi;
  e->desc = desc;
  e->lvl = lvl;
  e->done = done;
  e->source = source;
    p=L[lvl];
    if(l_len(p)==0)
    l_push_front(L[lvl],word,defi,desc,lvl, done, source);
    else if(p)
  {
     while(p->next) p = p->next;
     p->next = e;
     //cout<<"p:"<<p->next->word<<endl;
  }
  else p = e;
}
void l_push_back(Node * & head, string word, string defi, string desc, int lvl, bool done, string source){
  Node * p, * e;
  e = new Node;
  e->next = NULL;
  e->word = word;
  e->defi = defi;
  e->desc = desc;
  e->lvl = lvl;
  e->done = done;
  e->source = source;
  p = head;
  if(p)
  {
     while(p->next)
       p = p->next;
     p->next = e;
  }
  else
    head = e;
}
void l_remove(Node * & head, Node * e){
  Node * p;
  if(head == e)
    l_pop_front(head);
  else
  {
    p = head;
    while(p->next != e&&p->next!=NULL)
      p = p->next;
    p->next = e->next;
    delete e;
  }
}
void menu(){
    cout<<"Choose an option:"<<endl;
    cout<<"1. Play"<<endl;
    cout<<"2. Your Words"<<endl;
    cout<<"3. Stats"<<endl;
    cout<<"4. Settings"<<endl;
    cout<<"5. Exit and Save"<<endl;
    cout<<"6. Exit"<<endl;

    cout<<"Your choice: ";}
void Inspect(int lvl){
  Node * p;
  p = L[lvl];
  int i=1;
  while(p)
  {
  cout<<i<<". "<<p->word<<", "<<p->defi<<", "<<p->desc<<", "<<p->lvl<<", "<<p->done<<", "<<p->source<<endl;
  p=p->next;
  i++;
  }}
int main(){
SetConsoleOutputCP(CP_UTF8);
  for(int i=0; i<6; i++) L[i] = NULL;
    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    cout <<datetime.tm_yday<<endl;
    string tajm="0";
    Node* LTotal = NULL;
    fstream fileL;
    fileL.open(path+"load.txt",ios::in);
    if (!fileL.good()){
    cout << "Failed to load previous words." << endl;
    }
    else getline(fileL,tajm);
    string Temptxt;
    while(getline(fileL,Temptxt))
    {
      string Tempworda, Tempdefia, Tempdesca, Templvla, TempdoneA, Tempsource;
      string delimiter = "; ";
      size_t start = 0;
      size_t end;
      end = Temptxt.find(delimiter, start);
      Tempworda = Temptxt.substr(start, end - start);
      cout<<Tempdefia<<", ";
      start = end + delimiter.length();
      end = Temptxt.find(delimiter, start);
      Tempdefia = Temptxt.substr(start, end - start);
      cout<<Tempworda<<", ";
      start =  end + delimiter.length();
      end = Temptxt.find(delimiter, start);
      Tempdesca = Temptxt.substr(start, end - start);
      //cout<<Tempworda<<", "<<Tempdefia<<", "<<Tempdesca<<", "<<Templvla<<TempdoneA<<endl;
      start = end + delimiter.length();
      end = Temptxt.find(delimiter, start);
      Templvla=Temptxt.substr(start, end - start);
      cout<<Templvla<<", ";
      start = end + delimiter.length();
      end = Temptxt.find(delimiter, start);
      TempdoneA = Temptxt.substr(start, end - start);
      cout<<TempdoneA<<", ";
      start = end + delimiter.length();
      end = Temptxt.find(delimiter, start);
      Tempsource = Temptxt.substr(start, end - start);
      cout<<Tempsource<<endl;
      start = end + delimiter.length();
      determineList(Tempworda,Tempdefia,Tempdesca,stoi(Templvla,0,10),stoi(TempdoneA,0,10), Tempsource);
    }
    fileL.close();
    if(stoi(tajm)==datetime.tm_yday)cout<<"same day"<<endl;
    else{
      cout<<"new day"<<endl;
      for(int i=1;i<=5;i++)
      {
        Node *p = L[i];
        while(p) {
          p->done=0;
          p = p->next;
        }
      }
    }
    char choice=0;
    cout<<"Welcome to spaced repetitiion!"<<endl;
    cout<<"For your best experience please try to do it daily."<<endl;
    while(true){
        menu();
        choice=getch();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(choice){
            case '1':
            {
                bool choiceQ=0;
                cout<<"Random(0) or not random(1):";
                cin>>choiceQ;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                switch(choiceQ)
                {
                  case 1:
                  cout<<"Play with random off"<<endl;
                  cout<<"If you want to quit questions, write '333'"<<endl;
                  for(int i=1;i<=5;i++)
                  {
                    cout<<"Level "<<i<<endl;
                    Node *p = L[i];int num=1;
                    int Wnum=l_len(L[i]);
                    while(p) {
                    if(p->done==1){
                      p = p->next;
                      continue;
                    }
                    cout << "Word "<<num<<"/"<<Wnum<<": " << p->word << endl;
                    cout << "Your answer:";
                    string ans;
                    getline(cin, ans);

                    Node* next_p = p->next;

                    if(p->defi == ans) {
                    cout << "\033[32mCorrect!\033[0m\n";
                      if(p->lvl != 5) {
                          p->lvl += 1;
                          p->done=1;
                          l_push_back(L[p->lvl], p->word, p->defi, p->desc, p->lvl,p->done, p->source);
                          l_remove(L[p->lvl-1], p);
                      }
                    } else if(ans == "333") {
                      break;
                    } else {
                      cout << "\033[31mIncorrect; the answer is \033[0m" << p->defi << endl;
                      if(p->lvl != 1)p->lvl = 1;
                      p->done=1;
                    }
                    p = next_p;
                    num++;
                    }
                  }
                  break;
                  case 0:
                  cout<<"Play with random on"<<endl;
                  srand(time(0));
                  cout<<"If you want to quit questions, write '333'"<<endl;
                  for(int i=1;i<=5;i++)
                  {
                    cout<<"Level "<<i<<endl;
                    Node *p = L[i];int num=1;
                    int undoneNum=l_len_undone(L[i]);
                    if(undoneNum==0)continue;
                    int Wnum=l_len(L[i]);
                    while(p&&undoneNum>0){
                    int rando=rand()%undoneNum;
                    for(int j=0;j<rando;j++){
                      p=p->next;
                      if(p == NULL) {
                          p = L[i]; 
                      }
                      if(p->next==NULL&&undoneNum!=0)p=L[i];
                    }
                    if(p->done==1){
                      p = p->next;
                      continue;
                    }
                    if(!p){
                      p = L[i];
                      continue;
                    }
                    cout << "Word "<<num<<"/"<<Wnum<<": " << p->word << endl;
                    cout << "Your answer:";
                    string ans;
                    getline(cin, ans);
                    Node* next_p = p->next;

                    if(p->defi == ans) {
                    cout << "\033[32mCorrect!\033[0m\n";
                      if(p->lvl != 5) {
                          p->lvl += 1;
                          p->done=1;
                          l_push_back(L[p->lvl], p->word, p->defi, p->desc, p->lvl,p->done, p->source);
                          l_remove(L[p->lvl-1], p);
                      }
                      undoneNum--;
                    } else if(ans == "333") {
                      undoneNum=0;
                      break;
                    } else {
                      cout << "\033[31mIncorrect; the answer is \033[0m" << p->defi << endl;
                      if(p->lvl != 1)p->lvl = 1;
                      p->done=1;
                      undoneNum--;
                    }
                    p = next_p;
                    num++;
                    }
                  }
                  break;
                }
                break;
            }
            case '2':
            {
            cout<<"Your Words"<<endl;
            cout<<"|"<<l_len(L[1])<<"|>>|"<<l_len(L[2])<<"|>>|"<<l_len(L[3])<<"|>>|"<<l_len(L[4])<<"|>>|"<<l_len(L[5])<<"|"<<endl;
            cout<<"Options:"<<endl;
            char Xchoice=0;
            cout<<"1. Import words"<<endl;
            cout<<"2. Add new words from keyword"<<endl;
            cout<<"3. Export words"<<endl;
            if(l_len(L[1])!=0||l_len(L[2])!=0||l_len(L[3])!=0||l_len(L[4])!=0||l_len(L[5])!=0)
            {
                cout<<"4. Inspect list"<<endl;
            }
            cout<<"Your choice: ";
            Xchoice=getch();
            switch(Xchoice){
                case '1':
                {
                    cout<<endl<<"1. Import words"<<endl;
                    string myText;
                    string name;
                    cout<<"Write the name of the file (with .txt): ";
                    cin>>name;
                    ifstream MyFile(path+name);
                    while(getline(MyFile, myText)){
                    //cout << myText;
                    string Tempword, Tempdefi, Tempdesc, Templvl,Tempsource;
                    string delimiter = "; ";
                    size_t start = 0;
                    size_t end;
                    end = myText.find(delimiter, start);
                    Tempword = myText.substr(start, end - start);
                    start = end + delimiter.length();
                    end = myText.find(delimiter, start);
                    Tempdefi = myText.substr(start, end - start);
                    start = end + delimiter.length();
                    end = myText.find(delimiter, start);
                    Tempdesc = myText.substr(start, end - start);
                    start = end + delimiter.length();
                    end = myText.find(delimiter, start);
                    Templvl='1';
                    start = end + delimiter.length();
                    end = myText.find(delimiter, start);
                    Tempsource = name;
                    start = end + delimiter.length();
                    determineList(Tempword,Tempdefi,Tempdesc,stoi(Templvl,0,10),NULL,Tempsource);
                    cout<<Tempword<<", "<<Tempdefi<<", "<<Tempdesc<<", "<<Templvl<<", "<<Tempsource<<endl;
                    }
                    MyFile.close();
                }
                break;
                case '2':
                cout<<"2. Add new words from keyword"<<endl;
                break;
                case '3':
                {
                    cout<<"3. Save words/Export file"<<endl;
                    ofstream MyFile1(path+"out.txt");
                    for(int i=1;i<=5;i++)
                    {
                      Node* p=L[i];
                      while(p)
                      {
                        MyFile1<<p->word<<"; "<<p->defi<<"; "/*<<p->desc*/<<"; "<<p->lvl<<endl;
                        p=p->next;
                      }
                    }
                    MyFile1.close();
                    cout<<"Data exported successfully"<<endl;
                }
                break;
                case '4':
                cout<<"Inspect list:"<<endl;
                cout<<"1. L1, 2. L2, 3. L3, 4. L4, 5. L5"<<endl;
                cout<<"Your choice: ";
                Xchoice=getch();
                cout<<endl;
                switch(Xchoice){
                case '1':
                {
                Inspect(1);
                break;
                }
                case '2':
                {
                Inspect(2);
                break;
                }
                case '3':
                {
                Inspect(3);
                break;
                }
                case '4':
                {
                Inspect(4);
                break;
                }
                case '5':
                {
                Inspect(5);
                break;
                }
                }
                break;
            }
            break;
            }
            case '3':
            cout<<"Stats"<<endl;
            break;
            case '4':
            {
                cout<<"Settings"<<endl;
                char Schoice=0;bool Qchoice=1;
                cout<<"1. Question type: ";
                if(Qchoice)cout<<"Open-ended question"<<endl; else cout<<"Closed-Ended question"<<endl;
                cout<<"2. Back"<<endl;
                cout<<"Your choice: ";
                Schoice=getch();
                switch(Schoice){
                    case '1':
                        !Qchoice;
                    break;
                    case '2':
                    break;break;
                    default:
                    cout<<"Incorrect choice"<<endl;
                }
                break;
            }
            case '5':
            {
              cout<<"Save and Exit"<<endl;
             ofstream MyFile1(path+"load.txt");
            MyFile1<<datetime.tm_yday<<endl;
              for(int i=1;i<=5;i++)
              {
                Node* p=L[i];
                while(p)
                {
                  //cout<<"<p->done:"<<p->done;
                  //if(p->lvl==-1163005939)cout<<"";
                  //else{
                    if(p->done==NULL)p->done=0;
                  MyFile1<<p->word<<"; "<<p->defi<<"; "<<p->desc<<"; "<<p->lvl<<"; "<<p->done<<"; "<<p->source<<endl;
                  //}
                  p=p->next;
                }
              }
              MyFile1.close();
              cout<<"Data saved successfully"<<endl;
              cout<<"Bye.";
            exit(0);
            break;
            }
            case '6':
            {
              cout<<"Exit"<<endl;
              cout<<"Bye.";
            exit(0);
            break;
            }
            default:
            cout<<"Incorrect choice"<<endl;
        }
    }
    return 0;
}
