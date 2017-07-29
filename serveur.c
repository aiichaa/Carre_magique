#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef int Boolean;
#define TRUE 1
#define FALSE 0

int grille[5][5];

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
         if(grille[i][j]!=0){
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

int intRandom(int min, int max){ 
  return (min + (rand () % (max-min+1)));
   }

int main()
{

        int sock;
        int connected;
        int bytes_recieved,bytes_recieved2,bytes_recieved3;  
        char send_data [2];
        char send_data2 [2];
        char send_data3 [2];
        char recv_data[2];
        char recv_data2[2];
        char recv_data3[2];       
         Boolean saisieCorrecte = FALSE;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;    
        int sin_size;
        
        //Creation de socket
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }
        server_addr.sin_family = AF_INET;        
        server_addr.sin_port = htons(5000);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        //Bind
        if (bind(sock, (struct sockaddr *)&server_addr,
         sizeof(struct sockaddr)) == -1) {
            perror("Unable to bind");
            exit(1);
        }

        //Listen
        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
		
	      printf("\n.....");
        fflush(stdout);



        while(1)
        {  
            sin_size = sizeof(struct sockaddr_in); 

            //Accepter une demande de connexion
            connected = accept(sock, (struct sockaddr *)&client_addr,
              &sin_size);

            printf("\nconnection avec (%s , %d)",
              inet_ntoa(client_addr.sin_addr),
              ntohs(client_addr.sin_port));
            printf("\n");

            initialiseGrille();
            printf("\nGrille initiale\n");
            afficheGrille();
            //Tant que le message recu # 'Q'
            while (1)
            {
              do{
              afficheGrille();
             
              int a=atoi(send_data);
              int b=atoi(send_data2);
              int v=atoi(send_data3);
              int dd = intRandom(1,5);
              int bb = intRandom(1,5);
              int vv = intRandom(5,20);

              a=dd;
              b=bb;
              v=vv;
              if (a <= 5 && b <= 5) {
                        
                  grille[a][b] = v;
                      Boolean test= testligne();
                      Boolean test2 =testcolonne();
                      if( test == TRUE || test2 == TRUE){
                            printf("vous avez gagné");
                            break;
                      }else{
                        saisieCorrecte = TRUE;
                        printf("\n\n");
                        afficheGrille();                
                        sprintf(send_data, "%d\n\n", a);
                        sprintf(send_data2, "%d\n\n", b);
                        sprintf(send_data3, "%d\n\n", v);       
                      }
             } else         
      printf("Indice incorrect. Veuillez essayez a vouveau:\n"); 
            }while(!saisieCorrecte);
 		            send(connected, send_data,sizeof(send_data), 0);
                send(connected, send_data2,sizeof(send_data2), 0);  
                send(connected, send_data3,sizeof(send_data3), 0); 
              bytes_recieved = recv(connected,recv_data,2,0);
              bytes_recieved2 = recv(connected,recv_data2,2,0);
              bytes_recieved3 = recv(connected,recv_data3,2,0);
              printf("\n RECIEVED DATA = %s " , recv_data);
              printf("\n RECIEVED DATA = %s " , recv_data2);
              printf("\n RECIEVED DATA = %s " , recv_data3);
              int c=atoi(recv_data);
              int d=atoi(recv_data2);
              int k=atoi(recv_data3);
              grille[c][d] = k;
            fflush(stdout);          
        } 
      }     
      close(sock);
      return 0;
} 