#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"conio.h"
using namespace std;

class market
{
    long prod_no;
    char prod_name[25];
    float price;
    int stock;
public:
    friend void show(market l);
    void buy_prod();
    void create_prod();
    void show_prod();
    void modify_prod();
    void del();
};

class market1:public market
{
    public:
        market1()
        {
        }
        ~market1()
        {
        }
       void modify()
       {
           modify_prod();
       }
}p;



void enter()
{
    char pswd[15]="";
    char ch;
    int count=0;
    st:
    if(count==3)
    {
        cout<<"\n\nSorry, You are not allowed to access the Supermarket Billing System.....";
        exit(0);
    }
    else
    {
        int i=0;
    cout<<"\n\n\n\t\tEnter the password to enter Supermarket Billing System\n\t\t\t\t\t";
    ch=getch();
    while(ch!='\n')
    {
       pswd[i]=ch;
       cout<<"*";
       i++;
       ch=getch();
    }
    if(strcmp(pswd,"supermarket")==0)
    {
        cout<<"\n\t\t\t\tCorrect Password.....";
    }
    else
    {
        count++;
        if(count<3)
        cout<<"\n\t\tIncorrect Password...., Please enter correct password....";
        goto st;
    }
    }
}

void market::create_prod()
{
    ofstream x;
    x.open("Bill.dat",ios::app|ios::binary);
    char con;
    do
    {
    cin.ignore();
    cout<<"\nEnter the product name ";
    cin.getline(prod_name,25);
    cout<<"Enter the product id no. ";
    cin>>prod_no;
    cout<<"Enter the price of the Product ";
    cin>>price;
    cout<<"Enter the quantity of the product to add in the stock ";
    cin>>stock;
    x.write((char*)this,sizeof(market));
    cout<<"\nDo you want add more products?(y/n) ";
    cin>>con;
    }while(con=='y');
    x.close();
}

void show(market s)
{
    cout<<setw(5)<<s.prod_no<<setw(27)<<s.prod_name<<setw(17)<<(float)s.price<<setw(15)<<s.stock<<"\n";
}

void market::show_prod()
{
    ifstream y;
    y.open("Bill.dat",ios::in|ios::binary);
      cout<<"\n-------------------------------------------------------------------------------\n";
    cout<<"Prod Id"<<setw(26)<<"Product Name"<<setw(17)<<"Price"<<setw(15)<<"Stock"<<"\n";
    cout<<"-------"<<setw(26)<<"------------"<<setw(17)<<"-----"<<setw(16)<<"-----\n";
    while(!y.eof())
    {
        y.read((char*)this,sizeof(market));
        if(y.eof())
            break;
            show(p);
    }
      cout<<"\n-------------------------------------------------------------------------------";
    y.close();
}

void market::modify_prod()
{
    int pos,f,st,flag;
    float pr;
    char con;
    fstream z;
    long no;
    do
    {
        flag=0;
    cout<<"\nEnter the product id of the product you want to modify ";
    cin>>no;
    z.open("Bill.dat",ios::in|ios::out|ios::binary);
    while(z)
    {
        pos=z.tellg();
        z.read((char*)this,sizeof(market));
        if(z.eof())
            break;
        if(prod_no==no)
        {
            flag=1;
            break;
        }
    }
    try
    {
    if(flag==1)
    {
        cout<<"\n-------------------------------------------------------------------------------";
        cout<<"\nThe product details are:-\n";
    cout<<"Prod Id"<<setw(26)<<"Product Name"<<setw(17)<<"Price"<<setw(15)<<"Stock"<<"\n";
    cout<<"-------"<<setw(26)<<"------------"<<setw(17)<<"-----"<<setw(16)<<"-----\n";
        show(p);
        cout<<"\n-------------------------------------------------------------------------------\n";
         cout<<"\nWhich field of the following you wanna modify?\n1.Stock\n2.Price";
         cout<<"\nEnter your choice ";
            cin>>f;
            switch(f)
            {
                case 1:cout<<"Enter the New stock position of product "<<prod_name<<" ";
                cin>>st;
                stock=st;
                z.seekg(pos);
                z.write((char*)this,sizeof(market));
                break;
                case 2:cout<<"Enter the New price of the product "<<prod_name<<" ";
                cin>>pr;
                price=pr;
                z.seekg(pos);
                z.write((char*)this,sizeof(market));
                break;
                default:cout<<"Enter correct choice....";
            }
            cout<<"\nRecord Modified....";
    }
    else
    throw flag;
    }
    catch(int a)
    {
        cout<<"There is no product available with the entered id...";
    }
    z.close();
    cout<<"\n\nDo you wanna modify more product details?(y/n) ";
    cin>>con;
    }while(con=='y');
}

