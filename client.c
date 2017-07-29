#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

typedef int Boolean;
#define TRUE 1
#define FALSE 0

int  grille[5][5];
void initialiseGrille() {
  int i, j;
  for (i=0; i<5; i++) {
    for (j=0; j<5; j++) {
      grille[i][j] = 0;
    }
  }
}
void afficheGrille() {
  int i, j;
  for (i=0; i<5; i++) {
    for (j=0; j<5; j++) {
         if(grille[i][j]!= 0){
                printf(" %d ",grille[i][j]);

         }else{
                printf("_ ");
         }
    }
    printf("\n");
  }
}
Boolean testligne(){
  int i,j;
  Boolean res;
  for (i=0; i<5; i++) {
    int somme=0;
    for (j=0; j<5; j++) {
             somme = somme+grille[i][j];
    }
    if(somme>65){
        res = TRUE;
        return res;
        break;
    }else{
        continue;
    }
  }
  res = FALSE;
  return res;
}
Boolean testcolonne(){
  int i,j;
  Boolean res;
  for (i=0; i<5; i++) {
    int somme=0;
    for (j=0; j<5; j++) {
             somme = somme+grille[i][j];
    }
    if(somme>65){
        res = TRUE;
        return res;
        break;
    }else{
        continue;
    }
  }
  res = FALSE;
  return res;
}
int main()
{
        int sock, msg_recu,msg_recu2,msg_recu3;  
        char send_data[2];
        char send_data2[2];
        char send_data3[2];
        Boolean saisieCorrecte = FALSE;

        char recv_data[2];
        char recv_data2[2];
        char recv_data3[2];
        struct hostent *host;
        struct sockaddr_in serveur;  

        host = gethostbyname("127.0.0.1");

        //Creation de socket
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }
        serveur.sin_family = AF_INET;     
        serveur.sin_port = htons(5000);   
        serveur.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(serveur.sin_zero),8); 

        //Connect
      if (connect(sock, (struct sockaddr *)&serveur,
        sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }
       while (1)
            {
            	 msg_recu=recv(sock,recv_data,2,0);
            msg_recu2=recv(sock,recv_data2,2,0);
            msg_recu3=recv(sock,recv_data3,2,0);
            printf("\n RECIEVED DATA = %s " , recv_data);
            printf("\n RECIEVED DATA = %s " , recv_data2);
            printf("\n RECIEVED DATA = %s " , recv_data3);
               int t=atoi(recv_data);
               int o=atoi(recv_data2);
               int l=atoi(recv_data3);
               
               grille[t][o] = l;
               afficheGrille();
              do{
              printf("\n Entrez la ligne : ");
              scanf("%s",send_data);
              printf("\n entrez la colonne: ");
              scanf("%s",send_data2);  
              printf("\n Entrez la valeur ");
              scanf("%s",send_data3);
              int a=atoi(send_data);
              int b=atoi(send_data2);
              int v=atoi(send_data3);
              if (a <= 5 &&  b <= 5) {
                          
              if (grille[a][b] != 0) 
   printf("Cette case a deja ete remplie. Veuillez recommencer: \n");
              else {
                      grille[a][b] = v;
                      Boolean test= testligne();
                       Boolean test2 =testcolonne();
                      if( test == TRUE || test2 == TRUE){
                            printf("vous avez gagné");
                      }else{
                        saisieCorrecte = TRUE;
                      
                      afficheGrille();
                      }
                      
                     
                    }
              } else
printf("Indice incorrect. Veuillez recommencer:\n");
              
              }while(!saisieCorrecte);

            send(sock, send_data,sizeof(send_data), 0);
            send(sock, send_data2,sizeof(send_data2), 0);  
            send(sock, send_data3,sizeof(send_data3), 0);
        
        }   
return 0;
}