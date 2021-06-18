# include<stdlib.h>
# include<iostream>
# include<cmath>
# include<vector>

using namespace std;

# define inf 0x3f3f3f3f;

// idea: first calculate the barycenter and the total weights(area) of the machine. 
// we can use the fomula (Aire d'un polygone) learned in course to calculate the total weights.
// and use the following formula to calculate the barycenter of this polygone.
// https://en.wikipedia.org/wiki/Centroid#Of_a_polygon

// Calculate the range of lifting weight by using the formula of barycenter because
// if the barycenter after adding weight is out of the range of base, it will topple over).


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

class polygon : public point {
public:
    vector<point> points;

    point barycenter;

    double area = 0;
    
    double EPS = 1e-6;

    polygon() {
        ;
    }

    polygon(int m) {
        points = vector<point>(m, point());
    }

    void cal_area() {
        for (int i = 0; i < points.size(); i++) {
            area += cross_product(points[i], points[i+1]);
        }
        area /= 2.0;
        area = abs(area);
    }

    void cal_barycenter() {
        double temp_area = 0, cx = 0, cy = 0, CP;
        int m = points.size();

        for (int i = 0; i < m; i++) {
            CP = cross_product(points[i], points[(i+1)%m]);
            temp_area += CP;
            cx += (points[i].get_x() + points[(i+1)%(m)].get_x()) * CP;
            cy += (points[i].get_y() + points[(i+1)%(m)].get_y()) * CP;
        }
        
        temp_area /= 2.0;

        cx /= 6.0*temp_area;
        cy /= 6.0*temp_area;

        barycenter.setCoordinate(cx, cy);

        if (area < EPS) area = abs(temp_area);
    }
};

// new_bary_x = (x1*w1 + x2*w2) / (w1 + w2)
// so we can deduce that
// w2 = w1*(x1 - new_bary_x) / (new_bary_x - x2)
double cal_weight(double x1, double x2, double w1, double new_bary_x) {
    return w1*(x1 - new_bary_x) / (new_bary_x - x2);
}

int main() {
    int num_point, a, b, pos_x;
    while (cin >> num_point) {
        int base_left = 2000, base_right = -2000;
        polygon poly(num_point);
        for (int i = 0; i < num_point; i++) {
            cin >> a >> b;
            poly.points[i].setCoordinate(a, b);
            if (i == 0) {
                pos_x = a;
            }
            if (b == 0) {
                base_left = min(base_left, a);
                base_right = max(base_right, a);
            }
        }

        poly.cal_barycenter();

        point original_barycenter = poly.barycenter;

        // we only need the x
        double original_barycenter_x = original_barycenter.get_x();
        double original_weight = poly.area;

        // cout << original_barycenter_x << " " << original_weight << " " << pos_x << " " << base_left << " " << base_right << endl;

        // calculate the range of weight
        if (original_barycenter_x > base_right) {
            if (pos_x >= base_right) {
                cout << "unstable" << endl;
            }
            else if (pos_x >= base_left) {
                cout << int(floor(cal_weight(original_barycenter_x, pos_x, original_weight, base_right))) << " .. inf" << endl;
            }
            else {
                cout << int(floor(cal_weight(original_barycenter_x, pos_x, original_weight, base_right))) << " .. " << int(ceil(cal_weight(original_barycenter_x, pos_x, original_weight, base_left))) << endl;
            }
        }
        else if (original_barycenter_x >= base_left) {
            if (pos_x > base_right) {
                cout << 0 << " .. " << int(ceil(cal_weight(original_barycenter_x, pos_x, original_weight, base_right))) << endl;
            }
            else if (pos_x >= base_left) {
                cout << 0 << " .. inf" << endl;
            }
            else {
                cout << 0 << " .. " << int(ceil(cal_weight(original_barycenter_x, pos_x, original_weight, base_left))) << endl;
            }
        }
        else {
            if (pos_x > base_right) {
                cout << int(floor(cal_weight(original_barycenter_x, pos_x, original_weight, base_left))) << " .. " << int(ceil(cal_weight(original_barycenter_x, pos_x, original_weight, base_right))) << endl;
            }
            else if (pos_x > base_left) {
                cout << int(floor(cal_weight(original_barycenter_x, pos_x, original_weight, base_left))) << " .. inf" << endl;
            }
            else {
                cout << "unstable" << endl;
            }
        }
    }
    return 0;
}
