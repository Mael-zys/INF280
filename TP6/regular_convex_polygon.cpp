# include<stdlib.h>
# include<iostream>
# include<cmath>

using namespace std;

class point {
private:
    double x;
    double y;
public:
    point() {
        x=0.0; y=0.0;
    }
    point(double in_x, double in_y): x(in_x), y(in_y) {}

    void setCoordinate(double in_x, double in_y) {
        x = in_x;
        y = in_y;
    }

    double distance(point p, point q) {
        return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
    }
};

class angle {
private:
    double alpha;
public:
    double EPS = 1e-6;
    angle() {
        alpha=0.0;
    }
    angle(double in_alpha): alpha(in_alpha) {}

    angle remainder(angle num, angle denum) {
        angle temp;
        temp.alpha = ((num.alpha / denum.alpha) - round(num.alpha / denum.alpha)) * denum.alpha;
        return temp;
    }

    double get_angle() {
        return alpha;
    }

    bool operator == (angle beta) const {
        return (fabs(alpha - beta.alpha) < EPS);
    }
};

class triangle : public point, public angle{
public:
    point A, B, C; // 3 points
    double a, b, c; // 3 edges
    angle alpha, beta, gamma; // 3 angles
    
    double cal_angle(double l1, double l2, double l3) {
        return acos((l1*l1 + l2*l2 - l3*l3) / (2 * l1 * l2)) * 180.0 / M_PI;
    }
};

class cercle_circonscrit : public triangle{
public:

    // my original idea is to first calculate the barycentre and then the 3 central angles, but this is a little complex,
    // because I have to calculate all angles and then the tan() in order to calculate the barycentre.
    // // O = barycentre((A; tan(beta) + tan(gamma) ),(B; tan(alpha) + tan(gamma) ); (C; tan (alpha) + tan (beta))).
    point barycentre() {
        ;
    }

    angle central_alpha, central_beta, central_gamma;

    // In fact, we can directly calculate the central angles using Law of cosines and inscribed angle theorem.
    // The inscribed angle theorem states that an angle θ inscribed in a circle is half of the central angle 2θ
    double central_angle(double l1, double l2, double l3) {
        return 2 * cal_angle(l1, l2, l3);
    }
};


int main() {
    cercle_circonscrit CC;
    double temp1, temp2, temp3, temp4, temp5, temp6;
    while (cin >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6) {
        CC.A.setCoordinate(temp1, temp2);
        CC.B.setCoordinate(temp3, temp4);
        CC.C.setCoordinate(temp5, temp6);

        CC.a = CC.distance(CC.B, CC.C);
        CC.b = CC.distance(CC.A, CC.C);
        CC.c = CC.distance(CC.A, CC.B);
        // cout << CC.a << " " << CC.b << " " <<CC.c<<endl;
        
        CC.central_alpha = CC.central_angle(CC.b, CC.c, CC.a);
        CC.central_beta = CC.central_angle(CC.a, CC.c, CC.b);
        CC.central_gamma = CC.central_angle(CC.a, CC.b, CC.c);
        // cout<<(CC.central_alpha.get_angle()) << " " <<(CC.central_beta.get_angle()) << " " <<(CC.central_gamma.get_angle()) <<endl;
        
        angle zero(0.0);
        for (int i = 3; i <= 1000; i++) {
            angle temp(2*180.0/(i/1.0));
            // cout << i << " " << temp.get_angle()<<endl;

            if (CC.remainder(CC.central_alpha, temp) == zero && CC.remainder(CC.central_beta, temp) == zero && CC.remainder(CC.central_gamma, temp) == zero) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}