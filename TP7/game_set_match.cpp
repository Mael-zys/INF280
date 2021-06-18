# include <stdlib.h>
# include <iostream>
#include <iomanip>      // std::setprecision
#include <math.h>

using namespace std;

// my idea:
// https://drive.google.com/drive/folders/1EbknrYXeGm-WeoeAKiWTjCdoGpOoNZ-k?usp=sharing

double cal_pro_game(double p) {
    double p4 = pow(p, 4.0);
    return p4 + 4.0*p4*(1.0-p) + 10.0*p4 * pow((1.0-p), 2.0) + 20.0*p4*p*pow((1.0-p), 3.0)/(1.0-2.0*p*(1.0-p));
}

double cal_pro_set(double p, double pg) {
    double pg6 = pow(pg, 6.0);
    double p7 = pow(p, 7.0);
    return pg6 + 6.0*pg6*(1.0-pg) + 21.0*pg6*pow((1.0-pg), 2.0) + 56.0*pg6*pow((1.0-pg), 3.0) + 126.0*pg6*pow((1.0-pg), 4.0) + \
    252.0*pg6*pg*pow((1.0-pg), 5.0) + 504.0*pg6*pow((1.0-pg), 6.0) * (p7 + 7.0*p7*(1.0-p) + 28.0*p7*pow((1.0-p), 2.0) + \
    84.0*p7*pow((1.0-p), 3.0) + 210.0*p7*pow((1.0-p), 4.0) + 462.0*p7*pow((1.0-p), 5.0) + 924.0*p7*p*pow((1.0-p), 6.0)/(1.0-2.0*p*(1.0-p))); 
}

double cal_pro_match(double p_set) {
    return 3.0*pow(p_set, 2.0) - 2.0*pow(p_set, 3.0);
}

int main() {
    double p;
    while (cin >> p && p >= 0.0) {
        if (p == 0.0 || p == 1.0 || p == 0.5) {
            cout << fixed << setprecision(11) << p << " " << p << " " << p << endl;
            continue;
        }

        double p_game = cal_pro_game(p);
        double p_set = cal_pro_set(p, p_game);
        double p_match = cal_pro_match(p_set);
        cout << fixed << setprecision(11) << p_game << " " << p_set << " " << p_match << endl;
    }
    return 0;
}