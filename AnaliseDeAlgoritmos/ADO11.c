#include <stdio.h>
#include <stdlib.h>

struct Activity {
    int start;
    int end;
};

int compare(const void* a, const void* b) {
    return ((struct Activity*)a)->end - ((struct Activity*)b)->end;
}

void selectActivities(struct Activity activities[], int n) {
    qsort(activities, n, sizeof(struct Activity), compare);

    printf("Atividades selecionadas:\n");
    int i = 0;
    printf("Atividade %d: Inicio as %dh, Termino as %dh\n", i + 1, activities[i].start, activities[i].end);

    for (int j = 1; j < n; j++) {
        if (activities[j].start >= activities[i].end) {
            i = j;
            printf("Atividade %d: Inicio as %dh, Termino as %dh\n", i + 1, activities[i].start, activities[i].end);
        }
    }
}

int main() {
    struct Activity activities[] = {
        {1, 3},
        {2, 5},
        {4, 7}
    };
    int n = sizeof(activities) / sizeof(activities[0]);

    selectActivities(activities, n);

    return 0;
}
