# include<stdlib.h>
# include<iostream>
# include<cmath>
# include<vector>
# include<algorithm>
# include<stdio.h>

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

    double get_x() {
        return x;
    }

    double get_y() {
        return y;
    }

    double distance(point p, point q) {
        return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
    }

    double cross_product(point p, point q) {
        return p.x * q.y - q.x * p.y;
    }
};

class angle {
private:
    double alpha;
public:
    double EPS = 1e-10;
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

    void set_angle(double beta) {
        alpha = beta;
    }

    bool operator == (angle beta) const {
        return (fabs(alpha - beta.alpha) < EPS);
    }

    bool operator < (angle beta) const {
        return (alpha < beta.alpha);
    }

    bool operator > (angle beta) const {
        return (alpha > beta.alpha);
    }
};


class polar_coordinate : public angle {
public:
    double polar_length;
    angle polar_angle;

    bool cmp_angle (polar_coordinate b) {
        return (polar_angle < b.polar_angle);
    }

    polar_coordinate() {
        polar_length = 0;
        polar_angle = angle();
    }

    polar_coordinate(double l, double a) {
        polar_length = l;
        polar_angle = angle(a);
    }
};

class polar_system : public polar_coordinate {
public:
    vector<polar_coordinate> points_polar;

    polar_system() {
        ;
    }

    polar_system(int size) {
        points_polar = vector<polar_coordinate>(size, polar_coordinate());
    }

    // transform point from cartesien to polar
    void transform_point_cartesien_polar(point & points_cartesien) {
        polar_coordinate temp;

        double x = points_cartesien.get_x();
        double y = points_cartesien.get_y();
        
        temp.polar_length = hypot(x, y);
        temp.polar_angle.set_angle(atan2(y,x) <= 0 ? atan2(y,x) + 2*M_PI : atan2(y,x)); 
        // printf("%lf %lf %lf\n", x, y, temp.polar_angle);
        points_polar.push_back(temp);
    } 
};

// change the angle which is larger than pi to the range (0, pi), and then compare them
bool cmp(polar_coordinate pc1, polar_coordinate pc2) {
    angle pi(M_PI), temp1(pc1.polar_angle.get_angle()), temp2(pc2.polar_angle.get_angle());
    if (temp1 > pi) temp1.set_angle(temp1.get_angle() - M_PI);
    if (temp2 > pi) temp2.set_angle(temp2.get_angle() - M_PI);

    return ((temp1 == temp2 && pc1.polar_angle < pc2.polar_angle) || temp1 < temp2);
}

int main() {
    int num_point;
    while (cin >> num_point) {
        polar_system ps;
        int x1, x2, high_rank = 1, low_rank = 1, x1_temp, x2_temp, y_axis1 = 0, y_axis2 = 0;
        point temp;
        cin >> x1 >> x2;

        for (int i = 0; i < num_point - 1; i++) {
            cin  >> x1_temp >> x2_temp;
            x1_temp -= x1;
            x2_temp -= x2;
            if (x1_temp == 0 && x2_temp == 0) low_rank++;
            else if (x1_temp > 0) { 
                high_rank++;
                low_rank++;
            }
            else if (x1_temp == 0) {
                low_rank++; 
                if (x2_temp > 0) y_axis1++;
                else if (x2_temp < 0) y_axis2++;
            }
            if (x1_temp * x2_temp <= 0 && x1_temp!=0) {
                temp.setCoordinate(x1_temp, x2_temp);
                ps.transform_point_cartesien_polar(temp);
            }
        }

        sort(ps.points_polar.begin(), ps.points_polar.end(), cmp);

        // for (int i = 0; i < ps.points_polar.size(); i++) {
        //     cout << ps.points_polar[i].polar_angle.get_angle() << " " << ps.points_polar[i].polar_angle.get_angle() - M_PI << " " << ps.points_polar[i].polar_length << endl;
        // }

        // cout << rank << endl;
        int h = high_rank+y_axis1, l = low_rank-y_axis2;
        angle pi(M_PI), zero(0.0);
        int i = 0, flag = 0;
        while (!ps.points_polar.empty() && i < ps.points_polar.size() - 1) {
            int sum_h = 0, sum_l = 0, ins = 0, des = 0;
            angle temp_angle1(ps.points_polar[i].polar_angle.get_angle());
            angle temp_angle2(ps.points_polar[i+1].polar_angle.get_angle());
            do {
                if ((temp_angle1 > zero && temp_angle1 < pi) || temp_angle1 == pi) {
                    sum_l++;
                }
                else {
                    sum_h--;
                }
                i++;
                if (i >= ps.points_polar.size() - 1) break;
                temp_angle1 = angle(ps.points_polar[i].polar_angle.get_angle());
                temp_angle2 = angle(ps.points_polar[i+1].polar_angle.get_angle());
            } while ((temp_angle1 == temp_angle2 || temp_angle1 == angle(temp_angle2.get_angle() - M_PI) || temp_angle1 == angle(temp_angle2.get_angle() + M_PI)));

            if (i <= ps.points_polar.size() - 1) {
                temp_angle1 = angle(ps.points_polar[i-1].polar_angle.get_angle());
                temp_angle2 = angle(ps.points_polar[i].polar_angle.get_angle());
                if (temp_angle1 == temp_angle2 || temp_angle1 == angle(temp_angle2.get_angle() - M_PI) || temp_angle1 == angle(temp_angle2.get_angle() + M_PI)) {
                    flag = 1;
                    if ((temp_angle2 > 0 && temp_angle2 < pi) || temp_angle2 == pi) {
                        sum_l++;
                    }
                    else {
                        sum_h--;
                    }
                    i++;
                }
            }
            high_rank = min(high_rank, h + sum_h);
            low_rank = max(low_rank, l + sum_l);

            h += sum_h + sum_l;
            l += sum_h + sum_l;
            // cout << high_rank << " " << low_rank << endl;
        }

        if (!ps.points_polar.empty() && flag == 0 && i < ps.points_polar.size()) {
            angle temp_angle(ps.points_polar[i].polar_angle.get_angle());
            // cout << ps.points_polar[i].polar_angle.get_angle() << endl;
            if ((temp_angle > zero && temp_angle < pi) || temp_angle == pi) {
                l++;
                h++;
            }
            else {
                h--;
                l--;
            }
            high_rank = min(high_rank, h);
            low_rank = max(low_rank, l);
        }

        cout << high_rank << " " << low_rank << endl;
    }
    return 0;   
}