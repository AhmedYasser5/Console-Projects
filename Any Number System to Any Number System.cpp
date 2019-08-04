#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int numbers (char);
double Decimal ();
void NonDecimal (double, int);
void result (int, int[], int, int[], int&);
void numbers (int, int[], int&);
void number_sys (int);
int ct;
int R;
int main()
{
	double sum;
	char L;
	cout<<"How many numbers you want after the radix point?\n";
	cin>>R;
	while (R<0)
	{
		cout<<"Enter a valid number:\n";
		cin>>R;
	}
	do{
		sum=Decimal();
		if (ct==10) cout<<setprecision(R)<<fixed<<sum;
		else if (ct!=10) NonDecimal(sum, ct);
		cout<<"\n\nDo you have another number to convert? Enter \'y\' for yes and \'n\' for no:\n";
		cin>>L;
		while (L!='y' && L!='n')
		{
			cout<<"Enter a valid answer --> ";
			cin>>L;
		}
	} while (L=='y');
	cout<<"\nThank you for trusting the app! :)";
	return 0;
}

double Decimal ()
{
	char x[99];
	int m[99], n[99], i, j, k=0, y, k0=0, c;
	double sum=0;
	cout<<"\nEnter a number in any number system --> ";
	cin>>x;
	while (x[k0]!='\0')
	{
		c=x[k0];
		if (c==46) k++;
		if (((c<48 || c>58) && (c<65 || c>90) && c!=46) || k>1)
		{
			if (c==45) cout<<"Sorry! This app is not prepared for negative numbers!\n";
			cout<<"Enter a valid number using only numbers and capital letters --> ";
			cin>>x;
			k0=0;
			continue;
		}
		k0++;
	}
	cout<<"\nEnter the base number you want to convert from --> ";
	cin>>y;
	for (i=0;i<99;i++)
	{
		if (x[i]=='\0' || x[i]=='.')
		{
			i--;
			break;
		}
		m[i]=numbers (x[i]);
	}
	k=i+2; k0=0;
	while (k0<=i)
	{
		if (m[k0]>=y)
		{
			cout<<"Enter a valid base number --> ";
			cin>>y;
			k0=0;
			continue;
		}
		k0++;
	}
	k0=0;
	if (x[i+1]=='.' && x[i+2]!='\0')
	{
		for (j=1;x[k]!='\0';j++)
		{
			n[j-1]=numbers (x[k]);
			k++;
		}
		j--;
		while (k0<=j-1)
		{
			if (n[k0]>=y)
			{
				cout<<"Enter a valid base number --> ";
				cin>>y;
				k0=0;
				continue;
			}
			k0++;
		}
	}
	cout<<"\nEnter the base number you want to convert to --> ";
	cin>>ct;
	while (ct<2 || ct==y)
	{
		if (ct==y) cout<<"That's nonsense:\nYour number equals itself in the same number system!\nEnter another valid base number --> ";
		else cout<<"Enter a valid base number --> ";
		cin>>ct;
	}
	if (x[i+1]=='.' && x[i+2]!='\0') for (j;j>0;j--)
		sum+=n[j-1]*pow(y,-j);
	k=i;
	for (i;i>=0;i--)
		sum+=m[i]*pow(y,k-i);
	return sum;
}

int numbers (char a)
{
	int c;
	switch (a)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			c=a-48;
			break;
		default:
			c=a-55;
	}
	return c;
}

void NonDecimal (double x, int y)
{
	double x2;
	int r[99999], i, x1, k, m[R], X;
		X=0;
		//if (x<0) x=-x;
		x1=x;
		x2=x-x1;
		for (i=0; x1>0; i++)
		{
			r[i]=x1%y;
			x1/=y;
		}
		for (k=0; x2<0 || k<R; k++)
		{
			m[k]=x2*y;
			x2=x2*y-m[k];
		}
		i--; k--;
		cout<<endl<<"\nYour number equals";
		cout<<endl<<'[';
		//if (s<0) cout<<'1';
		result (i, r, k, m, X);
		if (x==0) cout<<'0';
		cout<<']';
		cout<<" in ";
		number_sys (y);
		//if (s<0) cout<<" in sign and magnitude form";
		if (X) cout<<"\n\nNote:\n\tNumbers between circular brackets  (_) couldn't be written using letters";
	return;
}

void result (int i, int r[], int k, int m[], int &X)
{
	for (i; i>=0; i--)
		numbers (i, r, X);
	cout<<'.';
	for (k=0; k<R; k++)
		numbers (k, m, X);
	int q=R-1;
	while (m[q]==0 && q>-1)
	{
		cout<<'\b';
		q--;
	}
	if (q==-1) cout<<'\b';
	return;
}

void numbers (int b, int a[], int &X)
{
	if (a[b]>=10 && a[b]<=35) 
	{
		char c;
		c='A'+a[b]-10;
		cout<<c;
	}
	else if (a[b]<10) cout<<a[b];
	else
	{
		cout<<'('<<a[b]<<')';
		X++;
	}
	return;
}

void number_sys (int y)
{
	switch (y)
	{
		case 2:
			cout<<"binary";
			break;
		case 8:
			cout<<"octal";
			break;
		case 10:
			cout<<"decimal";
			break;
		case 16:
			cout<<"hexadecimal";
			break;
		default:
			switch (y%10)
			{
				case 1:
					cout<<y<<"st";
					break;
				case 2:
					cout<<y<<"nd";
					break;
				case 3:
					cout<<y<<"rd";
					break;
				default:
					cout<<y<<"th";
			}
	}
	cout<<" number system";
	return;
}
