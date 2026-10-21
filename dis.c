#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

int compareX(const void* a, const void* b) {
    Point *p = (Point *)a, *q = (Point *)b;
    if (p->x < q->x) return -1;
    if (p->x > q->x) return 1;
    return 0;
}

int compareY(const void* a, const void* b) {
    Point *p = (Point *)a, *q = (Point *)b;
    if (p->y < q->y) return -1;
    if (p->y > q->y) return 1;
    return 0;
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double minimum(double a, double b) {
    return (a < b) ? a : b;
}

double bruteForce(Point a[], int n, Point *u, Point *v) {
    double m = 1e20;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = distance(a[i], a[j]);
            if (d < m) {
                m = d;
                *u = a[i];
                *v = a[j];
            }
        }
    }
    return m;
}

double stripClosest(Point a[], int n, double d, Point *u, Point *v) {
    double m = d;
    qsort(a, n, sizeof(Point), compareY);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n && (a[j].y - a[i].y) < m; ++j) {
            double k = distance(a[i], a[j]);
            if (k < m) {
                m = k;
                *u = a[i];
                *v = a[j];
            }
        }
    }
    return m;
}

double closestUtil(Point a[], int n, Point *u, Point *v) {
    if (n <= 3) {
        return bruteForce(a, n, u, v);
    }
    
    int m = n / 2;
    Point p = a[m];
    
    Point w, x, y, z;
    double d = closestUtil(a, m, &w, &x);
    double e = closestUtil(a + m, n - m, &y, &z);
    
    double f = minimum(d, e);
    if (d < e) {
        *u = w; 
        *v = x;
    } else {
        *u = y; 
        *v = z;
    }
    
    Point* s = (Point*)malloc(n * sizeof(Point));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(a[i].x - p.x) < f) {
            s[j] = a[i];
            j++;
        }
    }
    
    Point o, q;
    double g = stripClosest(s, j, f, &o, &q);
    free(s);
    
    if (g < f) {
        *u = o;
        *v = q;
        return g;
    }
    return f;
}

double closestPair(Point a[], int n, Point *u, Point *v) {
    qsort(a, n, sizeof(Point), compareX);
    return closestUtil(a, n, u, v);
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("At least 2 points are required.\n");
        return 1;
    }

    Point *a = (Point*)malloc(n * sizeof(Point));
    
    for (int i = 0; i < n; i++) {
        printf("Enter x and y for point %d: ", i + 1);
        scanf("%lf %lf", &a[i].x, &a[i].y);
    }
    
    Point u, v;
    double d = closestPair(a, n, &u, &v);
    
    printf("Points: (%.1f, %.1f), (%.1f, %.1f)\nDistance: %.5f\n", u.x, u.y, v.x, v.y, d);
    
    free(a);
    return 0;
}
