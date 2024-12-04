#include <stdio.h>
#include <stdlib.h>
#include <math.h>    //rand()
#include <time.h>   //srand(time())

#include<string.h>  //harf notu icin gerekli



//******SiNAV URETiCi*******/

//soru sayisi kadar bana random (65=A,66=B,67=C,68=D,69=E) þir cevap uretecek ve cevap_anahtari dizime ekleyecek
void cevap_anahtari_uret(char cevap_anahtari[], int S) {
    for (int i = 0; i < S; i++) {
        char cevap_sikki = 65 + rand() % 5;
        cevap_anahtari[i] = cevap_sikki;
    }
}




/*
her bir sorunun cevabini listeler, (soru:cevap) þeklinde
soru sayisini formati %03 olarak belirlendi
*/
void cevap_anahtari_yazdir(char cevap_anahtari[], int S) {
    for (int i = 0; i < S; i++) {
        if(i%10==0) printf("\n");
        printf(" %03d : %c | ", (i+1), cevap_anahtari[i]);
    }
}






void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D) {
    /*N adet öðrencinin her biri, S adet soruya cevaplar vermelidir (ya
    da bazi sorular bos birakilmalidir. */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < S; j++) {
            //bos olasilikta ise soruyu bos gec
            int bos_birakilma_ihtimali_olasiligi = rand() % 100;    //0.40*100=

            if (bos_birakilma_ihtimali_olasiligi <= (B * 100))        //bos birakma olasiligi gerceklesti
            {
                //cevap X iþaretle
                ogrenci_cevaplari[i][j] = 'X';
                continue;
            }
            //dogru olasilikta ise dogru cevabi isaretle
            int dogru_olma_olasiligi = rand() % 100;    //0.40*100=
            if (dogru_olma_olasiligi <= (D * 100))        //dogru olma olasiligi gerceklesti
            {
                ogrenci_cevaplari[i][j] = cevap_anahtari[j];//cevabi dogru iþaretle
                continue;
            }

            //yanlis cevap vermek zorunda, yanlis cevap sikkini sec
            char cevap;
            do {
                cevap = 65 + rand() % 5;
            } while (cevap_anahtari[j] == cevap);
            //buraya yanlis secenek gelir ve o cevabi verdi olarak isaretlenir
            ogrenci_cevaplari[i][j] = cevap;
        }
        // printf("%s", "\n");
    }
}


//ogrenci_ID 0 ~ N-1 arasinda degisen bir indis olarak verilmeli
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S) {
    for (int i = 0; i < S; i++){                //soru sayisi kadar for
        if(i%10==0) printf("\n");
        printf(" %03d : %c | ", (i + 1), ogrenci_cevaplari[ogrenci_ID][i]);
    }
}





//******Sinav Degerlendirici*******/
//fonksiyon, tum ögrencilerin ham basari notlarini hesaplayip double HBN[ ] dizisine yazacak
void ogrencileri_puanla(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], double HBN[ ], int N, int S)
{
    for(int i=0; i<N; i++)
    {
        //degiskenleer
        int yanlisCevapSayisi=0;
        double dobDogruPuani=0.0;
        double  eksilecek=0.0;
        int dogruCevapSayisi=0;
        //double hbn=0.0;
        double sinavSonucu=0.0;
        for(int j=0; j<S; j++)
        {
            //cevap anahtarindaki j. cevap
            char jnciC=cevap_anahtari[j];

            //i. ogrencinin j.cevabi
            char ininciOJninciC=ogrenci_cevaplari[i][j];


            if(ininciOJninciC!=jnciC) //cevap dogru degilse yanlis yapilan soru sayisi arttirilacak
            {
                yanlisCevapSayisi++;

            }
            else
            {

                dogruCevapSayisi++;
            }

        }
        //Hesap isleminde 4 yanlis 1 dogruyu goturecektir.
        eksilecek=(double)yanlisCevapSayisi/4*(100/S);//yanlis cevap sayisinin goturecegi double puan degeri 100 puana gore hesaplanmistir
        dobDogruPuani=(double)dogruCevapSayisi*(100/S);//dogru yapilan soru puani
        sinavSonucu=dobDogruPuani- eksilecek;//dogru puanindan yanlıs cevap Puani cikarilir

        //Öğrencinin notu negatif bir sayı çıkarsa not 0 olarak kabul edilecektir.
        if(sinavSonucu<0)
        {
            sinavSonucu=0.0;
            continue;
        }
        //double diziye her ogrencinin hbn notu yuklendi
        HBN[i]=sinavSonucu;;

    }

}


