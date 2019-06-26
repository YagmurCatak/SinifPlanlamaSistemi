#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ogrenci {
    char isim[20];
    char soyisim[20];
    char numara[10];
    int kayit_Sirasi;
    int ogrenim_Durumu;
};

struct listeDugumu{
    struct ogrenci veri;
    struct listeDugumu *next;
};


struct Sinif {
    int kapasite;
    int kisi_sayisi;
};

typedef struct ogrenci Ogrenci;
typedef struct listeDugumu listeDugumu;
typedef struct Sinif _sinif;
typedef listeDugumu *ListeDugumuPtr;

 void ekle(ListeDugumuPtr *ptr,Ogrenci ogr)
{
    ListeDugumuPtr yeniptr;
    ListeDugumuPtr oncekiptr;
    ListeDugumuPtr suandakiptr;

    yeniptr = malloc(sizeof(listeDugumu));

    if (yeniptr != NULL)
    {
        yeniptr -> veri = ogr;
        yeniptr -> next = NULL;

        oncekiptr = NULL;
        suandakiptr = *ptr;

        while (suandakiptr != NULL)
        {
            oncekiptr = suandakiptr;
            suandakiptr = suandakiptr -> next;
            //printf("listeyi dolasiyorum \n");
        }
        if (oncekiptr == NULL ) //Liste bos mu diye tekrar kontrol ediyor, e?er bo? ise yenidü?ümü ilk dü?üm kabul ediyor.
        {
            yeniptr->next = *ptr;
            *ptr = yeniptr;
            //printf("%s\n",yeniptr->veri.isim);
            //printf("liste bos.yeni veri ilk veri oldu.\n ");
        }
        else{
            oncekiptr->next = yeniptr;
            yeniptr->next = suandakiptr;
            //printf("yeni veri eklendi\n");
            //printf("%s\n",oncekiptr->next->veri.isim);
        }
    }
    else printf("ekleme yapilamadi.");

}

void yazdir(ListeDugumuPtr suandakiPtr)
{
        ListeDugumuPtr tmp = suandakiPtr;
        while (tmp != NULL)
        {
            printf("%s %s %s %d %d \n", tmp->veri.isim,tmp->veri.soyisim,tmp->veri.numara,tmp->veri.kayit_Sirasi,tmp->veri.ogrenim_Durumu);
            tmp = tmp -> next ;
        }

}

int dosyaOkuma(ListeDugumuPtr *baslangicPtr)
{
    char isim[20];
    char soyisim[20];
    char numara[10];
    int kayit_Sirasi;
    int ogrenim_Durumu;
    FILE *dosya; //veri.txt dosya göstericisi
    Ogrenci geciciOgrenci;
    if ( (dosya = fopen("veri.txt","r")) == NULL)
    {
        printf("dosya acilmadi");
        return 1;
    }
    else
    {
        while (!feof(dosya)) //feof() fonksiyonu dosyanın sonuna gelinip gelinmediğinin kontrolünü yapar.
        {

            fscanf(dosya, "%s %s %s %d %d \n", &isim,&soyisim,&numara,&kayit_Sirasi,&ogrenim_Durumu);
            strcpy(geciciOgrenci.isim,isim);
            strcpy(geciciOgrenci.soyisim,soyisim);
            strcpy(geciciOgrenci.numara,numara);
            geciciOgrenci.kayit_Sirasi = kayit_Sirasi;
            geciciOgrenci.ogrenim_Durumu = ogrenim_Durumu;
            ekle(baslangicPtr,geciciOgrenci);
        }
    }
    //yazdir(baslangicPtr);
    fclose(dosya);

    return 0;
}

