#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

int main(){

    while (1)
    {
        time_t waktunya;
        time(&waktunya);
        struct tm *waktu;
        waktu = localtime(&waktunya);

        char chara[1000];

        FILE *isi_cron;
        isi_cron = fopen("/home/paramastri/crontab.data", "r");

        while(fgets(chara,1000,isi_cron)!=NULL){
            if(strcmp(chara,"\n")!=0){ //newline tidak dicek
                char buffer[1000];// duplikat baris seblm di strtok
                char baris[6][5]; //isinya config format waktu
                strcpy(buffer,chara); //duplikat baris ke sementara
                char sisanya[1000]; //yg bukan bintang2
                char *toks = strtok(chara," "); // ambil bintang2nya dg strtok
                int i = 0,spasi = 0;
                while(1) 
                {
                    strcpy(baris[i],toks); //tiap bintang di simpan di array baris
                    toks = strtok(NULL, " ");
                    i++;
                    if(i==5) break; //ambil sampe 5 spasi
                }
                spasi = 0;
                for(i=0;i<strlen(buffer);i++){ //cek posisi spasi ke 5
                    if(buffer[i]==' ') spasi++;
                    if(spasi == 5) break;
                }
                strcpy(sisanya,buffer+i+1); // ambil setelah bintang, disimpen di sisanya
                int apakah_waktunya = 1; //cek apakah waktunya, 1 waktunya, 0 bukan waktunya
                int menit = atoi(baris[0]), jam = atoi(baris[1]), tanggal = atoi(baris[2]), bulan = atoi(baris[3]), hari = atoi(baris[4]);
                if ( //cek apakah waktunya
                    ((menit != waktu->tm_min) && strcmp(baris[0],"*")!=0) ||
                    ((jam != waktu->tm_hour) && strcmp(baris[1],"*")!=0) ||
                    ((tanggal != waktu->tm_mday) && strcmp(baris[2],"*")!=0) ||
                    ((bulan != waktu->tm_mon) && strcmp(baris[3],"*")!=0) ||
                    ((hari != waktu->tm_wday) && strcmp(baris[4],"*")!=0)
                ){
                    apakah_waktunya = 0;
                }
                

            }
        }
        fclose(isi_cron);
    }
}