//sinifin ortalamasini hesapla
double sinif_ortalamasi_hesapla(double HBN[ ], int N)
{
    double sinifOrtalama=0.0;
    double toplam=0.0;
    for(int i=0; i<N; i++)
    {
        toplam+=HBN[i];
    }
    sinifOrtalama=toplam/N;
    return sinifOrtalama;
}



//    bu silinecek      ogrencilerin hbn notlarini yazdirma
void hbnYazdir(double HBN[],int N)
{
    for(int i=0; i<N; i++)
    {
        //hbn notunun  virgulden sonra sadece iki degerini yazssin
        printf("\n%.2lf ", HBN[i]);

    }

}




//standart sapma hesaplanacak(verilen formul uygulandi)
double standart_sapma_hesapla(double ortalama, double HBN[ ], int N)
{
    double stdSonuc=0.0;
    double toplam=0.0;
    for(int i=0; i<N; i++)
    {
        //her ogrencinin(her i degeri için ) hbn ile ortalama farkinin karesi alinip  toplandi
        double fark=(HBN[i]-ortalama);
        toplam+=pow(fark,2);
    }
    //sdt elde etmek adina toplam sonuc ogrenci sayisina bolunerek karekoku alindi
    stdSonuc=sqrt(toplam/N);
    return stdSonuc;  //sdt sonucu donduruldu
}


//fonksiyon, tüm öğrencilerin T skorlarını tek seferde hesaplayıp double T_skoru[ ] dizisine yazacak
//Tskoru hesabi verilen isleme gore yapildi
void T_skoru_hesapla(double ortalama, double HBN[ ], int N, double std, double T_skoru[ ]){
    double fark;
    for(int i=0; i<N; i++)
    {
        fark=0.0;
        fark= HBN[i]-ortalama;
        T_skoru[i]=60+(10*(fark/std));
    }
}
//duzey bilgisi icin enum int turunden degerler tanimlama

//enum duzey { "ustun basari"=1, "Mukemmel"=2, "cok iyi"=3,"iyi"=4, "ortanin ustu"=5, "orta"=6,"zayif"=7,"kotu"=8} dzy;

//ortalamaya gore sinif duzeyini belirleme
int sinifDuzeyi(double ortalama)
{

    if (ortalama>80.0)     return 1;
    else  if(ortalama>70.0)return 2;
    else if(ortalama>62.5) return 3;
    else if(ortalama >57.5) return 4;
    else if(ortalama > 52.5)return 5;
    else if(ortalama >47.5)  return 6;
    else if(ortalama >42.5)return 7;
    else                    return 8;



}


