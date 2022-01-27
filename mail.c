#include <stdio.h>
#include <stdlib.h>

#define BoardMaxX 5
#define BoardMaxY 5

int count = 0;

int contains(int number, int *list, int len) {
    for (int i = 0; i < len; i++)
        if (list[i] == number)
            return 1;
    return 0;
}

int xyToBoard(int x, int y) {
    return 1 + x + BoardMaxX * y;
}

int getX(int board) {
    return (board - 1) % BoardMaxX;
}

int getY(int board) {
    return (board - 1) / BoardMaxX;
}

void seek(int *list, int len) {
//    printf("%d\n", list);

    if (len == BoardMaxY * BoardMaxX) {
//        for (int i = 0; i < BoardMaxX * BoardMaxY; i++)
//            printf("%2d ", list[i]);
//        printf("\n");
        count++;
//        if(count % 1000 == 0)
//            printf("%d ", count);
    }

    int found = 0;
    int xOffsets[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int yOffsets[] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (int i = 0; i < 8; i++) {
        int next = xyToBoard(getX(list[len - 1]) + xOffsets[i], getY(list[len - 1]) + yOffsets[i]);
        if ((getX(list[len - 1]) + xOffsets[i] >= 0) && (getX(list[len - 1]) + xOffsets[i] < BoardMaxX))
            if ((getY(list[len - 1]) + yOffsets[i] >= 0) && (getY(list[len - 1]) + yOffsets[i] < BoardMaxY))
                if (!contains(next, list, len)) {
//                    printf("%d\n", next);
                    int *list2;
                    list2 = malloc(sizeof(int) * (len + 1));
                    for (int o = 0; o < len; o++)
                        list2[o] = list[o];
                    list2[len] = next;
                    seek(list2, len + 1);
                    found++;
                }
    }

    free(list);

//    if (found == 0) {
//        for (int i = 0; i < 25;) {
//            for (int o = 0; o < 5; o++)
//                printf("%2d ", i++);
//            printf("\n");
//        }
//    }
}


int main() {
//    for (int i = 1; i < 26;) {
//        for (int o = 0; o < 5; o++)
//            printf("%2d ", i++);
//        printf("\n");
//    }

    for (int o = 1; o < (1 + BoardMaxX * BoardMaxY); o++) {
        int *list;
        list = malloc(sizeof(int) * BoardMaxY * BoardMaxX);
        for (int i = 0; i < BoardMaxX * BoardMaxY; i++)
            list[i] = 0;
        list[0] = o;
        seek(list, 1);
        printf("%d\n", count);
    }
    return 0;
}
