#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


typedef struct {
    double x, y;
    double w, h;
} Rectangle;


typedef struct {
    double y_bottom;
    double y_top;
    double x_bound;
} Building;


typedef struct {
    double y, x;
} Point;


double getPiercingLine(Rectangle* rects, int n) {
    double max_left = -1e9;
    double min_right = 1e9;
    
    for (int i = 0; i < n; i++) {
        max_left = MAX(max_left, rects[i].x);
        min_right = MIN(min_right, rects[i].x + rects[i].w);
    }
    return (max_left + min_right) / 2.0;
}


Point* mergeSkylines(Point* s1, int n1, Point* s2, int n2, int isRightHalf, double piercing_x, int* out_size) {
    // Max possible size is n1 + n2
    Point* merged = (Point*)malloc((n1 + n2) * sizeof(Point));
    int count = 0;
    
    int i = 0, j = 0;
    double h1 = piercing_x, h2 = piercing_x;
    
    while (i < n1 && j < n2) {
        double current_y;
        double current_x;
        
        if (s1[i].y < s2[j].y) {
            current_y = s1[i].y;
            h1 = s1[i].x;
            i++;
        } else if (s1[i].y > s2[j].y) {
            current_y = s2[j].y;
            h2 = s2[j].x;
            j++;
        } else {
            current_y = s1[i].y;
            h1 = s1[i].x;
            h2 = s2[j].x;
            i++; 
            j++;
        }
        
        if (isRightHalf) {
            current_x = MAX(h1, h2);
        } else {
            current_x = MIN(h1, h2);
        }
        
        if (count == 0 || merged[count - 1].x != current_x) {
            merged[count].y = current_y;
            merged[count].x = current_x;
            count++;
        }
    }
    
    while (i < n1) {
        merged[count++] = s1[i++];
    }
    while (j < n2) {
        merged[count++] = s2[j++];
    }
    
    *out_size = count;
    return merged;
}

Point* getSkyline(Building* buildings, int left, int right, int isRightHalf, double piercing_x, int* out_size) {
    if (left == right) {
        Point* res = (Point*)malloc(2 * sizeof(Point));
        res[0].y = buildings[left].y_bottom;
        res[0].x = buildings[left].x_bound;
        res[1].y = buildings[left].y_top;
        res[1].x = piercing_x; // Return to base
        *out_size = 2;
        return res;
    }
    
    int mid = left + (right - left) / 2;
    
    int n1, n2;
    Point* s1 = getSkyline(buildings, left, mid, isRightHalf, piercing_x, &n1);
    Point* s2 = getSkyline(buildings, mid + 1, right, isRightHalf, piercing_x, &n2);
    
    Point* merged = mergeSkylines(s1, n1, s2, n2, isRightHalf, piercing_x, out_size);
    free(s1);
    free(s2);
    
    return merged;
}

int main() {
    int n;
    printf("Enter the number of rectangles (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }
    
  
    Rectangle* rects = (Rectangle*)malloc(n * sizeof(Rectangle));
    Building* rightBuildings = (Building*)malloc(n * sizeof(Building));
    Building* leftBuildings = (Building*)malloc(n * sizeof(Building));
    
    printf("Enter x, y, width, height for each rectangle:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf", &rects[i].x, &rects[i].y, &rects[i].w, &rects[i].h);
        
        rightBuildings[i].y_bottom = rects[i].y;
        rightBuildings[i].y_top = rects[i].y + rects[i].h;
        rightBuildings[i].x_bound = rects[i].x + rects[i].w;
        
        leftBuildings[i].y_bottom = rects[i].y;
        leftBuildings[i].y_top = rects[i].y + rects[i].h;
        leftBuildings[i].x_bound = rects[i].x;
    }
    

    double piercing_x = getPiercingLine(rects, n);
    

    int rightSize, leftSize;
    Point* rightSkyline = getSkyline(rightBuildings, 0, n - 1, 1, piercing_x, &rightSize);
    Point* leftSkyline = getSkyline(leftBuildings, 0, n - 1, 0, piercing_x, &leftSize);
    
  
    Point* contour = (Point*)malloc(2 * (rightSize + leftSize) * sizeof(Point));
    int contour_count = 0;
    
 
    for (int i = 0; i < rightSize - 1; i++) {
        contour[contour_count].y = rightSkyline[i].y;
        contour[contour_count].x = rightSkyline[i].x;
        contour_count++;
        
        contour[contour_count].y = rightSkyline[i+1].y;
        contour[contour_count].x = rightSkyline[i].x; // Corner
        contour_count++;
    }

    for (int i = leftSize - 2; i >= 0; i--) {
        contour[contour_count].y = leftSkyline[i+1].y;
        contour[contour_count].x = leftSkyline[i].x;
        contour_count++;
        
        contour[contour_count].y = leftSkyline[i].y;
        contour[contour_count].x = leftSkyline[i].x; // Corner
        contour_count++;
    }
    
    printf("\nBoundary Contour Corners (X, Y):\n");
    for (int i = 0; i < contour_count; i++) {
        printf("(%.2lf, %.2lf)\n", contour[i].x, contour[i].y);
    }
    
    // Clean up dynamically allocated memory
    free(rects);
    free(rightBuildings);
    free(leftBuildings);
    free(rightSkyline);
    free(leftSkyline);
    free(contour);
    
    return 0;
}