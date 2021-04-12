#include <bits/stdc++.h>
#include <cmath>
#include <vector>
#define MAX_SIZE 10000
#define MAX_INPUTS 10001

using namespace std;

typedef struct cordinate {
    double posX;
    double posY;
} Point;

Point points[MAX_INPUTS];

double euclidean_distance(Point &point_a, Point &point_b);
double min_distance(double, double);
double closest_pair(int start, int end);
void print_data(double);
int comparador(const void *a, const void *b);

int main() {
    int n;
    double distance = 0;

    while (cin >> n) {
        if (n == 0) break;

        for (int i = 0; i < n; i++) {
            cin >> points[i].posX >> points[i].posY;
        }

        qsort(points, n, sizeof(points[0]), comparador);
        distance = closest_pair(0, n - 1);
        print_data(distance);
    }
    return 0;
}

int comparador(const void *a, const void *b) {
    Point *point_a = (Point *)a;
    Point *point_b = (Point *)b;
    if(point_a->posX > point_b->posX)
        return 1;
    else if(point_a->posX < point_b->posX)
        return -1;
    else {
        if(point_a->posY > point_b->posY)
            return 1;
        else
            return -1;
    }
    return -1;
}

double euclidean_distance(Point &point_a, Point &point_b) {
    double hipotenuza = hypot(point_a.posX - point_b.posX, point_a.posY - point_b.posY);
    return min_distance(hipotenuza, MAX_SIZE);
}

double closest_pair(int start, int end) {
    double left_result, right_result;
    double min_distance_euclidian = 0;

    if (start == end) {
        return MAX_SIZE;
    }
    else if (end - start == 1) {
        return euclidean_distance(points[end], points[start]);
    }
    else {
        int mid = (start+end)/2;
        left_result = closest_pair(start, mid);
        right_result = closest_pair(mid + 1, end);

        min_distance_euclidian = min_distance(left_result, right_result);

        int left_index = (start + end)/2;
        double left_point_result = points[left_index].posX;

        while(left_point_result - points[left_index].posX < min_distance_euclidian && left_index >= start) {
            int right_index = (start + end)/2 + 1;

            while(left_point_result - points[right_index].posX < min_distance_euclidian && right_index <= end){
                left_result = euclidean_distance(points[right_index], points[left_index]);
                min_distance_euclidian = min_distance(min_distance_euclidian, left_result);
                right_index++;
            }
            left_index--;
        }
        return min_distance_euclidian;
    }
}

double min_distance(double left, double right) {
    return (left < right) ? left : right;
}

void print_data(double info) {
    if(info >= MAX_SIZE) {
        cout << "INFINITY" << endl;
    }
    else {
        printf("%.4lf\n", info);
    }
}