int dosyaYazma (ListeDugumuPtr *baslangicPtr)
{
    FILE *dosyaPtr;
    ListeDugumuPtr sonrakiptr;
    dosyaPtr = fopen("veri1.text","w");

    sonrakiptr = *baslangicPtr;

    while (sonrakiptr != NULL)
        {
            fprintf(dosyaPtr,"%s %s %s %d %d\n",sonrakiptr->veri.isim,sonrakiptr->veri.soyisim,sonrakiptr->veri.numara,sonrakiptr->veri.kayit_Sirasi,sonrakiptr->veri.ogrenim_Durumu);
            sonrakiptr = sonrakiptr -> next;
        }

    fclose(dosyaPtr);

    return 0;
}

void sil (ListeDugumuPtr *ptr )
{
    int sil ;
    ListeDugumuPtr birinciEleman;
    ListeDugumuPtr ikinciEleman;
    ListeDugumuPtr geciciEleman;

    birinciEleman = *ptr;
    ikinciEleman = birinciEleman->next;


    while (ikinciEleman != NULL)
    {
        int result ;
        result = strcmp(birinciEleman->veri.isim,ikinciEleman->veri.isim);

        if (result == 0 )
        {
            geciciEleman = ikinciEleman;
            birinciEleman->next = ikinciEleman->next;
            printf("%s %s %s %d %d\n",geciciEleman->veri.isim,geciciEleman->veri.soyisim,geciciEleman->veri.numara,geciciEleman->veri.kayit_Sirasi,geciciEleman->veri.ogrenim_Durumu);
            free(geciciEleman);  //MemoryLeaking için.
            sil =1;
        }
        else//birinci ogretim ve ikinci ogretim kisi sayisi bulunur.
        {
        //do nothing.
        }
        birinciEleman = birinciEleman->next;
        if (birinciEleman != NULL)
        {
            ikinciEleman = birinciEleman->next;
        }
        else
        {
            ikinciEleman = NULL;
        }
    }
    if (sil==1)
     printf("Bu ogrencilerin 2 defa ismi gecmektedir, ogrencilerin kayitlari silinmistir.\n");
    else
    printf("2defa adi gecen isim yoktur.\n");

}

void siralaKayit (ListeDugumuPtr *baslangicPtr)
{
    int sirali;
    ListeDugumuPtr temp;
    ListeDugumuPtr iter = NULL;

    if(temp == NULL)
    {
        return;
    }
    do
    {
        sirali = 0;
        temp = *baslangicPtr;

        while (temp->next != iter)
        {
            if(temp->veri.kayit_Sirasi > temp->next->veri.kayit_Sirasi)
            {
                Ogrenci deger = temp->veri;
                temp->veri = temp->next->veri;
                temp->next->veri = deger;
                sirali = 1;
            }
            temp = temp->next;
        }
        iter = temp;
    }while(sirali);

}

void kayitSiraGuncelle(ListeDugumuPtr *baslangicPtr)
{

    int counter=0;
    ListeDugumuPtr temp;

    temp = *baslangicPtr;

    while (temp!= NULL)
    {
        if ( temp->veri.kayit_Sirasi == 0)
        {
            temp = temp->next;
            continue;
        }

        counter++;

        if(temp->veri.kayit_Sirasi != counter)
        {
            temp->veri.kayit_Sirasi = counter;
        }
        temp = temp ->next;

    }
}

void yeniNumara(ListeDugumuPtr *baslangicPtr)
{
    ListeDugumuPtr temp;

    temp = *baslangicPtr;

    while (temp != NULL)
    {
        if ( temp->veri.kayit_Sirasi != 0)
        {
            //yeni numara verilecek
            if (temp->veri.ogrenim_Durumu == 1)
            {
                char kayitsirasi[10];
                sprintf(kayitsirasi,"%03d",temp->veri.kayit_Sirasi);
                //printf("%s\n",kayitsirasi);
                char s1[10] = "1701";
                strcat(s1,kayitsirasi);
                //printf("%s\n",&s1);
                strcpy(temp->veri.numara,s1);
            }
            else
            {
                char kayitsirasi[10];
                sprintf(kayitsirasi,"%03d",temp->veri.kayit_Sirasi);
                //printf("%s\n",kayitsirasi);
                char s1[10] = "1702";
                strcat(s1,kayitsirasi);
                //printf("%s\n",&s1);
                strcpy(temp->veri.numara,s1);
            }
        }
        temp = temp -> next ;
    }
}

