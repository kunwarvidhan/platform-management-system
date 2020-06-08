#include <bits/stdc++.h>
//#include<conio.h>
using namespace std;
int mu = 1, full = 0, emp = 5, x = 0;
char a[5] = {'-', '-', '-', '-', '-'};
int leave[1000], it = 0, ok = 1;

//Display Function

void display()
{
    cout << "\t\t\tPLATFORM MANAGEMENT SYSTEM\n\n";
    cout << "The railway station contains 5 platforms, a train can be halted at any of the 5 platforms as per the station master's choice.\n";
    cout << "The trains are managed according to their arrival times and if the arrival time is same then priority of that train is taken into consideration.\n";
    cout << "Similarly a train from any platform can be departed. \n";
    cout << "Priority List\n1 - Rajdhani Express \n2 - Shatabdi Express \n3 - Other Premium and Superfast Trains \n4 - Express/Mail Trains \n5 - Passenger Trains.\n\n";
}

//struture of train 

struct train
{
    int p, hr, m, stay, minutes;
    bool stat = false;
};

//structure of platform

struct platform
{
    bool status = false;
    int rt = -1;
    int t;
};

int n;
struct train train[100]; //object  
struct platform p[5]; //object

//comparison funtion
bool comp(struct train a, struct train b)
{
    if (a.minutes < b.minutes)
    {
        return true;
    }
    else if (a.minutes == b.minutes)
    {
        if (a.p < b.p)
            return true;
        else
            return false;
    }
    else
        return false;
}

//Semaphore
int wait(int s)
{
    return (--s);
}

int signal(int s)
{
    return (++s);
}

//Producer
int entry(int n, int r)
{
    mu = wait(mu);
    train[n].stat = true; 
    int f = 0;
    for (int i = 0; i < 5; i++)
    {
        if (p[i].status == false)
        {
            f = 1;
            full = signal(full);
            emp = wait(emp);
            cout << "Train " << n + 1 << " goes into platform " << i + 1 << " at : " << (r / 60 <= 23 ? r / 60 : r / 60 - 24) << ":" << r % 60 << "\n";
            a[i] = '*';
            cout << "Platform Status " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << "\n\n";
            return i;
        }
    }
    if (!f)
        cout << "All platforms are busy\n";
    mu = signal(mu);
    return -1;
}

//Consumer

void exit1(int n, int r, int m)
{
    mu = wait(mu);

    if (ok)
    {
        leave[it] = r;
        ok = 0;
    }
    for (int i = 0; i < it; i++)
    {
        if (r == leave[i])
        {
            leave[it] = leave[it - 1] + 1;
            r = leave[it];
        }
        else
        {
            leave[it] = r;
        }
    }
    it++;

    if (r % 60 > 9)
        cout << "Train " << n + 1 << " goes out at: " << (r / 60 <= 23 ? r / 60 : r / 60 - 24) << ":" << (r % 60) << "\n";
    else
        cout << "Train " << n + 1 << " goes out at: " << (r / 60 <= 23 ? r / 60 : r / 60 - 24) << ":0" << (r % 60) << "\n";
    a[m] = '-';
    cout << "Platform Status " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << "\n\n";
    full = wait(full);
    emp = signal(emp);
    mu = signal(mu);
}

int main()
{
    display();
    int p1 = 2;
    while (p1 != 1)
    {
        cout << "Enter no of trains: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter priority , arrival time(HH MM) and stay time(MM) : ";
            cin >> train[i].p >> train[i].hr >> train[i].m >> train[i].stay;
            train[i].minutes = train[i].hr * 60 + train[i].m;
        }
        sort(train, train + n, comp);
        int j = 0, k;
        cout << "\nPlatform Status " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << "\n\n";
        for (int i = 0; i <= 1440; i++)
        {
            if (j < n)
            {
                if (train[j].minutes <= i && train[j].stat == false)
                {
                    k = entry(j, i);
                    if (k != -1)
                    {
                        p[k].status = true;
                        p[k].rt = train[j].minutes + train[j].stay;
                        p[k].t = j;
                        j++;
                    }
                }
            }
            for (int m = 0; m < 5; m++)
            {
                if (p[m].rt == i)
                {
                    p[m].status = false;
                    exit1(p[m].t, i, m);
                }
            }
        }
        cout<<"Press 1 to Exit and 2 to Continue: ";
        cin>>p1;
    }
    return 0;
}
/*Enter no of trains: 10
Enter priority , arrival time(HH:MM) and stay time(MM)1 12 55 5
Enter priority , arrival time(HH:MM) and stay time(MM)2 12 45 10
Enter priority , arrival time(HH:MM) and stay time(MM)1 13 30 30
Enter priority , arrival time(HH:MM) and stay time(MM)3 13 10 50
Enter priority , arrival time(HH:MM) and stay time(MM)2 13 15 5
Enter priority , arrival time(HH:MM) and stay time(MM)1 12 53 7
Enter priority , arrival time(HH:MM) and stay time(MM)1 13 16 4
Enter priority , arrival time(HH:MM) and stay time(MM)1 13 45 15
Enter priority , arrival time(HH:MM) and stay time(MM)1 14 10 5
Enter priority , arrival time(HH:MM) and stay time(MM)1 14 0 10
Platform Status - - - - -
Train 1 goes into platform 1
Platform Status * - - - -
Train 2 goes into platform 2
Platform Status * * - - -
Train 3 goes into platform 3
Platform Status * * * - -
Train 1 goes out at: 12:55
Platform Status - * * - -
Train 2 goes out at: 13:00
Platform Status - - * - -
Train 3 goes out at: 13:00
Platform Status - - - - -
Train 4 goes into platform 1
Platform Status * - - - -
Train 5 goes into platform 2
Platform Status * * - - -
Train 6 goes into platform 3
Platform Status * * * - -
Train 5 goes out at: 13:20
Platform Status * - * - -
Train 6 goes out at: 13:20
Platform Status * - - - -
Train 7 goes into platform 2
Platform Status * * - - -
Train 8 goes into platform 3
Platform Status * * * - -
Train 9 goes into platform 4
Platform Status * * * * -
Train 4 goes out at: 14:00
Platform Status - * * * -
Train 7 goes out at: 14:00
Platform Status - - * * -
Train 8 goes out at: 14:00
Platform Status - - - * -
Train 10 goes into platform 1
Platform Status * - - * -
Train 9 goes out at: 14:10
Platform Status * - - - -
Train 10 goes out at: 14:15
Platform Status - - - - -

Process returned 0 (0x0)   execution time : 119.884 s
Press any key to continue.
*/