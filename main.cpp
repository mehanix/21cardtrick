#include <iostream>
#include <string.h>
#include <time.h>
#include <algorithm>
using namespace std;

struct carte
{
    char numar[20];
    char semn[20];
} pachet[53];

struct nod
{
    carte info;
    nod* leg;
} *p1,*u1,*p2,*u2,*p3,*u3,*q,*p,*u;

char selection;

char numere[14][20] = {""," A", " 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"};
char semne[5][20] = {"","<3", "<>", "-%", "{>"};
int selected_column;

void adauga_nod_in_coloana(int nr_coloana,nod* n)
{
    switch(nr_coloana)
    {
        case 1:
        {
            if(p1==NULL)
                p1=u1=n;
                else
                {
                    u1->leg=n;
                    u1=n;
                }
            break;
        }
        case 2:
        {
            if(p2==NULL)
                p2=u2=n;
                else
                {
                    u2->leg=n;
                    u2=n;
                }
            break;
        }
        case 0:
        {
            if(p3==NULL)
                p3=u3=n;
                else
                {
                    u3->leg=n;
                    u3=n;
                }
            break;
        }
    }
}

void afiseaza_coloane(nod* p1, nod* p2, nod* p3)
{
    //afiseaza toate 3 coloane odata..un chin
    while(p1!=NULL && p2!=NULL && p3!=NULL)
    {
        cout << p1->info.numar<<' '<<p1->info.semn<<"     "<<p2->info.numar<<' '<<p2->info.semn<<"     "<<p3->info.numar<<' '<<p3->info.semn<<'\n';
        p1=p1->leg;
        p2=p2->leg;
        p3=p3->leg;
    }
}

void genereaza_coloane()
{
    //afiseaza cele 3 coloane, reamestecandu-le
    //formeaza cele 3 liste noi cu cartile rearanjate

    nod *q;
    q=p;
    int count=0;
    while(q)
    {
        count++;
        //cout<<q->info.numar<<' '<<q->info.semn<<'\n';
        adauga_nod_in_coloana(count%3,q);

        q=q->leg;
    }
    u2->leg=NULL;
    u1->leg=NULL;
    u3->leg=NULL;

}


void genereaza_pachet()
{
    //generarea pachetului - cartilor efectiv
    int nr_carte=1;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=13;j++)
            {
                strcpy(pachet[nr_carte].semn, semne[i]);
                strcpy(pachet[nr_carte].numar, numere[j]);
                nr_carte++;
            }

    //amesteca cartile!!! :D

    //set random - seteaza generarea in functie de data si ora curenta - ca sa fie diferit la fiecare rulare
    srand (time(NULL));
    //random shuffle!
    random_shuffle(&pachet[1], &pachet[53]);


    //pus primele 21 carti intr-o lista

    for(int i=1;i<=21;i++)
    {
        q=new nod;
        q->info=pachet[i];
        q->leg=NULL;
        if(p==NULL)
          {
              p=u=q;
          }
          else
          {
              u->leg=q;
              u=q;
          }


    }


    //for(int i=1;i<=52;i++)
     //   cout<<pachet[i].numar<<' '<<pachet[i].semn<<'\n';
}

void place_in_middle(int selected_column)
{
    //refa lista p, cu coloana selected_column in mijlocul celorlalte doua
    //sterge lista veche cu alea 21 de carti

    p=u=NULL;

    switch (selected_column)
    {

        case 1:
        {
            //daca prima e cea selectata, ordinea coloanelor: 2-1-3

            p=p2;
            u2->leg=p1;
            u1->leg=p3;
            u=u3;
            break;
        }
        case 2:
        {
            //daca a doua e cea selectata, ordinea coloanelor:1-2-3
            p=p1;
            u1->leg=p2;
            u2->leg=p3;
            u=u3;
            break;
        }
        case 3:
        {
            //daca a 3a e cea selectata.. ordinea coloanelor:1-3-2
            p=p1;
            u1->leg=p3;
            u3->leg=p2;
            u=u2;
            break;
        }
    }
    p1=u1=p2=u2=p3=u3=NULL;
        //temp afis.. to be removed!!!!!!!

}

nod* find_card()
{
    for(int i=1;i<=10;i++)
    {
        p=p->leg;
    }
    return p;
}

int main()
{
    cout << "Hello! Bine ai venit la trucul de carti.\nApasa 1 pentru a incepe, si orice altceva pentru a iesi din program." << endl;
    cin>>selection;

    if(selection=='1')
    {
        //1.
        genereaza_pachet();
        system("cls");

        //2.
        cout<<"Se afiseaza cele 3 coloane de carti..\n";
        genereaza_coloane();
        afiseaza_coloane(p1,p2,p3);

        //3.
        cout<<"\nAlege o carte dintre toate astea si spune-mi in care din coloane se afla!\n(introdu numarul coloanei):";
        cin>>selected_column;

        //4,5.
        place_in_middle(selected_column);
        system("cls");

        //6.
        genereaza_coloane();
        afiseaza_coloane(p1,p2,p3);

        //7.
        cout<<"\nAm reamestecat pachetul.\nIn ce coloana este cartea aleasa de tine acum?";
        cin>>selected_column;

        //8.
        place_in_middle(selected_column);
        system("cls");

        //9.
        genereaza_coloane();
        afiseaza_coloane(p1,p2,p3);

        //10.
        cout<<"\nUltima data!\nIn ce coloana se afla cartea ta acum?";
        cin>>selected_column;

        //11.
        place_in_middle(selected_column);
        system("cls");

        //12. cartea ar trebui sa fie a 11-a in pachet acum.. facem parcurgerea finala!

        nod *your_card=find_card();
        cout<<"Asta este tot! Acum stiu cartea ta :D\n\n\nCartea ta este:"<<your_card->info.numar<<' '<<your_card->info.semn<<"\n\n\n";

        //"readKey din c#"

        cin>>selection;
    }
     else
    {
        cout<<"Pa-pa!";
        cin>>selection;

        return 0;
    }
}
