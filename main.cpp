#include"headers.h"








int main(int argc, char* argv[]){

Graph *G;

G=InitializGraphe(false);
/*
//  Create 20 Nodes
    for(i=1;i<=4;i++)
    for(j=1;j<=5;j++)
    {
        addElementList(&G->tab[comp],i,j,0);
        comp++;
    }
//seccesseurs node 11
addElementList(&G->tab[0],1,2,0);
addElementList(&G->tab[0],2,2,0);
//seccesseurs node 12
addElementList(&G->tab[1],1,1,0);
addElementList(&G->tab[1],1,3,0);
addElementList(&G->tab[1],2,2,0);
//seccesseurs node 13
addElementList(&G->tab[2],1,2,0);
addElementList(&G->tab[2],2,2,0);
addElementList(&G->tab[2],2,3,0);
addElementList(&G->tab[2],1,4,0);
//seccesseurs node 14
addElementList(&G->tab[3],1,3,0);
addElementList(&G->tab[3],2,3,0);
addElementList(&G->tab[3],2,4,0);
addElementList(&G->tab[3],1,5,0);
addElementList(&G->tab[3],2,5,0);
//seccesseurs node 15
addElementList(&G->tab[4],1,4,0);
addElementList(&G->tab[4],2,4,0);
addElementList(&G->tab[4],2,5,0);
//seccesseurs node 21
addElementList(&G->tab[5],2,2,0);
addElementList(&G->tab[5],3,2,0);
//seccesseurs node 22
addElementList(&G->tab[6],1,1,0);
addElementList(&G->tab[6],2,1,0);
addElementList(&G->tab[6],1,2,0);
addElementList(&G->tab[6],1,3,0);
addElementList(&G->tab[6],2,3,0);
addElementList(&G->tab[6],3,2,0);
addElementList(&G->tab[6],3,1,-5);
//seccesseurs node 23
addElementList(&G->tab[7],2,2,0);
addElementList(&G->tab[7],1,3,0);
addElementList(&G->tab[7],1,4,0);
addElementList(&G->tab[7],2,4,0);
addElementList(&G->tab[7],3,3,0);
//seccesseurs node 24
addElementList(&G->tab[8],2,3,0);
addElementList(&G->tab[8],1,4,0);
addElementList(&G->tab[8],1,5,0);
addElementList(&G->tab[8],2,5,0);
addElementList(&G->tab[8],3,5,0);
addElementList(&G->tab[8],3,4,0);
addElementList(&G->tab[8],3,3,0);
//seccesseurs node 25
addElementList(&G->tab[9],1,4,0);
addElementList(&G->tab[9],1,5,0);
addElementList(&G->tab[9],2,4,0);
addElementList(&G->tab[9],3,4,0);
addElementList(&G->tab[9],3,5,0);


//displayGraph(G);

*/
vue(G);

/*
printf("\n\n\n **********************\n\n");
for(int i=0;i<G->numberNode;i++)
{
   displayList(G->tab[i]);
   printf("\n");
}
*/

return 0;
}
