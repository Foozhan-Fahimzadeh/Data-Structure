//Foozhan Fahimzade 400442306
#include <bits/stdc++.h>
#include <math.h>
using namespace std;
double P = 3.14;
class AdadMokhtalet
{
private:
    double real, imag;

public:
    AdadMokhtalet(double r = 0, double i = 0)
    {
        real = r;
        imag = i;
    }

    AdadMokhtalet(int n)
    {
        real = cos(2 * P / n);
        imag = sin(2 * P / n);
    }

    AdadMokhtalet operator*(AdadMokhtalet const &x)
    {
        AdadMokhtalet ans;
        ans.real = real * x.real - imag * x.imag;
        ans.imag = real * x.imag + imag * x.real;
        return ans;
    }


    AdadMokhtalet operator+(AdadMokhtalet const &x)
    {
        AdadMokhtalet ans;
        ans.real = real + x.real;
        ans.imag = imag + x.imag;
        return ans;
    }

    AdadMokhtalet operator*(double const &x)
    {
        AdadMokhtalet ans;
        ans.real = real * x;
        ans.imag = imag * x;
        return ans;
    }

    void setR(double r)
    {
        real = r;
    }
    double getR()
    {
        return real;
    }
    void setI(double i)
    {
        imag = i;
    }
    double getI()
    {
        return imag;
    }
};

AdadMokhtalet pow(AdadMokhtalet d, int n)
{
    AdadMokhtalet ans(1, 0);
    for (int i = 0; i < n; i++)
    {
        ans.setI((ans * d).getI());
        ans.setR((ans * d).getR());
    }
    return ans;
}

AdadMokhtalet func(AdadMokhtalet d, double *a, int n)
{
    AdadMokhtalet ans;
    for (int i = 0; i < n; i++)
    {
        ans = ans + pow(d, i) * a[i];
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    double *a = new double[n];
    AdadMokhtalet d(n);
    AdadMokhtalet *b = new AdadMokhtalet[n];

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = func(pow(d, i), a, n);
        cout << "b[" << i << "] = " << b[i].getR();
        if (b[i].getI() > 0)
        {
            cout << " + " << b[i].getI() << " * i";
        }
        else if (b[i].getI() < 0)
        {
            cout << " - " << -1 * b[i].getI() << " * i";
        }
        cout << endl;
    }

    delete b;
    delete a;
}
