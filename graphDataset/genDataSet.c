#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int numberOfNodes = atoi(argv[2]);
    int min=5,max=100;
    int i, j, k, times = 100;
    float w;
    FILE *arquivo;
    
    if ((arquivo = fopen(argv[1], "w")) == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        return -1;
    }

    srandom(time(NULL));
    for(k=0; k<times; k++) {
        for(i=1; i<numberOfNodes; i++) {
            for(j=i+1; j<=numberOfNodes; j++) {
                w = (random()%(100*(max-min)))/100.f +min;
                fprintf(arquivo, "%d %d %.2f\n",i, j, w);
            }
        }
        fprintf(arquivo, "#\n");
    }
    fclose(arquivo);
    return 0;
}