//sinif duzeyine(1(ustun basari)...8(kotu)) e kadar numaralandirildi gore belirlenen not araliklarinda t-skora gore   harf notu elde edilir
void sinifDuzeyineGoreOgrnHarfNotu(char harfNotu[] ,int duzey,double T_skoru[],int N){
        switch(duzey)
        {
            case 1:
                if (T_skoru[N]<32)             printf("%s","FF" );
                else if(T_skoru[N]<36.99) printf("%s","FD" ) ;
                else if(T_skoru[N]<41.99) printf("%s","DD" )  ;
                 else if(T_skoru[N]<46.99) printf("%s","DC" ) ;
                else if(T_skoru[N]<51.99)printf("%s","CC" );
                else if(T_skoru[N]<56.99)printf("%s","CB") ;
                else if(T_skoru[N]<61.99) printf("%s","BB");
                else if(T_skoru[N]<66.99) printf("%s","BA") ;
                else                      printf("%s","AA");
                break;
            case 2:
                if (T_skoru[N]<34)       printf("%s","FF") ;
                else if(T_skoru[N]<38.99)  printf("%s","FD")  ;
                else if(T_skoru[N]<43.99)printf("%s","DD");
                else if(T_skoru[N]<48.99)   printf("%s","DC");
                else if(T_skoru[N]<53.99) printf("%s","CC" );
                else if(T_skoru[N]<58.99)  printf("%s","CB");
                else if(T_skoru[N]<63.99)   printf("%s","BB") ;
                else if(T_skoru[N]<68.99) printf("%s","BA") ;
                else printf("%s","AA") ;
                break;
            case 3:

                if (T_skoru[N]<36)       printf("%s","FF") ;
                else if(T_skoru[N]<40.99)printf("%s","FD") ;
                else if(T_skoru[N]<45.99)printf("%s","DD");
                else if(T_skoru[N]<50.99) printf("%s","DC");
                else if(T_skoru[N]<55.99)printf("%s","CC" );
                else if(T_skoru[N]<60.99) printf("%s","CB");
                else if(T_skoru[N]<65.99) printf("%s","BB") ;
                else if(T_skoru[N]<70.99)  printf("%s","BA") ;
                else  printf("%s","AA") ;
                break;
            case 4:

                if (T_skoru[N]<38)        printf("%s","FF") ;
                else if(T_skoru[N]<42.99)  printf("%s","FD") ;
                else if(T_skoru[N]<47.99) printf("%s","DD") ;
                else if(T_skoru[N]<52.99) printf("%s","DC") ;
                else if(T_skoru[N]<57.99) printf("%s","CC") ;
                else if(T_skoru[N]<62.99)  printf("%s","CB") ;
                else if(T_skoru[N]<67.99)  printf("%s","BB") ;
                else if(T_skoru[N]<72.99)  printf("%s","BA") ;
                else  printf("%s","AA") ;
                break;
            case 5:

                if (T_skoru[N]<40)        printf("%s","FF") ;
                else if(T_skoru[N]<44.99) printf("%s","FD") ;
                else if(T_skoru[N]<49.99)  printf("%s","DD") ;
                else if(T_skoru[N]<54.99)  printf("%s","DC") ;
                else if(T_skoru[N]<59.99)  printf("%s","CC") ;
                else if(T_skoru[N]<64.99)  printf("%s","CB") ;
                else if(T_skoru[N]<69.99)  printf("%s","BB") ;
                else if(T_skoru[N]<74.99)  printf("%s","BA") ;
                else  printf("%s","AA") ;
                break;
            case 6:

                if (T_skoru[N]<42)        printf("%s","FF") ;
                else if(T_skoru[N]<46.99)  printf("%s","FD") ;
                else if(T_skoru[N]<51.99)  printf("%s","DD") ;
                else if(T_skoru[N]<56.99)  printf("%s","DC") ;
                else if(T_skoru[N]<61.99) printf("%s","CC") ;
                else if(T_skoru[N]<66.99)  printf("%s","CB") ;
                else if(T_skoru[N]<71.99)  printf("%s","BB") ;
                else if(T_skoru[N]<76.99)  printf("%s","BA") ;
                else  printf("%s","AA") ;
                break;
            case 7:

                if (T_skoru[N]<44)        printf("%s","FF") ;
                else if(T_skoru[N]<48.99) printf("%s","FD") ;
                else if(T_skoru[N]<53.99) printf("%s","DD") ;
                else if(T_skoru[N]<58.99) printf("%s","DC") ;
                else if(T_skoru[N]<63.99) printf("%s","CC") ;
                else if(T_skoru[N]<68.99) printf("%s","CB") ;
                else if(T_skoru[N]<73.99) printf("%s","BB") ;
                else if(T_skoru[N]<78.99) printf("%s","BA") ;
                else printf("%s","AA") ;
                break;
            case 8:

                if (T_skoru[N]<46)        printf("%s","FF") ;
                else if(T_skoru[N]<50.99) printf("%s","FD") ;
                else if(T_skoru[N]<55.99) printf("%s","DD") ;
                else if(T_skoru[N]<60.99) printf("%s","DC") ;
                else if(T_skoru[N]<65.99)printf("%s","CC") ;
                else if(T_skoru[N]<70.99) printf("%s","CB") ;
                else if(T_skoru[N]<75.99)printf("%s","BB") ;
                else if(T_skoru[N]<80.99) printf("%s","BA") ;
                else printf("%s","AA") ;
                break;
            default :
                printf("%s","xxx");
        }
    }

void ogrenciNotlari(double HBN[],double T_skoru[],int N){
        printf("%03d. ogrencinin \t HBN :%.2lf \t T_skoru :%.2lf \tharf notu: ",N+1,HBN[N],T_skoru[N]);
}

