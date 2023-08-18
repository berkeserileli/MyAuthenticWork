import time

class Hayvan():
    def __init__(self, aclikDurumu=0, bosaltimBilgisi="-", yavruBilgisi=0):
        self.aclikDurumu = aclikDurumu
        self.bosaltimBilgisi = bosaltimBilgisi
        self.yavruBilgisi = yavruBilgisi
    
    def besle(self, yemVer):
        self.aclikDurumu += yemVer
        return self.aclikDurumu
    
    def dogur(self, dogumYap):
        self.yavruBilgisi += dogumYap
        return self.yavruBilgisi 
    
    def bosaltimYap(self):
        if self.bosaltimBilgisi == "-":
            print("Bosaltim yapmama gerek yok!")
        elif self.bosaltimBilgisi == "+":
            self.bosaltimBilgisi = "-"
            print("Ihtiyacimi giderdim! Tesekkurler")
        else:
            print("Gecersiz isaret!")
    def __str__(self):
        return" Hayvanin aclik durumu: {}\n Hayvanin bosaltim bilgisi: {}\nHayvanin yavru bilgisi: {}\n".format(self.aclikDurumu,self.bosaltimBilgisi,self.yavruBilgisi)

class Kopek(Hayvan):
    def __init__(self, aclikDurumu, bosaltimBilgisi, yavruBilgisi, tuketilenEt=0):
        super().__init__(aclikDurumu, bosaltimBilgisi, yavruBilgisi)
        self.tuketilenEt = tuketilenEt

    def havla(self, havlamaSayisi):
        if self.aclikDurumu > 0:
            while (havlamaSayisi == 0):
                print("Havhav")
            time.sleep(1)
            havlamaSayisi -= 1
        else:
            print("Beni beslemelisin!")

class Kus(Hayvan):
    def __init__(self, aclikDurumu, bosaltimBilgisi, yavruBilgisi, uculanMesafe=0):
        super().__init__(aclikDurumu, bosaltimBilgisi, yavruBilgisi)
        self.uculanMesafe = uculanMesafe
            
    def Uc(self, uculanMesafe):
        if self.aclikDurumu > 5:
            if uculanMesafe < 1000:
                self.aclikDurumu -= 1
                print("1 km'den az uçtum")
            elif uculanMesafe > 1000:
                self.aclikDurumu -= 5
                print("1 km'den fazla uçtum!")
        else:
            print("Uçamam!")


class At(Hayvan):
    def __init__(self, aclikDurumu, bosaltimBilgisi, yavruBilgisi, kosulanMesafe=0):
        super().__init__(aclikDurumu, bosaltimBilgisi, yavruBilgisi)
        self.kosulanMesafe = kosulanMesafe
    def kos(self, kosulanMesafe):
        if self.aclikDurumu > 20:
            if kosulanMesafe < 1000:
                self.aclikDurumu -= 10
                print("1 km'den az koştum!")
            elif kosulanMesafe > 1000:
                self.aclikDurumu -= 20
                print("1 km'den fazla koştum!")
        else:
            print("Beni beslemelisin!")
    def __str__(self):
        return "Hayvanin aclik durumu: {}\n Hayvanin bosaltim bilgisi: {}\nHayvanin yavru bilgisi: {}\nKosulan Mesafe {}\n".format(self.aclikDurumu,self.bosaltimBilgisi,self.yavruBilgisi,self.kosulanMesafe)


#at1 = At(500,"-",10,1500)
#print(at1) # base de tanımladıgım str fonksiyonu ile 
#at1.kos(1500)
#print(at1)
#at1.kos(2000)
#print(at1)
#at2  = At(30,"-",10,2000)
#print(at2)
#at2.kos(3000)
#print(at2)
#at2.kos(3000)
#print(at2)

at3 = At(100,"-",10,5000)
print(at3)
at3.dogur(5)
print(at3)
at3.bosaltimYap()
print(at3)