void market::buy_prod()
{
    fstream w;
    float pr=0.0;
    char pn[20][25];
    int q[20],i=0,c=0;
    float r[20],cd[20];
    long no;
    char con;
    int qnty,pos,flag;
    do
    {
        flag=0;
    cout<<"\nEnter the product id of product,customer wanna buy ";
    cin>>no;
    w.open("Bill.dat",ios::in|ios::out|ios::binary);
    while(!w.eof())
    {
        pos=w.tellg();
        w.read((char*)this,sizeof(market));
        if(w.eof())
            break;
        if(prod_no==no)
        {
            flag=1;
            break;
        }
    }
  try
    {
    if(flag==1)
    {
          cout<<"\n-------------------------------------------------------------------------------";
        cout<<"\nThe product details are:-\n";
    cout<<"Prod Id"<<setw(26)<<"Product Name"<<setw(17)<<"Price"<<setw(15)<<"Stock"<<"\n";
    cout<<"-------"<<setw(26)<<"------------"<<setw(17)<<"-----"<<setw(16)<<"-----\n";
        show(p);
    cout<<"\n-------------------------------------------------------------------------------\n";
        st:
        cout<<"\nEnter the quantity of product customer wanna buy ";
        cin>>qnty;
        if(qnty>stock)
        {
            cout<<"\nSorry, Quantity of the product available is limited...";
            cout<<"\nPlease enter a valid quantity....";
            goto st;
        }
        else
        {
            w.seekg(pos);
            stock=stock-qnty;
            w.write((char*)this,sizeof(market));
            r[i]=price;
            q[i]=qnty;
            cd[i]=price*qnty;
            strcpy(pn[i],prod_name);
            i++;
            pr=pr+(price*qnty);
            cout<<"\nProduct has been successfully sold...";
        }
    }
    else
        throw flag;
    }
    catch(int a)
    {
        cout<<"There is no product available with the entered id...";
    }
    w.close();
    cout<<"\n\nDo customer wanna buy more products?(y/n) ";
    cin>>con;
    }while(con=='y');
    cout<<"\n-------------------------------------BILL--------------------------------------\n";
    cout<<"Sr.No."<<setw(20)<<"Product Name"<<setw(17)<<"Qty"<<setw(15)<<"Price"<<setw(15)<<"Total"<<"\n";
    cout<<"------"<<setw(20)<<"------------"<<setw(17)<<"---"<<setw(15)<<"-----"<<setw(16)<<"-----\n";
     for(int l=0;l<i;l++)
    cout<<" "<<++c<<setw(23)<<pn[l]<<setw(17)<<q[l]<<setw(15)<<r[l]<<setw(15)<<cd[l]<<"\n";
     cout<<"\n\n\t\t\tThe total amount to be paid :"<<pr;
     cout<<"\n-------------------------------------------------------------------------------";
}

void market::del()
{
    ifstream b;
    ofstream c;
    long pd;
    cout<<"Enter the product id to delete product ";
    cin>>pd;
    b.open("Bill.dat",ios::in|ios::binary);
    c.open("Bill1.dat",ios::app|ios::binary);
    while(b)
    {
        b.read((char*)this,sizeof(market));
        if(b.eof())
            break;
            if(pd!=prod_no)
            c.write((char*)this,sizeof(market));
    }
    cout<<"Record Deleted......";
    b.close();
    c.close();
    remove("Bill.dat");
    rename("Bill1.dat","Bill.dat");
}

int main()
{
    int ch;
    char con;
    enter();
    cout<<"\n\n\t       $$$$$$$$ Welcome to Supermarket Billing System $$$$$$$$$";
    do
    {
    cout<<"\n\nEnter what you wanna do\n0.Create\n1.Show\n2.Modify\n3.Buy\n4.Delete\n5.Exit\n";
    cout<<"Enter your choice ";
    cin>>ch;
    switch(ch)
    {
        case 0:p.create_prod();
        break;
        case 1:p.show_prod();
        break;
        case 2:p.modify();
        break;
        case 3:p.buy_prod();
        break;
        case 4:p.del();
        break;
        case 5:break;
        default:cout<<"Enter correct choice....";
    }

    }while(ch!=5);
    cout<<"\n\n\t    $$$$$$$ Thankyou for using Supermarket Billing System $$$$$$$";
    return 0;
}