void siralaNumara(ListeDugumuPtr *baslangicPtr)
{
    int sirali;
    ListeDugumuPtr temp;
    ListeDugumuPtr iter = NULL;

    if(temp == NULL)
    {
        return;
    }
    do
    {
        sirali = 0;
        temp = *baslangicPtr;

        while (temp->next != iter)
        {
            int result ;
            result = strcmp(temp->veri.numara,temp->next->veri.numara); //karşılaştırır,eşit=0,ilkveri buyukse=pozitif,ikinciveri buyukse=negatif

            if( result > 0 )
            {
                Ogrenci deger = temp->veri;
                temp->veri = temp->next->veri;
                temp->next->veri = deger;
                sirali = 1;
            }
            temp = temp->next;
        }
        iter = temp;
    }while(sirali);
}

void dosyaDuzenleme(ListeDugumuPtr *baslangicPtr)
{
    ListeDugumuPtr root = NULL;

    dosyaOkuma(&root);
    sil(&root);
    siralaKayit(&root);
    kayitSiraGuncelle(&root);
    yeniNumara(&root);
    siralaNumara(&root);
    dosyaYazma(&root);
    //yazdir(baslangicPtr);

    *baslangicPtr = root;
}

int main()
{
    ListeDugumuPtr root = NULL;
    ListeDugumuPtr temp;
    int sinifsayisi;
    int sinifkapasitesi;
    int i,j;
    int birinciogretim=0;
    int ikinciogretim=0;
    int doluSinif = 0;
    int ortbirinci ;
    int ortikinci ;
    int geciciBellek;
    int yerlestirme = 1 ;
    char isim[20],soyisim[20],numara[20];
    int kayitnum,ogrenimdurumu;
    char isim2[20],soyisim2[20],numara2[20];
    int kayitnum2,ogrenimdurumu2;

    FILE *gecicidosya;
    dosyaDuzenleme(&root);
    //yazdir(root);_sinif


    while(yerlestirme != 0){

        printf("Sinif sayisini giriniz:");
        scanf("%d",&sinifsayisi);
        _sinif sinif[sinifsayisi];
        //int kapasite[sinifsayisi];
        int topkapasite=0;

        printf("Sinif kapasitelerini giriniz:");
        for(j=0; j<sinifsayisi; j++)
        {
            scanf("%d",&sinifkapasitesi);
            sinif[j].kapasite=sinifkapasitesi;
            topkapasite = topkapasite + sinifkapasitesi;
        }

        temp = root;
        while (temp != NULL)
        {
            //birinci ogretim ve ikinci ogretim kisi sayisi bulunur.
            if (temp->veri.ogrenim_Durumu == 1)
            {
                birinciogretim++;
            }else{
                ikinciogretim++;
            }
            temp = temp -> next;
        }
        printf("Dersi alan ogrenci sayisi 1.ogretim : %d 2.ogretim : %d 'dir.\n",birinciogretim,ikinciogretim);


        if(topkapasite<birinciogretim || topkapasite<ikinciogretim)
        {
            printf("kapasite az oldugu icin yerlestirme yapilamaz.tekrardan sinif kapasiteleri belirleyiniz\n");
            birinciogretim = 0;
            ikinciogretim = 0;
            topkapasite = 0;
            yerlestirme = 1;
        }
        else
        {
            int secim;
            while (secim != 5)
            {

            printf("1-Esit dagilim\n2-En az dagilim\n3-Numarali ogrenci girisi\n4-Numarasiz ogrenci girisi\n5-Cikis\n");
            scanf("%d",&secim);

            switch(secim)
            {
            case 1:

                birinciogretim=0;
                ikinciogretim=0;
                temp = root;
                while (temp != NULL)
                {
            //birinci ogretim ve ikinci ogretim kisi sayisi bulunur.
                    if (temp->veri.ogrenim_Durumu == 1)
                {
                    birinciogretim++;
                }else{
                    ikinciogretim++;
                }
                temp = temp -> next;
                }

                ortbirinci = birinciogretim/sinifsayisi;
                ortikinci = ikinciogretim/sinifsayisi;
            /* kücükten büyüge siralama yapiliyor */

                for (i = 0; i <sinifsayisi ; i++) {

                for (j = 0; j < sinifsayisi; j++) {
                    geciciBellek = sinif[j].kapasite;
                    sinif[j].kapasite = sinif[i].kapasite;
                    sinif[i].kapasite = geciciBellek;
                    }
                }

            //Esit dagilim ile sinif yerlesimi

            while (ortbirinci != 0)
            {
                for(i=0; i<sinifsayisi; i++)
                {

                    if(sinif[i].kapasite <= ortbirinci)
                    {
                        sinif[i].kisi_sayisi = sinif[i].kapasite;
                    }
                    else
                    {
                        sinif[i].kisi_sayisi = ortbirinci;
                    }
                    birinciogretim =birinciogretim - sinif[i].kisi_sayisi;
                    doluSinif++;
                    if (doluSinif != sinifsayisi)
                        ortbirinci = birinciogretim / (sinifsayisi-doluSinif);
                    else
                        ortbirinci = 0;
                }
            }

            printf("1.ogretim Es sinif yerlesimi : \n");
            printf("************\n");
            for (i=0; i<sinifsayisi; i++)
            {
                printf("%d kisilik sinifa %d kisi atanmistir.\n",sinif[i].kapasite,sinif[i].kisi_sayisi);
            }

            ListeDugumuPtr iterbirinci ;
            iterbirinci = root;
            for(i=0; i<sinifsayisi; i++)
            {
                FILE *sinifdosya;
                char *filePath;

                filePath = (char*)malloc(sizeof(char)*20);
                sprintf(filePath, "Essinif%dOgr1.txt", i+1);
                sinifdosya = fopen(filePath,"w");
                int counter = 0;
                while(counter<sinif[i].kisi_sayisi)
                {
                    if (iterbirinci->veri.ogrenim_Durumu == 1)
                    {
                        fprintf(sinifdosya,"%s %s %s %d %d\n",iterbirinci->veri.isim,iterbirinci->veri.soyisim,iterbirinci->veri.numara,iterbirinci->veri.kayit_Sirasi,iterbirinci->veri.ogrenim_Durumu);
                        counter++;
                    }
                    iterbirinci = iterbirinci -> next ;
                }
                fclose(sinifdosya);
            }

            doluSinif = 0;
            while (ortikinci != 0)
            {
                for(i=0; i<sinifsayisi; i++)
                {

                    if(sinif[i].kapasite <= ortikinci)
                    {
                        sinif[i].kisi_sayisi = sinif[i].kapasite;
                    }
                    else
                    {
                        sinif[i].kisi_sayisi = ortikinci;
                    }
                    ikinciogretim =ikinciogretim - sinif[i].kisi_sayisi;
                    doluSinif++;
                    if (doluSinif != sinifsayisi)
                        ortikinci = ikinciogretim / (sinifsayisi-doluSinif);
                    else
                        ortikinci = 0;
                }
            }
            printf("2.ogretim Es sinif yerlesimi : \n");
            printf("***********\n");
            for (i=0; i<sinifsayisi; i++)
            {
                 printf("%d kisilik sinifaa %d kisi atanmistir.\n",sinif[i].kapasite,sinif[i].kisi_sayisi);
            }
            ListeDugumuPtr iterikinci ;
            iterikinci = root;
            for(i=0; i<sinifsayisi; i++)
            {
                FILE *sinifdosya2;
                char *filePath2;

                filePath2 = (char*)malloc(sizeof(char)*20);
                sprintf(filePath2, "Essinif%dOgr2.txt", i+1);
                sinifdosya2 = fopen(filePath2,"w");
                int counter2=0;
                while (counter2 < sinif[i].kisi_sayisi)
                {
                    if (iterikinci->veri.ogrenim_Durumu == 2)
                    {
                        fprintf(sinifdosya2,"%s %s %s %d %d\n",iterikinci->veri.isim,iterikinci->veri.soyisim,iterikinci->veri.numara,iterikinci->veri.kayit_Sirasi,iterikinci->veri.ogrenim_Durumu);
                        counter2++;
                    }
                    iterikinci = iterikinci ->next;

                }
                fclose(sinifdosya2);
            }

                break;
            case 2:
            //en az dagilim ile sinif yerlesimi
            birinciogretim=0;
            ikinciogretim=0;
              temp = root;
            while (temp != NULL)
            {
            //birinci ogretim ve ikinci ogretim kisi sayisi bulunur.
            if (temp->veri.ogrenim_Durumu == 1)
            {
                birinciogretim++;
            }else{
                ikinciogretim++;
            }
            temp = temp -> next;
        }



            //sinif kapasitelerini büyükten kücüge siralar.
                for (i = 0; i <sinifsayisi ; i++)
                {
                    for (j = 0; j < sinifsayisi; j++)
                    {
                         if (sinif[j].kapasite < sinif[i].kapasite)
                        {
                            geciciBellek = sinif[j].kapasite;
                            sinif[j].kapasite = sinif[i].kapasite;
                            sinif[i].kapasite = geciciBellek;
                        }
                    }
                }

            while (birinciogretim!=0)
            {
                for (i=0; i<sinifsayisi; i++)
                {
                    if(sinif[i].kapasite< birinciogretim)
                    {
                        sinif[i].kisi_sayisi = sinif[i].kapasite;
                        birinciogretim = birinciogretim - sinif[i].kisi_sayisi;
                    }
                    else
                    {
                        sinif[i].kisi_sayisi = birinciogretim;
                        birinciogretim = birinciogretim - sinif[i].kisi_sayisi;
                    }
                }
            }
            printf("1.ogretim En az sinif yerlesimi : \n");
            printf("***********\n");
            for (i=0; i<sinifsayisi; i++)
            {
                 printf("%d kisilik sinifaa %d kisi atanmistir.\n",sinif[i].kapasite,sinif[i].kisi_sayisi);
            }

            ListeDugumuPtr birinciptr;
            birinciptr = root;
            for (i=0; i<sinifsayisi;i++)
            {
                FILE *birincidosya;
                char *filePathbirinci;

                filePathbirinci = (char*)malloc(sizeof(char)*20);
                sprintf(filePathbirinci,"Enazsinif%dOgr1.txt",i+1);
                birincidosya = fopen(filePathbirinci,"w");
                int sayac = 0;
                while (sayac<sinif[i].kisi_sayisi)
                {
                    if (birinciptr->veri.ogrenim_Durumu == 1)
                    {
                        fprintf(birincidosya,"%s %s %s %d %d\n",birinciptr->veri.isim,birinciptr->veri.soyisim,birinciptr->veri.numara,birinciptr->veri.kayit_Sirasi,birinciptr->veri.ogrenim_Durumu);
                        sayac++;
                    }
                    birinciptr = birinciptr -> next;
                }
                fclose(birincidosya);
            }

            while (ikinciogretim!=0)
            {
                for (i=0; i<sinifsayisi; i++)
                {
                    if(sinif[i].kapasite <= ikinciogretim)
                    {
                        sinif[i].kisi_sayisi = sinif[i].kapasite;
                        ikinciogretim = ikinciogretim - sinif[i].kisi_sayisi;
                    }
                    else
                    {
                        sinif[i].kisi_sayisi = ikinciogretim;
                        ikinciogretim = ikinciogretim - sinif[i].kisi_sayisi;
                    }
                }
            }
            printf("2.ogretim En az sinif yerlesimi : \n");
            printf("***********\n");
            for (i=0; i<sinifsayisi; i++)
            {
                 printf("%d kisilik sinifaa %d kisi atanmistir.\n",sinif[i].kapasite,sinif[i].kisi_sayisi);
            }

            ListeDugumuPtr ikinciptr;
            ikinciptr = root;
            for (i=0; i<sinifsayisi;i++)
            {
                FILE *ikincidosya;
                char *filePathikinci;

                filePathikinci = (char*)malloc(sizeof(char)*20);
                sprintf(filePathikinci,"Enazsinif%dOgr2.txt",i+1);
                ikincidosya = fopen(filePathikinci,"w");
                int sayac2 = 0;
                while (sayac2<sinif[i].kisi_sayisi)
                {
                    if (ikinciptr->veri.ogrenim_Durumu == 2)
                    {
                        fprintf(ikincidosya,"%s %s %s %d %d\n",ikinciptr->veri.isim,ikinciptr->veri.soyisim,ikinciptr->veri.numara,ikinciptr->veri.kayit_Sirasi,ikinciptr->veri.ogrenim_Durumu);
                        sayac2++;
                    }
                    ikinciptr = ikinciptr -> next;
                }
                fclose(ikincidosya);
            }
                break;
            case 3:
                printf("Eklemek istediginiz ogrencinin adini, soyadini,numarasini ve ogrenim durumunu sirasi ile giriniz=\n");
                scanf("%s %s %s %d %d",&isim,&soyisim,&numara,&kayitnum,&ogrenimdurumu);
                Ogrenci ogr1;
                gecicidosya = fopen("veri.txt","a");


                strcpy(ogr1.isim,isim) ;
                strcpy(ogr1.soyisim,soyisim);
                strcpy(ogr1.numara,numara);
                ogr1.ogrenim_Durumu= ogrenimdurumu;
                ogr1.kayit_Sirasi= kayitnum;

                fprintf(gecicidosya,"%s %s %s %d %d\n",ogr1.isim,ogr1.soyisim,ogr1.numara,ogr1.kayit_Sirasi,ogr1.ogrenim_Durumu);
                ekle(&root,ogr1);
                sil(&root);
                siralaKayit(&root);
                kayitSiraGuncelle(&root);
                siralaNumara(&root);
                dosyaYazma(&root);

                fclose(gecicidosya);
                break;
            case 4:
                printf("Eklemek istediginiz ogrencinin adini, soyadini,kayit numarasini ve ogrenim durumunu sirasi ile giriniz=\n");
                scanf("%s %s %s %d %d",&isim2,&soyisim2,&numara2,&kayitnum2,&ogrenimdurumu2);
                Ogrenci ogr2;
                gecicidosya = fopen("veri.txt","a");


                strcpy(ogr2.isim,isim2) ;
                strcpy(ogr2.soyisim,soyisim2);
                strcpy(ogr2.numara,numara2);
                ogr2.ogrenim_Durumu= ogrenimdurumu2;
                ogr2.kayit_Sirasi= kayitnum2;

                fprintf(gecicidosya,"%s %s %s %d %d\n",ogr2.isim,ogr2.soyisim,ogr2.numara,ogr2.kayit_Sirasi,ogr2.ogrenim_Durumu);
                ekle(&root,ogr2);
                sil(&root);
                siralaKayit(&root);
                kayitSiraGuncelle(&root);
                yeniNumara(&root);
                siralaNumara(&root);
                dosyaYazma(&root);
                fclose(gecicidosya);
                break;
            default:
                printf("");
            }
            }

            yerlestirme = 0;
        }
    }



    getch();
    return 0;
    }