int main()
{

    //degiskenler
    int S, N = 0;
    double B, D;
    double sinifOrt = 0.0;
    double stdSonuc = 0.0;
    //random uretilen sonuclarin ayni olmasini engeller, gercek rastgele degerler uretmeyi saglar
    srand(time(NULL));
    printf(" %s", "Ogrenci sayisini giriniz (max 100) : ");//klavyeden consola  istenen veri girislerini yaptirma
     scanf("%d", &N);//ogrenci sayisi girdisi
    printf(" %s", "Soru sayisini giriniz (max 100) : "); //ogrenci cevaplarýný tutacak ogrenc_cevaplari dizisi tanimalnadi
     scanf("%d", &S); //soru sayisi degeri girilecek
    //cevaplari tutacak olan cevap anathar dizisi, ogrenci_cevaplari dizisi,   HBN dizisi tanimlandi
    char cevap_anahtari[S];
    char ogrenci_cevaplari[N][100];
    double HBN[N];
    double T_skoru[N];
    char harfNotu[5];
    printf(" %s", "Bos birakma ihtimalini giriniz (0.0 ~ 1.0) :"); //bos deger birakma ihtimali klavyeden alýnacak
     scanf("%lf", &B);
    printf(" %s", "Dogru cevap verme ihtimalini giriniz( 0.0 ~ 1.0) :"); //dogru cevap verme ihtimali degeri girilmesi isteniyor
    scanf("%lf", &D);
    printf("%s", "\n\n");//iki alt satira gec

    cevap_anahtari_uret(cevap_anahtari, S);// cevap anahtarý uret metodunu calistir
    printf(" %s", "Cevap Anahtari :\n");

    //cevap anahtarý yazdir metodunu calistir
    cevap_anahtari_yazdir(cevap_anahtari, S);
    //iki alt satira gec
    printf("%s", "\n\n");

    //sinavi uygula
    sinavi_uygula(ogrenci_cevaplari, cevap_anahtari, N, S, B, D);

    //tum ogrencilerin sinava verdiği cevaplar yazdir
    for (int i = 0; i < N; i++) //ogrenci sayisi kadar donecek
    {
        printf("\n\n %d. %s", (i + 1), "ogrencinin cevaplari :");
        ogrenci_cevabini_yazdir(ogrenci_cevaplari, i, S);
    }

    //sinav sonucunu hesapla HBN sonucu
    ogrencileri_puanla( ogrenci_cevaplari,cevap_anahtari, HBN,  N,   S);
    //sinif ortalamasi sonucu donen deger tutulur
    sinifOrt=sinif_ortalamasi_hesapla(HBN,N);
    printf("%s","\n");
    //sinif ortalamasi yazdirilir
    printf("\n%s: %.2lf  ","sinif ortalamasi ", sinifOrt);
    //standart sapma  sonucu donen deger tutulur
    stdSonuc=standart_sapma_hesapla(sinifOrt,HBN,N);
    //standart sapma sonucu
    printf("  %s: %.2lf \n  ", "Standart sapma",stdSonuc);
    //sinif Duzeyi durumu
    int duzey=sinifDuzeyi(sinifOrt);

    //gelen int degerine gore ekrana sinif  duzeyi yazacak
    if (duzey==1)     printf("\n%s: %s\n","sinif duzeyi","ustun basari");
    else  if(duzey==2) printf("\n%s: %s\n","sinif duzeyi","Mukemmel");
    else if(duzey==3)  printf("\n%s: %s\n","sinif duzeyi","cok iyi");
    else if(duzey==4) printf("\n%s: %s\n","sinif duzeyi","iyi");
    else if(duzey==5)printf("\n%s: %s\n","sinif duzeyi","ortanin ustu");
    else if(duzey==6)  printf("\n%s: %s\n","sinif duzeyi","orta");
    else if(duzey==7) printf("\n%s: %s\n","sinif duzeyi","zayif");
    else if(duzey==8)    printf("\n%s: %s\n","sinif duzeyi","kotu");
    else printf("%s","notr");
  printf("%s","\n");
    //T_skoru hesaplandi
    T_skoru_hesapla(sinifOrt,HBN,N,stdSonuc,T_skoru);
    for(int i=0;i<N;i++){

        //tum ogrencilerin istenen tum notlarini llisteler( hbn tskoru,harf notu)
        ogrenciNotlari(HBN,T_skoru,i);
        //sinif düzeyine ve t skotuna gore ogrenci harf notu belirlendi harfNotu dizisine atildi
        sinifDuzeyineGoreOgrnHarfNotu(harfNotu,duzey,T_skoru,i);
        printf("\n");
    }
    return 0;
}
